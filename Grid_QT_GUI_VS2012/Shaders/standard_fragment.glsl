#version 150

in vec3 normal_eye;   // normal in eye space
in vec3 half_vec_eye; // half vector in eye space

out vec4 out_color;

uniform sampler2D grid_texture;
uniform vec4 color;

// lighting constants
uniform vec3  light_dir_eye; // light direction in eye space
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
        normal_eye,
        half_vec_eye,
        light_dir_eye,
        shininess,
        shine_intensity,
        out_color);
}