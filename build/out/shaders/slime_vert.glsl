#version 110

varying vec4 pos;

uniform mat4 MVP;

void main()
{
    pos = gl_Vertex;

    gl_Position = MVP * gl_Vertex;
}