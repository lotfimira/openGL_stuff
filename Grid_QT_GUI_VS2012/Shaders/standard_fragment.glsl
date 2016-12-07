#version 150

out vec4 out_color;

uniform vec4 color;

// forward declaration
vec4 BlinnPhongLighting(vec4 inputColor);

void main(void)
{
    out_color = BlinnPhongLighting(color);
}