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

GameMechs *myGame;


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
    myGame = new GameMechs;
    myPlayer = new Player(myGame);
    

    exitFlag = false;
}

void GetInput(void)
{
    // if (MacUILib_hasChar()) {
    //     char input = MacUILib_getChar();
    //     myGame.setInput(input);  // Pass input to GameMechs
    // }
    // myGame.clearInput();
    myGame->getAsyncInput();
    

}

void RunLogic(void)
{
    loseFlag = myGame->getLoseFlagStatus();
    exitFlag = myGame->getExitFlagStatus();

    myPlayer->updatePlayerDir();
    myPlayer->movePlayer(); 
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    int sizeX = myGame->getBoardSizeX();
    int sizeY = myGame->getBoardSizeY();

    objPos playerPos = myPlayer->getPlayerPos();
    int playerx = playerPos.pos->x;
    int playery = playerPos.pos->y;
    

    for (int i = 0; i < sizeY; i++){
        for (int j = 0; j < sizeX; j++){
            if (i == 0 || i == (sizeY - 1)){ //header and footer border
                MacUILib_printf("%c",'#');
            } 
            else if (j == 0 || j == (sizeX - 1)){ //side borders
                MacUILib_printf("%c",'#');
            } 
            else if(i == playery && j == playerx){
                MacUILib_printf("%c", playerPos.symbol); // Place player's symbol on the board
                } 
            else {
                MacUILib_printf("%c",' '); // Empty space
                }
        }
        MacUILib_printf("%c",'\n');
    }
    
    /*
    for (int i = 0; i < sizeX; i++){
        for (int j = 0; j < sizeY; j++){
            MacUILib_printf("%c", gameBoard[i][j]);
        }
        MacUILib_printf("\n");
    }
    */
    MacUILib_printf("Score: %d\n", myGame->getScore());

    if(loseFlag == true)
    {
        exitFlag = myGame->getExitFlagStatus();
        MacUILib_clearScreen();
        MacUILib_printf("Your Score was: %d\n", myGame->getScore());
    }

    if (exitFlag == true){
        MacUILib_clearScreen();
        MacUILib_printf("Forced Exit.");
    }
}    


void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    delete myPlayer;
    delete myGame;

    MacUILib_clearScreen(); 
    MacUILib_uninit();
}
