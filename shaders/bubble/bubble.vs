#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out VS_OUT {
    vec3 color;
} vs_out;

uniform mat4 model;
uniform mat4 view;

void main()
{
    vs_out.color = aColor;
    gl_Position = model * vec4(aPos, 1.0);
}
