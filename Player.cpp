#include "Player.h"
#include "Food.h"
#include <iostream>
using namespace std;

//Player constructor: initialize player object, initial direction, and position on board 
Player::Player(GameMechs* thisGMRef, Food* foodRef)
{
    mainGameMechsRef = thisGMRef;
    mainFoodRef = foodRef; 
    myDir = STOP;

    playerPosList = new objPosArrayList();

    objPos headPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '%');

    playerPosList->insertHead(headPos);

}


//player deconstructor to deallocate Player object memory 
Player::~Player()
{
    // delete heap members here

    delete playerPosList;

}

//return the refernce to player position list 
objPosArrayList* Player::getPlayerPos() const
{
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // Updates player direction according to user input 
    char input = mainGameMechsRef->getInput();
    mainGameMechsRef->clearInput();
    switch(input) {
        case 'W':
        case 'w':
            if(myDir != UP && myDir != DOWN) {
                myDir = UP;
            }
            break;
        case 'S':
        case 's':
            if(myDir != UP && myDir != DOWN) {
                myDir = DOWN;
            }
            break;
        case 'A':
        case 'a':
            if(myDir != LEFT && myDir != RIGHT) {
                myDir = LEFT;
            }
            break;
        case 'D':
        case 'd':
            if(myDir != LEFT && myDir != RIGHT) {
                myDir = RIGHT;
            }
            break;

        case 27: // Ends the game
            mainGameMechsRef->setExitTrue();
            break;
    }
}
//Moves player in the set direction, handles wraparound condition, checks food consumption and fascilitates snake growth 
void Player::movePlayer()
{

    objPos tempPos = playerPosList->getHeadElement();

    switch (myDir)
    {
        // Switch the snake's direction ensuring only 90 degree movements
        case UP:
            tempPos.pos->y--;
            break;
        case DOWN:
            tempPos.pos->y++;
            break;
        case LEFT:
            tempPos.pos->x--;
            break;
        case RIGHT:
            tempPos.pos->x++;
            break;
        default:
            break;
    }

    // Border wraparound logic
    if(tempPos.pos->x <= 0) {
        tempPos.pos->x = mainGameMechsRef->getBoardSizeX()-2;
    } else if(tempPos.pos->x >= mainGameMechsRef->getBoardSizeX()-1) {
        tempPos.pos->x = 1;
    }

    if(tempPos.pos->y <= 0) {
        tempPos.pos->y = mainGameMechsRef->getBoardSizeY()-2;
    } else if (tempPos.pos->y >= mainGameMechsRef->getBoardSizeY()-1) {
        tempPos.pos->y = 1;
    }

    //Move snake head and update snake body 
    objPos temp = playerPosList->getHeadElement();
    temp.symbol = '~';
    playerPosList->removeHead();
    playerPosList->insertHead(temp);

    //Assess food consumption and score changes 
    if(eatenCheck() == 1) {
            playerPosList->insertHead(tempPos);
            mainGameMechsRef->incrementScore();
            mainFoodRef->generateFood(playerPosList);
        }
    else if(eatenCheck() == 2) {
            playerPosList->insertHead(tempPos);
            mainGameMechsRef->incrementScore10();
            mainFoodRef->generateFood(playerPosList);
        }
    else if(eatenCheck() == 3) {
            playerPosList->insertHead(tempPos);
            mainGameMechsRef->incrementScore50();
            mainFoodRef->generateFood(playerPosList);
            for (int i = 0; i<9; i++) {
                objPos tailEnd = playerPosList->getTailElement();
                playerPosList->insertTail(tailEnd);
            }
        } 
        else {
            playerPosList->insertHead(tempPos);
            playerPosList->removeTail();
        }
    
    //check for self-collisions 
    if(deathCheck()) {
        mainGameMechsRef->setExitTrue();
        mainGameMechsRef->setLoseFlag();
    }
}
 

// Return current player direction 
int Player::getDir() {
    return myDir;
}

//Method for checking if player has eaten different kinds of food and updates body accordingly 
int Player::eatenCheck() {
    for(int i=0; i<mainFoodRef->getFoodPos()->getSize(); i++) {

        if(playerPosList->getHeadElement().pos->x == mainFoodRef->getFoodPos()->getElement(i).pos->x && playerPosList->getHeadElement().pos->y == mainFoodRef->getFoodPos()->getElement(i).pos->y) {

            if (mainFoodRef->getFoodPos()->getElement(i).getSymbol() == 'o') {
                return 1;
            }
            else if (mainFoodRef->getFoodPos()->getElement(i).getSymbol() == '!') {
                return 2;
            }
            else if (mainFoodRef->getFoodPos()->getElement(i).getSymbol() == '$') {
                return 3;
            }
        }
    }

    return 0;
}
//Method for checking self-collisions 
bool Player::deathCheck() {

    for (int i = 1; i < playerPosList->getSize(); i++)
    {

        if(playerPosList->getHeadElement().pos->x == playerPosList->getElement(i).pos->x && playerPosList->getHeadElement().pos->y == playerPosList->getElement(i).pos->y) {
            return true;
        }
    }

    return false;
}