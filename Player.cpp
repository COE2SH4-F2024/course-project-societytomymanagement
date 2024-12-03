#include "Player.h"
#include "Food.h"
#include <iostream>
using namespace std;

Player::Player(GameMechs* thisGMRef, Food* foodRef)
{
    mainGameMechsRef = thisGMRef;
    mainFoodRef = foodRef; 
    myDir = STOP;

    playerPosList = new objPosArrayList();

    objPos headPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '%');

    playerPosList->insertHead(headPos);

}


Player::~Player()
{
    // delete any heap members here
    // No keyword new
    delete playerPosList;

}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos array list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // Gets input from the player and proccesses the movement accordingly
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

void Player::movePlayer()
{
    // Get the head element of the snake
    objPos tempPos = playerPosList->getHeadElement();

    switch (myDir)
    {
        // The below cases change either the x or y position depending on direction
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

    
    objPos temp = playerPosList->getHeadElement();
    temp.symbol = '~';
    playerPosList->removeHead();
    playerPosList->insertHead(temp);

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
    
    if(deathCheck()) {
        mainGameMechsRef->setExitTrue();
        mainGameMechsRef->setLoseFlag();
    }
}
 

// More methods to be added
int Player::getDir() {
    return myDir;
}

//this method allows us to define the conditions on which a snake has consumed food on the board.
int Player::eatenCheck() {
    for(int i=0; i<mainFoodRef->getFoodPos()->getSize(); i++) {
        //if the head of the snake is at an equivalent position to a food object.
        if(playerPosList->getHeadElement().pos->x == mainFoodRef->getFoodPos()->getElement(i).pos->x && playerPosList->getHeadElement().pos->y == mainFoodRef->getFoodPos()->getElement(i).pos->y) {
            //What type of food object are we colliding with? We change our return values depending on this, as it will allow us to adjust our
            //score increments and other snake properties inside movePlayer().
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

bool Player::deathCheck() {

    for (int i = 1; i < playerPosList->getSize(); i++)
    {

        if(playerPosList->getHeadElement().pos->x == playerPosList->getElement(i).pos->x && playerPosList->getHeadElement().pos->y == playerPosList->getElement(i).pos->y) {
            return true;
        }
    }

    return false;
}