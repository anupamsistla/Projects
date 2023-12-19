//-------------------------------------------------
// PROJECT 6:
// The purpose of this project its to implement a maze, titled "Escape the Labyrinth". 
// In order to escape, the player needs to collect three items, namely, "Spellbook", "Wand" and "Potion" while exploring the maze. 
// From the "start" position, the player is able to move in four directions, North, South, East and West
// The game is run through the console with the help of gdb
// The functionalities of this project were implemented with the help of classes, structs, pass by reference variables, dynamic memory allocation, arrays and pointers.
//This header file checks if the inputted path leads to escape

// Anupam Sai Sistla
// UIN: 659340448
// NetID: Asistl2
//-------------------------------------------------

#include <utility>
#include <random>
#include <set>
#include "grid.h"
#include "maze.h"
using namespace std;

const string kYourNetID = "asistl2";

const string kPathOutOfRegularMaze = "WWSNESSSWENNEESW"; //path to escape for regular maze
const string kPathOutOfTwistyMaze = "ESNWESE"; //path to escape for twisty maze 

bool isPathToFreedom(MazeCell *start, const string& moves) { //function to verify path to freedom
    int count1 = 0; // three counters for verifying if spellbook, wand and potion were found
    int count2 = 0; 
    int count3 = 0;
    
    if(start != nullptr){ //while current position is valid
        for(size_t i=0 ;i<moves.size(); i++){ //loop through string of moves

            //Before next move is entered by the user
            if(start->whatsHere == "Spellbook"){ //check if Spellbook is found
                count1 = 1;
            }
            else if(start->whatsHere == "Wand"){ //check if wand is found
                count2 = 1;
            }
            else if(start->whatsHere == "Potion"){ //check if potion is found
                count3 = 1;
            }

            if(moves[i] != 'N' && moves[i] != 'S' &&  moves[i] != 'E' && moves[i] != 'W'){ //check if inputted move is invalid
                return false;
            }
            else if(moves[i] == 'N'){ //move start to north
                start = start->north;
                
            }
            else if(moves[i] == 'S'){ //move start to south
                start = start->south;
            }
            else if(moves[i] == 'E'){ //move start to east
                start = start->east;
            }
            else if(moves[i] == 'W'){ //move start to west
                start = start->west;
            }

            if(start ==nullptr){ //if inputted move causes start to move to nullptr, return false
                return false;
            }
        
            //After move is inputted
            if(start->whatsHere == "Spellbook"){ //check if new postion has Spellbook
                count1 = 1; //intialize count1
            }
            else if(start->whatsHere == "Wand"){ //check if new position has Wand
                count2 = 1; //initialize count2 
            }
            else if(start->whatsHere == "Potion"){ //check if new postion has Potion
                count3 = 1; //initialize count3
            }
            
        }
        return (count1 && count2 && count3); //returns true of all 3 items are found, else returns false
    }
}

