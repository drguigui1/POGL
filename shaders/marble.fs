# version 460 core

#define PI 3.1415926538

struct DirectionalLight {
    vec3 dir;
    vec3 lightColor;
};

struct PointLight {
    vec3 pos;
    float kc; // constant
    float kl; // linear
    float kq; // quadratic
    vec3 lightColor;
};

out vec4 FragColor;

in vec3 normal;
in vec2 texCoord;
in vec3 fragPos;

// lights
#define MAX_LIGHTS 128
uniform int nbLights;
uniform DirectionalLight dirLight;
uniform PointLight pointLights[MAX_LIGHTS];

// position of the user
uniform vec3 userPos;

// Object texture information
uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;

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
        res = res * 2 + abs(perlin_noise(p.x * amplitude, p.y * amplitude, p.z * amplitude) * 2 - 1);
        freq *= 0.5;
    }
    return res;
}


float marble_eval(vec3 p, int scale, int depth, float freq, float amplitude) {
    return 1 - sqrt(abs(sin(fbm(p, depth, freq, amplitude) * 2 * PI)));
}

vec3 computeDirLightContribution(DirectionalLight light, vec3 normal, vec3 userPos, vec3 fragPos)
{
    vec3 norm = normalize(normal);

    // reverse light dir
    vec3 lightDir = normalize(-light.dir);

    // compute diffuse
    vec3 diff = max(dot(norm, lightDir), 0.0) * light.lightColor * diffuse.rgb;

    // compute specular
    float specularS = 0;
    float shininess = 16;
    vec3 userDir = normalize(userPos - fragPos);
    vec3 reflectDir = reflect(lightDir, norm);
    vec3 spec = specularS * pow(max(dot(userDir, reflectDir), 0.0), shininess) * light.lightColor * specular;

    float ambiantStrength = 0.1;
    vec3 ambiant = ambiantStrength * light.lightColor * ambient.rgb;

    return (ambiant + diff + spec);
}

vec3 computePLightContribution(PointLight light, vec3 normal, vec3 userPos, vec3 fragPos)
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.pos - fragPos);

    // compute the light distance
    float d = length(light.pos - fragPos);

    // compute light attenuation
    float den = (light.kc + light.kl * d + light.kq * (d * d));
    float lightAttenuation = 1.0 / den;

    // Get light color
    vec3 lColor = lightAttenuation * light.lightColor;

    // compute ambiant
    float ambiantStrength = 0.1;
    vec3 ambiant = ambiantStrength * lColor * ambient.rgb;

    // compute diffuse
    vec3 diff = max(dot(norm, lightDir), 0.0) * lColor * diffuse.rgb;

    // compute specular
    float specularS = 0;
    float shininess = 16;
    vec3 userDir = normalize(userPos - fragPos);
    vec3 reflectDir = reflect(lightDir, norm);
    vec3 spec = specularS * pow(max(dot(userDir, reflectDir), 0.0), shininess) * lColor * specular;

    return (ambiant + diff + spec);
}

void main()
{
    vec3 lightRes = computeDirLightContribution(dirLight, normal, userPos, fragPos);
    for (int i = 0; i < nbLights && i < MAX_LIGHTS; ++i) {
        lightRes += computePLightContribution(pointLights[i], normal, userPos, fragPos);
    }
    FragColor = vec4(lightRes, 1.0);

    float eval = marble_eval(fragPos.xyz, 2, 2, 1, 2);
    FragColor = vec4(mix(lightRes, vec3(1.0, 0.0, 0.0), eval), 1.0);
    FragColor = vec4(vec3(eval), 1.0);
}
