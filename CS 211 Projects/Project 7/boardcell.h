#ifndef _BOARDCELL_H
#define _BOARDCELL_H

using namespace std;

/*
Name: Anupam Sai Sistla
UIN: 659340448
NetID: Asistl2

This part of the project consists of the base BoardCell class, and several child classes such as Hero, Bat, Monster etc.
'boardcell.h' handles each specific operation for every cell object. This is enabled through Inheritance, Polymorphism and Virtual Functions
*/


class BoardCell {
	
    public:  
		BoardCell() {} // default contstructor (do nothing)
        virtual ~BoardCell() {} // destructor (do nothing)
        
        virtual char display( ) = 0; // pure virtual function; this is an abstract base class

    	virtual void attemptMoveTo(size_t& newR, size_t& newC, size_t hRow, size_t hCol) {
            newR = this->myRow; //set myRow and myCol after attempting move
            newC = this->myCol; 
        }
        
        virtual bool isHero( ) {return false;}
    	virtual bool isBaddie( ) {return false;}
    	virtual bool isSpace( ) {return false;}
        virtual bool isBarrier( ) {return false;}
        virtual bool isHole( ) {return false;}
    	virtual bool isExit( ) {return false;}
    	virtual bool isStatic( ) {return true;}

        virtual void setPower(int num) {}
        virtual int getPower() {return 1;}
        virtual void setNextMove(char inChar) {}
        
        void setMoved(bool m) {moved = m;}
        bool getMoved() {return moved;}
        void setRow(size_t r) {myRow = r;}
        size_t getRow() {return myRow;}
        void setCol(size_t c) {myCol = c;}
        size_t getCol() {return myCol;}
        void setPos(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }

    private:
        size_t myRow; // current row for this board cell in a 2D grid
        size_t myCol; // current column for this board cell in a 2D grid
        bool moved;   // true = this board cell already moved in the current round

}; // BoardCell (abstract base class)


class Hero: public BoardCell { //derived class for specific hero operations
    public:
    	Hero(size_t r, size_t c) { //parameterized constructor Hero 
            setRow(r);
            setCol(c);
        }
        
        virtual bool isHero( ) {return true;} //function to check if object on board is hero
        virtual bool isStatic( ) {return false;} //check if object on board is not nothing
        virtual char display( ) {return 'H';} //display hero on board
        
        virtual void setNextMove(char inChar ) { //setter for 'nextMove' private data member 
            nextMove = inChar;
        }
    	
        virtual void attemptMoveTo(size_t& newR, size_t& newC, size_t hRow, size_t hCol) { //attempt move for hero
            if(nextMove == 'q'){ //move up and left
                newR = getRow()-1; //shift vertical-up
                newC = getCol()-1; //shift horizontal-left
            }
            else if(nextMove ==  'a'){ //move left
                newC = getCol()-1; //shift horizontal-left, keep vertical 
                newR = getRow();
            }
            else if(nextMove == 'z'){ //move down and left
                newR = getRow()+1; //shift vertical-down
                newC = getCol()-1; //shift horizontal-left
            }
            else if(nextMove == 'w'){ //move up
                newR = getRow()-1; //shift vertical-up, keep horizontal
                newC = getCol();
            }
            else if(nextMove == 'x'){ //move down
                newR = getRow()+1; //shift vertical-down, keep horizontal
                newC = getCol();
            }
            else if(nextMove == 'e'){//move up and right
                newR = getRow()-1; //shift vertical-up
                newC = getCol()+1; //shirt horizontal-right
            }
            else if(nextMove == 'd'){ //move right
                newC = getCol() +1; //shift horizontal-right, keep vertical
                newR = getRow();
            }
            else if(nextMove == 'c'){ //move down and right
                newR = getRow() +1; //shift vertical-down
                newC = getCol()+1; //shift horizontal-right

            }

            else{ //remain in position 's', keep newR and newC
                newR = getRow();
                newC = getCol();
            }
        }

