/// @file tests.cpp
/// @author Anupam Sai Sistla
/// @date October 17, 2023
/// @brief Testing file to implement Catch 1.x framework tests. 

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


#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "shape.h"
#include "canvaslist.h"

using namespace std;

TEST_CASE("Test Getter") //function to test the getter of the Shape class
{
  Shape test(1,2) ;
  REQUIRE(test.getX() == 1);
}

TEST_CASE("Test Setter"){ //function to test the setter of the Shape class
  Shape test(3,4);
  test.setX(1);
  REQUIRE(test.getX() == 1);
}


TEST_CASE("Test push_front"){ //test push_front() function, insert two nodes, front node must be p, pop_back() should return 's'
  CanvasList myCanvas;
	
	Shape *s = new Shape(1, 3);
	myCanvas.push_front(s);

	Rect *p = new Rect(4, 6, 2, 1);
	myCanvas.push_front(p);

  REQUIRE(myCanvas.pop_back() == s) ; 
}

TEST_CASE("Test push_back"){ //test push_back() function
  CanvasList myCanvas;
	
  SECTION("Small list"){ //test using small list
    Circle *s = new Circle(1, 3, 5);
	  myCanvas.push_back(s);

	  Shape *p = new Shape(4, 6);
	  myCanvas.push_back(p);

    REQUIRE(myCanvas.pop_back() == p); //after push_back(), new last node must be 'p'
  }

  SECTION("Small list-Size"){ //test using small list, same as test above but this checks if the size if correctly being updated
    Circle *s = new Circle(1, 3, 5);
	  myCanvas.push_back(s);

	  Shape *p = new Shape(4, 6);
	  myCanvas.push_back(p);

    REQUIRE(myCanvas.size() == 2) ; //size must be 2 after all push_back() operations
  }
  
  SECTION("Large List"){ //test using large list
    Shape *a = new Circle(1, 2, 3);
    myCanvas.push_back(a);
    Shape *b = new Rect(4, 5, 6, 7);
    myCanvas.push_back(b);
    Shape *c  = new RightTriangle(8, 9, 10, 11);
    myCanvas.push_back(c);
    Shape *d = new Shape(12, 13);
    myCanvas.push_back(d);
    Shape *e = new Shape(14, 15);
    myCanvas.push_back(e);
    Shape *f = new Shape(16, 17);
    myCanvas.push_back(f);
    Shape *g = new Shape(18, 19);
    myCanvas.push_back(g);
    Shape *h = new Shape(20, 21);
    myCanvas.push_back(h);
    Shape *i = new Shape(22, 23);
    myCanvas.push_back(i);
    Shape *j = new Shape(24, 25);
    myCanvas.push_back(j);
    Shape *k = new Shape(26, 27);
    myCanvas.push_back(k);
    Shape *l = new Shape(28, 29);
    myCanvas.push_back(l);
    REQUIRE(myCanvas.pop_back() == l); //last element must be l
  }

  SECTION("Large List-Size"){ //same as test above, checks if size is correctly being updated
    Shape *a = new Circle(1, 2, 3);
    myCanvas.push_back(a);
    Shape *b = new Rect(4, 5, 6, 7);
    myCanvas.push_back(b);
    Shape *c  = new RightTriangle(8, 9, 10, 11);
    myCanvas.push_back(c);
    Shape *d = new Shape(12, 13);
    myCanvas.push_back(d);
    Shape *e = new Shape(14, 15);
    myCanvas.push_back(e);
    Shape *f = new Shape(16, 17);
    myCanvas.push_back(f);
    Shape *g = new Shape(18, 19);
    myCanvas.push_back(g);
    Shape *h = new Shape(20, 21);
    myCanvas.push_back(h);
    Shape *i = new Shape(22, 23);
    myCanvas.push_back(i);
    Shape *j = new Shape(24, 25);
    myCanvas.push_back(j);
    Shape *k = new Shape(26, 27);
    myCanvas.push_back(k);
    Shape *l = new Shape(28, 29);
    myCanvas.push_back(l);
    REQUIRE(myCanvas.size() == 12); //size must be 12 after all push_back() operations.
  }
  
}

