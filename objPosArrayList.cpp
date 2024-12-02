#include "objPosArrayList.h"

// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.


//default constructor 
objPosArrayList::objPosArrayList()
{
    arrayCapacity = 200; //default snake size 
    aList = new objPos[arrayCapacity]; //memory allocated for snake 
    listSize = 0; 
    
}

//deconstructor 
objPosArrayList::~objPosArrayList()
{
    delete [] aList; 

}

//copy constructor 

 objPosArrayList::objPosArrayList(const objPosArrayList &o){

     arrayCapacity = 200; //default snake size 
     aList = new objPos[arrayCapacity]; //memory allocated for snake 
     listSize = 0; 
 }

//copy assignment operator 

// objPosArrayList& objPosArrayList::operator=(const objPosArrayList &o){

// }

int objPosArrayList::getSize() const
{
    return listSize; 

}

void objPosArrayList::insertHead(objPos thisPos)
{
    //shift all of the elements down the list to insert at the head 

    int i; 
    if (listSize < arrayCapacity){
    for(i = listSize; i > 0; --i){
        aList[i] = aList[i-1]; 
        }
    }

    //insert at head 
    aList[0] = thisPos; 
    listSize++; //increment the size of list upon shifting elements to the right
    
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize < arrayCapacity){
    //insert at tail 
    aList[listSize] = thisPos; 
    listSize++;} //increment list size
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










