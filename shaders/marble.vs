# version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;

out vec3 normal;
out vec2 texCoord;
out vec3 fragPos;
out vec3 outColor;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

int mask = 255;
int permutation[256] = { 151,160,137,91,90,15,
    131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
    190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
    88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
    77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
    102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
    135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
    5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
    223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
    129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
    251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
    49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
    138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
};

int p[512];

void init_permutation_table() {
    for (int i = 0; i < 256 ; i++) {
        p[256 + i] = permutation[i];
        p[i] = permutation[i];
    }
}

float grad(int hash, float x, float y, float z) {
    int h = hash & 15;
    float u = h < 8 ? x : y;
    float v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

float relative_pos(float x) {
    return x - floor(x);
}

float fade(float t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

float lerp(float t, float a, float b) {
    return a + t * (b - a);
}

float perlin_noise(float x, float y, float z) {
    int x0 = int(floor(x)) & mask;
    int y0 = int(floor(y)) & mask;
    int z0 = int(floor(z)) & mask;

    x = relative_pos(x);
    y = relative_pos(y);
    z = relative_pos(z);

    float u = fade(x);
    float v = fade(y);
    float w = fade(z);

    int p00 = p[p[x0    ] + y0     ] + z0;
    int p01 = p[p[x0    ] + y0 + 1 ] + z0;
    int p10 = p[p[x0 + 1] + y0     ] + z0;
    int p11 = p[p[x0 + 1] + y0 + 1 ] + z0;

    float a, b;

    a = grad(p[p00],     x,     y,     z);
    b = grad(p[p10],     x - 1, y,     z);
    float l1 = lerp(u, a, b);

    a = grad(p[p01],     x,     y - 1, z);
    b = grad(p[p11],     x - 1, y - 1, z);
    float l2 = lerp(u, a, b);

    a = grad(p[p00 + 1], x,     y,     z - 1);
    b = grad(p[p10 + 1], x - 1, y,     z - 1);
    float l3 = lerp(u, a, b);

    a = grad(p[p01 + 1], x,     y - 1, z - 1);
    b = grad(p[p11 + 1], x - 1, y - 1, z - 1);
    float l4 = lerp(u, a, b);

    return lerp(w, lerp(v, l1, l2), lerp(v, l3, l4));
}

float fbm(vec3 p, int octaves, float freq, float amplitude) {
    float res = 0;
    for (int i = 0; i < octaves; i++) {
        res += abs(perlin_noise(p.x * amplitude, p.y * amplitude, p.z * amplitude)) * freq;
        amplitude *= 2;
        freq *= 0.5;
    }
    return res;
}

float marble_eval(vec3 p, int scale, int depth, float freq, float amplitude) {
    return 0.3 + sqrt(abs(sin(scale * p.z + fbm(p, depth, freq, amplitude) / 2 + 0.5))) * 0.5;
}

void main()
{
    init_permutation_table();

    gl_Position = projection * view * model * vec4(aPos, 1.0);
    normal = aNormal;
    texCoord = vec2(aTex.x, aTex.y);
    fragPos = vec3(model * vec4(aPos, 1.0));

    float eval = marble_eval(fragPos.xyz, 5, 5, 7, 3) * 0.7;
    eval += marble_eval(fragPos.xyz, 2, 5, 10, 5) * 0.3;

    outColor = vec3(eval);
}