TEST_CASE("Test insertAfter"){ //test insertAfter() function
  CanvasList myCanvas;

  SECTION("Small list"){ //test using small liist
    Circle *s = new Circle(1, 3, 7);
	  myCanvas.push_front(s);

	  Rect *p = new Rect(4, 6, 1, 2);
	  myCanvas.push_front(p);
    Shape *c = new Shape(3, 4);

    myCanvas.insertAfter(1, c);
  
    REQUIRE(myCanvas.pop_back() == c) ; //after inserting at the end, new last node must be 'c'
  }

  SECTION("Smal list-Size"){ //Same as the test above, just checking if the size if correctly being updated
    Circle *s = new Circle(1, 3, 7);
	  myCanvas.push_front(s);

	  Rect *p = new Rect(4, 6, 1, 2);
	  myCanvas.push_front(p);
    Shape *c = new Shape(3, 4);

    myCanvas.insertAfter(1, c);
  
    REQUIRE(myCanvas.size() == 3); //after insertAfter(), new size must be 3
  }

  SECTION("Smal list-Insert in middle"){ //this tests inserting in the middle of the small list
    Circle *s = new Circle(1, 3, 7);
	  myCanvas.push_front(s);

	  Rect *p = new Rect(4, 6, 1, 2);
	  myCanvas.push_front(p);
    Shape *c = new Shape(3, 4);

    myCanvas.insertAfter(0, c);
  
    REQUIRE(myCanvas.pop_back() == s); // this checks if the last node is still 's' after inserting in the middle 
  }
	
  SECTION("Large list"){ //test the insertAfter() function using a large list
    Shape *a = new Circle(1, 2, 3);
    myCanvas.push_back(a);
    Shape *b = new Rect(4, 5, 6, 7);
    myCanvas.push_back(b);
    Shape *c  = new RightTriangle(8, 9, 10, 11);
    myCanvas.push_back(c);
    Shape *d = new Shape(12, 13);
    myCanvas.push_back(d);
    Shape *e = new Shape(14, 15);
    myCanvas.push_back(e);
    Shape *f = new Shape(16, 17);
    myCanvas.push_back(f);
    Shape *g = new Shape(18, 19);
    myCanvas.push_back(g);
    Shape *h = new Shape(20, 21);
    myCanvas.push_back(h);
    Shape *i = new Shape(22, 23);
    myCanvas.push_back(i);
    Shape *j = new Shape(24, 25);
    myCanvas.push_back(j);
    Shape *k = new Shape(26, 27);
    myCanvas.push_back(k);
    Shape *l = new Shape(28, 29);
    myCanvas.push_back(l);
    Shape *m = new Shape(30, 31);
    myCanvas.insertAfter(11,m);
    REQUIRE(myCanvas.pop_back() == m); //after inserting at the end new last node must be 'm'
  }

  SECTION("Large List-Size"){
    Shape *a = new Circle(1, 2, 3);
    myCanvas.push_back(a);
    Shape *b = new Rect(4, 5, 6, 7);
    myCanvas.push_back(b);
    Shape *c  = new RightTriangle(8, 9, 10, 11);
    myCanvas.push_back(c);
    Shape *d = new Shape(12, 13);
    myCanvas.push_back(d);
    Shape *e = new Shape(14, 15);
    myCanvas.push_back(e);
    Shape *f = new Shape(16, 17);
    myCanvas.push_back(f);
    Shape *g = new Shape(18, 19);
    myCanvas.push_back(g);
    Shape *h = new Shape(20, 21);
    myCanvas.push_back(h);
    Shape *i = new Shape(22, 23);
    myCanvas.push_back(i);
    Shape *j = new Shape(24, 25);
    myCanvas.push_back(j);
    Shape *k = new Shape(26, 27);
    myCanvas.push_back(k);
    Shape *l = new Shape(28, 29);
    myCanvas.push_back(l);
    Shape *m = new Shape(30, 31);
    myCanvas.insertAfter(11,m);
    REQUIRE(myCanvas.size() == 13); //same as test above, just checking if size if correctly being updated 
  }

  SECTION("Large List-Insert in middle"){ //testing inserting a node in the middle of a large list
    Shape *a = new Circle(1, 2, 3);
    myCanvas.push_back(a);
    Shape *b = new Rect(4, 5, 6, 7);
    myCanvas.push_back(b);
    Shape *c  = new RightTriangle(8, 9, 10, 11);
    myCanvas.push_back(c);
    Shape *d = new Shape(12, 13);
    myCanvas.push_back(d);
    Shape *e = new Shape(14, 15);
    myCanvas.push_back(e);
    Shape *f = new Shape(16, 17);
    myCanvas.push_back(f);
    Shape *g = new Shape(18, 19);
    myCanvas.push_back(g);
    Shape *h = new Shape(20, 21);
    myCanvas.push_back(h);
    Shape *i = new Shape(22, 23);
    myCanvas.push_back(i);
    Shape *j = new Shape(24, 25);
    myCanvas.push_back(j);
    Shape *k = new Shape(26, 27);
    myCanvas.push_back(k);
    Shape *l = new Shape(28, 29);
    myCanvas.push_back(l);
    Shape *m = new Shape(30, 31);
    myCanvas.insertAfter(9,m);
    REQUIRE(myCanvas.pop_back() == l); //after inserting in the middle, last node must still be l
  }
}

