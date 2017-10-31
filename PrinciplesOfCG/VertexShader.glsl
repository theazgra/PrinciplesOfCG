#version 400

layout(location = 0) in vec3 localPosition;
layout(location = 1) in vec3 normalPosition;


out vec3 outWorldPosition;
out vec3 outWorldNormal;

out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;
out vec3 Normal_cameraspace;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;



void main () {
    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(localPosition, 1.0);

    vec3 localPosition_cameraspace = ( viewMatrix * modelMatrix * vec4(localPosition,1)).xyz;

	//EyeDirection_cameraspace = vec3(0,0,0) - localPosition_cameraspace;
    EyeDirection_cameraspace = vec3(0,0,0) - localPosition_cameraspace;

    vec3 LightPosition_cameraspace = ( viewMatrix * vec4(lightPosition,1)).xyz;
	LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;

    Normal_cameraspace = ( viewMatrix * modelMatrix * vec4(normalPosition,0)).xyz;

    outWorldPosition = (modelMatrix * vec4(localPosition, 1.0)).xyz;
    //outWorldNormal = ((modelMatrix) * vec4(normalPosition, 1.0)).xyz;
    outWorldNormal = transpose(inverse(mat3(modelMatrix)))*normalPosition;
    //worldNormal   = transpose(inverse(mat3(modelMatrix)))*normal;


}
