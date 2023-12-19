/*
PROJECT 3
Author: Anupam Sai Sistla
UIN: 659340448
NetID: Asistl2

DESCRIPTION:
This project implements a singly linked list of type CanvasList, with each of its nodes having type ShapeNode. 
All ShapeNodes have characteristics value (Shape of Object) and next (pointer to next node). 
This program implements several functionalities such as removeAt(), removeEveryOther(), pop_back(), pop_front(), push_back(), push_front(), shapeAt(), insertAfter(), clear(), find(), print(), copy() and printAddresses()
All functions were implemented with the help of dynamic memory allocation, object oriented programming, inheritance and linked lists
*/

#include "canvaslist.h"
#include "shape.h"
#include <string>
#include <iostream>

void CanvasList::removeAt(int index) //function to remove a node at specific index
{
    if(index >=listSize){ //checking for invalid index, index can never be greater than size of list
        return;
    }

    if(listFront == nullptr){ //check if list is empty
        return;
    }

    int count = 0;
    if(index == listSize-1){ //check if user wants to delete last node
        ShapeNode* thisNode = listFront;
        while(thisNode != nullptr){ //traverse through list
            if(count == index-1){ //loop to node before the node to delete
                ShapeNode *delNode = thisNode->next; //set node to delete
                thisNode->next = nullptr; // set the next node to null
                listSize--;
                delete delNode->value; //delete node
                delete delNode;
                return;
            }
            thisNode = thisNode->next; 
            count++;
        }
    }
    int iterator = 0;
    ShapeNode* currNode = listFront;
    if(index == 0){ //check if user wants to delete first node, must reset head pointer
        listFront = currNode->next; //reset head
        listSize--;
        delete currNode->value; //delete the first node
        delete currNode;
        return;
    }
    else{
        while(currNode != nullptr){ //traverse through list
            if(iterator == index-1){ //loop to node before the node to delete
                ShapeNode* nodeTodelete = currNode->next; //set node to delete
                currNode->next = currNode->next->next; //reset next node
                delete nodeTodelete->value;
                delete nodeTodelete; //delete the node and its corresponding shape
                listSize--;
            }
            iterator++;
            currNode = currNode->next; 
        }
    }
}

void CanvasList::removeEveryOther() //function to remove every other node i.e., every node at the odd index
{
    if(listFront == nullptr){ //check if list is empty
        return;
    }

    if(listFront->next == nullptr){ //No change can be made to list as listFront is index 0
        return;
    }

    ShapeNode* currNode = listFront;
    while(currNode->next != nullptr){
        if(currNode->next->next == nullptr){ //check if the current position of currNode is the second last nodem, this prevent segmentation faults towards the end of the list
            ShapeNode* nodeToDelete = currNode->next; //set node to delete
            currNode->next = nullptr; //set next node to null
            delete nodeToDelete->value;
            delete nodeToDelete; //delete node and decrement size
            listSize--;
            return;
        }

        ShapeNode* nodeToDelete = currNode->next; //set node to delete
        currNode->next = currNode->next->next; //reset pointer of currNode's next
        delete nodeToDelete->value;
        delete nodeToDelete; //delete node
        currNode = currNode->next;
        listSize--;
    }
}

Shape *CanvasList::pop_front() //remove head and return head's shape
{
    Shape* temp;
    if(listFront == nullptr){ //nothing to pop if the list is empty
        return nullptr;
    }

    if(listFront->next == nullptr){ //if there is only one item in the list, then the list must be empty after pop_front() is called
        temp = listFront->value;
        delete listFront; //delete list head
        listFront = nullptr; //set head to null
        listSize --;
        return temp;
    }
    else{
        ShapeNode* currNode = listFront; 
        temp = listFront->value; //get the shape from listFront
        listFront = currNode->next; //reset head pointer 
        delete currNode; //delete old head
        listSize--;
        return temp; //return the shape
    }
    return nullptr;
}

Shape *CanvasList::pop_back() //remove node at the end of the list and return shape
{
    Shape* temp;
    if(listSize == 0){ //nothing to pop_back if list is empty
        return nullptr;
    }

    if(listFront->next == nullptr){ //if there is only one item in the list, then the list must be empty after pop_back() is called
        temp = listFront->value; //get shape from list head
        listSize--;
        delete listFront; //delete head node
        listFront = nullptr; //set head to null
        return temp;
    }
    else{
        ShapeNode* currNode = listFront;
        while(currNode != nullptr){
            if(currNode->next->next == nullptr){ //loop to the second last node in the list
                ShapeNode* tail = currNode->next; //make a temporary tail pointer that points to the end of the list
                temp = tail->value; //get shape from the tail
                currNode->next = nullptr; //reset next pointer
                delete tail; //delete the tail
                listSize--;
                return temp; //return the shape
            }
            currNode = currNode->next; //advance pointer
        }
    }

    return nullptr;
}

ShapeNode *CanvasList::front() const //function to return head pointer
{
    return listFront;
}
       

bool CanvasList::isempty() const //function to check if the list is empty
{
    if(listSize == 0){
        return true;
    }
    return false;
}

int CanvasList::size() const //function that returns the size of the list
{
    return listSize;
}

int CanvasList::find(int x, int y) const //function that finds a Shape with specific x and y values
{
    int index = 0;
    ShapeNode* currNode = listFront;
    if(listFront == nullptr){ //check if list is empty
        return -1;
    }
    while(currNode != nullptr){ //loop through the entire list
        int origX = currNode->value->getX(); //get x and y value from each shape of the list
        int origY = currNode->value->getY();
        if(origX == x && origY == y){ //compare every x and y value, if found return index of the shape
            return index;
        }
        currNode = currNode->next;
        index++;
    }
    return -1; //shape does not exist in the list 
}

