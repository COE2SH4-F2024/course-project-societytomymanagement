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
    myFood = new Food(myGame); 
    myPlayer = new Player(myGame,myFood);

    objPosArrayList playerPos = *myPlayer->getPlayerPos(); //get the array of player locations 

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
    int i, playerX, playerY; 
    char input, playerSym; 

    input = myGame->getInput(); 

    objPosArrayList playerPos = *myPlayer->getPlayerPos(); 

    for(i=0; i<playerPos.getSize(); i++){
        playerX = playerPos.getElement(i).pos->x; 
        playerY = playerPos.getElement(i).pos->x ;
    }



    
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
    const objPosArrayList* snakeBody = myPlayer->getPlayerPos(); 

    //objPos playerPos = myPlayer->getPlayerPos()->getHeadElement();
    //objPos foodPos = myFood ->getFoodPos(); 
    //int playerx = playerPos.pos->x;
    //int playery = playerPos.pos->y;
    

    for (int i = 0; i < sizeY; i++){
        for (int j = 0; j < sizeX; j++){
            if (i == 0 || i == (sizeY - 1)){ //header and footer border
                MacUILib_printf("%c",'#');
            } 
            else if (j == 0 || j == (sizeX - 1)){ //side borders
                MacUILib_printf("%c",'#');
            } 
            //check if the position matches the snake body 
            else{
                bool isSnake = false; 
                for(int m = 0; m<snakeBody->getSize(); m++){
                    if(snakeBody->getElement(m).pos->x == j && snakeBody->getElement(m).pos->y == i){
                        MacUILib_printf("%c", snakeBody->getElement(m).symbol); 
                        isSnake = true; 
                        break;
                    }
                }

                if(!isSnake){
                    if(!isSnake){
                        if(i== myFood->getFoodPos().pos->y && j == myFood->getFoodPos().pos->y){
                            MacUILib_printf("%c", myFood->getFoodPos().symbol);
                        }
                        else{
                            MacUILib_printf(" "); 
                        }
                    }
                }
            }
            // else if(i == playery && j == playerx){
            //     MacUILib_printf("%c", playerPos.symbol); // Place player's symbol on the board
            //     }

            // else if(j == foodPos.pos->x && i == foodPos.pos->y){
            //     MacUILib_printf("%c", foodPos.symbol);
            // }
           
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
