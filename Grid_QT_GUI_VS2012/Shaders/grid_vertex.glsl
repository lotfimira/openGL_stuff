#version 150

in vec3 pos;
in vec4 color;
in vec2 tex_coord;

out vec4 i_color;
out vec2 i_tex_coord;

uniform mat4 mvp_mat;

void main(void)
{
    gl_Position = mvp_mat * vec4(pos, 1.0);

    i_color = color;
    i_tex_coord = tex_coord;
}
