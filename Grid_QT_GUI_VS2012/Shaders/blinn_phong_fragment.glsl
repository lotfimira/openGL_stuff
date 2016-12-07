#version 150

const float AMBIANT = 0.3;
const float DIFFUSE = 0.8;

in vec3 normal_eye;   // normal in eye space
in vec3 half_vec_eye; // half vector in eye space

// lighting constants
uniform vec3  light_dir_eye; // light direction in eye space
uniform float shininess;
uniform float shine_intensity;

//-----------------------------------------------------------------------------
vec4 BlinnPhongLighting(vec4 input_color)
{
    //init with Ambient Term:
    vec4 frag_color = input_color * AMBIANT;

    //add Diffuse Terms
    frag_color += input_color * DIFFUSE * max(dot(normal_eye, light_dir_eye), 0.0);

    // add specular term
    //fragColor += shine_intensity * pow( max(dot(normal, half_vec_eye), 0.0), shininess );

    return frag_color;
}
