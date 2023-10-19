#include "Map.h"
#include "Game.h"
#include "CubeFigure.h"
#include "TrianguleFigure.h"

const int  rowSize = 20;

const int colSize = 25;

const float cellWidth = 1.0f;
const float cellHeight = 10.0f;


Texture *brickTex = nullptr;
Texture *lava = nullptr;



int MapArray[rowSize][colSize] ={
    {0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0},
    {0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0},
    {0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0},
    {0,0,0,0,0,2,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,2,0,0},
    {0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0},
    {0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0},
    {0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,0},
    {0,0,0,0,0,1,1,1,1,0,0,1,0,0,0,0,2,0,0,0,0,0,2,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0}, //indice 9 row and col 11//we can say that that is the middle
    {0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0},
    {0,2,0,0,1,1,1,1,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0},
    {0,2,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0},
    {0,2,0,0,0,0,0,1,1,1,1,1,1,0,0,0,2,0,0,0,0,0,0,0,0},
    {0,2,0,0,0,0,0,0,0,0,1,1,1,1,1,0,2,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0}
    
};






Map::Map(Manager& mManager, Shader &shader)
:Entity(mManager)
{
    
    Map::shader = &shader;
    setUpTexture(shader);
    //set up map
    SetUpMapX(mManager);
    //there are no collision on rotations so this is still not being tested
    SetUpMapY(mManager);


  




}



Map::~Map()
{
    brickTex->Delete();
}



void Map::update(float deltaTime)
{

    Entity::update(deltaTime);
    
    for(auto& en : objects){
        
        TransformComponent *tra = &en->getComponent<TransformComponent>();
        //FigureComponent *fig = tra->getMainFigureComponent();
       
        
        en->getComponent<TransformComponent>().Scale(tra->getMainFigureComponent()->scaleFactorFigure);

    }

    TrianguleFigure *tra = &Entity::getComponent<TrianguleFigure>(); 

	

    tra->ScaleFigure(tra->scaleFactorFigure);






}

void Map::setUpTexture(Shader &shader)
{

    shader.use();

    brickTex = new Texture("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    
    brickTex->texUnit(shader, "tex0", 0);
    
    lava = new Texture("lave.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    
    lava->texUnit(shader, "tex0", 0);



    TrianguleFigure *tri = &Entity::addComponent<TrianguleFigure>(shader,Vector3D(15.0f,15.0f,15.0f), * lava);
	



	Entity::addComponent<TransformComponent>(Vector3D(-10.0f,0.6f,-3.0f),true,tri);
	
    
    Entity::addComponent<PhysicsComponent>();

    Entity::addGroup(Game::groupColliders);





    
}

void Map::SetUpMapX(Manager &mManager)
{

    for(int row = 0; row < rowSize; row++){
        
        int counter = 0;
        
        
        //col always 0 plus the counter
        while(counter < colSize){
                        
            //for the position
            float scaleFactorX =1.0f;
            float indexRow = static_cast<float>(row);
            const int currentCol = counter;
            float indexCol = static_cast<float>(currentCol);
            if(MapArray[row][currentCol] == 1){
                //create a new entity
                //calculate how much we need to scale
                CalculateScaleX(counter,row, counter, scaleFactorX,1);
                GenerateUnRotatedWall(indexRow,indexCol,scaleFactorX,mManager);   
            }
            counter++;
            //we always aument the counter
            
        }
    }
    
    // //first we set up a simple map
    // objects 

}

void Map::SetUpMapY(Manager &mManager)
{

    int row = 0;

    while(row < rowSize){
            
        //col always 0 plus the counter
        for(int j=0;  j < colSize; j++){
                        
            //for the position
            const int currentRow = row;
            float indexRow = static_cast<float>(currentRow);
            float indexCol = static_cast<float>(j);
            
            if(MapArray[row][j] == 2){
                float scaleFactorY =1.0f;
                //create a new entity
                //calculate how much we need to scale
                CalculateScaleY(row,j,scaleFactorY,2);
                GenerateRotatedWall(indexRow,indexCol,scaleFactorY,mManager);   
            }
            row++;
            //we always aument the counter
            
        }
    }



}

void Map::CalculateScaleX(int& counter, int row, int col,float &scaleFactorX, int checkDigit)
{
   
 
    while (MapArray[row][counter] == checkDigit)
    {
        scaleFactorX ++;
        counter ++;
    }
    
    
}

void Map::CalculateScaleY(int &row,int col,float &scaleFactorY,int checkDigit)
{
    //we want to go down now
    while (MapArray[row][col] == checkDigit)
    {
        scaleFactorY ++;
        row ++;
    }


}

void Map::GenerateUnRotatedWall(float row, float col, float scaleFactorX, Manager &mManager)
{
    auto &ent(mManager.addEntity());

    CubeFigure *cube = &ent.addComponent<CubeFigure>(*shader,Vector3D(scaleFactorX,cellHeight,1.0f), *brickTex);
                
    ent.addComponent<TransformComponent>(Vector3D(row + scaleFactorX/2.0f,cellHeight/2,col),true,cube);
                
    //add a physics component
    ent.addComponent<PhysicsComponent>();
                
    //add the tranfrom
    //add it to the group colliders
    ent.addGroup(Game::groupColliders);
            
    objects.push_back(&ent);

}

void Map::GenerateRotatedWall(float row, float col, float scaleFactorY, Manager &mManager)
{
    auto &ent(mManager.addEntity());

    CubeFigure *cube = &ent.addComponent<CubeFigure>(*shader,Vector3D(1.0f,cellHeight,scaleFactorY), *brickTex);
                
    ent.addComponent<TransformComponent>(Vector3D(row,cellHeight/2,col + scaleFactorY/2.0f),true,cube);
                
    //add a physics component
    ent.addComponent<PhysicsComponent>();
                
    //add the tranfrom
    //add it to the group colliders
    ent.addGroup(Game::groupColliders);
            
    objects.push_back(&ent);


}

