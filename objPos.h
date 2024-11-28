#ifndef OBJPOS_H
#define OBJPOS_H

// Not really a C++ thing
typedef struct 
{
    int x;
    int y;
} Pos;

class objPos
{
    public:
        Pos* pos;        
        char symbol;

        objPos(); //constructor
        objPos(int xPos, int yPos, char sym); 
        
        // Respect the rule of six / minimum four
        // [TODO] Implement the missing special member functions to meet the minimum four rule
        objPos(const objPos &obpo); //copy constructor
		objPos operator=(const objPos &obpo); //assignment operator
        ~objPos(); //destructor
        
        void setObjPos(objPos o);   //setters     
        void setObjPos(int xPos, int yPos, char sym);  

        objPos getObjPos() const;   //getters
        char getSymbol() const;
        char getSymbolIfPosEqual(const objPos* refPos) const;
        
        bool isPosEqual(const objPos* refPos) const;
};

#endif