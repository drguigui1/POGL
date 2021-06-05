#version 330

out vec4 FragColor;

in vec3 outPos;

uniform float height;

void main() {
    vec3 color1 = vec3(1, 1.8, 1);
    vec3 color2 = vec3(0.226,0.5,0.615);

    float mixValue = distance(outPos.y, height);

    vec3 color = mix(color1, color2, mixValue);
    FragColor = vec4(color, 1.0);
}