TEST_CASE("Test clear"){ //function to test the clear() function, it removes all nodes in the list
  CanvasList myCanvas;
  SECTION("Small list"){ //clear all elements in a small list
	  Circle *s = new Circle(1, 3, 5);
	  myCanvas.push_front(s);

	  Shape *p = new Shape(4, 6);
	  myCanvas.push_front(p);
    myCanvas.clear();
    int size = myCanvas.size();

    REQUIRE(size == 0); //size must be zero after clear()
  }
	
  SECTION("Large List"){ //test clear using a large list
    Shape *a = new Circle(1, 2, 3);
    myCanvas.push_back(a);
    Shape *b = new Rect(4, 5, 6, 7);
    myCanvas.push_back(b);
    Shape *c  = new RightTriangle(8, 9, 10, 11);
    myCanvas.push_back(c);
    Shape *d = new Shape(12, 13);
    myCanvas.push_back(d);
    Shape *e = new Shape(14, 15);
    myCanvas.push_back(e);
    Shape *f = new Shape(16, 17);
    myCanvas.push_back(f);
    Shape *g = new Shape(18, 19);
    myCanvas.push_back(g);
    Shape *h = new Shape(20, 21);
    myCanvas.push_back(h);
    Shape *i = new Shape(22, 23);
    myCanvas.push_back(i);
    Shape *j = new Shape(24, 25);
    myCanvas.push_back(j);
    Shape *k = new Shape(26, 27);
    myCanvas.push_back(k);
    Shape *l = new Shape(28, 29);
    myCanvas.push_back(l);
    Shape *m = new Shape(30, 31);
    myCanvas.clear();
    int size = myCanvas.size();
    REQUIRE(size == 0); //size must be zero after clear function
  }
}

TEST_CASE("Test Front"){ //test the front() function that returns the Shape at the front of the list
  CanvasList myCanvas;
  SECTION("Small List"){ //test front() using small list
	  Shape *s = new Shape(1, 3);
	  myCanvas.push_front(s);
	  Shape *p = new Shape(4, 6);
	  myCanvas.push_front(p);
    ShapeNode *c = myCanvas.front();
    Shape *cValue = c->value;
    REQUIRE(cValue == p);  //front must be 'p' after all operations
  }

  SECTION("Large List"){ //test front() using large list
    Shape *a = new Circle(1, 2, 3);
    myCanvas.push_back(a);
    Shape *b = new Rect(4, 5, 6, 7);
    myCanvas.push_back(b);
    Shape *c  = new RightTriangle(8, 9, 10, 11);
    myCanvas.push_back(c);
    Shape *d = new Shape(12, 13);
    myCanvas.push_back(d);
    Shape *e = new Shape(14, 15);
    myCanvas.push_back(e);
    Shape *f = new Shape(16, 17);
    myCanvas.push_back(f);
    Shape *g = new Shape(18, 19);
    myCanvas.push_back(g);
    Shape *h = new Shape(20, 21);
    myCanvas.push_back(h);
    Shape *i = new Shape(22, 23);
    myCanvas.push_back(i);
    Shape *j = new Shape(24, 25);
    myCanvas.push_back(j);
    Shape *k = new Shape(26, 27);
    myCanvas.push_back(k);
    Shape *l = new Shape(28, 29);
    myCanvas.push_back(l);
    ShapeNode *m = myCanvas.front();
    Shape* mValue = m->value;
    REQUIRE(mValue == a); //front must still be 'a' after all operations
  }
}

