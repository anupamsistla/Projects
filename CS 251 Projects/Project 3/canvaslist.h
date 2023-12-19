/// @file canvaslist.h
/// @author Anupam Sai Sistla
/// @date October 17, 2023
/// @brief The canvaslist file contains declarations for the CanvasList
///     class that is a linked list class that mimics the drawing of 
///     shapes to a screen or space. For our simplified drawing we do
///     not use GUI but each shape in the list will output its details to
///     the console when draw is called.

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

#pragma once

#include "shape.h"

using namespace std;

// ShapeNode class used as nodes in linked list
// implemented akin to a struct as all data is public
class ShapeNode
{
    public:
        Shape *value;
        ShapeNode *next;
};

// The CanvasList class implements the functionality of a linked list.
// This linked list can contain all types of Shape and its derived classes.
class CanvasList
{
    private:
        int listSize; //size of the linked list
        ShapeNode *listFront; //pointer to the head of the list

    public:
        CanvasList(); //default constructor of CanvasList class
        CanvasList(const CanvasList &); //copy constructor, returns copy of linked list provided as an argument
        CanvasList& operator=(const CanvasList &); //function that assigns the characteristics of one CanvasList object to another
        
        virtual ~CanvasList(); //destructor: deletss CanvasList objects after stack is freed
        void clear(); //remove all elements from the list
        
        void insertAfter(int, Shape *); //insert a shape after a specific index
        void push_front(Shape *); //insert a shape at the front of the list
        void push_back(Shape *); //insert a shape at the end of the list
        
        void removeAt(int); //remove a shape at a specific index
        void removeEveryOther(); //remove every node at odd indexes
        Shape* pop_front(); //return and remove shape at front of list
        Shape* pop_back(); //return and remove shape at the end of the list

        ShapeNode* front() const; //return head pointer to the list
        bool isempty() const; //check if the list is empty
        int size() const; //return the size of the list

        int find(int x, int y) const; //find a shape with specific 'x' and 'y' values
        Shape* shapeAt(int) const; //return pointer to shape at a specific index
        
        void draw() const; //print shape and its corresponding characteristics
        void printAddresses() const; //print addresseses of Shape objects
};
