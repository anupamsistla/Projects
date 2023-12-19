/*
Name: Anupam Sai Sistla
UIN: 659340448
NetID: Asistl2

Project 07 - Outlast the Baddies & Avoid the Abyss
The purpose of this project is to implement a dynamic board game where the goal of the user is to avoid baddies/obstacles in the way
to reach the Escape Ladder, if they do they WIN!, Else they LOSE! This project was implemented with the help of dynamic memory allocation,
Object Oriented Programming: Inheritance, Polymorphism, Pass by reference variables, Virtual functions, exception handling (Through Try and Catch)
Customized ADT (Grid Class), random numbers and templated variables
*/


#ifndef _GAMEBOARD_H
#define _GAMEBOARD_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <stdexcept>

#include "boardcell.h"
#include "grid.h"

using namespace std;

class GameBoard { //Base GameBoard Class
	private: 
	    Grid<BoardCell*> board;
        size_t numRows;
        size_t numCols;
        int HeroRow; // Hero's position row
	    int HeroCol; // Hero's position column
        int numMonsters;
        int numSuperMonsters;
        int numAbysses;
        int numBats;
        bool wonGame; // false, unless the Hero reached the exit successfully

		
	public: 
		/* default constructor */
        GameBoard() {
            numMonsters = 4;
            numSuperMonsters = 2;
            numAbysses = 50;
            numBats = 2;
            wonGame = false;
            
            this -> numRows = 15;
            this -> numCols = 40;
            
            Grid<BoardCell*> boardnew(numRows, numCols);
            board = boardnew;
            
            blankBoard();
        }
        
        /* param constructor */
        GameBoard(size_t numRows, size_t numCols) {
            numMonsters = 4;
            numSuperMonsters = 2;
            numAbysses = 20;
            numBats = 3;
            wonGame = false;
            
            this -> numRows = numRows;
            this -> numCols = numCols;
            
            Grid<BoardCell*> boardnew(numRows, numCols);
            board = boardnew;
            
            blankBoard();
        }
        
        /* destructor */
        virtual ~GameBoard() {
            for (size_t row = 0; row < board.numrows(); row++) {
                for (size_t col = 0; col < board.numcols(row); col++) {
                    delete board(row, col);
                }
            }
        }

        void blankBoard() { //fill the entire board with nothing
            for (size_t row = 0; row < board.numrows(); row++) { //loop through each row
                for (size_t col = 0; col < board.numcols(row); col++) { //loop through col
                    board(row, col) = new Nothing(row,col); //create nothing for each cell
                }
            }
        }

        char getCellDisplay(size_t r, size_t c) { //display the item at that position
            return board(r,c)->display(); 
        }

        void setCell(BoardCell* myCell, size_t r, size_t c) { //setter for cell
            board(r,c) = myCell;
        }
    
        void freeCell(size_t r, size_t c) { //free memory for cell
            delete board(r,c); //delete cell
        }

        // fills board with by randomly placing...
        //  - Hero (H) in the first three columns
        //  - EscapeLadder (*) in last three columns
        //  - 3 vertical Walls (+), each 1/2 of board height, in middle segment
        //  - Abyss cells (#), quantity set by numAbysses, in middle segment
        //  - Baddies [Monsters (m), Super Monsters (M), & Bats (~)] in middle segment;
        //    number of Baddies set by numMonsters, numSuperMonsters, & numBats
        void setupBoard(int seed) {
            srand(seed);
            size_t r,c;

            r = rand() % numRows;
            c = rand() % 3;
            delete board(r,c);
            board(r,c) = new Hero(r,c);
            HeroRow = r;
            HeroCol = c;

            r = rand() % numRows;
            c = numCols - 1 - (rand() % 3);
            delete board(r,c);
            board(r,c) = new EscapeLadder(r,c);
            
            int sizeMid = numCols - 6;

            c = 3 + (rand() % sizeMid);
            for (r = 0; r < numRows/2; ++r) {
                delete board(r,c);
                board(r,c) = new Wall(r,c);
            }
            size_t topc = c;

            while (c == topc || c == topc-1 || c == topc+1) {
                c = 3 + (rand() % sizeMid);
            }
            for (r = numRows-1; r > numRows/2; --r) {
                delete board(r,c);
                board(r,c) = new Wall(r,c);           
            }
            size_t botc = c;

            while (c == topc || c == topc-1 || c == topc+1 || c == botc || c == botc-1 || c == botc+1) {
                c = 3 + (rand() % sizeMid);
            }
            for (r = numRows/4; r < 3*numRows/4; ++r) {
                delete board(r,c);
                board(r,c) = new Wall(r,c);
            }

            for (int i = 0; i < numMonsters; ++i) {
                r = rand() % numRows;
                c = 3 + (rand() % sizeMid);
                while (board(r,c)->display() != ' ') {
                    r = rand() % numRows;
                    c = 3 + (rand() % sizeMid);
                }
                delete board(r,c);
                board(r,c) = new Monster(r,c);  
                board(r,c)->setPower(1);        
            }

            for (int i = 0; i < numSuperMonsters; ++i) {
                r = rand() % numRows;
                c = 3 + (rand() % sizeMid);
                while (board(r,c)->display() != ' ') {
                    r = rand() % numRows;
                    c = 3 + (rand() % sizeMid);
                }
                delete board(r,c);
                board(r,c) = new Monster(r,c); 
                board(r,c)->setPower(2);               
            }

            for (int i = 0; i < numBats; ++i) {
                r = rand() % numRows;
                c = 3 + (rand() % sizeMid);
                while (board(r,c)->display() != ' ') {
                    r = rand() % numRows;
                    c = 3 + (rand() % sizeMid);
                }
                delete board(r,c);
                board(r,c) = new Bat(r,c); 
            }

            for (int i = 0; i < numAbysses; ++i) {
                r = rand() % numRows;
                c = 3 + (rand() % sizeMid);
                while (board(r,c)->display() != ' ') {
                    r = rand() % numRows;
                    c = 3 + (rand() % sizeMid);
                }
                delete board(r,c);
                board(r,c) = new Abyss(r,c);              
            }
        }

