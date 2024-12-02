#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

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

Food *myFood; 


Player *myPlayer;


//char gameBoard[15][30];

bool loseFlag = false;


int main(void)
{

    Initialize();

    while(!myGame->getExitFlagStatus())  
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
    myFood = new Food(myGame); 

    myFood->generateFood(myPlayer->getPlayerPos()->getHeadElement());
    

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

    objPos playerPos = myPlayer->getPlayerPos()->getHeadElement();
    objPos playerPos1 = myPlayer->getPlayerPos()->getElement(1);
    objPos foodPos = myFood ->getFoodPos(); 
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
                MacUILib_printf("%c", '*'); // Place player's symbol on the board
                }
            // else if(i+1 == playerPos1.pos->y && j+1 == playerPos1.pos->x){
            //     MacUILib_printf("%c", '*'); // Place player's symbol on the board
            //     }
            else if(j == foodPos.pos->x && i == foodPos.pos->y){
                MacUILib_printf("%c", foodPos.symbol);
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
    delete myFood; 

    MacUILib_clearScreen(); 
    MacUILib_uninit();
}