Shape *CanvasList::shapeAt(int index) const //function the return shape at a specific index
{
    int iterator = 0;
    if(listSize == 0){ //check if list is empty
        return nullptr;
    }
    if(index >= listSize){ //check if the index is invalid, index can never be greater than the size of the list
        return nullptr;
    }
    
    ShapeNode* currNode = listFront;
    while(currNode != nullptr){ //loop through every node in the list
        if(iterator == index){ //one index is found return the corresponding shape at that node
            return currNode->value;
        }
        iterator++;
        currNode = currNode->next;
    }

    return nullptr; //return nullptr is index does not exist in the list, this should not happen as there is a check above to prevent that
}

void CanvasList::draw() const //function to describe a shape and its characteristics
{
    ShapeNode* currNode = listFront;
    while(currNode != nullptr){ //loop through entire list
        cout << currNode->value->printShape(); //print characteristics of each node 
        currNode = currNode->next;
    }
}

void CanvasList::printAddresses() const //function to print the address of each node in the list
{
    ShapeNode* currNode = listFront;
    while(currNode != nullptr){ //loop through the entire list
        cout << "Node Address: " << currNode << " Shape Address: " << currNode->value << endl; //print address of each node
        currNode = currNode->next;
    }
}

CanvasList::CanvasList() //default constructor of canvas list class
{
    listFront = nullptr; //set head to null and list size of zero
    listSize = 0;
}

CanvasList::CanvasList(const CanvasList &Before) //copy constructor, returns copy of linked list provided as an argument
{
    this->listSize = 0; //set listSize and head pointer of deep copy list to 0 and null respectively
    this->listFront= nullptr;
    ShapeNode* currNode = Before.listFront;
    while(currNode != nullptr){ //loop through the list to copy 
        this->push_back(currNode->value->copy()); //push_back() a copy of each node of the old list to the new list. Each node now has a new unique address due to the copy function
        currNode = currNode->next;
    }
}

CanvasList &CanvasList::operator=(const CanvasList &toCopy) //function that assigns the characteristics of one CanvasList object to another
{
    clear(); //remove all elements from the list
    ShapeNode* currNode = toCopy.front();
    while(currNode != nullptr){ //loop through the list to copy
        this->push_back(currNode->value->copy());//push_back() a copy of each node of the old list to the new list. Each node now has a new unique address due to the copy function
        currNode = currNode->next;
    }
    return (*this); //return new list
}

CanvasList::~CanvasList() //destructor, delete all unwanted ShapeNode and CanvasList object after stack is freed
{
    clear(); 
}

void CanvasList::clear() //function to remove all nodes from the list 
{
    if(listFront == nullptr){ //nothing to clear if list is empty
        return;
    }

    if(listFront->next == nullptr){ //if there is only one element, it is the head that must be deleted and its pointer must be rest
        delete listFront -> value; //delete corresponding shape and node itself
        delete listFront;
        listFront = nullptr; //set head to null
        listSize--;
        return;
    }
    
    ShapeNode* currNode = listFront;
    while(currNode != nullptr){ //loop through each node in the list
        ShapeNode* temp = currNode; 
        currNode = currNode->next; //set current pointer to next to avoid losing the currNode pointer
        delete temp->value; //delete corresponding shape and object of CanvasList class
        delete temp;
        listSize--;
    }
    listFront = nullptr;
}

void CanvasList::insertAfter(int position, Shape *Node) //function to insert a shape after a specified index
{
    if(listFront == nullptr){ //No shape to insert after if list is empty
        return;
    }

    if(position >= listSize){ //check if input index is invalid, no index can be greater than list size itself
        return;
    }

    int iterator = 0;
    ShapeNode* currNode = listFront;
    
    while(currNode != nullptr){ //loop through each node in the list till we encounter the desiered node
        if(position == iterator){ //node to insert after is found
            ShapeNode* newNode = new ShapeNode();
            newNode->next = currNode->next; //rest the pointer of new node
            currNode->next = newNode; //set currNode's next pointer to point to the new node
            newNode->value = Node; //set new node's shape to the argument shape
            listSize++;
            return;
        }

        currNode = currNode->next;
        iterator++;
    } 
}

void CanvasList::push_front(Shape *newShape) //function to insert a shape to the front of the list
{
    ShapeNode* newNode = new ShapeNode();
    if(listFront == nullptr){ //if the list is empty, the new node is the head
        listFront = newNode; //set head pointer
        listFront->value = newShape; //set argument shape to be the listFront's shape
        listSize++;
        return;
    }

    newNode->next = listFront; //rest head pointer
    newNode->value = newShape; //set shape of the new node to be the argument shape
    listFront = newNode; //rest the head pointer
    listSize++;
}

void CanvasList::push_back(Shape *newShape) //function to insert a node at the end of a list
{
    ShapeNode* newNode = new ShapeNode();
     if(listFront == nullptr){ //if list is empty, new node will be the head of the list
        listFront = newNode; //set head pointer to point to new node
        newNode->value = newShape; // set shape to argument shape
        listSize++;
        return;
    }


    ShapeNode* currNode = listFront; 
    while(currNode->next != nullptr){ //loop till the end of the list
        currNode = currNode->next;
    }
    currNode->next = newNode; //reset the currNode's next pointer to point to the new node
    newNode->value = newShape; //set the shape of the new node to be the argument newShape
    newNode->next = nullptr; //set next pointer to null as this is the new last element
    listSize++;
    return;
}
