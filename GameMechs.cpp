#include "GameMechs.h"
#include "MacUILib.h"
#include "Player.h"
#include "objPos.h"
#include "GameMechs.h"

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
    if (boardX <= 3) {
        boardSizeX = 30;
    } else {
        boardSizeX = boardX;
    }

    if (boardY <= 3) {
        boardSizeY = 15;
    } else {
        boardSizeY = boardY;
    }

    // Allocate memory for a 2D array
    board = new int*[boardSizeY];  // Allocate rows (Y-axis)
    for (int i = 0; i < boardSizeY; i++) {
        board[i] = new int[boardSizeX];  // Allocate columns (X-axis) for each row
    }

    // Initialize the board
    for (int i = 0; i < boardSizeY; i++) {
        for (int j = 0; j < boardSizeX; j++) {
            if (i == 0 || i == (boardSizeY - 1) || j == 0 || j == (boardSizeX - 1)) {
                board[i][j] = '#'; //border
            } else {
                board[i][j] = ' '; 
            }
        }
    }
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    for (int i = 0; i < boardSizeY; i++) {
        delete[] board[i];  // Delete each row
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
    if(MacUILib_hasChar()){
        input = NULL;
    }
}

// More methods should be added here
void GameMechs::printBoard(const objPos &playerPos)
{
    for(int i = 0; i < boardSizeY; i++){
        for(int j = 0; j < boardSizeX; j++){
            if (i == playerPos.pos->y && j == playerPos.pos->x) {
                MacUILib_printf("%c", playerPos.symbol);  // Print player's symbol
            } else {
                MacUILib_printf("%c", board[i][j]);  // Print board content
            }
        }
        MacUILib_printf("\n");
    }
    MacUILib_printf("Score: %d", score);
}
void GameMechs::clearBoard(){
    for (int i = 1; i < boardSizeY - 1; i++) { // Loop over rows (Y)
        for (int j = 1; j < boardSizeX - 1; j++) { // Loop over columns (X)
            board[i][j] = ' ';
        }
    }
}