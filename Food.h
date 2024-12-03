#ifndef FOOD_H
#define FOOD_H
#define MAX_FOOD 5

#include "GameMechs.h"
#include "objPosArrayList.h"


class Food {
private:
    objPosArrayList* foodBucket;
public:

    GameMechs* mainGameMechsRef; 
    Food(GameMechs *thisGMRef);
    ~Food();

    void generateFood(objPosArrayList* blockOff); // Generates a new food item while keeping track of the player
    objPosArrayList* getFoodPos() const;

};

#endif

