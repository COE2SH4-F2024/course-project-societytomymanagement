// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.

#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    listSize = 0;
    arrayCapacity = 200;
    aList = new objPos[200];
}

//Special constructor specifying the array container size 
objPosArrayList::objPosArrayList(int size)
{
    listSize = 0;
    arrayCapacity = size;
    aList = new objPos[200];
}

//Destructs objects on the heap 
objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

//Return the list size
int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    //Checks for snake size capacity 
    if(listSize == arrayCapacity)
    {
        //The snake cannot extend any farther 
        return;
    }

    // Shift the elements down by account for the new head 
    for(int i=listSize; i>0; i--)
    {
        aList[i] = aList[i-1]; 
    }

    //Increment snake size and insert the head 
    aList[0] = thisPos;
    listSize++; 

}

void objPosArrayList::insertTail(objPos thisPos)
{
    //Checks if the snake is at max capacity
    if(listSize == arrayCapacity)
    {
        //The tail cannot be extended at max capacity 
        return;
    }

    //Elements do not need to be shifted as the tail is simply appended at the back of the list

    aList[listSize] = thisPos;
    listSize++; 
}

void objPosArrayList::removeHead()
{   
    //Checks if any snake body exists 
    if (listSize == 0){
        return;
    }

    //Shift all elements towards the start of the list, effectively removing the head 
    for(int i = 0; i<listSize-1; i++){
        aList[i] = aList[i+1];
    }
    //Decrease snake size 
    listSize--;
}

void objPosArrayList::removeTail()
{   
    if (listSize == 0){
        return;
    }
    //Lazy appraoch to removing snake tail 
    listSize--;
}

//Get the head element of the snake 
objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

//Get the tail element of the snke 
objPos objPosArrayList::getTailElement() const
{
    return aList[listSize-1];
}

//Get any specified index of the snake 
objPos objPosArrayList::getElement(int index) const
{
    //error troubleshooting to ensure the index chosen is not out of bounds of our list
    if (index < 0 || index >= listSize)
    {
        return objPos();
    }

    return aList[index];
}