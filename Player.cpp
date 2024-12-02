#include "Player.h"
#include "MacUILib.h"
#include "GameMechs.h"
#include "objPos.h"


Player::Player(GameMechs* thisGMRef, Food* foodRef)
{
    mainGameMechsRef = thisGMRef;
    mainFoodRef = foodRef;
    myDir = STOP;

    playerPosList = new objPosArrayList();
    // more actions to be included
    //playerPos.pos = new Pos();
    // playerPos.pos->x = 15;
    // playerPos.pos->y = 8;  
    // playerPos.symbol = '*';

    objPos headPos(15, 8, '*'); 

    playerPosList->insertHead(objPos (15, 8, '*')); 
   // playerPosList->insertHead(objPos (15, 8, '*')); 
   // playerPosList->insertHead(objPos (15, 8, '*')); 


}


Player::~Player()
{
    //delete playerPos.pos;
    //do we need this here?

   delete playerPosList; 
}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos array list
    return playerPosList;
}

void Player::updatePlayerDir()
{
        // PPA3 input processing logic
    if(mainGameMechsRef->getInput() != 0)  // if not null character
    {
        MacUILib_printf("Input received: %c\n", mainGameMechsRef->getInput());
        switch(mainGameMechsRef->getInput())
        {                      
            case ' ':  // exit
                mainGameMechsRef->setExitTrue();
                myDir = STOP;
                break;
            case 'w':
                if(myDir != DOWN && myDir != UP){
                    myDir = UP;
                }
                break;
            case 'a':
                if(myDir != RIGHT && myDir != LEFT){
                    myDir = LEFT;
                }
                break;
            case 's':
                if(myDir != UP && myDir != DOWN){
                    myDir = DOWN;
                }
                break;
            case 'd':
                if(myDir != LEFT && myDir != RIGHT){
                    myDir = RIGHT;
                }
                break;

            default:
                break;
        }
        mainGameMechsRef->clearInput();
    }
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    objPos tempPos = playerPosList->getHeadElement();

    switch(myDir)
    {
        case STOP:
            break;
        case UP:
            tempPos.pos->y--;
            break;
        case LEFT:
            tempPos.pos->x--;
            break;
        case DOWN:
            tempPos.pos->y++;
            break;
        case RIGHT:
            tempPos.pos->x++; 
            break;
    }
    if (tempPos.pos->x < 1) {
        tempPos.pos->x = (mainGameMechsRef->getBoardSizeX() - 2);
    } 
    else if (tempPos.pos->x > (mainGameMechsRef->getBoardSizeX() - 2)) {
        tempPos.pos->x = 1;
    }

    if (tempPos.pos->y < 1) {
        tempPos.pos->y = (mainGameMechsRef->getBoardSizeY() - 2);
    } 
    else if (tempPos.pos->y > (mainGameMechsRef->getBoardSizeY() - 2)) {
        tempPos.pos->y = 1;
    }

    // objPos foodPos = mainFoodRef->getFoodPos(); ****THERE IS A SEGMENTATION FAULT SOMEWHERE IN HERE****

    // if(tempPos.pos->x == foodPos.pos->x && tempPos.pos->y == foodPos.pos->y){
    //     playerPosList->insertHead(tempPos);
    //     mainFoodRef->generateFood(tempPos);
    // }
    // else{
    //     playerPosList->insertHead(tempPos);
    //     playerPosList->removeTail();
    // }
    playerPosList->insertHead(tempPos);
    playerPosList->removeTail();
}

// More methods to be added