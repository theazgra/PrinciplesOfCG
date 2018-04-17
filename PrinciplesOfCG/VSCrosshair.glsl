#version 400
layout(location = 0) in vec3 localPosition;

uniform mat4 modelMatrix;

void main () 
{
    gl_Position =  modelMatrix * vec4(localPosition, 1.0); 
}