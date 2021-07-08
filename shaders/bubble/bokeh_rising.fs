#version 460 core

out vec4 FragColor;

in vec3 fColor;
in vec2 fTexCoord;

uniform float vTime;

uniform float vWidth;
uniform float vHeight;

const vec4 color1 = vec4(0.3, 0.8, 0.5, 1.0);
const vec4 color2 = vec4(0.0, 0.0, 1.0, 1.0);

float random_float(vec2 p) {
    return fract(sin(dot(p.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

vec2 random_vec2(vec2 p) {
    float x = random_float(p);
    float y = random_float(p + x);
    return vec2(x, y);
}

float compute_time(vec2 uv) {
    uv = floor(uv);
    float lifeTime = uv.y + random_float(uv) * 4.0;
    lifeTime += vTime - 1.5;
    lifeTime = 1.0 - lifeTime * 0.4;

    return clamp(lifeTime, 0.0, 1.0);
}

vec2 update_uv(vec2 uv) {
    vec2 random_uv = random_vec2(floor(uv));

    vec2 center = (random_uv - 0.5) * 0.6;
    center.x *= sin(vTime * random_uv.x * 5.0);

    return fract(uv) - 0.5 - center;
}

vec4 compute_circle_dist(vec2 uv, float time) {
    uv = update_uv(uv);
    float r = 0.2;
    return vec4(1.0 - smoothstep(r - 0.1 * (1.0 - time), r, length(uv)));
}

vec2 init_uv(float a, float c) {
    float x = a * fTexCoord.x * vWidth / vHeight;
    float y = a * fTexCoord.y - c * vTime;
    return vec2(x, y);
}

void main() {
    vec2 uv = init_uv(5.0, 0.8);

    float lifeTime = compute_time(uv);
    if (lifeTime == 0)
        discard;

    vec4 color = mix(color2, color1, lifeTime);
    vec4 dist = compute_circle_dist(uv, lifeTime);

    FragColor = dist * color * lifeTime;
}
