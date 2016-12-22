#version 150

in vec3 pos;
in vec3 normal;

out vec3 v_normal;

void main(void)
{
  gl_Position = vec4(pos, 1.0);
  v_normal = normal;
}