        // neatly displaying the game board 
		void display( ) {
            cout << '-';
            for (size_t col = 0; col < board.numcols(0); col++) {
                cout << '-';
            }
            cout << '-';
            cout << endl;
            for (size_t row = 0; row < board.numrows(); row++) {
                cout << '|';
                for (size_t col = 0; col < board.numcols(row); col++) {
                    cout << board(row,col)->display();
                }
                cout << '|';
                cout << endl;
            }
            cout << '-';
            for (size_t col = 0; col < board.numcols(0); col++) {
                cout << '-';
            }
            cout << '-';
            cout << endl;
            
        }
		
        bool getWonGame() { //return either true or false if game is won
            return wonGame;
        }
        
        // distributing total number of monsters so that 
        //  ~1/3 of num are Super Monsters (M), and
        //  ~2/3 of num are Regular Monsters (m)
        void setNumMonsters(int num) { 
            numSuperMonsters = num/3;
            numMonsters = num - numSuperMonsters;
        }

        void setNumAbysses(int num) { //set the number of abyss cells
            numAbysses = num;
        }

        void setNumBats(int num) { //set the number of bats on the board
            numBats = num;
        }

        size_t getNumRows() {  //return the number of rows on the board
            return numRows;
        }

        size_t getNumCols() { //return the number of cols on the board
            return numCols;
        }

        
        //---------------------------------------------------------------------------------
        // void getHeroPosition(size_t& row, size_t& col)
        //
        // getter for Hero's position, which are private data members
        //      int HeroRow;
	    //      int HeroCol;
        //---------------------------------------------------------------------------------

        void getHeroPosition(size_t& row, size_t& col) {
            row = HeroRow;  
            col = HeroCol;  
        }

        
        //---------------------------------------------------------------------------------
        // void setHeroPosition(size_t row, size_t col)
        //
        // setter for Hero's position, which are private data members
        //      int HeroRow;
	    //      int HeroCol;
        //---------------------------------------------------------------------------------

        void setHeroPosition(size_t row, size_t col) {
            this->HeroRow = row;
            this->HeroCol = col;
        }

        
        //---------------------------------------------------------------------------------
        // findHero()
        //
        // updater for Hero's position, which are private data members
        //      int HeroRow;
	    //      int HeroCol;
        // this function should find Hero in board and update
        //      HeroRow and HeroCol with the Hero's updated position;
        // if Hero cannot be found in board, then set Hero's position to (-1,-1)
        //---------------------------------------------------------------------------------
        void findHero() {
            bool found = false;
            for(size_t i =0; i<numRows; i++){ //loop through each row
                for(size_t j =0; j<numCols; j++){ //loop through each col
                   BoardCell* myNode = board(i, j);
                   if(myNode->isHero()){ //check if hero is found
                    found = true; //set flag to true
                    setHeroPosition(i, j); //set the hero position
                    break;
                   }
                }
            }

            if(!found){ //if not found, set hero row and col to -1
                this->HeroRow = -1;
                this->HeroCol = -1;
            }
        
        }

        
        //---------------------------------------------------------------------------------
        // bool makeMoves(char HeroNextMove)
        // EACH MOVE IS ONE ITERATION OF GAMEPLAY
        // 
        //  - Allow user to input their next move 
        //  - Get the attempted move position and move Hero and Baddie resolving any potential collisions along the way
        //  - return true if Hero is still on board at the end of the round
        //  - return false if Hero is NOT on board at the end of the round
        //---------------------------------------------------------------------------------

