#include "GameMechs.h"
#include "MacUILib.h"
#include <iostream>

using namespace std;

//Default constructor for game mech object 
GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = 30;
    boardSizeY = 15;

}

//Additional Constructor for custom game board dimensions 
GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = boardX;
    boardSizeY = boardY;
}

//Unused deconstructor 
GameMechs::~GameMechs()
{

}

// Returns exitFlag indicateing game end 
bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

// Returns flag to indicate that the user lost 
bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

// Returns the input member field
char GameMechs::getInput()
{
    return input;
}

// Returns the score member field
int GameMechs::getScore() const
{
    return score;
}

// Increments the score by 1
void GameMechs::incrementScore()
{
    score++;
}

// Increments the score by 10
void GameMechs::incrementScore10()
{
    score+=10;
}

// Increments the score by 50
void GameMechs::incrementScore50()
{
    score+=50;
}

// Returns the x board size instance 
int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

// Returns the y board size instance 
int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


// Sets the exitFlag to true
void GameMechs::setExitTrue()
{
    exitFlag = true;
}

// Sets the loseFlag to true
void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

// Sets the input instance to some char
void GameMechs::setInput(char this_input)
{
    input = this_input;
}

// Nullify the input 
void GameMechs::clearInput()
{
    input = '\0';
}

// Collects async input from the user
void GameMechs::collectAsyncInput() {
    if(MacUILib_hasChar() != '\0') {
        input = MacUILib_getChar();
    }
}
