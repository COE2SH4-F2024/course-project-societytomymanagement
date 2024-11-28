#include "Player.h"
#include "MacUILib.h"
#include "GameMechs.h"
#include "objPos.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.pos = new Pos(); // Proper initialization
    playerPos.pos->x = 15;
    playerPos.pos->y = 8;  
    playerPos.symbol = '*';
}


Player::~Player()
{
    // delete any heap members here
    delete playerPos.pos;
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos array list
    return playerPos;
}

void Player::updatePlayerDir()
{
        // PPA3 input processing logic
    int lastInput;

    if(mainGameMechsRef->getInput() != 0)  // if not null character
    {
        switch(mainGameMechsRef->getInput())
        {                      
            case ' ':  // exit
                mainGameMechsRef->setExitTrue();
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
    switch(newDirection)
    {
        case STOP:
            break;
        case UP:
            playerPos.pos->y-=1;
            break;
        case LEFT:
            playerPos.pos->x-=1;
            break;
        case DOWN:
            playerPos.pos->y+=1;
            break;
        case RIGHT:
            playerPos.pos->x+=1;
            break;
    }
    if (playerPos.pos->x < 1) {
        playerPos.pos->x = mainGameMechsRef->getBoardSizeX() - 2;
    } 
    else if (playerPos.pos->x > (mainGameMechsRef->getBoardSizeX() - 2)) {
        playerPos.pos->x = 1;
    }

    if (playerPos.pos->y < 1) {
        playerPos.pos->y = mainGameMechsRef->getBoardSizeY() - 2;
    } 
    else if (playerPos.pos->y > (mainGameMechsRef->getBoardSizeY() - 2)) {
        playerPos.pos->y = 1;
    }
}

// More methods to be added