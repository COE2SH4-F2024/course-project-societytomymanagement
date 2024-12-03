#include "Food.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "GameMechs.h"

using namespace std;

Food::Food(GameMechs *thisGMRef) {

    mainGameMechsRef = thisGMRef; 
    // Creates a new arraylist to hold food items
    foodBucket = new objPosArrayList(5);
    // Creates 5 filler food items
    for(int i=0; i<MAX_FOOD; i++) {
        if (i == 0){
            //This object insantiates once initially as the 10 point special object.
            objPos foodPos(5, i+3, '!');
            foodBucket->insertHead(foodPos);
        }
        else if (i == (MAX_FOOD-1)){
            //This is the 50 point special object that increases length by 10.
            objPos foodPos(5, i+3, '$');
            foodBucket->insertHead(foodPos);
        }
        else{
            //This is the normal food object.
            objPos foodPos(5, i+3, 'o');
            foodBucket->insertHead(foodPos);
        }
    }
}

Food::~Food() {
    // Deletes the arraylist heap member
    delete foodBucket;
}

void Food::generateFood(objPosArrayList* blockOff) {
    srand(time(0)); // Seeds the random number generator
    int xBoard = mainGameMechsRef->getBoardSizeX(); 
    int yBoard = mainGameMechsRef->getBoardSizeY(); 
    for(int i=0; i<MAX_FOOD; i++) {
        int repeat, potentialX, potentialY;
        do {
            repeat = 0;
            potentialX = (rand() % (xBoard-3)) + 1; // Creates a random number from [1, xRange-2]
            potentialY = (rand() % (yBoard-3)) + 1; // Creates a random number from [1, yRange-2]
            for(int j=0; j<blockOff->getSize(); j++) {
                if(blockOff->getElement(j).pos->x == potentialX && blockOff->getElement(j).pos->y == potentialY) {
                    // If the coordinates match the position of any body of the snake, restart the generation
                    repeat = 1;
                }
            }

            for(int k=0; k<foodBucket->getSize(); k++) {
                if(potentialX == foodBucket->getElement(k).pos->x && potentialY == foodBucket->getElement(k).pos->y) {
                    // If the new food item matches the coordinates of a previous one, restart the generation
                    repeat = 1;
                }
            }
            // Stop this do-while loop once the new coordinates of the food item are different and the above if statmenents have passed

        } while(potentialX == foodBucket->getElement(i).pos->x && potentialY == foodBucket->getElement(i).pos->y || repeat);

        // Depending on the loop iteration, add either a normal food object or one of the special ones
        if (i == 0){
            objPos foodPos(potentialX, potentialY, '!');
            foodBucket->removeHead();
            foodBucket->insertTail(foodPos);
        }
        else if (i == (MAX_FOOD-1)){
            objPos foodPos(potentialX, potentialY, '$');
            foodBucket->removeHead();
            foodBucket->insertTail(foodPos);
        }
        else{
            objPos foodPos(potentialX, potentialY, 'o');
            foodBucket->removeHead();
            foodBucket->insertTail(foodPos);
        }
    }
}

objPosArrayList* Food::getFoodPos() const {
    // Returns a pointer to the foodBucket
    return foodBucket;
}