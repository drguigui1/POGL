#version 460 core

out vec4 FragColor;

in vec2 fTexCoord;

uniform float vTime;

uniform float vWidth;
uniform float vHeight;

float circle(vec2 uv, float r){
    float dist = length(uv - 0.5);
    return smoothstep(r + 0.01, r, dist);
}

float generator(vec2 cell) {
    return fract(sin(cell.x * vTime * 0.125) + sin(cell.y * vTime * 0.0625));
}

void main() {
    vec2 uv = fTexCoord.xy * 10.0;
    uv.x *= vWidth / vHeight;

    vec3 color = generator(ceil(uv)) * vec3(1.0, 0.5 + 0.5 * cos(vTime),0.5 + 0.5 * sin(vTime));
    color *= circle(fract(uv), 0.4);

    float alpha = max(color.r, min(color.g, color.b));
    FragColor = vec4(color, alpha);
}
