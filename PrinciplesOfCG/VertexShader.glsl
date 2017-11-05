#version 400

layout(location = 0) in vec3 localPosition;
layout(location = 1) in vec3 normalPosition;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 outFragPos;
out vec3 outNormalPos;



void main () {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(localPosition, 1.0);
    outFragPos = vec3(modelMatrix * vec4(localPosition, 1.0));
    outNormalPos = mat3(transpose(inverse(modelMatrix))) * normalPosition;
}