    private:
        char nextMove;

}; // Hero


class Monster: public BoardCell {  //polymorphic child class for Monster, handles Monster operations in a seperate class
    public:
		Monster(size_t r, size_t c) { //parameterized constructor for Monster, default power = 1
            setRow(r);
            setCol(c);
            power = 1;
        }
        
        virtual bool isBaddie( ) {return true;} //Monster is a baddie
        virtual bool isStatic( ) {return false;} //Monster is not a 'nothing'
        
        virtual char display( ) { //display function for Monster
            if (power == 2) {
                return 'M'; // Super Monster
            } else {
                return 'm'; // Monster
            } 
        }

        virtual void setPower(int num) { //set power for monster
            power = num;
        }

        virtual int getPower() { //get power for monster
            return power;
        }
        
    	virtual void attemptMoveTo(size_t& newR, size_t& newC, size_t hRow, size_t hCol) { //Monster attempt move
            int distanceR = getRow() - hRow; //vertical distance to hero
            int distanceC = getCol() - hCol; //horizontal distance to hero
            if(power == 1){
                if(getRow() == hRow && getCol() == hCol){ //if already at here position, retain hRow, hCol
                    newR = getRow();
                    newC = getCol();
                }

                else if(getRow() == hRow){ //if monster in the same row as hero, shift col accordingly
                    if(getCol() > hCol){ //if monster to the right of hero 
                        newC = getCol()-1; //shift left 1 step closer to hero
                        newR = getRow();
                    }
                    
                    else if(getCol() < hCol){ //if monster to the left of hero
                        newC = getCol()+1; //shift right 1 step closer to ther hero
                        newR = getRow();
                    }
                }

                else if(getCol() == hCol){ //if monster in the same col as hero
                    if(getRow() > hRow){ //if monster above hero
                        newR = getRow()-1; //shift monster one row up
                        newC = getCol();
                    }
                    
                    else if(getRow() < hRow){ //if monster below hero 
                        newR = getRow()+1; //shift monster down 1-step closer to the hero
                        newC = getCol();
                    }
                }

                else{ 
                    if(distanceR >= 1 && distanceC >= 1){ //if hero below and right to monster position
                        newR = getRow()-1; //shift up
                        newC = getCol()-1; //shift left
                    }
                    else if(distanceR >= 1 && distanceC <=-1){ //if hero is below and left to monster position
                        newR = getRow()-1; //shift up one unit
                        newC = getCol()+1; //shift right one unit
                    }
                    else if(distanceC >=1 && distanceR <=-1){ //if hero is above and right to monster position
                        newC = getCol()-1; //shift left 
                        newR = getRow()+1; //move down
                    }
                    
                    else if(distanceR <= -1 && distanceC <= -1){ //if hero is down and right to monster position
                        newR = getRow()+1; //shift down 
                        newC = getCol()+1; //shift right
                    }

                    else if(distanceR <=-1 && distanceC >= 1){ //if hero is dow and left to monster position
                        newR = getRow()+1; //shift down
                        newC = getCol()-1; //shift left
                    }
                    else if(distanceC <=-1 && distanceR>=1){ //if hero is above and right to monster position
                        newR = getRow()-1; //shift up
                        newC = getCol()+1; //shift right
                    }
                }
            }

            else if(power == 2){ //Attempt move for Super Monster
                if(getRow() == hRow && getCol() == hCol){ //if baddie in same row and col as hero i.e, at hero position
                    newR = getRow();
                    newC = getCol();
                }

                else if(getRow() == hRow){ // if baddie in the same row as hero
                    if(getCol() > hCol){ //if baddie to the right of hero
                        newC = getCol()-2; //shift two units left
                        newR = getRow();
                    }
                    
                    else if(getCol() < hCol){ //if baddie to the left of hero
                        newC = getCol()+2; //shift right
                        newR = getRow();
                    }
                }

                else if(getCol() == hCol){ //if baddie in the same coloumn as hero
                    if(getRow() > hRow){ //if baddie below hero
                        newR = getRow()-2; //move up
                        newC = getCol();
                    }
                    
                    else if(getRow() < hRow){ //if baddie below above hero 
                        newR = getRow()+2; //move down
                        newC = getCol();
                    }
                }

                else{//Not in same col  or row
                    if(distanceR >= 1 && distanceC >= 1){ //if hero up and left
                        newR = getRow()-2; //move up
                        newC = getCol()-2; //move left
                    }
                    else if(distanceR >= 1 && distanceC <=-1){ //if the hero is up and right
                        newR = getRow()-2; //shift up
                        newC = getCol()+2; //shift down
                    }
                    else if(distanceC >=1 && distanceR <=-1){ //if the hero is left and down
                        newC = getCol()-2; //shift left
                        newR = getRow()+2; //shift down
                    }
                    
                    else if(distanceR <= -1 && distanceC <= -1){ //if the hero is down and right
                        newR = getRow()+2; //shift down
                        newC = getCol()+2; //shift right
                    }

                    else if(distanceR <=-1 && distanceC >= 1){ //if the hero is down and left
                        newR = getRow()+2; //shift down 
                        newC = getCol()-2; //shift left
                    }
                    else if(distanceC <=-1 && distanceR>=1){ //if the hero is up and right
                        newR = getRow()-2; //shift up
                        newC = getCol()+2; //shift right
                    }
                }
            }
        }
    
