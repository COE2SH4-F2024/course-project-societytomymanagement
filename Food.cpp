#include "Food.h"
#include "time.h"
#include <stdlib.h>

Food::Food(GameMechs *thisGMRef){

    mainGameMechsRef = thisGMRef;

   foodPos.setObjPos(-10, -10, 'o'); //initialize somewhere outside the gameboard so that it doesn't appear in the corner of the gameboard 

}

Food::~Food(){

}

void Food::generateFood(objPos blockOff){

    srand(time(NULL));

    int boardSizeX = mainGameMechsRef->getBoardSizeX();
    int boardSizeY = mainGameMechsRef->getBoardSizeY();

    bool openPos; 

    while(!openPos){
        int potentialX = rand() % (boardSizeX);
        int potentialY = rand() % (boardSizeY);
        
        if(potentialX != blockOff.pos->x && potentialY != blockOff.pos->y){
            foodPos.setObjPos(potentialX, potentialY, 'o'); 
            openPos = true; 
        }

    } 
     

    }


objPos Food::getFoodPos() const{
    return foodPos; 
} 