        bool makeMoves(char HeroNextMove) { 
            size_t newR, newC;
            board(HeroRow,HeroCol)->setNextMove(HeroNextMove); //set next move for the hero
            board(HeroRow,HeroCol)->attemptMoveTo(newR,newC,HeroRow,HeroCol); //attempt move using the HeroRow and HeroCol, store in newR, newC
            
            try {
                if (newR < 0 || newR >= numRows) { //invalid newR or newR out of bounds
                    throw runtime_error("Hero trying to move out-of-bounds with an invalid row");
                } 
            }
            catch (runtime_error& excpt) {
                cout << excpt.what() << endl;
                newR = HeroRow; //if out of bounds don't change row
                cout << "Changing row for Hero position to stay in-bounds" << endl;
            }

            try{
                if(newC < 0 || newC >= numCols){ //if newC is invalid or out of bounds, throw an exception
                   throw runtime_error("Hero trying to move out-of-bounds with an invalid coloumn"); 
                }
            }

            catch (runtime_error& excpt) {
                cout << excpt.what() << endl;
                newC = HeroCol; //if out of bounds, don't change horizontal
                cout << "Changing coloumn for Hero position to stay in-bounds" << endl;
            }


            try{
                if(board(newR, newC)->isBarrier()){ //if attempted move puts hero into a wall, throw exception
                  throw runtime_error("Hero moving onto a wall cell");  
                }
            }

            catch(runtime_error& excpt){
                cout << excpt.what() << endl;
                
                newC = HeroCol; //change col back to original and check if this is a valid move
            
                try{
                    if(board(newR, newC)->isBarrier()){ //if barrier, throw an exception
                        throw runtime_error("Hero moving onto a wall cell, ignoring horizontal");
                    }  
                }

                catch(runtime_error& excpt){ //change, newR back to original HeroRow
                    cout << excpt.what() << endl;
                    newR = HeroRow;
                }
            }


            try{ 
                if(board(newR, newC)->isExit()){ //if attempted move leads to escape ladder, throw exception. This is the winning case
                    throw runtime_error("Hero escaped!");
                }
            }

            catch(runtime_error& excpt){
                wonGame = true; //player won game
                delete board(HeroRow, HeroCol); //delete data at the Hero Position
                board(HeroRow, HeroCol) = new Nothing(HeroRow, HeroCol); //Set nothing at old Hero Position
                setHeroPosition(-1,-1); //set row: -1, col: -1 indicating that Hero is not on the board anymore
                return false;
            }

            try{
                if(board(newR, newC)->isHole()){ //Attempted move puts hero onto an abyss cell
                    throw runtime_error("Hero moving to abyss! Lost game");
                }
            }
            
            catch(runtime_error& excpt){
                delete board(HeroRow, HeroCol); //delete data associated with hero
                board(HeroRow, HeroCol) = new Nothing(HeroRow, HeroCol); //replace with nothing
                setHeroPosition(-1,-1); //hero does not exist anymore so set row: -1, col: -1
                return false;
            }

            try{
                if(board(newR, newC)->isBaddie()){ //if attempted move leads to baddie
                    throw runtime_error("Hero met a baddie! Lost game");
                }
            }

            catch(runtime_error& excpt){
                delete board(HeroRow, HeroCol); //delete hero and hero data from board
                board(HeroRow, HeroCol) = new Nothing(HeroRow, HeroCol); //make nothing object at hero position
                return false;
            }

            try{
                throw runtime_error("Valid Move!");
            }

            catch(runtime_error& expct){ //valid Hero move
                auto temp = board(newR, newC); //temporary variable to store data at attempted move position
                board(newR, newC) = board(HeroRow, HeroCol); //move hero to attempted position
                board(HeroRow, HeroCol) = temp; //set old hero position to nothing
            
                setHeroPosition(newR, newC); //set new hero position
                board(HeroRow, HeroCol)->setPos(HeroRow, HeroCol); //update myRow and myCol private data members for Hero
                board(newR, newC)->setPos(newR, newC); //update myRow and myCol private data members for Hero
                board(HeroRow, HeroCol)->setMoved(true); //hero has moved
            }

            for(int i =0; i<numRows; i++){ //loop through all rows and cols
                for(int j =0; j<numCols; j++){
                    if(!board(i,j)->isStatic()){ //not an empty position
                        board(i,j)->setMoved(false); //for each object on the board that is not nothing, move should be false
                    }
                }
            }

                for(size_t i =0; i<numRows; i++){ //loop through each row 
                    for(size_t j = 0; j<numCols; j++){ //loop through each col
                        if(board(i, j)->isBaddie() && !board(i, j)->getMoved()){ //if board object is a baddie and the baddie has not moved
                            board(i ,j)->attemptMoveTo(newR, newC, HeroRow, HeroCol); //get attempted move for each baddie
                            
                            try {
                                if (newR < 0 || newR >= numRows) { //if attempted move leads to invalid position
                                    throw runtime_error("Baddie trying to move out-of-bounds with an invalid row");
                                } 
                            }

                            catch (runtime_error& excpt) {
                                cout << excpt.what() << endl;
                                newR = i; //don't change the baddie position
                                cout << "Changing row for Baddie position to stay in-bounds" << endl;
                            }

                            try{
                                if(newC < 0 || newC >= numCols){ //if attempted move puts baddie out of bounds throw exception
                                    throw runtime_error("Baddie trying to move out-of-bounds with an invalid coloumn"); 
                                }
                            }

                            catch (runtime_error& excpt) {
                                cout << excpt.what() << endl;
                                newC = j; //return newC to original baddie coloumn and check if this new move leads to a wall
                                cout << "Changing coloumn for Baddie position to stay in-bounds" << endl;
                            }

                            try{
                                if(board(newR, newC)->isBarrier() || board(newR, newC)->isExit()){ //if attempted position is a wall or an escape ladder throw exception
                                    throw runtime_error("Baddie moving onto a wall cell");  
                                }
                            }

                            catch(runtime_error& excpt){
                                cout << excpt.what() << endl;
                                newC = j; //ignore horizontal and try vertical
                
                                try{
                                    if(board(newR, newC)->isBarrier() || board(newR, newC)->isExit()){ //if vertical position too is out of bounds, throw exception
                                        throw runtime_error("Baddie moving onto a wall cell, ignoring horizontal");
                                    }  
                                }

                                catch(runtime_error& excpt){
                                    cout << excpt.what() << endl;
                                    newR = i; //ignore horizontal and vertical move
                                    board(newR, newC)->setPos(newR, newC); 
                                    board(newR, newC)->setMoved(true); //baddie has moved so set private member 'moved' to true
                                    continue;
                                }
                            }

                            try{
                                if(board(newR, newC)->isHole()){ //if attempted move puts baddie onto an abyss cell throw exception
                                    throw runtime_error("Baddie moving to abyss!");
                                }
                            }
            
                            catch(runtime_error& excpt){
                                delete board(i, j); //delete baddie
                                board(i, j) = new Nothing(i, j); //create nothing object at baddie position
                                continue;
                            }

                            try{
                                if(board(newR, newC)->isHero()){ //if attempted move puts baddie onto a hero, game is lost
                                    throw runtime_error("Baddie met a hero! Lost game");
                                }
                            }

                            catch(runtime_error& excpt){
                                delete board(newR, newC); //remove hero from the board
                                board(newR, newC) = board(i, j); //move baddie to old hero position
                                board(i, j) = new Nothing(i, j); //create nothing object at old baddie position
                                board(newR, newC)->setPos(newR, newC); 
                                board(newR, newC)->setMoved(true); //baddie has now moved
                            }

                            try{
                                if(board(newR, newC)->isBaddie()){ //if baddie meets another baddie
                                    throw runtime_error("Baddie Ran Into a Baddie");
                                }
                            }

                            catch(runtime_error& excpt){ //retain old position
                                newR = i;
                                newC = j;
                            }

                            try{ //all checks passed and valid baddie move
                                throw runtime_error("Valid Baddie Move");
                            }

                            catch(runtime_error& expct){
                                auto tempBaddie = board(newR, newC); //store nothing object in temporary variable
                                board(newR, newC) = board(i, j); //swap baddie position
                                board(i, j) = tempBaddie; //replace old baddie position with nothing
                                board(i, j)->setPos(i, j); //set myRow and myCol for i, j
                                board(newR, newC)->setPos(newR, newC); //set myRow and myCol for newR, newC
                                board(newR, newC)->setMoved(true); //baddie has moved
                            }

                        }
                    }
                }

                findHero(); //find hero after all baddie moves
                if(HeroRow == -1 || HeroCol == -1){ //if the hero position is -1, -1, game is lost as hero is not on board
                    return false;
                }

                return true; //valid move made by both hero and baddie
            } 
};

#endif //_GAMEBOARD_H