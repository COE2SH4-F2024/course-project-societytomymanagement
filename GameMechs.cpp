#include "GameMechs.h"
#include "MacUILib.h"
#include "Player.h"
#include "objPos.h"
#include "GameMechs.h"

GameMechs::GameMechs()
{
    input = '\0';
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = 30;
    boardSizeY = 15;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    if (boardX <= 3) {
        boardSizeX = 30;  // Default width
    } else {
        boardSizeX = boardX;  // Use provided width
    }

    if (boardY <= 3) {
        boardSizeY = 15;  // Default height
    } else {
        boardSizeY = boardY;  // Use provided height
    }

    // Allocate memory for a 2D array
    board = new char*[boardSizeY];  // Allocate rows (Y-axis)
    for (int i = 0; i < boardSizeY; i++) {
        board[i] = new char[boardSizeX];  // Allocate columns (X-axis) for each row
    }

    // Initialize the board with border and empty spaces
    for (int i = 0; i < boardSizeY; i++) {         // Loop over rows
        for (int j = 0; j < boardSizeX; j++) {     // Loop over columns
            if (i == 0 || i == (boardSizeY - 1) || j == 0 || j == (boardSizeX - 1)) { 
                board[i][j] = '#';  // Border
            } else {
                board[i][j] = ' ';  // Empty space
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
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true; 
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = '\0';
}

// More methods should be added here
void GameMechs::printBoard(const objPos &playerPos)
{
    for (int i = 0; i < boardSizeY; i++) { // Loop over rows
        for (int j = 0; j < boardSizeX; j++) { // Loop over columns
            if (i == playerPos.pos->y && j == playerPos.pos->x) { // Correct position
                MacUILib_printf("%c", playerPos.symbol); // Print player's symbol
            } else {
                MacUILib_printf("%c", board[i][j]); // Print board content
            }
        }
        MacUILib_printf("\n");
    }
    MacUILib_printf("Score: %d\n", score);
}
void GameMechs::clearBoard(){
    for(int i = 1; i < (boardSizeX - 1); i++){
        for(int j = 1; j < (boardSizeY - 1); j++){
            board[j][i] = ' ';  // Fill with empty spaces
        }
    }
}
void GameMechs::generateFood() {
    food.pos->x = rand() % (boardSizeX - 2) + 1;
    food.pos->y = rand() % (boardSizeY - 2) + 1;
    food.symbol = '*';
}