    private:
        int power; // power = 1 for Monster, power = 2 for SuperMonster

}; // Monster

class Bat: public BoardCell { //Polymorphic child class 'Bat'. This class handles 'Bat' operations
    public:
		Bat(size_t r, size_t c) { //parameterized constructor for Bat 
            setRow(r);
            setCol(c);
        }
        virtual bool isBaddie( ) {return true;} //Bat is a baddie
        virtual bool isStatic( ) {return false;} //Bat is not a space
        virtual char display( ) {return '~';} //bat symbol
        
    	virtual void attemptMoveTo(size_t& newR, size_t& newC, size_t hRow, size_t hCol) { //attemp move function for bat, attempts move to hero's coloumn without changing rows
            newR = getRow(); //getRow() is the current row of the bat
            newC = hCol; // attempt move to hero col        
        }

}; // Bat


class Abyss: public BoardCell { //Polymorphic child class for Abyss, handles all operations for Abyss
	public:
    	Abyss(size_t r, size_t c) { //Parameterized constructor for Abyss
            setRow(r);
            setCol(c);
        }
        virtual char display( ) {return '#';} //Abyss symbol
        virtual bool isHole( ) {return true;} 
}; // Abyss


class Wall: public BoardCell { //Polymorphic child class for Wall, handles all operations for Wall
	public:
    	Wall(size_t r, size_t c) { //Parameterized constructor for Wall
            setRow(r);
            setCol(c);
        }
        virtual char display( ) {return '+';} //Wall symbol
    	virtual bool isBarrier( ) {return true;}
}; // Wall


class Nothing: public BoardCell { //Polymorphic child class for Nothing
	public:
    	Nothing(size_t r, size_t c) { //Parameterized constructor for nothing
            setRow(r);
            setCol(c);
        }
        virtual char display( ) {return ' ';} //Nothing symbol
    	virtual bool isSpace( ) {return true;}
}; // Nothing


class EscapeLadder: public BoardCell { //Polymorphic child class for EscapeLadder, handles all operations for EscapeLadder. If the hero enters the escape ladder, they win
	public:
    	EscapeLadder(size_t r, size_t c) { //Parameterized constructor for EscapeLadder
            setRow(r);
            setCol(c);
        }
        virtual char display( ) {return '*';} //Symbol for EscapeLadder
    	virtual bool isExit( ) {return true;}
}; // EscapeLadder


#endif //_BOARDCELL_H
