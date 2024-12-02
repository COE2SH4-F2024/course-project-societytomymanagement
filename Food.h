
#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "GameMechs.h"
#include "objPosArrayList.h"

class Food
{
    private:
        objPos foodPos; //holds recently generated foodPos
    
    public:
        Food(GameMechs *thisGMRef); 
        ~Food(); 

        void generateFood(objPos blockOff); //blockoff is the position where you shouldn't generate more food, this is the position of your player
        objPos getFoodPos() const; 

        GameMechs* mainGameMechsRef;


}; 

#endif

