#version 400
out vec4 frag_colour;

uniform vec3 lightPosition;
uniform vec3 lightIntensity;
uniform vec3 lightAmbient;
uniform float lightPower;

uniform vec3 cameraPosition;

in vec3 outFragPos;
in vec3 outNormalPos;

in vec2 texCoord;
uniform sampler2D _texture;

void main()
{
	vec4 color = texture(_texture, texCoord);
	//vec4 color = vec4(0.385, 0.647, 0.812, 1.0);  

	//ambient part = lightAmbient
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightIntensity;
	
	//diffuse
	vec3 norm = normalize(outNormalPos);
	vec3 lightDirection = normalize(lightPosition - outFragPos);
	float diff = max(dot(norm, lightDirection), 0.0);
	vec3 diffuse = diff * lightIntensity;

	//specular
	float specularStrength = 0.5f;
	float specularExponent = 10;
	vec3 viewDirection = normalize(cameraPosition - outFragPos);
	vec3 reflectDirection = reflect(-lightDirection, norm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), specularExponent);
	vec3 specular = specularStrength * spec * lightIntensity;

	frag_colour = vec4((ambient + diffuse + specular), 1.0) * color;
	//frag_colour = color;
}
