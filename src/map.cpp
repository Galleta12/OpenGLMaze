#include "Map.h"
#include "Game.h"
#include "CubeFigure.h"
#include "TrianguleFigure.h"

const int  rowSize = 20;

const int colSize = 25;

const float cellWidth = 5.0f;
const float cellHeight = 10.0f;
const float cellWidthZ = 5.0f;

Texture *brickTex = nullptr;
Texture *lava = nullptr;



int MapArray[rowSize][colSize] ={
    {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0},
    {0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,2,0,0,0,0,0,0,0,0},
    {0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //indice 9 row and col 11//we can say that that is the middle
    {0,2,0,0,0,0,0,1,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,2,0,0,0,0,0,1,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0},
    {0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0},
    {0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0},
    {0,0,2,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    
};




extern Manager manager;
auto &trigle1( manager.addEntity());
auto &trigle2( manager.addEntity());
Map::Map(Manager& mManager, Shader &shader)
:Entity(mManager)
{
    
    Map::shader = &shader;
    setUpTexture(shader);
    //set up map
    SetUpMapX(mManager);
    //there are no collision on rotations so this is still not being tested
    //SetUpMapY(mManager);




}



Map::~Map()
{
    brickTex->Delete();
}



void Map::update(float deltaTime)
{

    
    tmpAngle += deltaTime;
    
    
    Entity::update(deltaTime);
    
    for(auto& en : objects){
        
        TransformComponent *tra = &en->getComponent<TransformComponent>();
        //FigureComponent *fig = tra->getMainFigureComponent();
       
        const Vector3D currentPos = en->getComponent<TransformComponent>().position; 

        //en->getComponent<TransformComponent>().Traslation(Vector3D(0.0f,0.0f,0.0f));
        en->getComponent<TransformComponent>().Traslation(currentPos);
        en->getComponent<TransformComponent>().Scale(tra->getMainFigureComponent()->scaleFactorFigure);


    }

    
    
    
    TrianguleFigure *tra = &trigle1.getComponent<TrianguleFigure>(); 

	

    tra->ScaleFigure(tra->scaleFactorFigure);
    
    
    TrianguleFigure *tra2 = &trigle2.getComponent<TrianguleFigure>(); 
	
    tra2->ScaleFigure(tra2->scaleFactorFigure);
    



    tra2->RotationAboutAxisFigure(Vector3D(-1.0f,1.0f,0.0f),tmpAngle);




}

void Map::setUpTexture(Shader &shader)
{

    shader.use();

    brickTex = new Texture("wood.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    
    brickTex->texUnit(shader, "tex0", 0);
    
    lava = new Texture("lave.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    
    lava->texUnit(shader, "tex0", 0);



    TrianguleFigure *tri = &trigle1.addComponent<TrianguleFigure>(shader,Vector3D(15.0f,15.0f,15.0f), * lava);
	



	trigle1.addComponent<TransformComponent>(Vector3D(-10.0f,0.6f,-3.0f),true,tri);
	
    
    trigle1.addComponent<PhysicsComponent>();

    trigle1.addGroup(Game::groupColliders);
    


    TrianguleFigure *tr2 = &trigle2.addComponent<TrianguleFigure>(shader,Vector3D(15.0f,15.0f,15.0f), * lava);
	



	trigle2.addComponent<TransformComponent>(Vector3D(20.0f,18.0f,-3.0f),true,tr2);
	
    
   trigle2.addComponent<PhysicsComponent>();

    trigle2.addGroup(Game::groupColliders);
    
    




    
}

void Map::SetUpMapX(Manager &mManager)
{

    for(int row = 0; row < rowSize; row++){
        
  
          for(int col =0; col < colSize; col++){

            float indexRow = static_cast<float>(row);
            
            float indexCol = static_cast<float>(col);
            
            if(MapArray[row][col] == 1){
                //create a new entity
                GenerateUnRotatedWall(indexCol,indexRow,mManager);   
            }
            else if(MapArray[row][col] == 2){
                GenerateRotatedWall(indexCol,indexRow,mManager);   

            }
          
          
          }
           
            
        
    }
    
}




void Map::GenerateUnRotatedWall(float row, float col, Manager &mManager)
{
    auto &ent(mManager.addEntity());

    CubeFigure *cube = &ent.addComponent<CubeFigure>(*shader,Vector3D(cellWidth,cellHeight,1.0f), *brickTex);
                
    ent.addComponent<TransformComponent>(Vector3D(row + cellWidth/2 + 10,cellHeight/2,col+ cellWidthZ/2 + 10),true,cube,true);
                
    //add a physics component
    ent.addComponent<PhysicsComponent>();
                
    //add the tranfrom
    //add it to the group colliders
    ent.addGroup(Game::groupColliders);
            
    objects.push_back(&ent);

}

void Map::GenerateRotatedWall(float row, float col, Manager &mManager)
{
    auto &ent(mManager.addEntity());

    CubeFigure *cube = &ent.addComponent<CubeFigure>(*shader,Vector3D(1.0f,cellHeight,cellWidthZ), *brickTex);
                
    ent.addComponent<TransformComponent>(Vector3D(row + cellWidth/2- 10,cellHeight/2,col+ cellWidthZ/2+10),true,cube,true);
                
    //add a physics component
    ent.addComponent<PhysicsComponent>();
                
    //add the tranfrom
    //add it to the group colliders
    ent.addGroup(Game::groupColliders);
            
    objects.push_back(&ent);


}

