//DIFFUSE COLOR VERTEX SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

in vec3 vertex;
in vec3 normal;
in vec2 uv;

uniform	mat4 	projectionMatrix;
uniform	mat4 	viewMatrix;
uniform	mat4 	modelMatrix;

out vec3 fNormal;
out vec3 fPosition;
out vec2 fuv;

uniform float maxHeight;
uniform sampler2D heightMap;



void main( void ){
		vec4 heightData = texture(heightMap, uv);
    	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 1.f) + vec4(0,heightData.x*maxHeight,0,1);


	
		//vec4 transformedNormal = * vec4(normal, 1.0f); 
		fNormal =  mat3(modelMatrix)* normal;
		fPosition =mat3(modelMatrix)*vertex;
		fuv = uv;
}
