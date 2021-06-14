#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 outColor;

uniform mat4 iProjection;
uniform mat4 iView;
uniform mat4 iModel;

void main()
{
    gl_Position = iProjection * iView * iModel * vec4(aPos, 1.0f);
    outColor = aColor;
}
