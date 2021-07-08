#version 460 core

out vec4 FragColor;

in vec3 fColor;
in vec2 fTexCoord;

uniform float vTime;

uniform float vWidth;
uniform float vHeight;

const float radius = 0.05;

float random_float(vec2 p) {
    return fract(sin(dot(p.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

float compute_circle(vec2 uv, vec2 offset) {
    vec2 iuv = floor(uv) - offset;
    float random_iuv = random_float(iuv);

    vec2 center = iuv + 0.75 + 0.5 * random_iuv;
    center.x += 0.2 * sin(random_iuv * vTime);
    center.y += 0.2 * cos(random_iuv * vTime);

    vec2 dist = uv - center;
    float r = 0.01 + 0.05 * random_iuv;

    return 1.0 - smoothstep(r, r + 0.01, dot(dist, dist));
}

vec2 compute_uv(float a, float b, float c) {
    float x = a * fTexCoord.x * vWidth / vHeight + 0.1 * sin(b * vTime);
    float y = a * fTexCoord.y - c * vTime;
    return vec2(x, y);
}

float get_color_component(vec2 uv, float coef, float power) {
    float res = 0.0;

    res += compute_circle(uv, vec2(0.0, 0.0));
    res += compute_circle(uv, vec2(0.0, 1.0));
    res += compute_circle(uv, vec2(1.0, 0.0));
    res += compute_circle(uv, vec2(1.0, 1.0));

    return pow(coef * res, power);
}

void main() {
    vec2 uv;

    uv = compute_uv(5.0, 1.0, 0.6);
    float r = get_color_component(uv, 0.15, 0.65);

    uv = compute_uv(6.0, 1.2, 0.5);
    float g = get_color_component(uv, 0.2, 0.95);

    uv = compute_uv(8.0, 1.3, 0.4);
    float b = get_color_component(uv, 0.3, 1.05);

    if (r == 0 && g == 0 && b == 0)
        discard;

    float alpha = max(r, max(g, b));

    FragColor = vec4(r, g, b, alpha);
}
