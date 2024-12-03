#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "string.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

//Declare gobal player, game, and food pointer objects 
Player *myPlayer;
GameMechs *myGame;
Food *myFood; 


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);


int main(void)
{

    Initialize();

    //Run until game end
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

    //Initialize the game board mechanics, food, and player objects 
    myGame = new GameMechs(30, 30);
    myFood = new Food(myGame); 
    myPlayer = new Player(myGame, myFood);

}

//Collects input from the player
void GetInput(void)
{
    myGame->collectAsyncInput();
    char userInput = myGame->getInput(); 

    if (userInput != 0) { 
        myPlayer->updatePlayerDir(); 
    }
}

//Execute the game logic: update player movement, clear previous inputs 
void RunLogic(void)
{
    if(myPlayer->getDir() != myPlayer->STOP) {
        myPlayer->movePlayer(); //Move player direction if game is running 
    }
    myGame->clearInput();
}

//Draw the game board, snake, and items from food bucket 
void DrawScreen(void)
{
    MacUILib_clearScreen();

    //Print the game title 
    MacUILib_printf("\n=======================================================\n");
    MacUILib_printf("\n\t\tYou're Invited to the \n\t\t  !!SERPENT'S FEAST!!\n\n");
    MacUILib_printf("\n=======================================================\n");
    int xBoard = myGame->getBoardSizeX(); 
    int yBoard = myGame ->getBoardSizeY(); 
    bool drawSnakeBody, drawFood;

    // Loop to print the game board and game entities (food, snake)
    for(int y=0; y<yBoard; y++) {
        for(int x=0; x<xBoard; x++) {
            drawSnakeBody = false;
            drawFood = false;

            // Print out the snake body, checking if the current position matches any position of the snake
            for(int i=0; i<myPlayer->getPlayerPos()->getSize(); i++) {
                objPos tempPos = myPlayer->getPlayerPos()->getElement(i);
                if(tempPos.pos->x == x && tempPos.pos->y == y) {
                    MacUILib_printf("%c ", tempPos.getSymbol());
                    drawSnakeBody = true;
                    break;
                }
            }

            // Skip printing if the snake body has been drawn
            if(drawSnakeBody) {
                continue;
            }

            // Iterate over each coordinate to and check if food exists. If so, print the food item 
            for(int i=0; i<myFood->getFoodPos()->getSize(); i++) {
                if(x == myFood->getFoodPos()->getElement(i).pos->x && y == myFood->getFoodPos()->getElement(i).pos->y) {
                    MacUILib_printf("%c ", myFood->getFoodPos()->getElement(i).getSymbol());
                    drawFood = true;
                    break;
                }
            }

            // Skip printing if food is drawn 
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

    MacUILib_printf("\n=======================================================\n");

    //Print footer with game instructions and score 
    MacUILib_printf("*Navigate with WASD and hit ESC to end  game*\n");
    MacUILib_printf("Gain one point for every 'o' food item  collected\n");
    MacUILib_printf("Collect special '$' food items to gain 50 points but grow by 10 bits\n");
    MacUILib_printf("Collect special '!' food items to gain 10 points\n");
    MacUILib_printf("Remember, don't feast on yourself...\n");

    MacUILib_printf("\n=======================================================\n");

    MacUILib_printf("Score: %d\n", myGame->getScore());
    MacUILib_printf("Size: %d\n", myPlayer->getPlayerPos()->getSize());

    //Display game end messages 
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

    delete myPlayer;
    delete myGame;
    delete myFood; 

    MacUILib_uninit();
}