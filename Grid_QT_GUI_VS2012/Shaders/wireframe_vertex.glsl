#version 150

in vec3 pos;

uniform mat4 mvp_mat;

void main(void)
{
    gl_Position = mvp_mat * vec4(pos, 1.0);
}
