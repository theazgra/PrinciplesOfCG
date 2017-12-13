#version 400

layout(location = 0) in vec3 localPosition;
layout(location = 1) in vec3 normalPosition;
layout(location = 2) in vec2 vertexUV;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform mat4 depthViewMatrix;
uniform mat4 depthProjectionMatrix;

out vec3 outFragPos;
out vec3 outNormalPos;

out vec2 texCoord;
out vec4 ShadowCoord;

mat4 biasMatrix;


void main () {
	biasMatrix[0] = vec4(0.5, 0.0, 0.0, 0.5);
	biasMatrix[1] = vec4(0.0, 0.5, 0.0, 0.5);
	biasMatrix[2] = vec4(0.0, 0.0, 0.5, 0.5);
	biasMatrix[3] = vec4(0.5, 0.5, 0.5, 1.0);




    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(localPosition, 1.0);
    outFragPos = vec3(modelMatrix * vec4(localPosition, 1.0));
    outNormalPos = mat3(transpose(inverse(modelMatrix))) * normalPosition;

	//ShadowCoord = (biasMatrix * (depthProjectionMatrix * depthViewMatrix * modelMatrix)) * vec4(localPosition, 1.0); 
	ShadowCoord = biasMatrix * depthProjectionMatrix * depthViewMatrix * modelMatrix * vec4(localPosition, 1.0); 

    texCoord = vec2(vertexUV.x, 1.0 - vertexUV.y);//vertexUV;
}


