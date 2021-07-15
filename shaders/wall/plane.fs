#version 330

out vec4 FragColor;

in vec2 fTexCoord;

uniform float vTime;
float gTime;

vec3 init_color() {
    vec3 factor = vec3(0.81f, 0.54f, 0.28f);
    vec3 offset = vec3(0.40f, 0.70f, 1.00f);

    return 0.4 * sin(gTime * factor) + offset;
}

vec2 compute_position(const float offset) {
    vec2 pos = vec2(sin(gTime + offset) * cos(gTime + offset));
    //vec2 pos = vec2(sin(gTime * offset) * cos(gTime + offset));
    pos.x *= sin(gTime * offset);
    pos.y *= cos(gTime * offset);
    return pos;
}

float intensity(vec2 uv, const float radius, vec2 position) {
    float dist = radius / distance(uv, position);
    return pow(dist, 2.0f);
}

vec3 compute_color(const float nb_particles, const float radius) {
    //vec2 uv = 2.25f * (fTexCoord - vec2(0.5f));
    vec2 uv = 1.25f * (fTexCoord - vec2(0.5f));

    vec3 color = init_color();

    vec3 res = vec3(0.0f);
    for (float i = 0.0f; i < 1.0f; i += 1.0f / nb_particles)
        res += color * intensity(uv, radius * i, compute_position(i));

    color = 0.5f * sin(gTime + uv.xyx + vec3(0.0f, 2.0f, 4.0f));
    return mix(color, res, 0.75f);
}

void main() {
    gTime = 2.0f * vTime;

    const float nb_particles = 100.0f;
    const float radius = 0.01f;

    vec3 color = compute_color(nb_particles, radius);
    FragColor = vec4(color, 1.0f);
}
