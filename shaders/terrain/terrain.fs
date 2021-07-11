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

// lights
#define MAX_LIGHTS 128

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

uniform int nbLights;
uniform DirectionalLight dirLight;
uniform PointLight pointLights[MAX_LIGHTS];

vec3 get_diffuse_color() {
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

vec3 computeDirLightContribution(DirectionalLight light, vec3 diffuse) {
    vec3 norm = normalize(fNormal);

    // reverse light dir
    vec3 lightDir = normalize(-light.dir);

    // compute diffuse
    vec3 diff = max(dot(norm, lightDir), 0.0) * light.lightColor * diffuse.rgb;

    return diff;
}

vec3 computePLightContribution(PointLight light, vec3 diffuse) {
    vec3 norm = normalize(fNormal);
    vec3 lightDir = normalize(light.pos - fFragPos);

    // compute the light distance
    float d = length(light.pos - fFragPos);

    // compute light attenuation
    float den = (light.kc + light.kl * d + light.kq * (d * d));
    float lightAttenuation = 1.0 / den;

    // Get light color
    vec3 lColor = lightAttenuation * light.lightColor;

    // compute diffuse
    vec3 diff = max(dot(norm, lightDir), 0.0) * lColor * diffuse.rgb;

    return diff;
}

void main() {
    vec3 diffuse = get_diffuse_color();

    vec3 lightRes = computeDirLightContribution(dirLight, diffuse);
    for (int i = 0; i < nbLights && i < MAX_LIGHTS; ++i)
        lightRes += computePLightContribution(pointLights[i], diffuse);

    FragColor = vec4(lightRes, 1.0);
}
