#version 150

in vec3 normal_i;   // normal in eye space
in vec3 half_vec_i; // half vector in eye space

out vec4 out_color;

uniform sampler2D grid_texture;
uniform vec4 color;

// lighting constants
uniform vec3  light_dir; // light direction in eye space
uniform float shininess;
uniform float shine_intensity;

// forward declaration
void BlinnPhongLighting(
    in vec4 inputColor, 
    in vec3 normal,     // normalized normal in eye space
    in vec3 half_vec,   // normalized half vector in eye space
    in vec3 light_dir,  // normalized lights directions in eye space
    in float shininess,
    in float shine_intensity,
    out vec4 fragColor);

void main(void)
{
    BlinnPhongLighting( 
        color,
        normal_i,
        half_vec_i,
        light_dir,
        shininess,
        shine_intensity,
        out_color);
}