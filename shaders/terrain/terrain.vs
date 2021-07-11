# version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

out vec2 fTexCoord;
out vec3 fColor;
out vec3 fNormal;
out vec3 fFragPos;
out float fY;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform float amplitude;
uniform sampler2D heightmap;

vec3 get_normal() {
    const ivec3 offset = ivec3(-1, 0, 1);
    const float s01 = textureOffset(heightmap, aTex, offset.xy).x;
    const float s21 = textureOffset(heightmap, aTex, offset.zy).x;
    const float s10 = textureOffset(heightmap, aTex, offset.yx).x;
    const float s12 = textureOffset(heightmap, aTex, offset.yz).x;

    const vec2 size = vec2(1.0, 0.0);
    const vec3 va = normalize(vec3(size.xy, s21 - s01));
    const vec3 vb = normalize(vec3(size.yx, s12 - s10));

    return cross(va, vb);
}

void main() {
    float y = texture(heightmap, aTex).r;
    //if (y < 0.1) y = 0;

    fY = y;

    y = (y - 1) * amplitude;

    gl_Position = projection * view * model * vec4(aPos.x, y, aPos.z, 1.0);

    fTexCoord = aTex;
    fColor = vec3(texture(heightmap, aTex));
    fNormal = get_normal();
    fFragPos = vec3(model * vec4(aPos.x, y, aPos.z, 1.0));
}
