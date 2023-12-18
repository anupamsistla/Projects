#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "MinPopVote.h"

bool setSettings(int argc, char** argv, int* year, bool* fastMode, bool* quietMode) {
    *year = 0;
    *fastMode = false;
    *quietMode = false;
    for(int i =1; i<argc; i++){
        if(strcmp(argv[i],"-f") == 0){
            *fastMode = true;
        }
        else if(strcmp(argv[i], "-y") == 0){
            *year = atoi(argv[i+1]);
            if(*year >= 1828 && *year <=2020 && *year%4 == 0){
                *year = atoi(argv[i+1]);
            }
            else{
                *year = 0;
            }
            i++;
        }
        else if(strcmp(argv[i], "-q") == 0){
            *quietMode = true;
        }
        else{
          return false;
        }
    }
    //------------------------------------------------   
    // TODO: Task 1 - write the setSettings() function
    //------------------------------------------------

    //sample processing of command-line arg...
    return true;
}

void inFilename(char* filename, int year) {
    //------------------------------------------------   
    // TODO: Task 2 - write the inFilename() function
    //------------------------------------------------
    char num[50];
    strcpy(filename, "data");
    sprintf(num, "%d", year);
    strcat(filename, "/");
    strcat(filename, num);
    strcat(filename, ".csv");

    return;
}

void outFilename(char* filename, int year) {
    //------------------------------------------------   
    // TODO: Task 2 - write the outFilename() function
    //------------------------------------------------
    char num[50];
    strcpy(filename, "toWin");
    sprintf(num, "%d", year);
    strcat(filename, "/");
    strcat(filename, num);
    strcat(filename, "_win.csv");
    return;
}

bool parseLine(char* line, State* myState) {
    int count = 0;
    if(line[strlen(line)-1] == '\n'){
      line[strlen(line)-1] = '\0';
    }

    for(int i =0; i<strlen(line); i++){
        if(line[i] == ','){
            count ++;
        }
    }
    if(count !=3){
        return false;
    }
    //------------------------------------------------   
    // TODO: Task 4 - write the parseLine() function
    //------------------------------------------------

    int i = 0;
    char words[4][100];
    const char s[2] = ","; 
    char* word = strtok(line, s);
    for (int i = 0; word != NULL; i++) {
        strcpy(words[i], word);
        word = strtok(NULL, s);
    }
    strcpy(myState->name, words[0]);
    myState->name[strlen(myState->name)] = '\0';
    strcpy(myState->postalCode, words[1]);
    myState->postalCode[strlen(myState->postalCode)] = '\0';
    myState->electoralVotes = atoi(words[2]);
    myState->popularVotes = atoi(words[3]);
    return true; 
}

bool readElectionData(char* filename, State* allStates, int* nStates) {
    char line[50];
    FILE* myFile = NULL;
    myFile = fopen(filename, "r");

    if(myFile == NULL){
        return false;
    }

    while(!feof(myFile)){
        if (fgets(line, 50, myFile) != NULL) {
          if (parseLine(line, &(allStates[*nStates]))) {
            (*nStates)++;
          }
        }
    }
    fclose(myFile);
    //-----------------------------------------------------   
    // TODO: Task 5 - write the readElectionData() function
    //-----------------------------------------------------
    return true; //modify or replace this
}

int totalEVs(State* states, int szStates) {
    int totalVotes = 0;

    // for (int i = 0; i < szStates; i++) {
    //     totalVotes += states[i].electoralVotes;
    // }

    return totalVotes;
}

int totalPVs(State* states, int szStates) {
    int totalVotes = 0;

    // for (int i = 0; i < szStates; i++) {
    //     totalVotes += states[i].popularVotes;
    // }

    return totalVotes;
}


