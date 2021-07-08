#version 460 core

out vec4 FragColor;

in vec3 fColor;
in vec2 fTexCoord;

uniform float vTime;

uniform float vWidth;
uniform float vHeight;

const float nb_layer = 5;

float random_float(vec2 p) {
    return fract(sin(dot(p.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

vec2 random_vec2(vec2 p) {
    float x = random_float(p);
    float y = random_float(p + x);
    return vec2(x, y);
}

vec2 random_position(vec2 uv) {
    return 0.4 * sin(random_vec2(uv) * (vTime + 100.0) * 0.6);
}

float compute_shine(vec2 uv) {
    vec2 p = random_position(floor(uv)) + 0.5;
    float dist = length(fract(uv) - p);
    return smoothstep(0.07, 0.01, dist);
}

float get_color_component(float shine, float a, float b) {
    return shine * a * abs(sin(vTime * b));
}

void main() {
    vec2 uv = fTexCoord.xy;
    uv.x *= vWidth / vHeight;

    float shine = 0.2;
    for (float i = 0; i < nb_layer; i++)
        shine += compute_shine(1.5 * uv * i + i);

    float r = get_color_component(shine, 0.9, 0.25);
    float g = get_color_component(shine, 0.4, 0.20);
    float b = get_color_component(shine, 0.7, 1.25);

    if (r == 0 && g == 0 && b == 0)
        discard;

    float alpha = max(r, max(g, b));

    FragColor = vec4(r, g, b, alpha);
}
