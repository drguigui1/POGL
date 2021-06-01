// https://www.shadertoy.com/view/td3XzX

#version 330

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 outColor;
out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    gl_Position = projection * view * vec4(aPos, 1.0f);
    outColor = aColor;
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
