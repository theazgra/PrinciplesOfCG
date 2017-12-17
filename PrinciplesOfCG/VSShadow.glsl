#version 400

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 localPosition;

uniform mat4 depthMVP;

void main(){
    gl_Position = depthMVP * vec4(localPosition, 1);
}

