#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

GameMechs myGame(15, 30);
int sizeX = myGame.getBoardSizeX();
int sizeY = myGame.getBoardSizeY();

Player *myPlayer;

char gameBoard[15][30];

bool loseFlag = false;


int main(void)
{

    Initialize();

    while(exitFlag == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myPlayer = new Player(&myGame);

    exitFlag = false;
}

void GetInput(void)
{
    if (MacUILib_hasChar()) {
        char input = MacUILib_getChar();
        myGame.setInput(input);  // Pass input to GameMechs
    }
    myGame.clearInput();
}

void RunLogic(void)
{
    loseFlag = myGame.getLoseFlagStatus();

    myPlayer->updatePlayerDir();
    myPlayer->movePlayer(); 
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    for (int i = 0; i < sizeX; i++){
        for (int j = 0; j < sizeY ; j++){
            if (i == 0 || i == (sizeX - 1)){ //header and footer border
                gameBoard[i][j] = '#';
            } 
            else if (j == 0 || j== (sizeY - 1)){ //side borders
                gameBoard[i][j] = '#';
            } 
            else{
                gameBoard[i][j] = ' ';
            }
        }
    }

    for (int i = 0; i < sizeX; i++){
        for (int j = 0; j < sizeY; j++){
            MacUILib_printf("%c", gameBoard[i][j]);
        }
        MacUILib_printf("\n");
    }
    printf("Score: %d\n", myGame.getScore());

    if(loseFlag == 1)
    {
        exitFlag = myGame.getExitFlagStatus();
        MacUILib_clearScreen();
        MacUILib_printf("Your Score was: %d\n", myGame.getScore());
    }
}    


void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    delete myPlayer;

    MacUILib_clearScreen(); 
    MacUILib_uninit();
}
