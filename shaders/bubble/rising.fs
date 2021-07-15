#version 460 core

out vec4 FragColor;

in vec3 fColor;
in vec2 fTexCoord;

uniform float vTime;

const float smooth_factor = 0.05f;

float random_float(vec2 p) {
    return fract(sin(dot(p.xy , vec2(12.9898f, 78.233f))) * 43758.5453f);
}

vec2 compute_uv(const float a) {
    vec2 uv = fTexCoord * 50.0f;
    vec2 x = vec2(ceil(uv.x));

    uv.y -= vTime * a * random_float(x);

    return uv;
}

vec3 compute_color(const vec2 uv, const float a, const float b) {
    float len = length(fract(uv) - a);

    float rand = random_float(ceil(uv)) * a;
    rand *= step(0.7, 1 - rand);

    float res = smoothstep(rand, rand - smooth_factor, len)
        - smoothstep(rand * b, rand * b - smooth_factor, len);

    return vec3(res);
}

void main(void) {
    vec2 uv = compute_uv(2.0f);

    vec3 res = compute_color(uv, 0.5f, 0.6f);

    if (res.r < 0.2 && res.g < 0.2 && res.b < 0.2)
        discard;

    FragColor = vec4(res, 0.5);
}
