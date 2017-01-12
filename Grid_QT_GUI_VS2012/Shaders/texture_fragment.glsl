#version 150

in vec2 tex_coord_i;

out vec4 out_color;

uniform sampler2D main_texture;

void main()
{
    out_color = texture(main_texture, tex_coord_i);
}