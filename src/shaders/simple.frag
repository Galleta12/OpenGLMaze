#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// imporver from the vert shader
in vec3 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 uv_coordinates_tex;
// impott the normal
in vec3 Normal;
// Imports the current position from the Vertex Shader
in vec3 position;

// get the texture units
uniform sampler2D tex0;
//get second texture
uniform sampler2D tex1;



// Gets the color of the light from the main function
uniform vec4 lightColor;
uniform vec4 lightColor2;
// Gets the position of the light from the main function
uniform vec3 lightPos;
//for the ligth 2
uniform vec3 lightPos2;
// Gets the position of the camera from the main function
uniform vec3 u_eye_position;

//this is fed by the main program
//specular light
uniform float u_ligh_specular;
uniform float u_ambient_light;

uniform float squareConstantA;
uniform float squareConstantB;

uniform float u_shinisses;

uniform float outerCone;
uniform float innerCone;

//the intensity of how far the ligth can reach
//smaller than one and the light can reach further

vec4 calculatePointLight(){
	
	
	//distance to the light
	//first get the v_s that is the direction from the point to the light

	vec3 v_s = lightPos - position;
	float dist = length(v_s);
	//inverse square law
	// float a = 3.0;
	// float b = 0.7;
	
	
	//more distnace
	// float a = 0.05;
	// float b = 0.01;
	float inten = 1.0f / (squareConstantA * dist * dist + squareConstantB * dist + 1.0f);
	

	// diffuse lighting
	//get the v_normal of the position
	vec3 v_normal = normalize(Normal);
	vec3 lightDirection = normalize(v_s);
	
	
	//lamber
	float lambert = max(dot(v_normal, lightDirection), 0.0f);

	//this is the ambien light
	//float u_ambient_light = 0.50f;
	
	//point where the camera will draw
	vec3 viewDirection = normalize(u_eye_position - position);

	//instead of the v_h i am using the reflection.
	vec3 reflectionDirection = reflect(-lightDirection, v_normal);
	//float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	
	
	//calculate phong 
	//apply material shininess
	float phong = pow(max(dot(viewDirection, reflectionDirection), 0.0f), u_shinisses);
	float specular = phong * u_ambient_light;

	// outputs final color
	// multiply the red value by ths specular light

	return (texture(tex0,uv_coordinates_tex)* (lambert * inten + u_ligh_specular) + texture(tex1,uv_coordinates_tex).r * specular * inten) * lightColor;
}

vec4 calculateDirectionLight(){


 
	// diffuse lighting
	vec3 normal = normalize(Normal);
	
	
	//point in the opposite direction that u want to face
	
	vec3 v_s = normalize(vec3(1.0f, 1.0f, 0.0f));
	
	
	float diffuse = max(dot(normal, v_s), 0.0f);

	vec3 viewDirection = normalize(u_eye_position - position);
	
	vec3 reflectionDirection = reflect(-v_s, normal);
	
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), u_shinisses);
	
	float specular = specAmount * u_ambient_light;

	// outputs final color
	// multiply the red value by ths specular light

	return (texture(tex0, uv_coordinates_tex) * (diffuse + u_ligh_specular) + texture(tex1, uv_coordinates_tex).r * specular) * lightColor;



}



vec4 calculateSpotLight(){




	vec3 normal = normalize(Normal);
	
	//direction
	vec3 v_s = normalize(lightPos2 - position);
	
	float lambert = max(dot(normal, v_s), 0.0f);

	
	vec3 viewDirection = normalize(u_eye_position - position);
	
	vec3 reflectionDirection = reflect(-v_s, normal);
	
	
	float phong = pow(max(dot(viewDirection, reflectionDirection), 0.0f), u_shinisses);
	float specular = phong * u_ambient_light;

	//caulculate the intensity of the position on angle to the center of the light.
	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -v_s);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	
	
	return (texture(tex0, uv_coordinates_tex) * (lambert * inten + u_ligh_specular) + texture(tex1, uv_coordinates_tex).r * specular * inten) * lightColor2;


}



vec4 calculateCombinedLight() {
    vec4 pointLightColor = calculatePointLight();
    vec4 spotLightColor = calculateSpotLight();
    
    // Combine the colors by adding them
    return pointLightColor + spotLightColor;
}


void main()
{
	
	
	//FragColor =  calculateDirectionLight();
	FragColor =   calculateCombinedLight();
}