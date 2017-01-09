#version 150

in vec3 pos;
in vec2 tex_coord;

out vec3 camera_vec_eye;
out vec2 tex_coord_i;

uniform mat4 mvp_mat;
uniform mat3 normal_mat;
uniform vec3 camera_pos;

void main(void)
{
    gl_Position = mvp_mat * vec4(pos, 1.0);

    // camera vector in eye space
    camera_vec_eye = normal_mat * (camera_pos - pos);

    tex_coord_i = tex_coord;
}