//----------------------------------------------  
//                a recursive helper function;
//                returns MinInfo for the subset
//                of [states] from index [start]
//                to the end with the minimum
//                popular vote total that has 
//                sufficient [EVs] to win
//---------------------------------------------- 
MinInfo minPopVoteAtLeast(State* states, int szStates, int start, int EVs) {
    MinInfo res;
    // if (start == szStates) {
    //     res.sufficientEVs = false;
    //     res.subsetPVs = 0;
    //     res.szSomeStates = 0;
    //     return res;
    // } 
    // if (EVs <= 0) {
    //     res.subsetPVs = 0;
    //     res.szSomeStates = 0;
    //     res.sufficientEVs = true;
    //     return res;
    // }
    
    // MinInfo includeState = minPopVoteAtLeast(states, szStates, start + 1, EVs - states[start].electoralVotes);

    // includeState.someStates[includeState.szSomeStates] = states[start];
    // includeState.subsetPVs += (states[start].popularVotes/2 + 1);
    // includeState.szSomeStates++;
    

    // MinInfo excludeState = minPopVoteAtLeast(states, szStates, start + 1, EVs);

    // if (excludeState.sufficientEVs && includeState.subsetPVs > excludeState.subsetPVs) {
    //     return excludeState;
    // } else {
    //     return includeState;
    // }
    return res;
}

MinInfo minPopVoteToWin(State* states, int szStates) {
    int totEVs = totalEVs(states,szStates);
    int reqEVs = totEVs/2 + 1; // required EVs to win election
    return minPopVoteAtLeast(states, szStates, 0, reqEVs);
}

MinInfo minPopVoteAtLeastFast(State* states, int szStates, int start, int EVs, MinInfo** memo) {
    MinInfo res;
    // if (start == szStates) {
    //     res.sufficientEVs = false;
    //     res.subsetPVs = 0;
    //     res.szSomeStates = 0;
    //     return res;
    // } 

    // if (EVs <= 0) {
    //     res.subsetPVs = 0;
    //     res.szSomeStates = 0;
    //     res.sufficientEVs = true;
    //     return res;
    // }

    // if (memo[start][EVs].subsetPVs != -1) {
    //     return memo[start][EVs];
    // }

    // MinInfo includeState = minPopVoteAtLeastFast(states, szStates, start + 1, EVs - states[start].electoralVotes, memo);

    // includeState.someStates[includeState.szSomeStates] = states[start];
    // includeState.subsetPVs += states[start].popularVotes/2 + 1;
    // includeState.szSomeStates++;

    // MinInfo excludeState = minPopVoteAtLeastFast(states, szStates, start + 1, EVs, memo);

    // if (excludeState.sufficientEVs && includeState.subsetPVs > excludeState.subsetPVs) {
    //     memo[start][EVs] = excludeState;
    //     return excludeState;
    // } else {
    //     memo[start][EVs] = includeState;
    //     return includeState;
    // }
    return res;
}

MinInfo minPopVoteToWinFast(State* states, int szStates) {
    int totEVs = totalEVs(states,szStates);
    int reqEVs = totEVs/2 + 1; // required EVs to win election

    MinInfo** memo = (MinInfo*)malloc((szStates+1)*sizeof(MinInfo));
    for (int i = 0; i < szStates+1; ++i) {
        memo[i] = (MinInfo*)malloc((reqEVs+1)*sizeof(MinInfo));
        for (int j = 0; j < reqEVs+1; ++j) {
            memo[i][j].subsetPVs = -1;
        }
    }
    MinInfo res = minPopVoteAtLeastFast(states, szStates, 0, reqEVs, memo);
    
    // for (int i = 0; i < szStates + 1; i++) {
    //     free(memo[i]);
    // }
    // free(memo);

    return res;
}

bool writeSubsetData(char* filenameW, int totEVs, int totPVs, int wonEVs, MinInfo toWin) {
    // FILE* outFile = fopen(filenameW, "w");
    // if (outFile == NULL) {
    //     return false;
    // }

    // fprintf(outFile, "%d,%d,%d,%d\n", totEVs, totPVs, wonEVs, toWin.subsetPVs);

    // for (int i = toWin.szSomeStates - 1; i >= 0; i--) {
    //     fprintf(outFile, "%s,%s,%d,%d\n", toWin.someStates[i].name, toWin.someStates[i].postalCode, toWin.someStates[i].electoralVotes, toWin.someStates[i].popularVotes);
    // }

    // fclose(outFile);
    return false;
}