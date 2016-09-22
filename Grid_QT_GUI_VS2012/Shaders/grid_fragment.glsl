#version 150

in vec4 in_color;
in vec2 tex_coord;

out vec4 out_color;

uniform sampler2D grid_texture;

void main(void)
{
    // for the moment ignore the texture
    out_color = in_color;
}