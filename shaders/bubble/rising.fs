#version 460 core

out vec4 FragColor;

in vec3 fColor;
in vec2 fTexCoord;

uniform float vTime;

#define SIZE 50.

const float smooth_factor = 0.05;

float rand(vec2 p) {
    return fract(sin(dot(p.xy , vec2(12.9898, 78.233))) * 43758.5453);
}

void main(void) {
    vec2 ruv = fTexCoord * SIZE;
    vec2 id = ceil(ruv);

    ruv.y -= vTime * 2. * (rand(vec2(id.x))*0.5+.5);
    ruv.y += ceil(mod(id.x, 2.))*0.3 * vTime;
    vec2 guv = fract(ruv) - 0.5;

    ruv = ceil(ruv);
    float g = length(guv);

    float v = rand(ruv) * 0.5;
    v *= step(0.7, 1 - v);

    float m = smoothstep(v, v - smooth_factor, g);
    v*=.8;
    m -= smoothstep(v, v - smooth_factor, g);

    vec3 col = vec3(m);

    if (col.r < 0.2 && col.g < 0.2 && col.b < 0.2)
        discard;

    FragColor = vec4(col, 0.5);
}
