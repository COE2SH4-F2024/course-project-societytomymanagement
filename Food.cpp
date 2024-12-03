#include "Food.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "GameMechs.h"

using namespace std;

Food::Food(GameMechs *thisGMRef) {
    mainGameMechsRef = thisGMRef;  // Store reference to GameMechs
    foodBucket = new objPosArrayList(5);  // Create a list to store food items
    
    // Initialize 5 food items
    for(int i = 0; i < MAX_FOOD; i++) {
        if (i == 0) {
            objPos foodPos(5, i + 3, '!');  // Special item for 10 points
            foodBucket->insertHead(foodPos);
        }
        else if (i == (MAX_FOOD - 1)) {
            objPos foodPos(5, i + 3, '$');  // Special item for 50 points and growth
            foodBucket->insertHead(foodPos);
        }
        else {
            objPos foodPos(5, i + 3, 'o');  // Regular food item
            foodBucket->insertHead(foodPos);
        }
    }
}

Food::~Food() {
    delete foodBucket;  // Clean up dynamically allocated memory for food items
}

void Food::generateFood(objPosArrayList* blockOff) {
    srand(time(0));  // Seed the random number generator for food placement
    
    int xBoard = mainGameMechsRef->getBoardSizeX();  // Get board dimensions
    int yBoard = mainGameMechsRef->getBoardSizeY();

    for (int i = 0; i < MAX_FOOD; i++) {
        int repeat, potentialX, potentialY;
        
        // Generate food at random positions, ensuring it doesn't overlap with the snake or existing food
        do {
            repeat = 0;
            potentialX = (rand() % (xBoard - 3)) + 1;  // Random X position within bounds
            potentialY = (rand() % (yBoard - 3)) + 1;  // Random Y position within bounds

            // Ensure food doesn't overlap with snake body
            for (int j = 0; j < blockOff->getSize(); j++) {
                if (blockOff->getElement(j).pos->x == potentialX && blockOff->getElement(j).pos->y == potentialY) {
                    repeat = 1;
                }
            }

            // Ensure food doesn't overlap with existing food
            for (int k = 0; k < foodBucket->getSize(); k++) {
                if (potentialX == foodBucket->getElement(k).pos->x && potentialY == foodBucket->getElement(k).pos->y) {
                    repeat = 1;
                }
            }
        } while (repeat);  // Repeat until a valid position is found

        // Add food to the bucket, choosing a type based on index
        if (i == 0) {
            objPos foodPos(potentialX, potentialY, '!');
            foodBucket->removeHead();
            foodBucket->insertTail(foodPos);  // Special item (10 points)
        }
        else if (i == (MAX_FOOD - 1)) {
            objPos foodPos(potentialX, potentialY, '$');
            foodBucket->removeHead();
            foodBucket->insertTail(foodPos);  // Special item (50 points, growth)
        }
        else {
            objPos foodPos(potentialX, potentialY, 'o');
            foodBucket->removeHead();
            foodBucket->insertTail(foodPos);  // Regular food item
        }
    }
}

objPosArrayList* Food::getFoodPos() const {
    return foodBucket;  // Return a pointer to the food list
}
