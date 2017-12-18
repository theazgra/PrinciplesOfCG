#version 400

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 localPosition;

uniform mat4 depthMVP;
uniform mat4 depthVP;
uniform mat4 modelMatrix;

void main(){
    gl_Position = depthVP * modelMatrix * vec4(localPosition, 1);
    //gl_Position = depthMVP * vec4(localPosition, 1);
}

