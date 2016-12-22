#version 150
layout(triangles) in;

// Three lines will be generated: 6 vertices
layout(line_strip, max_vertices=6) out;

uniform float normal_length;
uniform mat4 mvp_mat;

in vec3 v_normal[];

void main()
{
    for(int i = 0; i < gl_in.length(); i++)
    {
        vec3 pos = gl_in[i].gl_Position.xyz;
        vec3 normal = v_normal[i];

        gl_Position = mvp_mat * vec4(pos, 1.0);
        EmitVertex();

        gl_Position = mvp_mat * vec4(pos + normal * normal_length, 1.0);
        EmitVertex();

        EndPrimitive();
    }
}