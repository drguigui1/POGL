# version 460 core

out vec4 FragColor;

in vec3 normal;
in vec2 texCoord;
in vec3 fragPos;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 userPos;

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;

void main()
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);

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
