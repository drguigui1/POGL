# version 460 core

out vec4 FragColor;

in vec3 ourColor;
in vec3 normal;
in vec2 texCoord;
in vec3 fragPos;

uniform sampler2D texture1;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 userPos;

void main()
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);

    // compute ambiant
    float ambiantStrength = 0.1;
    vec3 ambiant = ambiantStrength * lightColor;

    // compute diffuse
    vec3 diffuse = max(dot(norm, lightDir), 0.0) * lightColor;

    // compute specular
    float specularS = 0.5;
    float shininess = 16;
    vec3 userDir = normalize(userPos - fragPos);
    vec3 reflectDir = reflect(lightDir, norm);
    vec3 specular = specularS * pow(max(dot(userDir, reflectDir), 0.0), shininess) * lightColor;

    vec4 res = vec4((ambiant + diffuse + specular), 1.0) * texture(texture1, texCoord);
    FragColor = texture(texture1, texCoord);
}