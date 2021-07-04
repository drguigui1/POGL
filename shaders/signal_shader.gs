#version 460 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

in VS_OUT {
    vec3 color;
} gs_in[];

out vec3 fColor;
out vec2 fTexCoord;

void build_house(vec4 position)
{
    fColor = gs_in[0].color;
    gl_Position = position + vec4(-1.0, -1.0, 0.0, 0.0); // 1:bottom-left
    fTexCoord = vec2(0.0, 0.0);
    EmitVertex();

    fColor = gs_in[0].color;
    gl_Position = position + vec4( 1.0, -1.0, 0.0, 0.0); // 2:bottom-right
    fTexCoord = vec2(1.0, 0.0);
    EmitVertex();

    fColor = gs_in[0].color;
    gl_Position = position + vec4(-1.0,  1.0, 0.0, 0.0); // 3:top-left
    fTexCoord = vec2(0.0, 1.0);
    EmitVertex();

    fColor = gs_in[0].color;
    gl_Position = position + vec4( 1.0,  1.0, 0.0, 0.0); // 4:top-right
    fTexCoord = vec2(1.0, 1.0);
    EmitVertex();
    EndPrimitive();
}

void main() {
    build_house(gl_in[0].gl_Position);
}
