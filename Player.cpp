#include "Player.h"
#include "MacUILib.h"
#include "GameMechs.h"
#include "objPos.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.pos->x = 15;
    playerPos.pos->y -= 8;  
    playerPos.symbol = '*';
    
    playerPos.pos = new Pos;
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
                if(newDirection != DOWN && newDirection != UP){
                    newDirection = UP;
                }
                break;
            case 'a':
                if(newDirection != RIGHT && newDirection != LEFT){
                    newDirection = LEFT;
                }
                break;
            case 's':
                if(newDirection != UP && newDirection != DOWN){
                    newDirection = DOWN;
                }
                break;
            case 'd':
                if(newDirection != LEFT && newDirection != RIGHT){
                    newDirection = RIGHT;
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
    if(playerPos.pos->x < 1){
        playerPos.pos->x = mainGameMechsRef->getBoardSizeY() - 2;
    }
    else if (playerPos.pos->x > (mainGameMechsRef->getBoardSizeY()-2)){
        playerPos.pos->x = 1;
    }

    if(playerPos.pos->y < 1){
        playerPos.pos->y = mainGameMechsRef->getBoardSizeX() - 2;
    }
    else if (playerPos.pos->y > (mainGameMechsRef->getBoardSizeX()-2)){
        playerPos.pos->y = 1;
    }
}

// More methods to be added