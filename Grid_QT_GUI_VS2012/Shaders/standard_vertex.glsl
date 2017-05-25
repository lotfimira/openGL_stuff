#version 150

in vec3 pos;
in vec2 tex_coord;
in vec3 normal;
in vec3 tangent;
in vec3 bitangent;

out vec3 camera_vec_eye;
out vec2 tex_coord_i;
out vec3 normal_i;
out vec3 tangent_i;
out vec3 bitangent_i;

uniform mat4 mvp_mat;
uniform mat3 normal_mat;
uniform vec3 camera_pos;

void main(void)
{
    gl_Position = mvp_mat * vec4(pos, 1.0);

    // camera vector in eye space
    camera_vec_eye = normal_mat * (camera_pos - pos);

    tex_coord_i = tex_coord;

    normal_i = normal;
    tangent_i = tangent;
    bitangent_i = bitangent;
}
