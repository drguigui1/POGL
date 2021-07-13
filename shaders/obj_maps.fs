# version 460 core

/* Out */
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

out vec4 FragColor;

/* In */
in vec3 normal;
in vec2 texCoord;
in vec3 fragPos;

/* Uniform */
// Lights
#define MAX_LIGHTS 128
uniform int nbLights;
uniform DirectionalLight dirLight;
uniform PointLight pointLights[MAX_LIGHTS];

// Position of the user
uniform vec3 userPos;

// Object texture information
uniform vec3 ambient;
uniform sampler2D diffuse_map;
uniform sampler2D specular_map;
uniform sampler2D normal_map;

vec3 computeDirLightContribution(DirectionalLight light, vec3 normal, vec3 userPos, vec3 fragPos, vec3 diffuse, vec3 specular)
{
    vec3 norm = normalize(normal);

    // reverse light dir
    vec3 lightDir = normalize(-light.dir);

    // compute diffuse
    vec3 diff = max(dot(norm, lightDir), 0.0) * light.lightColor * diffuse.rgb;

    // compute specular
    float specularS = 0;
    float shininess = 16;
    vec3 userDir = normalize(userPos - fragPos);
    vec3 reflectDir = reflect(lightDir, norm);
    vec3 spec = specularS * pow(max(dot(userDir, reflectDir), 0.0), shininess) * light.lightColor * specular;

    float ambiantStrength = 0.1;
    vec3 ambiant = ambiantStrength * light.lightColor * ambient.rgb;

    return (ambiant + diff + spec);
}

vec3 computePLightContribution(PointLight light, vec3 normal, vec3 userPos, vec3 fragPos, vec3 diffuse, vec3 specular)
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.pos - fragPos);

    // compute the light distance
    float d = length(light.pos - fragPos);

    // compute light attenuation
    float den = (light.kc + light.kl * d + light.kq * (d * d));
    float lightAttenuation = 1.0 / den;

    // Get light color
    vec3 lColor = lightAttenuation * light.lightColor;

    // compute ambiant
    float ambiantStrength = 0.1;
    vec3 ambiant = ambiantStrength * lColor * ambient.rgb;

    // compute diffuse
    vec3 diff = max(dot(norm, lightDir), 0.0) * lColor * diffuse.rgb;

    // compute specular
    float specularS = 0;
    float shininess = 16;
    vec3 userDir = normalize(userPos - fragPos);
    vec3 reflectDir = reflect(lightDir, norm);
    vec3 spec = specularS * pow(max(dot(userDir, reflectDir), 0.0), shininess) * lColor * specular;

    return (ambiant + diff + spec);
}

void main() {
    vec3 diffuse = texture(diffuse_map, texCoord).rgb;
    vec3 specular = texture(specular_map, texCoord).rgb;

    vec3 lightRes = computeDirLightContribution(dirLight, normal, userPos, fragPos, diffuse, specular);
    for (int i = 0; i < nbLights && i < MAX_LIGHTS; ++i) {
        lightRes += computePLightContribution(pointLights[i], normal, userPos, fragPos, diffuse, specular);
    }

    FragColor = vec4(lightRes, 1.0f);
}
