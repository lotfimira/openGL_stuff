#version 150

in vec3 pos;
in vec3 normal;

out vec3 normal_i;
out vec3 half_vec_i;

uniform mat4 mvp_mat;
uniform mat4 mv_mat;
uniform vec3 light_dir; // light direction in eye space

void main(void)
{
    gl_Position = mvp_mat * vec4(pos, 1.0);
    normal_i = (mv_mat * vec4(normal, 1.0)).xyz; // normal in eye space

    // camera vector in eye space
    vec3 camera_vec = normalize((mv_mat * vec4(pos, 1.0)).xyz);

    // light direction in eye space
    vec4 tempo = mv_mat * vec4(light_dir, 1.0);
    vec3 light_vec = normalize(tempo.xyz);

    // half vector in eye space
    half_vec_i = normalize(camera_vec + light_vec);
}
