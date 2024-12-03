#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "string.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer;
GameMechs *myGame;
Food *myFood; 

// Used to print the state string for debugging
char dirList[5][6] = {"UP", "DOWN", "LEFT", "RIGHT", "STOP"};

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);


int main(void)
{

    Initialize();

    while(myGame->getExitFlagStatus() == false && myGame->getLoseFlagStatus() == false)  
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

    myGame = new GameMechs(30, 15);
    myFood = new Food(myGame); 
    myPlayer = new Player(myGame, myFood);

}

void GetInput(void)
{
    myGame->collectAsyncInput();
    char userInput = myGame->getInput(); 

    if (userInput != 0) { 
        myPlayer->updatePlayerDir(); 
    }
}

void RunLogic(void)
{
    if(myPlayer->getDir() != myPlayer->STOP) {
        myPlayer->movePlayer();
    }
    myGame->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    int xBoard = myGame->getBoardSizeX(); 
    int yBoard = myGame ->getBoardSizeY(); 
    bool drawSnakeBody, drawFood;

    // Loop to print the game board
    for(int y=0; y<yBoard; y++) {
        for(int x=0; x<xBoard; x++) {
            drawSnakeBody = false;
            drawFood = false;

            // Print out the snake body
            for(int i=0; i<myPlayer->getPlayerPos()->getSize(); i++) {
                objPos tempPos = myPlayer->getPlayerPos()->getElement(i);
                if(tempPos.pos->x == x && tempPos.pos->y == y) {
                    MacUILib_printf("%c ", tempPos.getSymbol());
                    drawSnakeBody = true;
                    break;
                }
            }

            // Move onto the following coordinates upon printing out the body
            if(drawSnakeBody) {
                continue;
            }

            // Iterate over each coordinate to print out the items in the food bucket 
            for(int i=0; i<myFood->getFoodPos()->getSize(); i++) {
                if(x == myFood->getFoodPos()->getElement(i).pos->x && y == myFood->getFoodPos()->getElement(i).pos->y) {
                    MacUILib_printf("%c ", myFood->getFoodPos()->getElement(i).getSymbol());
                    drawFood = true;
                    break;
                }
            }

            // Move onto the following coordinates upon printing out the food item
            if(drawFood) {
                continue;
            }


            // Prints the game board 
            if(x == 0 || x == myGame->getBoardSizeX() - 1 || y == 0 || y == myGame->getBoardSizeY()-1) {
                MacUILib_printf("# ");
            } else {
                MacUILib_printf("  "); // Otherwise print an empty space
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("\n==============================================\n");

    MacUILib_printf("Welcome to the snake game !!!\n");
    MacUILib_printf("Please use the WASD characters to move and esc to end the game .\n");
    MacUILib_printf("Gain one point for every apple you collect!!\n");
    MacUILib_printf("Collect special '$' food items to gain 50 points - this will increase your snake length by 10.\n");
    MacUILib_printf("Collect special '!' food items to gain 10 points.\n");
    MacUILib_printf("Remember, don't run into yourself!\n");

    MacUILib_printf("==============================================\n");

    MacUILib_printf("Score: %d\n", myGame->getScore());
    MacUILib_printf("Size: %d\n", myPlayer->getPlayerPos()->getSize());

    if (myGame->getLoseFlagStatus() == true){
        MacUILib_printf("\nYou Lost!"); // Lose message
    } else if (myGame->getExitFlagStatus() == true) {
        MacUILib_printf("\nYou ended the game."); // Quitting game early message
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    //MacUILib_clearScreen(); Uncomment to clear the screen upon game end

    delete myPlayer;
    delete myGame;
    delete myFood; 

    MacUILib_uninit();
}