TEST_CASE("Test Find"){ //test find() function, which finds a Shape with specific x and y values
  CanvasList myCanvas;
	
  SECTION("Small List"){ //test using a small list
    Shape *s = new Shape(1, 3);
	  myCanvas.push_front(s);

	  Rect *p = new Rect(4, 6, 5, 4);
	  myCanvas.push_front(p);
  
    SECTION("SHAPE FOUND"){
      int index = myCanvas.find(4, 6);
      REQUIRE(index == 0); //find must return zero as 'p' is at index 0
    }
  
    SECTION("SHAPE NOT FOUND"){
      int index = myCanvas.find(1, 1); //Shape with 1, 1 does not exist so index from shapeAt() must be -1
      REQUIRE(index == -1);
   }
  }

  SECTION("Large List"){ //test shape at using large list
    Shape *a = new Circle(1, 2, 3);
    myCanvas.push_back(a);
    Shape *b = new Rect(4, 5, 6, 7);
    myCanvas.push_back(b);
    Shape *c  = new RightTriangle(8, 9, 10, 11);
    myCanvas.push_back(c);
    Shape *d = new Shape(12, 13);
    myCanvas.push_back(d);
    Shape *e = new Shape(14, 15);
    myCanvas.push_back(e);
    Shape *f = new Shape(16, 17);
    myCanvas.push_back(f);
    Shape *g = new Shape(18, 19);
    myCanvas.push_back(g);
    Shape *h = new Shape(20, 21);
    myCanvas.push_back(h);
    Shape *i = new Shape(22, 23);
    myCanvas.push_back(i);
    Shape *j = new Shape(24, 25);
    myCanvas.push_back(j);
    Shape *k = new Shape(26, 27);
    myCanvas.push_back(k);
    Shape *l = new Shape(28, 29);
    myCanvas.push_back(l);
  
    SECTION("SHAPE NOT FOUND"){ //tries to find a shape that doesnt exist in the list
      int index = myCanvas.find(0,0);
      REQUIRE(index == -1); //shapeAt() must return -1 if Shape does not exist
   }

   SECTION("SHAPE FOUND"){ //if shape if found index returned must be correct
      int index = myCanvas.find(16,17);
      REQUIRE(index == 5); // Shape with 16, 17 is at the 5th index
   }
  }
}

TEST_CASE("Test pop_front"){ //test pop_front function
  CanvasList myCanvas;

	Shape *s = new Shape(1, 3);
	myCanvas.push_front(s);

  SECTION("ONE ELEMENT IN LIST"){ //with one element in the list, after pop_front() new size must be zero
    Shape *c = myCanvas.pop_front();
    int size = myCanvas.size();
    REQUIRE(size == 0);
  }

	Circle *p = new Circle(4, 6, 7);
	myCanvas.push_front(p);
  
  SECTION("RETURN FIRST ELEMENT"){ //pop_front() must return first element
    Shape *c = myCanvas.pop_front();
    REQUIRE(c == p); //in this case first element is c
  }
  
  SECTION("EMPTY LIST"){ //if list is empty 'c' must point to nullptr
    myCanvas.clear();
    Shape *c = myCanvas.pop_front();
    REQUIRE(c == nullptr);
  }
 
}

