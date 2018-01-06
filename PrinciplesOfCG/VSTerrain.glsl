#version 400

layout(location = 0) in vec3 localPosition;
layout(location = 1) in vec3 normalPosition;
layout(location = 2) in vec2 vertexUV;
layout(location = 3) in vec3 tangents;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 depthBiasMVP;

//test
uniform mat4 depthVP;

out vec3 outFragPos;
out vec3 outNormalPos;
out vec3 outTangent;

out vec2 texCoord;
out vec4 ShadowCoord;

uniform sampler2D heightMapTexture;

float calcHeight(vec4 heightMap);

void main () {

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(localPosition, 1.0);
	
    outFragPos = vec3(modelMatrix * vec4(localPosition, 1.0));
    outNormalPos = mat3(transpose(inverse(modelMatrix))) * normalPosition;
    outTangent = tangents;


	//ShadowCoord = depthBiasMVP * vec4(localPosition,1);
    ShadowCoord = depthVP * modelMatrix * vec4(localPosition, 1);
	
    texCoord = vec2(vertexUV.x, 1.0 - vertexUV.y);

	vec4 heightMap = texture(heightMapTexture, vertexUV);

	gl_Position.y += calcHeight(heightMap);
}

float calcHeight(vec4 heightMap)
{
	float height = 0;

	float red = heightMap.r / 255;
	float green = heightMap.g / 255;
	float blue = heightMap.b / 255;
	float part = 0.33;

	height = (part * red) + (part * green) + (part * blue);

	return height;
}




