#version 110

varying vec4 pos;
varying vec2 tex_pos;

uniform sampler2D tex1;

uniform mat4 MVP;

void main()
{
    pos = gl_Vertex;
    tex_pos = (pos.xy + 1.0)/2.0;  

    gl_Position = MVP * gl_Vertex;
}