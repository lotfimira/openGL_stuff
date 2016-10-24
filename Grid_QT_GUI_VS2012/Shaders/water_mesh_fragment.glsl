#version 150

out vec4 out_color;

uniform sampler2D grid_texture;
uniform vec4 color;

void main(void)
{
    out_color = color;
}