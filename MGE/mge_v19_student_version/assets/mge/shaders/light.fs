//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform int lightType;



uniform vec3 diffuseColor;
uniform vec3 ambientColor;



//SPecular data
uniform vec3 specularColor;
uniform float shininess;
uniform vec3 cameraPosition;


//Spot Light
uniform float coneAngle;
uniform float coneFallOffAngle;


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

	float intensity;
	
	//vec3 finalColor = (diffuseColor+ambientColor)*intensity;
	//fragment_color = vec4(finalColor,1);


	//Point light section
	vec3 lightVector =  fPosition - pointLightPos;
	float lightDistance = length(lightVector);
	normalizedLightDirection =normalize(lightVector); // light direction


	//lightType =1;
	if(lightType ==0){
		intensity =max(dot(normalizedNormal, -normalizedLightDirection),0);
	}else if(lightType==1){
		//Point Light Intensity
		intensity =max(dot(normalizedNormal, -normalizedLightDirection),0)/(1+lightDistance);
	}else if(lightType==2){
		//Spot Light
		
		vec3 FragmentToLight = normalize(lightVector);

		float angleCos = dot(FragmentToLight,lightDirection);



		float FallOfEdge = cos(radians((coneAngle-coneFallOffAngle)/2)); //Cos at the edge of most bright part
		float DarkEdge =cos(radians(coneAngle/2)); //Cos at the edge of the light cone

		float coneintensity = clamp( (angleCos-DarkEdge)/(FallOfEdge -DarkEdge),0,1);//



		if(cos(radians(coneAngle/2))<angleCos){
			intensity =max(dot(normalizedNormal, -normalizedLightDirection),0)/(1+lightDistance)*coneintensity;
		}
	}


	//Specular intensity
	vec3 reflectedLight =normalize(normalizedLightDirection + dot(-normalizedLightDirection,normalizedNormal)*2*normalizedNormal);	
	vec3 viewDirection = normalize(cameraPosition-fPosition);

	vec3 specularTerm = pow(dot(reflectedLight,viewDirection),shininess)* ambientColor *  specularColor;

	
	vec3 finalColor = (diffuseColor+ambientColor+specularTerm)*intensity ;
	fragment_color = vec4(finalColor,1);

	
	

	
	


	

}
