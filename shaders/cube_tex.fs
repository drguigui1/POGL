# version 460 core

out vec4 FragColor;

in vec3 ourColor;
in vec3 normal;
in vec2 texCoord;
in vec3 fragPos;

uniform sampler2D texture1;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);

    // compute ambiant
    float ambiantStrength = 0.1;
    vec3 ambiant = ambiantStrength * lightColor;

    // compute diffuse
    vec3 diffuse = max(dot(norm, lightDir), 0.0) * lightColor;

    vec4 res = vec4((ambiant + diffuse), 1.0) * texture(texture1, texCoord);
    FragColor = res;
}