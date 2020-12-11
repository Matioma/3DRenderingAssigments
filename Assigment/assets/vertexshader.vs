#version 330

float PI = 3.1415926538;

in vec3 vertex;
in vec3 color;
in vec2 uv;

uniform vec2 offset;
uniform float rotation;
uniform float scale;


out vec3 fColor;
out vec2 fuv;

vec2 RotateVec2(vec2 vector, float radians){
    float x = vector.x*cos(radians) - vector.y*sin(radians);
    float y = vector.x*sin(radians) + vector.y*cos(radians);

    return vec2(x,y);
}


vec2 scaled(vec2 vector, float pScale){
    float x = vector.x* pScale;
    float y = vector.y * pScale;

    return vec2(x,y);
}

void main (void) {
    gl_Position = vec4(vertex,1) + vec4(offset,0,1);
    fColor = color;

    vec2 newUv = uv;

    newUv -= vec2(0.5,0.5);
    newUv = scaled(newUv,scale);
    newUv = RotateVec2(newUv,rotation);
    newUv += vec2(0.5,0.5);
	fuv = newUv;
}