TEST_CASE("Test pop_back"){ //function to test pop_back() function
  CanvasList myCanvas;
	
	Shape *s = new Shape(1, 3);
	myCanvas.push_front(s);

   SECTION("1 item list"){ //if there is only one item in the list, then pop_back() must return the listFront which is 's'
    Shape *a = myCanvas.pop_back();
    REQUIRE(s == a);
  }

	Shape *p = new Shape(4, 6);
	myCanvas.push_front(p);
  
 

  SECTION("RETURN LAST ELEMENT"){ //tests if pop_back() correctly returns the last element
    Shape *c = myCanvas.pop_back();
    REQUIRE(c == s); // in this case last element is 's'
  }
  
  SECTION("EMPTY LIST"){ //test if list is empty
    myCanvas.clear();
    Shape *c = myCanvas.pop_back(); 
    REQUIRE(c == nullptr); //if list is empty 'c' must point to null
  }
}


TEST_CASE("Test shapeAt"){ //test shapeAt() function that returns a Shape object at a specific index
  CanvasList myCanvas;
  SECTION("EMPTY LIST"){ //if list is empty 'c' must point to null
    Shape *c = myCanvas.shapeAt(1);
    REQUIRE(c == nullptr);
  }
  SECTION("Small List"){ //test using small list
    Shape *s = new Shape(1, 3);
	  myCanvas.push_front(s);

	  RightTriangle *p = new RightTriangle(4, 6, 1, 2);
	  myCanvas.push_front(p);
    Shape *c = myCanvas.shapeAt(0);
    REQUIRE(c == p); //shape at listFront must be 'p'
  }

  SECTION("Large List"){ //testing using large list
    Shape *a = new Circle(1, 2, 3);
    myCanvas.push_back(a);
    Shape *b = new Rect(4, 5, 6, 7);
    myCanvas.push_back(b);
    Shape *c  = new RightTriangle(8, 9, 10, 11);
    myCanvas.push_back(c);
    Shape *d = new Shape(12, 13);
    myCanvas.push_back(d);
    Shape *e = new Shape(14, 15);
    myCanvas.push_back(e);
    Shape *f = new Shape(16, 17);
    myCanvas.push_back(f);
    Shape *g = new Shape(18, 19);
    myCanvas.push_back(g);
    Shape *h = new Shape(20, 21);
    myCanvas.push_back(h);
    Shape *i = new Shape(22, 23);
    myCanvas.push_back(i);
    Shape *j = new Shape(24, 25);
    myCanvas.push_back(j);
    Shape *k = new Shape(26, 27);
    myCanvas.push_back(k);
    Shape *l = new Shape(28, 29);
    myCanvas.push_back(l);
    Shape *z = myCanvas.shapeAt(4);
    REQUIRE(z == e); //after all operations, Shape obkect at index 4 must be 'e'
  }


  SECTION("INVALID INDEX"){ //if invalid index is entered, 'c' must point to null
    Shape *c = myCanvas.shapeAt(100);
    REQUIRE(c == nullptr);
  }
}

