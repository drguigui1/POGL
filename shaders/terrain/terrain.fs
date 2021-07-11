# version 460 core

out vec4 FragColor;

in float fY;
in vec2 fTexCoord;
in vec3 fColor;
in vec3 fNormal;
in vec3 fFragPos;

uniform sampler2D snow;
uniform sampler2D rock;
uniform sampler2D grass;
uniform sampler2D dirt;
uniform sampler2D path;

const vec3 default_color2 = vec3(0.36, 0.31, 0.30);
const vec3 default_color3 = vec3(0.27, 0.22, 0.11);
const vec3 default_color4 = vec3(0.41, 0.34, 0.24);
const vec3 default_color5 = vec3(1.00, 1.00, 1.00);

vec3 get_color() {
    vec3 color0 = texture(path, fTexCoord).rgb;
    vec3 color1 = texture(dirt, fTexCoord).rgb;
    vec3 color2 = texture(grass, fTexCoord).rgb;
    vec3 color3 = texture(rock, fTexCoord).rgb;
    vec3 color4 = texture(snow, fTexCoord).rgb;

    color2 = mix(color2, default_color2, 0.5);
    color1 = mix(color1, color2, 0.25);
    color1 = mix(color1, color0, 0.5);

    color3 = mix(color3, default_color3, 0.5);
    color4 = mix(color4, default_color4, 0.2);

    float threshold = 0.25;
    if (fY < threshold) {
        return mix(color1, color2, 1 - (threshold - fY) * 4);
    }

    if (fY < 0.5) {
        return color2;
    }

    threshold = 0.75;
    if (fY < threshold) {
        return mix(color2, color3, 1 - (threshold - fY) * 4);
    }

    return mix(color3, color4, 1 - (1.0 - fY) * 4);
}

void main() {
    FragColor = vec4(get_color(), 1.0);
}
