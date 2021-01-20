//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform vec3 diffuseColor;
uniform vec3 ambientColor;
uniform vec3 lightDirection;



uniform vec3 pointLightPos;



out vec4 fragment_color;


in vec3 fNormal;
in vec3 fPosition;

void main( void ) {
	vec3 normalizedLightDirection = normalize(lightDirection);
	vec3 normalizedNormal = normalize(fNormal);

	float intensity =max(dot(normalizedNormal, -normalizedLightDirection),0);
	
	vec3 finalColor = (diffuseColor+ambientColor)*intensity;
	fragment_color = vec4(finalColor,1);


	
	//Point light section
	vec3 lightVector =  fPosition - pointLightPos;

	float lightDistance = length(lightVector);
	normalizedLightDirection =normalize(lightVector); // light direction
	intensity =max(dot(normalizedNormal, -normalizedLightDirection),0)/lightDistance;
	finalColor = (diffuseColor+ambientColor)*intensity;

	fragment_color = vec4(finalColor,1);
}
