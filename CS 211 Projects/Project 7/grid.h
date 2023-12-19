//-------------------------------------------------
// Anupam Sai Sistla
// UIN: 659340448
// NetID: Asistl2

// 'grid.h' implements a custom dynamic ADT that mimics a gameboard. This ADT can be compared to a array of struct objects.
//  This was implemented with the help of classes, templated variables, operator overloading () -> allows for accessing objects in the grid
//  operator '='  -> assign one grid object to another, pointers, exception handling (try and catch), dynamic memory allocation and pass by reference variables
//-------------------------------------------------

#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>
#include <algorithm>

using namespace std;

template<typename T>
class Grid {
private:
  struct ROW {
    T*  Cols;     // array of column elements
    size_t NumCols;  // total # of columns (0..NumCols-1)
  };

  ROW* Rows;     // array of ROWs
  size_t  NumRows;  // total # of rows (0..NumRows-1)
    
public:
  //
  // default constructor:
  //
  // Called automatically by to construct a 4x4 Grid. 
  // All elements initialized to default value of T.
  //
  Grid() {
    Rows = new ROW[4];  // 4 rows
    NumRows = 4;

    // initialize each row to have 4 columns:
    for (size_t r = 0; r < NumRows; ++r) {
      Rows[r].Cols = new T[4];
      Rows[r].NumCols = 4;

      // initialize the elements to their default value:
      for (size_t c = 0; c < Rows[r].NumCols; ++c) {
        Rows[r].Cols[c] = T();  // default value for type T:
      }
    }
  }

  //
  // parameterized constructor:
  //
  // Called automatically to construct a Grid 
  // with R rows, where each row has C columns. 
  // All elements initialized to default value of T.
  //
  Grid(size_t R, size_t C) { //Parameterized constructor
        if (R < 1) { //if there is an invalid number of rows, throw an exception
            throw invalid_argument("Grid::constructor: # of rows");
        }
        if (C < 1) { //if there is an invalid number of coloumns, throw an exception
            throw invalid_argument("Grid::constructor: # of cols");
        }
       
        Rows = new ROW[R]; //create new grid with 'R' rows
        NumRows = R; //set NumRows

        for (size_t r = 0; r < NumRows; ++r) { //loop through all rows in the new grid
            Rows[r].Cols = new T[C]; //create new array of coloumn elements for each array element
            Rows[r].NumCols = C; //set the number of coloums for each row 

            for (size_t c = 0; c < Rows[r].NumCols; ++c) { //loop through all coloumns
                Rows[r].Cols[c] = T();  //initialize each all elements in the grid
            }
        }
  }
    
  //
  // destructor:
  //
  // Called automatically to free memory for this Grid.
  //
  virtual ~Grid() {
    for (size_t r = 0; r < NumRows; r++) { //loop through all rows
      delete[] Rows[r].Cols; //delete each coloumn
    }
      delete[] Rows; //delete the grid itself
  }


  //
  // copy constructor:
  //
  // Called automatically to construct a Grid that contains a
  // copy of an existing Grid.  Example: this occurs when passing
  // Grid as a parameter by value
  //
  //   void somefunction(Grid<int> G2)  <--- G2 is a copy:
  //   { ... }
  //
  Grid(const Grid<T>& other) {
      
    this->Rows = new ROW[other.NumRows]; //create new copy grid with the same number of elements as other
    this->NumRows = other.NumRows; //set copy grid's NumRows

    for (size_t r = 0; r < other.NumRows; ++r) { //loop through entire other grid
      size_t other_numcols = other.Rows[r].NumCols; //set copy grid's number of coloumns to be the same as other grid

      this->Rows[r].Cols = new T[other_numcols]; // create new array of coloums, with the number of elements equal to NumCols of other
      this->Rows[r].NumCols = other_numcols; //set NumCols of each grid item of copy to equal other

      for (size_t c = 0; c < other_numcols; ++c) { //loop through all coloumns
        this->Rows[r].Cols[c] = other.Rows[r].Cols[c]; //set each element in the copy grid to be the same as other
        }
      }
  }
    
  //
  // copy operator=
  //
  // Called when one Grid is assigned into another, i.e. this = other;
  //
  Grid& operator=(const Grid& other) { 
      if (this == &other) { //if lhs grid already equals rhs, return pointer to rhs grid
        return *this;
      }
       
      for (size_t r = 0; r < NumRows; ++r) { //loop through all rows in rhs 
        delete[] Rows[r].Cols; //delete all grid elements
      }
      delete[] Rows; //delete grid itself
       
      this->Rows = new ROW[other.NumRows];  //create new grid for rhs with same rows as lhs
      this->NumRows = other.NumRows; //set NumRoms of rhs to equal lhs
       
      for (size_t r = 0; r < other.NumRows; ++r) { //loop through all rows of lhs
        size_t other_numcols = other.Rows[r].NumCols; //get NumCols of lhs
           
        this->Rows[r].Cols = new T[other_numcols]; //create new coloumn array of each row element of rhs
        this->Rows[r].NumCols = other_numcols; //set NumCols of each rhs row element to other_numcols
           
        for (size_t c = 0; c < other_numcols; ++c) { //loop through all coloumn elements
          this->Rows[r].Cols[c] = other.Rows[r].Cols[c]; //set all elements of each row's coloumn array to equal lhs coloumn array
        }
      }
      return *this; //return new pointer to rhs (copy of lhs)
  }

  //
  // numrows
  //
  // Returns the # of rows in the Grid.  
  // The indices for these rows are 0..numrows-1.
  //
  size_t numrows() const {
    return NumRows; //return number of rows in the grid
  }

  //
  // numcols
  //
  // Returns the # of columns in row r.  
  // The indices for these columns are 0..numcols-1.  
  // For now, each row has the same number of columns.
  //
  size_t numcols(size_t r) const {

    size_t count = 0;
    if(r < 0 || r >= NumRows ){ //if invalid number of rows or argument 'r' is more than grid's NumRows, throw an exception
      throw invalid_argument("Grid::constructor: # of rows");
    }
    return Rows[r].NumCols; //return number of coloumns for each row element
  }

  //
  // size
  //
  // Returns the total # of elements in the Grid.
  //
  size_t size() const { 
      size_t size = 0;
      for(size_t i=0; i<NumRows; i++){ //loop through all rows
        size = size + numcols(i); //size is equal to the sum of the number of coloumns in the grid
      }

      return size; //return the calculated size of the grid 
  }

  //
  // ()
  //
  // Returns a reference to the element at location (r, c);
  // this allows you to access or assign the element:
  //
  //    grid(r, c) = ...
  //    cout << grid(r, c) << endl;
  //
  T& operator()(size_t r, size_t c) { 
      if(r < 0 || r >= NumRows ){ //if invalid number of rows or argument 'r' is more than grid's NumRows, throw an exception
            throw invalid_argument("Grid::constructor: # of rows");
        }
        if(c < 0 || c >= numcols(r)){ //if invalid number of coloumns or argument 'c' is more than numcols for each row item, throw an exception
           throw invalid_argument("Grid::constructor: # of cols");
        }
        return Rows[r].Cols[c];  //return reference to location
  }

  //
  // _output
  //
  // Outputs the contents of the grid; for debugging purposes.  
  // This is not tested.
  //
  void _output() {


  }
};
