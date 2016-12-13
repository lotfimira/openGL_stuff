#version 150

in vec3 pos;
in vec3 normal;

out vec3 normal_eye;
out vec3 camera_vec_eye;

uniform mat4 mvp_mat;
uniform mat3 normal_mat;
uniform vec3 light_dir_eye; // light direction in eye space
uniform vec3 camera_pos;

void main(void)
{
    gl_Position = mvp_mat * vec4(pos, 1.0);

    // normal in eye space
    normal_eye = normal_mat * normal;

    // camera vector in eye space
    camera_vec_eye = normal_mat * (camera_pos - pos);
}
