#include "GameMechs.h"
#include "MacUILib.h"
#include "Player.h"
#include "objPos.h"
#include "objPosArrayList.h"

GameMechs::GameMechs()
{
    input = NULL;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = 10;
    boardSizeY = 20;

    gameData = new int*[boardSizeX];

    for(int i = 0; i < boardSizeX; i++)
	{
		gameData[i] = new int[boardSizeY];
	}

	for(int i = 0; i < boardSizeX; i++)
		for(int j = 0; j < boardSizeY; j++)
			gameData[i][j] = 0;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    if(boardX <= 0){
        boardX = 10;
    }
    else{
        boardSizeX = boardX;
    }
    if(boardY <= 0){
        boardY = 20;
    }
    else{
        boardSizeX = boardY;
    }

    gameData = new int*[boardSizeX];

	for(int i = 0; i < boardSizeX; i++)
	{
		gameData[i] = new int[boardSizeY];
	}

	for(int i = 0; i < boardSizeX; i++)
		for(int j = 0; j < boardSizeY; j++)
			gameData[i][j] = 0;
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    for(int i = 0; i < boardSizeX; i++){
		delete[] gameData[i];
	}
	delete[] gameData;
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    if(input == 32){
        exitFlag = true;
    }
}

void GameMechs::setLoseFlag()
{
    loseFlag = true; 
}

void GameMechs::setInput(char this_input)
{
    if(MacUILib_hasChar()){
        input = MacUILib_getChar();
    }
}

void GameMechs::clearInput()
{
    if(MacUILib_hasChar){
        input = NULL;
    }
}

// More methods should be added here