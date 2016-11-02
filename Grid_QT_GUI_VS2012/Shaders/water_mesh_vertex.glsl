#version 150

in vec3 pos;
in vec3 normal;

out vec3 normal_i;
out vec3 half_vec_i;

uniform mat4 mvp_mat;
uniform mat4 mv_mat;

void main(void)
{
    gl_Position = mvp_mat * vec4(pos, 1.0);
    normal_i = normal * mv_mat; // normal in eye space
    half_vec_i = 
}
