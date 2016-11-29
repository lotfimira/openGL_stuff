#version 150

const float AMBIANT = 0.3;
const float DIFFUSE = 0.8;

void BlinnPhongLighting(
    in vec4 inputColor, 
    in vec3 normal,     // normalized normal in eye space
    in vec3 half_vec,   // normalized half vector in eye space
    in vec3 light_dir,  // normalized lights directions in eye space
    in float shininess,
    in float shine_intensity,
    out vec4 fragColor)
{
    //init with Ambient Term:
    fragColor = inputColor * AMBIANT;

    //add Diffuse Terms
    fragColor += inputColor * DIFFUSE * max(dot(normal,light_dir), 0.0);

    // add specular term
    //fragColor += shine_intensity * pow( max(dot(normal, half_vec), 0.0), shininess );
}
