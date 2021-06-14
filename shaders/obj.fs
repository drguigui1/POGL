# version 460 core

struct PointLight {
    vec3 pos;
    float kc; // constant
    float kl; // linear
    float kq; // quadratic
    vec3 lightColor;
};

out vec4 FragColor;

in vec3 normal;
in vec2 texCoord;
in vec3 fragPos;

uniform PointLight pointLight;
uniform vec3 userPos;

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;

void main()
{
    // compute the light distance
    float distance = length(pointLight.pos - fragPos);

    // compute light attenuation
    float den = (pointLight.kc + pointLight.kl * distance + pointLight.kq * (distance * distance));
    float lightAttenuation = 1.0 / den;

    // get light dir
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(pointLight.pos - fragPos);

    // Get light color
    vec3 lightColor = lightAttenuation * pointLight.lightColor;

    // compute ambiant
    float ambiantStrength = 0.1;
    vec3 ambiant = ambiantStrength * lightColor * ambient.rgb;

    // compute diffuse
    vec3 diff = max(dot(norm, lightDir), 0.0) * lightColor * diffuse.rgb;

    // compute specular
    float specularS = 0;
    float shininess = 16;
    vec3 userDir = normalize(userPos - fragPos);
    vec3 reflectDir = reflect(lightDir, norm);
    vec3 spec = specularS * pow(max(dot(userDir, reflectDir), 0.0), shininess) * lightColor * specular;

    vec4 res = vec4((ambiant + diff + spec), 1.0);
    FragColor = res;
}
