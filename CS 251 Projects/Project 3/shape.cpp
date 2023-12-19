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

#include "shape.h"
#include <string>
#include<iostream>

using namespace std;

Shape::Shape() //default constructor, set initial 'x' and 'y' values
{
    x = 0;
    y = 0;
}
Shape::Shape(int x, int y) //constructor, set 'x' and 'y' values to argument values 
{
    this->x = x;
    this->y = y;
}

Shape::~Shape()
{
}

Shape *Shape::copy() // function that returns a copy of a shape, with same 'x' and 'y' values but different address 
{
    int tempX = this->x;
    int tempY = this->y;
    Shape* copyShape = new Shape(tempX, tempY); //call constructor with old 'x' and 'y' values, this returns a new address
    return copyShape;
}

int Shape::getX() const //get 'x' value
{
    return x;
}

int Shape::getY() const //get 'y' value
{
    return y;
}

void Shape::setX(int x) //set 'x' value 
{
    this->x = x;
}

void Shape::setY(int y) //set 'y' value
{
    this->y = y;
}

string Shape::printShape() const //print a shape'ss corresponding 'x' and 'y' values 
{
    string output = "It's a Shape at x: " + to_string(this->x)+ ", y: "+to_string(this->y);
    return output;
}

Circle::Circle() //default constructor for Circle object
{
    x = 0;
    y = 0;
    radius = 0;
}

Circle::Circle(int r) //constructor to set radius to argument value
{
    radius = r;
}

Circle::Circle(int x, int y, int r) //constructor to set 'x', 'y' and radius to argument values
{
    this->x = x;
    this->y = y;
    radius = r;
}

Circle::~Circle() 
{
}

Circle *Circle::copy()//function that returns a copy of a shape, with same 'x', 'y' and radius values but different address 
{
    int tempX = this->x;
    int tempY = this->y;
    int r = radius;
    Circle* copyCircle = new Circle(tempX, tempY, r);//call constructor with old 'x' , 'y' and radius values, this returns a new address
    return copyCircle;
}

int Circle::getRadius() const //function to get radius 
{
    return radius;
}

void Circle::setRadius(int r) //function to set radius
{
    radius = r;
}

string Circle::printShape() const //function to print Circle with corresponding 'x', 'y' and radius values
{
    string output = "It's a Circle at x: " + to_string(this->x)+ ", y: "+to_string(this->y) + ", radius: " + to_string(radius);
    return output;
}

Rect::Rect() //default constructor for Rect object
{
    x =0;
    y=0;
    width = 0;
    height = 0;
}

Rect::Rect(int w, int h) //constructor to set the 'width' and 'height' values to argument values
{
    width = w;
    height = h;
}

Rect::Rect(int x, int y, int w, int h) //constructor to set the 'x', 'y', 'width' and 'height' values to argument values
{
    this->x = x;
    this->y = y;
    width = w;
    height = h;
}

Rect::~Rect()
{
}

Rect *Rect::copy() //function that returns a copy of a shape, with same 'width', 'height', 'x' and 'y' values but different address 
{
    int tempX = this->x;
    int tempY = this->y;
    int w = width;
    int h = height;
    Rect* copyRect = new Rect(tempX, tempY, w, h); //call constructor with old width, height 'x' and 'y' values, this returns a new address
    return copyRect;
}

int Rect::getWidth() const //function to return width
{
    return width;
}

int Rect::getHeight() const //function to return height
{
    return height;
}

void Rect::setWidth(int w) //function to return width
{
    width = w;
}

void Rect::setHeight(int h) //function to set height
{
    height = h;
}

string Rect::printShape() const //function to print shape with corresponding, 'x', 'y', 'width' and 'height' values
{
    string output = "It's a Rectangle at x: " + to_string(this->x)+ ", y: "+to_string(this->y) + " with width: " + to_string(width) + " and height: " + to_string(height);
    return output;
}

RightTriangle::RightTriangle() //default constructor for RightTraingle object 
{
    x =0;
    y =0;
    base =0;
    height =0;
}

RightTriangle::RightTriangle(int b, int h) //constructor for RightTriangle object that sets its corresponding base and height
{
    base = b;
    height = h;
}

RightTriangle::RightTriangle(int x, int y, int b, int h)//constructor for RightTriangle object that sets its corresponding 'x', 'y', base and height
{
    this->x = x;
    this->y = y;
    base = b;
    height = h;
}

RightTriangle::~RightTriangle()
{
}

RightTriangle *RightTriangle::copy()//function that returns a copy of a shape, with same 'base', 'height', 'x' and 'y' values but different address 
{
    int tempX = this->x;
    int tempY = this->y;
    int b = base;
    int h = height;
    RightTriangle* copyRightTriangle = new RightTriangle(tempX, tempY, b, h);//call constructor with old base, height 'x' and 'y' values, this returns a new address
    return copyRightTriangle;
}

int RightTriangle::getBase() const //function to return base
{
    return base;
}

int RightTriangle::getHeight() const //function to return height
{
    return height;
}

void RightTriangle::setBase(int b) //function to set base
{
    base = b;
}

void RightTriangle::setHeight(int h) //function to set height 
{
    height = h;
}

string RightTriangle::printShape() const //function to print RightTriangle object with corresponding base, height, 'x' and 'y' values
{
    string output = "It's a Right Triangle at x: " + to_string(this->x)+ ", y: "+to_string(this->y) + " with base: " + to_string(base) + " and height: " + to_string(height);
    return output;
}
