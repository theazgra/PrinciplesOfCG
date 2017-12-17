#version 400
//#define NUMBER_OF_LIGHTS 10
const uint POINT_LIGHT = 1;
const uint DIRECTIONAL_LIGHT = 2;
const uint SPOT_LIGHT = 3;

struct Light
{
	uint lightType;

	vec3 position;
	vec3 direction;

	float cutOff;
	float outerCutOff;

	vec3 lightColor;
	float ambientStrength;
	float specularStrength;

	float constant;
	float linear;
	float quadratic;

	float power;
};


uniform int lightCount;

uniform vec3 cameraPosition;

in vec3 outFragPos;
in vec3 outNormalPos;

in vec2 texCoord;
in vec4 ShadowCoord;

uniform sampler2D textura;
uniform sampler2D shadowMap;

uniform Light lights[20];

out vec4 frag_colour;

vec3 CalcPointLight(Light light, vec3 normal, vec3 viewDirection, vec3 fragPosition);
vec3 CalcDirectionalLight(Light light, vec3 normal, vec3 viewDirection);
vec3 CalcSpotLight(Light light, vec3 normal, vec3 viewDirection, vec3 fragPosition);

void main()
{

	float visibility = 1.0;

	float distanceFromLight = texture(shadowMap, ShadowCoord.xy).z;
	float distanceFromCamera = ShadowCoord.z;
	bool shadow = false;
	if (distanceFromLight < distanceFromCamera){
		visibility = 0.5;
		shadow = true;
	}

	vec3 norm = normalize(outNormalPos);
	vec3 viewDirection = normalize(cameraPosition - outFragPos);

	//textura je cislo texturovaci jednotky
	vec4 color = texture(textura, texCoord);	

	vec3 result = vec3(0, 0, 0);

	for (int i = 0; i < lightCount; i++)
	{
		switch(lights[i].lightType)
		{
			case POINT_LIGHT:
				result += CalcPointLight(lights[i], norm, viewDirection, outFragPos);
				break;
			case DIRECTIONAL_LIGHT:
				result += CalcDirectionalLight(lights[i], norm, viewDirection);
				break;
			case SPOT_LIGHT:
				result += CalcSpotLight(lights[i], norm, viewDirection, outFragPos);
				break;
		}
			
	}
	
	frag_colour = (vec4(result, 1.0) * color) * visibility;
	if (shadow)
		frag_colour = vec4(0.0, 1.0, 0.0, 1.0);

}

vec3 CalcDirectionalLight(Light light, vec3 normal, vec3 viewDirection)
{
	vec3 lightDir = normalize(-light.direction);
	
	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDirection = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 20.0f);

	vec3 ambient = 		light.lightColor * light.ambientStrength;
	vec3 diffuse = 		diff * light.lightColor;
	vec3 specular = 	light.specularStrength * spec * light.lightColor;

	return (ambient + diffuse + specular) * light.power;
}

vec3 CalcPointLight(Light light, vec3 normal, vec3 viewDirection, vec3 fragPosition)
{
	vec3 lightDir = normalize(light.position - fragPosition);
	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDirection = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 20);

	float distance = length(light.position - fragPosition);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	vec3 ambient = 		light.ambientStrength * light.lightColor;
	vec3 diffuse = 		light.lightColor * diff;
	vec3 specular = 	light.specularStrength * spec * light.lightColor;

	ambient 	*= attenuation;
	diffuse 	*= attenuation;
	specular 	*= attenuation;

	return (ambient + diffuse + specular) * light.power;
}
vec3 CalcSpotLight(Light light, vec3 normal, vec3 viewDirection, vec3 fragPosition)
{
	vec3 lightDir = normalize(light.position - fragPosition);
	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDirection = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 20);

	float distance = length(light.position - fragPosition);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	vec3 ambient = 		light.ambientStrength * light.lightColor;
	vec3 diffuse = 		light.lightColor * diff;
	vec3 specular = 	light.specularStrength * spec * light.lightColor;

	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;

	return (ambient + diffuse + specular) * light.power;
}