TEST_CASE("Test removeAt"){ //test removeAt() which removes a ShapeNode at a specified index
  CanvasList myCanvas;
  
  SECTION("Small List"){ //test using small list
    Shape *s = new Shape(1, 3);
	  myCanvas.push_front(s);

	  Shape *p = new Shape(4, 6);
	  myCanvas.push_front(p);

    Shape *a = new Shape(9, 0);
	  myCanvas.push_front(a);

  
    SECTION("DELETE HEAD"){ //test deleting head
      myCanvas.removeAt(0);
      Shape *c = myCanvas.pop_back();
      REQUIRE(c == s); //new element at end must be 's'
    }

    SECTION("DELETE MIDDLE NODE"){ //test deleting node in the middle
      myCanvas.removeAt(1);
      Shape *c = myCanvas.pop_back();
      REQUIRE(c == s); //node at end must be 's'
    }

    SECTION("DELETE LAST NODE"){ //test deleting last node
      myCanvas.removeAt(2);
      Shape *c = myCanvas.pop_back();
      REQUIRE(c == p); //node at the end must be 'p'
    }

    SECTION("DELETE NODE - SIZE"){ //test if size if correctly being decremented
      myCanvas.removeAt(2);
      int size = myCanvas.size();
      REQUIRE(size == 2); //new list size must be 2
    }
  }
  
  SECTION("Large List"){ //test removeAt() using large list
    Shape *a = new Circle(1, 2, 3);
    myCanvas.push_back(a);
    Shape *b = new Rect(4, 5, 6, 7);
    myCanvas.push_back(b);
    Shape *c  = new RightTriangle(8, 9, 10, 11);
    myCanvas.push_back(c);
    Shape *d = new Shape(12, 13);
    myCanvas.push_back(d);
    Shape *e = new Shape(14, 15);
    myCanvas.push_back(e);
    Shape *f = new Shape(16, 17);
    myCanvas.push_back(f);
    Shape *g = new Shape(18, 19);
    myCanvas.push_back(g);
    Shape *h = new Shape(20, 21);
    myCanvas.push_back(h);
    Shape *i = new Shape(22, 23);
    myCanvas.push_back(i);
    Shape *j = new Shape(24, 25);
    myCanvas.push_back(j);
    Shape *k = new Shape(26, 27);
    myCanvas.push_back(k);
    Shape *l = new Shape(28, 29);
    myCanvas.push_back(l);

    SECTION("DELETE HEAD"){ //test removing head
      myCanvas.removeAt(0);
      Shape *c = myCanvas.pop_front();
      REQUIRE(c == b); //new head must be 'b'
    }

    SECTION("DELETE MIDDLE NODE"){ //test removing a middle node
      myCanvas.removeAt(10);
      Shape *j = myCanvas.pop_back();
      REQUIRE(j == l); //node at the end must be 'l'
    }

    SECTION("DELETE LAST NODE"){ //test deleting last node
      myCanvas.removeAt(11);
      Shape *c = myCanvas.pop_back();
      REQUIRE(c == k); //new last node must be 'k'
    }
    
    SECTION("DELETE NODE-SIZE"){ //test to check if the size is being correctly decremented for after removeAt() for a large list
      myCanvas.removeAt(11);
      int size = myCanvas.size();
      REQUIRE(size == 11); //new size must be 11
    }
  }
}

TEST_CASE("Test removeEveryOther"){ //test the removeEveryOther() function that remove every node at odd indices
  CanvasList myCanvas;
  SECTION("EMPTY LIST"){ //if list is empty, size must be zero
    myCanvas.removeEveryOther();
    int size = myCanvas.size();
    REQUIRE(size == 0);
  }
  
  SECTION("Small List"){ //test using small list
    Shape *a = new Shape(1, 3);
	  myCanvas.push_front(a);

	  Shape *b = new Shape(4, 6);
	  myCanvas.push_front(b);

    Shape *c = new Shape(8, 7);
	  myCanvas.push_front(c);

    Shape *d = new Shape(3, 2);
	  myCanvas.push_front(d);

    Shape *e = new Shape(5, 4);
	  myCanvas.push_front(e);
  
    SECTION("REMOVE EVERY OTHER"){ //after removeEveryOther() new size must be 3
      myCanvas.removeEveryOther(); 
      int size = myCanvas.size();
      REQUIRE(size == 3);
    }
  }

  SECTION("Large List"){ //test using large list
    Shape *a = new Circle(1, 2, 3);
    myCanvas.push_back(a);
    Shape *b = new Rect(4, 5, 6, 7);
    myCanvas.push_back(b);
    Shape *c  = new RightTriangle(8, 9, 10, 11);
    myCanvas.push_back(c);
    Shape *d = new Shape(12, 13);
    myCanvas.push_back(d);
    Shape *e = new Shape(14, 15);
    myCanvas.push_back(e);
    Shape *f = new Shape(16, 17);
    myCanvas.push_back(f);
    Shape *g = new Shape(18, 19);
    myCanvas.push_back(g);
    Shape *h = new Shape(20, 21);
    myCanvas.push_back(h);
    Shape *i = new Shape(22, 23);
    myCanvas.push_back(i);
    Shape *j = new Shape(24, 25);
    myCanvas.push_back(j);
    Shape *k = new Shape(26, 27);
    myCanvas.push_back(k);
    Shape *l = new Shape(28, 29);
    myCanvas.push_back(l);
    
    SECTION("REMOVE EVERY OTHER"){//after removeEveryOther(), new size must be 6 
      myCanvas.removeEveryOther();
      int size = myCanvas.size();
      REQUIRE(size == 6);
    }
  }
}

