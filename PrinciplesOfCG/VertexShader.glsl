#version 400

layout(location = 0) in vec3 localPosition;
layout(location = 1) in vec3 normalPosition;
layout(location = 2) in vec2 vertexUV;
layout(location = 3) in vec3 tangents;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 depthBiasMVP;

out vec3 outFragPos;
out vec3 outNormalPos;
out vec3 outTangent;

out vec2 texCoord;
out vec4 ShadowCoord;


void main () {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(localPosition, 1.0);
    outFragPos = vec3(modelMatrix * vec4(localPosition, 1.0));
    outNormalPos = mat3(transpose(inverse(modelMatrix))) * normalPosition;
    outTangent = tangents;

	ShadowCoord = depthBiasMVP * vec4(localPosition,1);
	

    texCoord = vec2(vertexUV.x, 1.0 - vertexUV.y);//vertexUV;
}


