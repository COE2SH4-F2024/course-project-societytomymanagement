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

    boardSizeX = 30;
    boardSizeY = 15;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    if(boardX <= 3){
        boardX = 15;
    }
    else{
        boardSizeX = boardX;
    }
    if(boardY <= 3){
        boardY = 30;
    }
    else{
        boardSizeY = boardY;
    }

    int i = 0, j = 0;
    board = new int*[boardSizeX];

    for (i = 0; i < boardSizeX; i++){
        for (j = 0; j < boardSizeY ; j++){
            if (i == 0 || i == (boardSizeX-1)){
                board[j][i] = '#';
            } 
            else if (j == 0 || j== (boardSizeY-1)){
                board[j][i] = '#';
            } 
            else{
                board[j][i] = ' ';
            }
        }
    }
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    for(int i = 0; i < boardSizeX; i++){
		delete[] board[i];
	}
	delete[] board;
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
void GameMechs::printBoard()
{
    for(int i = 0; i < boardSizeX; i++){
        for(int j = 0; j < boardSizeY; j++){
            MacUILib_printf("%c", board[j][i]);
        }
        MacUILib_printf("\n");
    }
    MacUILib_printf("Score: %d", score);
}
void GameMechs::clearBoard(){
    for (int i = 0; i < boardSizeX; i++){
        for (int j = 0; j < boardSizeY ; j++){
            if ((i > 0 || i < (boardSizeX-1)) && (j > 0 || j < (boardSizeY-1))){
                board[j][i] = ' ';
            }
        }
    }
}