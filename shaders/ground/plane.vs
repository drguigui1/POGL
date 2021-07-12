# version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTex;

out vec3 color;
out vec3 normal;
out vec2 texCoord;
out vec3 fragPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    color = aColor;
    normal = aNormal;
    texCoord = vec2(aTex.x, aTex.y);
    fragPos = vec3(model * vec4(aPos, 1.0));
}