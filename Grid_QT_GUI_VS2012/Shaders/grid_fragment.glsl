#version 150

in vec4 i_color;
in vec2 i_tex_coord;

out vec4 out_color;

uniform sampler2D grid_texture;

void main(void)
{
    vec4 tex_color = texture(grid_texture, i_tex_coord);

    // for the moment ignore the texture
    out_color = tex_color * i_color;
}