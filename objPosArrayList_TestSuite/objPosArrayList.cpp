#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    arrayCapacity = 200; //default snake size 
    aList = new objPos[arrayCapacity]; //memory allocated for snake 
    listSize = 0; 
    
}

objPosArrayList::~objPosArrayList()
{
    delete [] aList; 

}

int objPosArrayList::getSize() const
{
    return listSize; 

}

void objPosArrayList::insertHead(objPos thisPos)
{
    //shift all of the elements down the list to insert at the head 

    int i; 

    for(i = listSize; i > 0; --i){
        aList[i] = aList[i-1]; 
    }

    listSize++; //increment the size of list upon shifting elements to the right

    //insert at head 
    aList[0] = thisPos; 
    
}

void objPosArrayList::insertTail(objPos thisPos)
{

    //insert at tail 
    aList[listSize] = thisPos; 
    listSize++; //increment list size
}

void objPosArrayList::removeHead()
{
    if(listSize > 0){
        //remove the head element by shiting all elements to towards left
        for(int i = 0; i < listSize - 1; i++){
            aList[i] = aList[i+1]; 
        }
    listSize--; //decrement the list size 
    }

    
}

void objPosArrayList::removeTail()
{
    //removes tail element but decrementing list 
    if(listSize > 0){
        listSize--; 
    }
    
}

objPos objPosArrayList::getHeadElement() const
{
    return aList[0]; 
}

objPos objPosArrayList::getTailElement() const
{
    return aList[listSize-1]; 
}

objPos objPosArrayList::getElement(int index) const
{
    return aList[index]; 
    
}