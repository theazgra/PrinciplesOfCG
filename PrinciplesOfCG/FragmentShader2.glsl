#version 440
out vec4 frag_colour;


//in vec3 vp_color;
uniform sampler2D shadowMap;
in vec2 texCoord;
in vec4 ShadowCoord;

void main () {
	frag_colour =  texture(shadowMap, ShadowCoord.xy);
}


