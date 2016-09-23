#version 150

in vec4 i_color;
in vec2 i_tex_coord;

out vec4 out_color;

uniform sampler2D grid_texture;

void main(void)
{
    vec4 tex_color = texture(grid_texture, i_tex_coord);

    // for the moment ignore the texture
    out_color = mix(i_color, tex_color, vec4(0.5));
}