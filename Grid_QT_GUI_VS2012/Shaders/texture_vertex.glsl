#version 150

in vec3 pos;
in vec2 tex_coord;

out vec2 tex_coord_i;

uniform mat4 mvp_mat;

void main(void)
{
    gl_Position = mvp_mat * vec4(pos, 1.0);

    tex_coord_i = tex_coord;
}
