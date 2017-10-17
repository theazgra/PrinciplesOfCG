#version 400
out vec4 frag_colour;


in vec3 vp_color;


void main () {
  frag_colour = vec4 (vp_color[0], vp_color[1], vp_color[2], 1.0);
}
