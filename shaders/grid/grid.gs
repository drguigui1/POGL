#version 460 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

out vec2 fTexCoord;

void build_plane(vec4 position) {
    gl_Position = position + vec4(-1.0, -1.0, 0.0, 0.0); // 1:bottom-left
    fTexCoord = vec2(0.0, 0.0);
    EmitVertex();

    gl_Position = position + vec4( 1.0, -1.0, 0.0, 0.0); // 2:bottom-right
    fTexCoord = vec2(1.0, 0.0);
    EmitVertex();

    gl_Position = position + vec4(-1.0,  1.0, 0.0, 0.0); // 3:top-left
    fTexCoord = vec2(0.0, 1.0);
    EmitVertex();

    gl_Position = position + vec4( 1.0,  1.0, 0.0, 0.0); // 4:top-right
    fTexCoord = vec2(1.0, 1.0);
    EmitVertex();
    EndPrimitive();
}

void main() {
    build_plane(gl_in[0].gl_Position);
}
