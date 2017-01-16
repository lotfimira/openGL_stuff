#version 150

in vec3 pos;
in vec2 tex_coord;

out vec3 v_normal;

uniform sampler2D normal_texture;

void main(void)
{
  gl_Position = vec4(pos, 1.0);
  vec3 mapped_normal = texture(normal_texture, tex_coord).xyz;
  v_normal = (mapped_normal - 0.5) * 2.0;
}
