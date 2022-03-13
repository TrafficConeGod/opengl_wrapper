#version 330 core

uniform sampler2D tex_sampler;

in vec2 uv;

out vec4 color;

void main() {
    color = texture(tex_sampler, uv).rgba;
}