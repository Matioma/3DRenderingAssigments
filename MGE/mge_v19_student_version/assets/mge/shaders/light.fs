//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform vec3 diffuseColor;
uniform vec3 ambientColor;
uniform vec3 specularColor;

uniform float shininess;


uniform float intensity;


uniform vec3 cameraPosition;



//Directional
uniform vec3 lightDirection;

//Point Light
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

	//diffuse Intentity
	intensity =max(dot(normalizedNormal, -normalizedLightDirection),0)/(1+lightDistance);
	

	//Specular intensity
	
	
	//vec3 reflectedLight =normalizedLightDirection + 2*fNormal;

	vec3 reflectedLight =normalize(normalizedLightDirection + dot(-normalizedLightDirection,normalizedNormal)*2*normalizedNormal);	
	vec3 viewDirection = normalize(cameraPosition-fPosition);


	// float shininess =20;
	//vec3 specularColor = vec3(1,1,1);
	vec3 specularTerm = pow(dot(reflectedLight,viewDirection),shininess)* ambientColor *  specularColor;

	


	finalColor = (diffuseColor+ambientColor+specularTerm)*intensity ;
	fragment_color = vec4(finalColor,1);

}
