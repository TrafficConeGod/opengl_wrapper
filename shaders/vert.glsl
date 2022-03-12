#version 330 core

layout(location = 0) in vec2 vertex_pos;
layout(location = 1) in vec2 vertex_uv;

uniform vec2 color_shift_value;

out vec2 uv;

void main() {
    gl_Position = vec4(vertex_pos.x, vertex_pos.y, 0.0, 1.0);
    uv = vertex_uv + color_shift_value;
}