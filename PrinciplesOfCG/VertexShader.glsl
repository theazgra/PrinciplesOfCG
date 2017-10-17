#version 400

layout(location = 0) in vec3 localPosition;
layout(location = 1) in vec3 normals;




//in vec3 vp;
out vec3 vp_color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main () {
    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(localPosition, 1.0);
    vp_color = localPosition;
}
