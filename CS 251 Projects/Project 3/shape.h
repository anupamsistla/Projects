/// @file shape.h
/// @author Anupam Sai Sistla
/// @date October 17, 2023
/// @brief The shape file contains declarations for the Shape
///     class and its derived classes to be used with CanvasList.

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

#include <string>

using namespace std;

class Shape //parent class
{
    protected:
        int x;
        int y;

    public: 
        Shape();
        Shape(int x, int y);

        virtual ~Shape();
        virtual Shape* copy(); //returns deep copy of Shape with new address of Shape object being returned

        int getX() const;
        int getY() const;
        void setX(int);
        void setY(int);
        
        virtual string printShape() const; //print shape and its corresponding characteristics
};


class Circle : public Shape //child class of Shape class
{
    private:
        int radius;

    public: 
        Circle();
        Circle(int r);
        Circle(int x, int y, int r);

        virtual ~Circle();
        virtual Circle* copy();//returns deep copy of Circle with new address of Circle object being returned
        
        int getRadius() const;
        void setRadius(int);
        
        virtual string printShape() const; //print Cirlce with corresponding characteristics
};


class Rect : public Shape //child of Shape class
{
    private:
        int width;
        int height;

    public: 
        Rect();
        Rect(int w, int h);
        Rect(int x, int y, int w, int h);
        
        virtual ~Rect();
        virtual Rect* copy(); //returns deep copy of Rect() object with new address
        
        int getWidth() const;
        int getHeight() const;
        void setWidth(int);
        void setHeight(int);
        
        virtual string printShape() const; //print Rect() with corresponding characteristics
};

class RightTriangle : public Shape //child of shape class
{
    private:
        int base;
        int height;

    public: 
        RightTriangle();
        RightTriangle(int b, int h);
        RightTriangle(int x, int y, int b, int h);
        
        virtual ~RightTriangle();
        virtual RightTriangle* copy(); //returns deep copy of RightTriangle object with new address
        
        int getBase() const;
        int getHeight() const;
        void setBase(int);
        void setHeight(int);

        virtual string printShape() const; //print RightTriangle with corresponding characteristics
};


// DO NOT REMOVE - USED BY AUTOGRADER
#include "moreshapes.h"
// DO NOT REMOVE - USED BY AUTOGRADER