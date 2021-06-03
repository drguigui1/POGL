// https://www.shadertoy.com/view/td3XzX

#version 330

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTexCoord;

out vec3 outColor;
out vec3 outNormal;
out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    gl_Position = projection * view * vec4(aPos, 1.0f);
    outColor = aColor;
    outNormal = aNormal;
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
