#version 330

in vec3 vertex;
in vec3 color;
in vec2 uv;


in vec2 UvRotationOffset;

uniform vec2 offset;



out vec3 fColor;




out vec2 fuv;

void main (void) {
    gl_Position = vec4(vertex,1) + vec4(offset,0,1);
    fColor = color;

	fuv =uv;
}

