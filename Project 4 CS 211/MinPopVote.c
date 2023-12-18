/*
Name: Anupam Sai Sistla
UIN: 659340448
NetID: Asistl2

PROJECT-4 (POPULAR VOTE MINIMIZER)
The purpose of this project is to recursively find the minimum amount of popular votes needed to win an election from an array of State objects.
This was acheived with the help of Recursion, Memoization, Structs and Dynamic Memory.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "MinPopVote.h"

bool setSettings(int argc, char** argv, int* year, bool* fastMode, bool* quietMode) { //function to get command line arguments 
    *year = 0;
    *fastMode = false;
    *quietMode = false;
    for(int i =1; i<argc; i++){ //loop through all command-line arguments
        if(strcmp(argv[i],"-f") == 0){ //set fastMode
            *fastMode = true;
        }
        else if(strcmp(argv[i], "-y") == 0){
            *year = atoi(argv[i+1]); //convert string year to integer
            if(*year >= 1828 && *year <=2020 && *year%4 == 0){ //must check if valid, data only availible from 1828 to 2020 -> every 4 years
                *year = atoi(argv[i+1]);
            }
            else{ //year is invalid
                *year = 0;
            }
            i++;
        }
        else if(strcmp(argv[i], "-q") == 0){ //set quiet mode
            *quietMode = true;
        }
        else{ //invalid command line argument
          return false;
        }
    }

    return true;
}

void inFilename(char* filename, int year) { //function to get file name to access
    char num[50];
    strcpy(filename, "data"); //copy over "data"-where all files to access are stored
    sprintf(num, "%d", year); //convert integer num to string
    strcat(filename, "/");
    strcat(filename, num); //add number to filename and file type
    strcat(filename, ".csv");
    return;
}

void outFilename(char* filename, int year) { //function to make filename to write too
    char num[50];
    strcpy(filename, "toWin"); //copy over "toWin"-where all files to write too are stored
    sprintf(num, "%d", year);//convert integer num to string
    strcat(filename, "/");
    strcat(filename, num);//add number to filename and file type
    strcat(filename, "_win.csv");
    return;
}

bool parseLine(char* line, State* myState) { //function to parse lines from readElectionData() and store in State objects
    int count = 0;
    if(line[strlen(line)-1] == '\n'){ //remove endline, replace with null character to allow for easy iteration
      line[strlen(line)-1] = '\0';
    }

    for(int i =0; i<strlen(line); i++){ //count number of commas to determine if line is valid
        if(line[i] == ','){
            count ++;
        }
    }
    
    if(count !=3){ //invalid line hence, cannot parse line 
        return false;
    }

    char words[4][100]; //array to store each sub string
    char* word = strtok(line, ","); //similar to getline in c++, gets everything till comma
    int i = 0;
    for(int i =0; word != NULL; i++){ //get each string store in words -> array of strings
        strcpy(words[i], word);
        word = strtok(NULL, ","); //copy everything till next comma
    }
  
    strcpy(myState->name, words[0]); //store each State object's member
    myState->name[strlen(myState->name)] = '\0'; //place null character, allows to iterate through string later
    strcpy(myState->postalCode, words[1]);
    myState->postalCode[strlen(myState->postalCode)] = '\0';
    myState->electoralVotes = atoi(words[2]);
    myState->popularVotes = atoi(words[3]);
    return true; 
}


bool readElectionData(char* filename, State* allStates, int* nStates) { //function to read input file 
    *nStates = 0;
    
    char line[100];
    FILE* myFile = NULL;
    myFile = fopen(filename, "r"); //open file, myFile stores filestream
    
    if(myFile == NULL){ //could not open file, hence terminate function
        return false;
    }
    State temp;
    while(!feof(myFile)){ //loop till end of file
        if(fgets(line, 100, myFile)){ //get 100 number of characters from myFile and store in line
            if(parseLine(line, &temp)){ //parse each line from the file
                (allStates[*nStates]) = temp; //store each state object in array
                (*nStates)++; //increase count of number of states
            }
        }
    }
    fclose(myFile); //close file
    return true; 
}

int totalEVs(State* states, int szStates) { //count the total number of electoral votes for all states
    int sum = 0;
    for(int i =0; i<szStates; i++){ //loop through all states and get sum of all electoral votes 
        sum += states[i].electoralVotes;
    }

    return sum; //return total electoral votes
}

int totalPVs(State* states, int szStates) {//count the total number of popular votes for all states
    int sum = 0;
    for(int i =0; i<szStates; i++){//loop through all states and get sum of all popular votes 
        sum += states[i].popularVotes;
    }

    return sum; //return total popular votes
}

MinInfo minPopVoteAtLeast(State* states, int szStates, int start, int EVs) { //slow recursion function to calculate minimum array of states to win election
    MinInfo Include;
    MinInfo Exclude;

    if(EVs <=0){ //BASE CASE 1: Required electoral votes to win has been reached
        Exclude.subsetPVs = 0; //initialize all members
        Exclude.szSomeStates = 0;
        Exclude.sufficientEVs = true; //sufficient number of electoral votes reached
        return Exclude;
    }

    if(start == szStates){ //BASE CASE 2: Required electoral votes to win not reached and all states visited
        Exclude.subsetPVs = 0; //initialize all members
        Exclude.szSomeStates = 0;
        Exclude.sufficientEVs = false; //sufficient number of electoral votes not reached
        return Exclude;
    }

        Include = minPopVoteAtLeast(states, szStates, start+1, EVs- states[start].electoralVotes); //RECURSIVE CALL: When including a state we need to calculate the new minimum array of states
       
        Include.subsetPVs = Include.subsetPVs + states[start].popularVotes/2 + 1; //Calculate popular vote for states and set data from states to Include
        Include.someStates[Include.szSomeStates] = states[start];
        Include.szSomeStates++;
        
        Exclude = minPopVoteAtLeast(states, szStates, start+1, EVs);//RECURSIVE CALL: When excluding a state we need to calculate the new minimum array of states
        if(Exclude.sufficientEVs && Exclude.subsetPVs<Include.subsetPVs){ 
            return Exclude; //fewer EVs needed hence, exclude current state
        }
        else{
            return Include; // did not get sufficient EVs hence, Include current state since condition not met
        }
}

MinInfo minPopVoteToWin(State* states, int szStates) { //return the states array with the minimum number of popular votes to win
    int totEVs = totalEVs(states,szStates);
    int reqEVs = totEVs/2 + 1;  //calculate required EVs
    return minPopVoteAtLeast(states, szStates, 0, reqEVs); //start recursion
}

MinInfo minPopVoteAtLeastFast(State* states, int szStates, int start, int EVs, MinInfo** memo) { //"fast" recursive function with memoization to calculate minimum array of states to win election
    MinInfo Include;
    MinInfo Exclude;
    if(EVs <=0){//BASE CASE 1: Required electoral votes to win has been reached
        Exclude.subsetPVs = 0;//initialize all members
        Exclude.szSomeStates = 0;
        Exclude.sufficientEVs = true;//sufficient number of electoral votes reached
        return Exclude;
    }

    if(start == szStates){//BASE CASE 2: Required electoral votes to win not reached and all states visited
        Exclude.subsetPVs = 0;//initialize all members
        Exclude.szSomeStates = 0;
        Exclude.sufficientEVs = false;//sufficient number of electoral votes not reached
        return Exclude;
    }

    if(memo[start][EVs].subsetPVs != -1){ //check if popular votes previously calculated, if yes then return the struct object
        return memo[start][EVs];
    }
        Include = minPopVoteAtLeastFast(states, szStates, start+1, EVs- states[start].electoralVotes, memo);  //RECURSIVE CALL: When including a state we need to calculate the new minimum array of states - with memoization 
        
        Include.subsetPVs = Include.subsetPVs + states[start].popularVotes/2 + 1; //Calculate popular vote for states and set data from states to Include
        Include.someStates[Include.szSomeStates] = states[start];
        Include.szSomeStates++;

        Exclude = minPopVoteAtLeastFast(states, szStates, start+1, EVs, memo); //RECURSIVE CALL: When Excluding a state we need to calculate the new minimum array of states - with memoization 

        if(Exclude.sufficientEVs && Exclude.subsetPVs<Include.subsetPVs){ 
            memo[start][EVs] = Exclude; //add new result to memo array -memoizaton
            return Exclude;//fewer EVs needed hence, exclude current state
        }
        else{
            memo[start][EVs] = Include; //add new result to memo array -memoization
            return Include;// did not get sufficient EVs hence, Include current state as condition not met
        }
}

MinInfo minPopVoteToWinFast(State* states, int szStates) { //return the states array with the minimum number of popular votes to win
    int totEVs = totalEVs(states,szStates);
    int reqEVs = totEVs/2 + 1; // required EVs to win election

    MinInfo** memo = (MinInfo**)malloc((szStates+1)*sizeof(MinInfo*)); //create memoization array to store all results
    for (int i = 0; i < szStates+1; ++i) {
        memo[i] = (MinInfo*)malloc((reqEVs+1)*sizeof(MinInfo)); //allocate memory for each state
        for (int j = 0; j < reqEVs+1; ++j) {
            memo[i][j].subsetPVs = -1;
        }
    }
    MinInfo res = minPopVoteAtLeastFast(states, szStates, 0, reqEVs, memo); //This call starts a recursive function that calculates the minimum array of states
    
    for(int i =0; i<szStates+1; i++){ //free all dynamically allocated memory 
        free(memo[i]);
    }
    free(memo); //free memoization array

    return res;
}

bool writeSubsetData(char* filenameW, int totEVs, int totPVs, int wonEVs, MinInfo toWin) { //function to output to file
    FILE* myFile = NULL;
    myFile = fopen(filenameW, "w"); //open file, 'w' mean write to file
    if(myFile == NULL){ //could not open file
        return false;
    }

    fprintf(myFile, "%d,%d,%d,%d\n", totEVs, totPVs, wonEVs, toWin.subsetPVs); //output to file, first line is [TotalEVs],[TotalPVs],[EVsWon],[PVsWon]
    for(int i = toWin.szSomeStates-1; i>=0; i--){ //outputs all elements into file in descending order
        int popVot = toWin.someStates[i].popularVotes/2 +1;
        fprintf(myFile, "%s,%s,%d,%d\n", toWin.someStates[i].name, toWin.someStates[i].postalCode, toWin.someStates[i].electoralVotes, popVot); //output to file [stateName],[postalCode],[electoralVotes],[popularVotesToWinState]   

    }
    fclose(myFile); //close file
    return true; 
}
