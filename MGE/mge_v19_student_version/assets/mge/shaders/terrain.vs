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

out vec3 testColor;

void main( void ){
		vec4 heightData = texture(heightMap, uv);
    	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 1.f) + vec4(0,heightData.x*maxHeight,0,1);



		float maxTerrainHeight = 10;


		float step = 1.0/64*2;

		float planeWidth = 2;
		float planeHeight =2;

		float heightX1 = length(texture(heightMap, uv - vec2(step,0)))*maxTerrainHeight;
		float heightX2 = length(texture(heightMap, uv + vec2(step,0)))*maxTerrainHeight;
		
		float heightY1 = length(texture(heightMap, uv - vec2(0, step)))*maxTerrainHeight;
		float heightY2 = length(texture(heightMap, uv + vec2(0, step)))*maxTerrainHeight;
		

		vec3 horizontal = vec3(2*step*planeWidth,heightX2-heightX1,0);
		vec3 vertical = vec3(0,heightY1-heightY2,2*step*planeHeight);                          


		vec3 newNormal = cross(horizontal,-vertical);

		
		//fNormal =  mat3(modelMatrix)* newNormal;
		
		
		//fNormal = mat3(modelMatrix)* normal;
		fNormal = mat3(modelMatrix)*newNormal;


		//vec3 demo = 
		testColor =normalize(newNormal);


		fPosition =vertex;
		fuv = uv;
}
