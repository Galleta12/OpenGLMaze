#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Imports the color from the Vertex Shader
in vec3 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the current position from the Vertex Shader
in vec3 crntPos;

// Gets the Texture Unit from the main function
uniform sampler2D tex0;
//get second texture
uniform sampler2D tex1;

// Gets the color of the light from the main function
uniform vec4 lightColor;
// Gets the position of the light from the main function
uniform vec3 lightPos;
// Gets the position of the camera from the main function
uniform vec3 u_eye_position;




//the intensity of how far the ligth can reach
//smaller than one if the light reach far

vec4 calculatePointLight(){
	
	
	//distance to the light
	vec3 lightVec = lightPos - crntPos;
	float dist = length(lightVec);
	//inverse square law
	float a = 3.0;
	float b = 0.7;
	
	//more distnace
	// float a = 0.05;
	// float b = 0.01;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);
	
	
	// ambient lighting
	float ambient = 0.20f;
 
	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(u_eye_position - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	//float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	// outputs final color
	// multiply the red value by ths specular light

	return (texture(tex0,texCoord)* (diffuse * inten + ambient) + texture(tex1,texCoord).r * specular * inten) * lightColor;
}

vec4 calculateDirectionLight(){

	// ambient lighting
	float ambient = 0.20f;
 
	// diffuse lighting
	vec3 normal = normalize(Normal);
	
	
	//point in the opposite direction that u want to face
	//vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	
	vec3 lightDirection = normalize(u_eye_position);
	
	
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(u_eye_position - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	//float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	// outputs final color
	// multiply the red value by ths specular light

	return (texture(tex0, texCoord) * (diffuse + ambient) + texture(tex1, texCoord).r * specular) * lightColor;



}



vec4 calculateSpotLight(){

	// controls how big the area that is lit up is
	float outerCone = 0.90f;
	float innerCone = 0.95f;

	// ambient lighting
	float ambient = 0.20f;


	// diffuse lighting
	vec3 normal = normalize(Normal);
	
	//vec3 lightDirection = normalize(lightPos - crntPos);
	vec3 lightDirection = normalize(lightPos - crntPos);
	
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(u_eye_position - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	// calculates the intensity of the crntPos based on its angle to the center of the light cone
	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	
	
	return (texture(tex0, texCoord) * (diffuse * inten + ambient) + texture(tex1, texCoord).r * specular * inten) * lightColor;


}

vec4 calculateCombinedLight() {
    vec4 pointLightColor = calculateDirectionLight();
    vec4 directionLightColor = calculateSpotLight();
    
    // Combine the colors by adding them
    return pointLightColor + directionLightColor;
}


void main()
{
	

	
	//FragColor = calculatePointLight();
	//if we want light to came above it should point up
	//FragColor =  calculateDirectionLight();
	FragColor =   calculateCombinedLight();
}