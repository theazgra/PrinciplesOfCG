#version 400
out vec4 frag_colour;


in vec3 outWorldPosition;
in vec3 outWorldNormal;

in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

uniform vec3 lightPosition;
uniform vec3 lightIntensity;
uniform vec3 lightAmbient;
uniform float lightPower;


void main () {
  vec4 color = vec4(0.385, 0.647, 0.812, 1.0);  
  
  // Distance to the light
	float distance = length(lightPosition - outWorldNormal);

  // Normal of the computed fragment, in camera space
	vec3 n = normalize( Normal_cameraspace );
	// Direction of the light (from the fragment to the light)
	vec3 l = normalize( LightDirection_cameraspace );

  // Cosine of the angle between the normal and the light direction, 
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendicular to the triangle -> 0
	//  - light is behind the triangle -> 0
	float cosTheta = clamp( dot( n,l ), 0,1 );

  // Eye vector (towards the camera)
	vec3 E = normalize(EyeDirection_cameraspace);
	// Direction in which the triangle reflects the light
	vec3 R = reflect(-l,n);

  // Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	float cosAlpha = clamp( dot( E,R ), 0,1 );
  //float LightPower = 55.0f;
  frag_colour = 
		// Ambient : simulates indirect lighting
		lightAmbient +
		// Diffuse : "color" of the object
		color * lightIntensity * lightPower * cosTheta / (distance*distance) +
		// Specular : reflective highlight, like a mirror
		color * lightIntensity * lightPower * pow(cosAlpha,10) / (distance*distance);
}
