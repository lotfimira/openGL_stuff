#version 150

in vec3 in_pos;
in vec4 in_color;
in vec2 in_tex_coord;

out vec4 out_color;
out vec2 out_tex_coord;

uniform mat4 mvp_mat;

void main(void)
{
    gl_Position = mvp_mat * vec4(in_pos, 1.0);

    out_color = in_color;
    out_tex_coord = in_tex_coord;
}
