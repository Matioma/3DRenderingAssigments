//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform int lightType;



// uniform vec3 diffuseColor;
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

uniform sampler2D splatMap;
uniform sampler2D diffuseTexture1;
uniform sampler2D diffuseTexture2;
uniform sampler2D diffuseTexture3;
uniform sampler2D diffuseTexture4;

out vec4 fragment_color;


in vec3 fNormal;
in vec3 fPosition;
in vec2 fuv;


in vec3 testColor;


void main( void ) {
	vec4 textureSample= texture(diffuseTexture3, fuv);
	vec4 splatMapSample = texture(splatMap,fuv);
	
	float lengthSample = length(splatMapSample); 

	vec4 diff1Sample = texture(diffuseTexture1, fuv);
	vec4 diff2Sample = texture(diffuseTexture2, fuv);
	vec4 diff3Sample = texture(diffuseTexture3, fuv);
	vec4 diff4Sample = texture(diffuseTexture4, fuv);

	//vec4 framentTexture = splatMapSample;


	vec4 framentTexture = vec4(splatMapSample.r*diff1Sample) + 
						vec4(splatMapSample.g*diff2Sample) + 
						vec4(splatMapSample.b*diff3Sample) +
						vec4(splatMapSample.a* diff4Sample);


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
		vec3 normalizedLightDirection = normalize(lightDirection);


		intensity =max(dot(normalizedNormal, -normalizedLightDirection),0);
		//intensity=0;
	}else if(lightType==1){
		//Point Light Intensity
		//intensity =max(dot(normalizedNormal, -normalizedLightDirection),0)/(1+lightDistance);
	}else if(lightType==2){
		//Spot Light
		vec3 FragmentToLight = normalize(lightVector);
		float angleCos = dot(FragmentToLight,lightDirection);

		float FallOfEdge = cos(radians((coneAngle-coneFallOffAngle)/2)); //Cos at the edge of most bright part
		float DarkEdge =cos(radians(coneAngle/2)); //Cos at the edge of the light cone

		float coneintensity = clamp( (angleCos-DarkEdge)/(FallOfEdge -DarkEdge),0,1);//

		if(cos(radians(coneAngle/2))<angleCos){
			//intensity =max(dot(normalizedNormal, -normalizedLightDirection),0)/(1+lightDistance)*coneintensity;
		}
	}


	//Specular intensity
	vec3 reflectedLight =normalize(normalizedLightDirection + dot(-normalizedLightDirection,normalizedNormal)*2*normalizedNormal);	
	vec3 viewDirection = normalize(cameraPosition-fPosition);

	vec3 specularTerm = pow(dot(reflectedLight,viewDirection),shininess)* ambientColor *  specularColor;

	



	vec4 finalColor = (framentTexture)*(intensity);// (framentTexture+ambientColor+specularTerm)*intensity ;
	//fragment_color = vec4(framentTexture,1);
	
	fragment_color = vec4(finalColor.xyz,1);
	
	//fragment_color = vec4(testColor,1);


}
