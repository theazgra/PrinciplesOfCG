#version 400

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;


uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(){
    //gl_Position =  depthMVP * vec4(vertexPosition_modelspace,1);
    gl_Position =  projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPosition_modelspace,1);
}

