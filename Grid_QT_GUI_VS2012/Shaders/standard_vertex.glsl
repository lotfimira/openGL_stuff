#version 150

in vec3 pos;
in vec3 normal;

out vec3 normal_eye;
out vec3 half_vec_eye;

uniform mat4 mvp_mat;
uniform mat4 mv_mat;
uniform vec3 light_dir_eye; // light direction in eye space

void main(void)
{
    gl_Position = mvp_mat * vec4(pos, 1.0);

    // normal in eye space
    normal_eye = normalize((mv_mat * vec4(normal, 1.0)).xyz);

    // camera vector in eye space
    vec3 camera_vec_eye = normalize((mv_mat * vec4(pos, 1.0)).xyz);

    // half vector in eye space
    half_vec_eye = normalize(camera_vec_eye + light_dir_eye);
}
