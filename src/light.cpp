#include "Light.h"
GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};


LightSource::LightSource(Manager &mManager, Shader &shader, Vector3D position ,Vector3D color, float a, int lighNum)
:Entity(mManager), mColor(color),mPosition(position),lightShader(shader),rgba(a), numofLight(lighNum)
{

    setUpArrayBuffer();
    mModelMatrix = std::make_unique<ModelMatrix>();
	mModelMatrix->loadIdentity();
	mModelMatrix->traslation(position);
    
    lightShader.use();
    

	lightShader.set_model_matrix(mModelMatrix->getMatrix());
	//this will vary if if is light 2 or light for1
	//for the light 2 this is the function
	
	if(numofLight == 2){
		
		lightShader.set_light_color2(color.x, color.y, color.z, a);

	}else{
		//for the light 1 this is the function
		lightShader.set_light_color(color.x, color.y, color.z, a);

	}


	Entity::addGroup(Game::groupLights);

}


void LightSource::update(float deltaTime)
{

}

void LightSource::draw(Shader &shader)
{
	
    //shader.use();
	//in this case we want to global shader
	//to set up the colors
	


    
    lightShader.use();
    

    lightVAO->Bind();
    mModelMatrix->loadIdentity();
    mModelMatrix->pushMatrix();
	mModelMatrix->traslation(mPosition);

	//modelmatrix of light
    lightShader.set_model_matrix(mModelMatrix->getMatrix());
	if(numofLight==1){

		lightShader.set_light_color(mColor.x, mColor.y, mColor.z, rgba);
		
	}else{
		lightShader.set_light_color2(mColor.x, mColor.y, mColor.z, rgba);

	}

    glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
	mModelMatrix->popMatrix();
}

void LightSource::setUpArrayBuffer()
{

    lightShader.use();
    lightVAO = new VAO;
	lightVAO->Bind();
    lightVAO = new VAO;
	lightVAO->Bind();
	// Generates Vertex Buffer Object and links it to vertices
	lightVBO = new VBO(lightVertices, sizeof(lightVertices));
	// Generates Element Buffer Object and links it to indices
	lightEBO = new EBO(lightIndices, sizeof(lightIndices));
	// Links VBO attributes such as coordinates and colors to VAO
	lightVAO->LinkAttrib(*lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	// Unbind all to prevent accidentally modifying them
	lightVAO->Unbind();
	lightVBO->Unbind();
	lightEBO->Unbind();

}
