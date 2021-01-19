//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform vec3 diffuseColor;
uniform vec3 ambientColor;
uniform vec3 lightDirection;

out vec4 fragment_color;
in vec3 fNormal;

void main( void ) {
	vec3 normalizedDirection = normalize(lightDirection);
	vec3 normalizedNormal = normalize(fNormal);

	//float intensity =0.4;
	float intensity =dot(normalizedNormal, -normalizedDirection);
	//fragment_color = vec4(diffuseColor,1)*vec4(ambientColor,1);

	fragment_color = vec4(intensity,intensity,intensity,1);
}
