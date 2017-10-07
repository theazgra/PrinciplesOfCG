#version 400

in vec3 vp;
out vec3 vp_color;

uniform mat4 ModelMatrix;

void main () {
    //gl_Position = vec4(vp, 1.0);
    gl_Position = ModelMatrix * vec4(vp, 1.0);

    vp_color = vp;
}
