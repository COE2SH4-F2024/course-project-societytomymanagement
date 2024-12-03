#include "objPos.h"

objPos::objPos() {
    pos = new Pos;        // Dynamically allocate memory for position
    pos->x = 0;
    pos->y = 0;
    symbol = 0;           // Initialize symbol as NULL (0)
}

objPos::objPos(int xPos, int yPos, char sym) {
    pos = new Pos;        // Dynamically allocate memory for position
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;         // Set symbol to provided value
}

objPos::~objPos() {
    delete pos;           // Deallocate memory for position
}

objPos::objPos(const objPos &obj) {
    pos = new Pos;        // Allocate new memory for position
    pos->x = obj.pos->x;
    pos->y = obj.pos->y;
    symbol = obj.getSymbol();  // Copy symbol from the other object
}

objPos &objPos::operator=(const objPos &obpo) {
    if (this != &obpo) {  // Prevent self-assignment
        pos = new Pos;    // Allocate new memory for position
        pos->x = obpo.pos->x;
        pos->y = obpo.pos->y;
        symbol = obpo.getSymbol();  // Copy symbol from the other object
    }
    return *this;
}

void objPos::setObjPos(objPos o) {
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;   // Set position and symbol from another objPos
}

void objPos::setObjPos(int xPos, int yPos, char sym) {
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;        // Set position and symbol directly from arguments
}

objPos objPos::getObjPos() const {
    objPos returnPos;    // Create a new objPos to return
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;  // Copy position and symbol
    return returnPos;
}

char objPos::getSymbol() const {
    return symbol;       // Return the symbol
}

bool objPos::isPosEqual(const objPos* refPos) const {
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);  // Compare positions
}

char objPos::getSymbolIfPosEqual(const objPos* refPos) const {
    if (isPosEqual(refPos)) 
        return symbol;    // Return symbol if positions match
    else 
        return 0;          // Return 0 if positions don't match
}
