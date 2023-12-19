//Elementary Cellular Automaton
//Name: Anupam Sai Ssitla
//UIN: 659340448
//NetID: Asistl2

#include <stdio.h>
#include <stdbool.h> 
#include <math.h>
const int WORLD_SIZE = 65; //fixed world size for the project

typedef struct cell_struct{
    bool state[3]; //active status for [left, me, right] cells 
    bool active; //current active status for this cell
} cell;

//convert an 8-bit integer rule (0-255) to array of bits 
//(stored in reverse order)
//   ex: rule = 6  = 00000110 -> [01100000] 
//   ex: rule = 30 = 00011110 -> [01111000] 
//   ex: rule = 65 = 01000001 -> [10000010]
//return true if input rule is valid (0-255)
//return false if input rule is invalid
bool setBitArray(bool bitArray[8], int rule) {
  int index = 0; //used to iterate through the bit array
  int remainder = 0; //remainder obtained after dividing rule number by 2
  if(rule > 255 || rule < 0){ //check if the rule number is valid
    return false;
  }
  for(int i = 0; i<8; i++){
    bitArray[i] = 0;
  }
  while(rule > 0){
    remainder = rule%2;
    bitArray[index] = remainder;
    rule = rule/2; //following the process of decimal to binary, hence decreasing the rule number by a factor of 2 to move to the next 2's complement
    index = index + 1; //move to the next index
  }
  return true; //returns true as the rule number is valid
}

void evolutionState(bool bitArray[8]){ //This function reports the evolution step for all possible cell states
    printf("|***|   |** |   |* *|   |*  |   | **|   | * |   |  *|   |   |\n"); //Default evolution state
    char temp;
    printf(" ");
    for(int i= 7; i >=0; i--){ //We iterate in the opposite direction as the binary bits are stored in reverse order in the array
        printf("|");
        if(bitArray[i] == 1){ //checks if the bit is active
            temp = '*';
        }
        else{ //checks if the bit is inactive
            temp = ' ';
        }
        printf("%c|", temp);
        if(i>=1){
          printf("     ");
        }
    }
    
}

//convert a 3-bit state array to its 
//associated index of the rule# bit array
//   ex: {0 0 0} -> 0
//   ex: {0 0 1} -> 1
//   ex: {1 0 1} -> 5
int stateToIndex(bool state[3]) { //This function put simply converts a binary array to an integer
    int sum = 0;
    int count =2; //represents the power of two's complement, decreases after every iteration
    for(int i =0; i<3; i++){
      if(state[i] == 1){
        sum = sum + pow(2, count); //Obtain the integer value
      }
        count--; //decrement power of two's complement
    }
  return sum; //return final integer value
}

//update the state array for each cell in the world array based on the
//current status of active for the nearby [left,me,right] cells
//note: world is assumed periodic/cyclic,
//with front-to-back and back-to-front wrapping 
void setStates(cell world[WORLD_SIZE]) {
  for(int i =0; i<WORLD_SIZE; i++){
    if(i ==64){//front to back wrapping-edge case-1
      world[64].state[0] = world[63].active;
      world[64].state[1] = world[64].active;
      world[64].state[2] = world[0].active;
    }
    else if(i == 0){//back to front wrapping- edge case-2
      world[0].state[0] = world[64].active;
      world[0].state[1] = world[0].active;
      world[0].state[2] = world[1].active;
    }
    else{
      world[i].state[0] = world[i-1].active; //set the state array of the cell based on (active/inactive status of left cell
      world[i].state[1] = world[i].active; //set the state array of the cell based on (active/inactive) status of middle cell
      world[i].state[2] = world[i+1].active;//set the state array of the cell based on (active/inactive) status of right cell
    }
  }
}

//evolve each cell's active status to the next generation 
//  using its state array
//ruleBitArray contains the 8-bits for the rule#, 
//  stored in reverse order
void evolveWorld(cell world[WORLD_SIZE], bool ruleBitArray[8]) { //takes two parameters, struct object of type cell and a boolean ruleBitArray

    int count = 0;
    for(int i =0; i< WORLD_SIZE; i++){ //loop through the world
        count = stateToIndex(world[i].state); //get the integer value of binary state
        world[i].active = ruleBitArray[count];//set activity in world based on the true/false value of the rule bit array at the count index
    }
    return;
}


int main() {
    cell world[WORLD_SIZE]; //this is the world, it contains two members, the state array and a boolean variable called active
    int ruleNumber; //Rule Number entered by the user
    bool bitArray[8]; //Initialise the bit array
    int Generations; //Generations entered by user
    printf("Welcome to the Elementary Cellular Automaton!\n");
    printf("Enter the rule # (0-255): ");
    scanf("%d", &ruleNumber);
    printf("\n");
  
    while(setBitArray(bitArray, ruleNumber) == false){ //checks if rule number is valid
        printf("Enter the rule # (0-255):\n");
        scanf("%d", &ruleNumber);
    }
    printf("The bit array for rule #%d is ", ruleNumber);
    for(int i =7; i>=0; i--){ //prints out the bit array - in reverse loop as binary bits are stored in opposite order in an array
        printf("%d", bitArray[i]);
    }
    printf("\n\n");
    printf("The evolution of all possible states are as follows:\n");
    evolutionState(bitArray); //prints evolution step for all possible cell states
    printf("\n\n");
    printf("Enter the number of generations: ");
    scanf("%d", &Generations);
    printf("\nInitializing world & evolving...\n");
    for(int i = 0; i<WORLD_SIZE; i++){
        world[i].active = false;
    }
    world[32].active = true; //set middle cell to active
    setStates(world);//set all states to inactive
    for(int i =0 ;i<WORLD_SIZE; i++){//prints world with middle index active
        if(world[i].active == true){
            printf("*");
        }
        else{
            printf(" ");
        }
    }
    printf("\n");
    for(int i = 0; i<Generations-1; i++){ //loop through every generation except for last one
      evolveWorld(world, bitArray); //evolve world for user specified number of generations
      setStates(world); //sets state array for the world for each generation
      for(int j =0 ;j<WORLD_SIZE; j++){ //loops through the world
        if(world[j].active == true){ //prints active cell as "*"
          printf("*");
        }
        else{ //prints inactive cell as " "
          printf(" ");
        }
      }
      printf("\n");
    }

    return 0;
}