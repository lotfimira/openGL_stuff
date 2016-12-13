#version 150

const float AMBIANT = 0.3;
const float DIFFUSE = 0.8;

in vec3 normal_eye;   // normal in eye space
in vec3 camera_vec_eye;

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
    vec3 normal = normalize(normal_eye);
    frag_color += input_color * DIFFUSE * max(dot(normal, light_dir_eye), 0.0);

    // add specular term
    vec3 camera_vec = normalize(camera_vec_eye);
    vec3 half_vec_eye = normalize(camera_vec + light_dir_eye); // half vector in eye space
    frag_color += shine_intensity * pow( max(dot(normal, half_vec_eye), 0.0), shininess );

    return frag_color;
}
