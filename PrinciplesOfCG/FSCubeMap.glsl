#version 400

in vec3 texCoord;
out vec4 frag_colour;
uniform samplerCube textura;

void main()
{
	frag_colour = texture(textura, texCoord);
}
