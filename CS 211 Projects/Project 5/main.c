/*
Name: Anupam Sai Sistla
UIN : 659340448
NetID: Asistl2

PROJECT 5 CS 211
The purpose of this project is to find the shortest word ladder between two valid words in a dictionary. This was acheived with the help of 
adjacency lists (implemented with linked lists), linked lists, pointers, pass by reference variables, dynamic memory allocation, recursion and file reading algorithms.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct WordNode_struct { //WordNode struct
    char* myWord; //word in node
    struct WordNode_struct* next; //pointer to next node
} WordNode;

typedef struct LadderNode_struct { //LadderNode struct, functions similar to an adjacency list
    WordNode* topWord; //pointer to ladder
    struct LadderNode_struct* next; //pointer to next ladder
} LadderNode;

int countWordsOfLength(char* filename, int wordSize) {//count the number of words in the file that are exactly <wordSize> letters long
    int count =0;
    FILE* myFile = NULL; //get file stream
    myFile = fopen(filename, "r"); //open file to read
    if(myFile == NULL){ //file not opened successfully
        return -1;
    }
    char tempWord[50];
    while(!feof(myFile)){ //read till end of file
        fscanf(myFile, "%s", tempWord); //get each lione
        if(strlen(tempWord) == wordSize){ //check each word length
            count++;
        }
    }
    fclose(myFile); //close file
    return count;
}

bool buildWordArray(char* filename, char** words, int numWords, int wordSize) { //fill the pre-allocated word array <words> with only words that are exactly <wordSize> letters long;
    int fileWordCount = 0; //number of words in file
    FILE* myFile = NULL; //get file stream
    myFile = fopen(filename, "r"); //open file to read
    if(myFile == NULL){ //file not opened successfully
        return false;
    }
    char tempWord[50];
    while(!feof(myFile)){ //read till end of file
        fscanf(myFile, " %s", tempWord); //read each line of the file
        if(fileWordCount > numWords){ //invalid fileWordCount
            fclose(myFile);
            return false;
        }
        if(strlen(tempWord) == wordSize){ //check size and copy valid word
            strcpy(words[fileWordCount], tempWord);
            fileWordCount++;
        }
    }
    fclose(myFile); //close file
    if(fileWordCount == numWords){ //check if file contains exactly numWords words
        return true;
    }
    return false;
}

int findWord(char** words, char* aWord, int loInd, int hiInd) { // binary search for string <aWord> in an alphabetically sorted array of strings <words>, only between <loInd> & <hiInd>
    while(loInd <= hiInd){
        int mid = loInd + (hiInd-loInd)/2; //get middle index
        if(strcmp(words[mid], aWord) == 0){ //check if the middle word is desired word
            return mid; //return index if desired word
        }

        if(strcmp(words[mid], aWord) < 0){ //if less than shorted the bounds to search 
            loInd = mid + 1;
        }
        
        else{ //if greater than shorted the bounds to search 
            hiInd = mid - 1;
        }
    }
    return -1; //word not found
}

void freeWords(char** words, int numWords) { //free up all heap-allocated space for <words>, which is an array of <numWords> C-strings
    for(int i=0; i<numWords; i++){
        free(words[i]); //free the space allocated for each C-string 
    }
    free(words); //free words array pointer
}

void insertWordAtFront(WordNode** ladder, char* newWord) { //insert word at front of ladder
    WordNode* newNode = malloc(sizeof(WordNode)); //malloc memory for new node
    newNode->myWord = newWord; //set new word

    if(*ladder == NULL){ //check if head is null
        newNode->next = NULL;//set next to null as only one node in list
        *ladder = newNode; //set new head
        return;
    }

    newNode->next = *ladder; //advace head and set newNode as head
    *ladder = newNode;
}

int getLadderHeight(WordNode* ladder) { // find & return number of words in <ladder> list
    int ladderSize = 0;
    WordNode* currNode = ladder;
    while(currNode!= NULL){ //;loop through each node in the list
        ladderSize++; //count height
        currNode = currNode->next;
    }
    return ladderSize; //return ladder height
}

WordNode* copyLadder(WordNode* ladder) { //make a complete copy of <ladder> and return it
    WordNode* currNode = ladder; //set currNode as head
    WordNode* copy = NULL;
    if(ladder == NULL || currNode == NULL){ //base case, if head or currNode null at end of list
        return NULL;
    }

    copy = malloc(sizeof(WordNode)); //malloc new memory for each node for the "copy" list
    copy->myWord = currNode->myWord;
    copy->next = copyLadder(currNode->next); //recursively copy each node

    return copy; //return deep copy for "ladder"
}

void freeLadder(WordNode* ladder) { //free up all heap-allocated space for <ladder>;
    WordNode* currNode = ladder; 
    WordNode* wordToDelete = NULL;
    while(currNode != NULL){ //loop through each node in the list
        wordToDelete = currNode; //set wordToDelete
        currNode = currNode->next; //advamce temp pointer
        free(wordToDelete); //free old pointer 
    }
}

void insertLadderAtBack(LadderNode** list, WordNode* newLadder) { //function to insert ladder at back of adjaceny list
    LadderNode* currNode = *list; //set currNode to head
    LadderNode* newNode = malloc(sizeof(LadderNode)); //malloc memory for new LadderNode
    newNode->topWord = newLadder; //set topWord
    if(currNode == NULL){ //if adjacency list is empty, new node is the head
        *list = newNode;
        newNode->next = NULL;
        return;
    }
    
    while(currNode->next != NULL){ //else loop till the end of the list
        currNode = currNode->next;
    }
    currNode->next = newNode; //set new LadderNode to the end of the list
    newNode->next = NULL;
}

WordNode* popLadderFromFront(LadderNode** list) { //pop the first Ladder from the front of the list by returning the pointer to the head node of <list> AND updating the head node of <list> to the next [LadderNode]
    if(*list == NULL){ //if list is empty, nothing to be popped
        return NULL;
    }
    LadderNode* nodeToPop = *list; //head is the node to pop
    WordNode* temp = nodeToPop->topWord; //get ladder
    *list = (*list)->next; //reset head
    free(nodeToPop); //free old head
    return temp; 
}

void freeLadderList(LadderNode* myList) { //free up all heap-allocated space for <myList> for each ladder in <myList>:
    while(myList != NULL){ //loop through every ladder
        LadderNode* NodeToDelete = myList; //ladder to delete
        myList = myList->next; //move to next ladder
        freeLadder(NodeToDelete->topWord); //free ladder -first word
        free(NodeToDelete); //free ladder itself
    }
}

WordNode* findShortestWordLadder(char** words, bool* usedWord, int numWords, int wordSize, char* startWord, char* finalWord){ //find the shortest word ladder from <startWord> to <finalWord> in the <words> word array, where each word is <wordSize> long and there are <numWords> total words
    LadderNode* myList = NULL; 
    WordNode* myLadder = NULL;
    int indexOfStartWord = findWord(words, startWord, 0, numWords-1); //get the index of the start word
    usedWord[indexOfStartWord] = true; //start word already visited

    insertWordAtFront(&myLadder, startWord); //insert startWord into ladder
    insertLadderAtBack(&myList, myLadder); //inser new ladder into the adjacency list
    char tempWord[50];

    while(myList != NULL){ //loop through the adjacney list
        myLadder = popLadderFromFront(&myList); //pop ladder from adjacency list
        for(int i =0; i<wordSize; i++){ //loop through each word in ladder
            for(int j =0; j<26; j++){ //loop through all alphabets 
                strcpy(tempWord, myLadder->myWord); //copy each word for ladder
                tempWord[i] = 'a' + j; //get all possibilities of words
                int indexOfWord = findWord(words, tempWord, 0, numWords-1); // get index of new manipulated word

                if(indexOfWord != -1 && !usedWord[indexOfWord]){ //check if valid word
                    usedWord[indexOfWord] = true; //word is now visited
                    if(strcmp(tempWord, finalWord) == 0){ //check if this is the target word
                        insertWordAtFront(&myLadder, words[indexOfWord]); //insert into ladder
                        freeLadderList(myList); //free adjacency list
                        return myLadder;
                    }
                    else{
                        WordNode* nextLadder = copyLadder(myLadder); //copy unsuccessful ladder
                        insertWordAtFront(&nextLadder, words[indexOfWord]); //insert word into new ladder
                        insertLadderAtBack(&myList, nextLadder); //insert new ladder into the adjaceny list
                    }
                }
            }
        }
        freeLadder(myLadder); //free ladder
    }
    
    freeLadderList(myList); //free adjacency list
    return NULL;
}

// interactive user-input to set a word; 
//  ensures sure the word is in the dictionary word array
void setWord(char** words, int numWords, int wordSize, char* aWord) {
    bool valid = false;
    printf("  Enter a %d-letter word: ", wordSize);
    int count = 0;
    while (!valid) {
        scanf("%s",aWord);
        count++;
        valid = (strlen(aWord) == wordSize);
        if (valid) {
            int wordInd = findWord(words, aWord, 0, numWords-1);
            if (wordInd < 0) {
                valid = false;
                printf("    Entered word %s is not in the dictionary.\n",aWord);
                printf("  Enter a %d-letter word: ", wordSize); 
            }
        } else {
            printf("    Entered word %s is not a valid %d-letter word.\n",aWord,wordSize);
            printf("  Enter a %d-letter word: ", wordSize);
        }
        if (!valid && count >= 5) { //too many tries, picking random word
            printf("\n");
            printf("  Picking a random word for you...\n");
            strcpy(aWord,words[rand()%numWords]);
            printf("  Your word is: %s\n",aWord);
            valid = true;
        }
    }
}

// helpful debugging function to print a single Ladder
void printLadder(WordNode* ladder) {
    WordNode* currNode = ladder;
    while (currNode != NULL) {
        printf("\t\t\t%s\n",currNode->myWord);
        currNode = currNode->next;
    }
}

// helpful debugging function to print the entire list of Ladders
void printList(LadderNode* list) {
    printf("\n");
    printf("Printing the full list of ladders:\n");
    LadderNode* currList = list;
    while (currList != NULL) {
        printf("  Printing a ladder:\n");
        printLadder(currList->topWord);
        currList = currList->next;
    }
    printf("\n");
}


int main() {
    srand((int)time(0));
    
    printf("\nWelcome to the CS 211 Word Ladder Generator!\n\n");

    // set word length using interactive user-input
    int wordSize;
    printf("Enter the word size for the ladder: ");
    scanf("%d",&wordSize);
    printf("\n");

    printf("This program will make the shortest possible\n"); 
    printf("word ladder between two %d-letter words.\n\n",wordSize);
    
    // interactive user-input sets the dictionary file;
    //  check that file exists; if not, user enters another file
    //  if file exists, count #words of desired length [wordSize]
    char dict[100];
    printf("Enter filename for dictionary: ");
    scanf("%s", dict);
    printf("\n");
    int numWords = countWordsOfLength(dict,wordSize);
    while (numWords < 0) {
        printf("  Dictionary %s not found...\n",dict);
        printf("Enter filename for dictionary: ");
        scanf("%s", dict);
        printf("\n");
        numWords = countWordsOfLength(dict,wordSize);
    }
    
    // allocate heap memory for the word array; only words with desired length
    char** words = (char**)malloc(numWords*sizeof(char*));
    for (int i = 0; i < numWords; ++i) {
        words[i] = (char*)malloc((wordSize+1)*sizeof(char));
    }

    // end program if file does not have at least two words of desired length
    if (numWords < 2) {
        printf("  Dictionary %s contains insufficient %d-letter words...\n",dict,wordSize);
        printf("Terminating program...\n");
        return -1;
    }
    
    // [usedWord] bool array has same size as word array [words];
    //  all elements initialized to [false];
    //  later, usedWord[i] will be set to [true] whenever 
    //      words[i] is added to ANY partial word ladder;
    //      before adding words[i] to another word ladder,
    //      check for previous usage with usedWord[i] 
    bool* usedWord = (bool*)malloc(numWords*sizeof(bool));
    for (int i = 0; i < numWords; ++i) {
        usedWord[i] = false;
    }
    
    // build word array (only words with desired length) from dictionary file
    printf("Building array of %d-letter words... ", wordSize);
    //bool status = true;
    bool status = buildWordArray(dict,words,numWords,wordSize);
    if (!status) {
        printf("  ERROR in building word array.\n");
        printf("  File not found or incorrect number of %d-letter words.\n",wordSize);
        printf("Terminating program...\n");
        return -1;
    }
    printf("Done!\n"); 

    // set the two ends of the word ladder using interactive user-input
    //  make sure start and final words are in the word array, 
    //  have the correct length (implicit by checking word array), AND
    //  that the two words are not the same
    char startWord[30];
    char finalWord[30];
    printf("Setting the start %d-letter word... \n", wordSize);
    setWord(words, numWords, wordSize, startWord);
    printf("\n");
    printf("Setting the final %d-letter word... \n", wordSize);
    setWord(words, numWords, wordSize, finalWord);
    while (strcmp(finalWord,startWord) == 0) {
        printf("  The final word cannot be the same as the start word (%s).\n",startWord);
        printf("Setting the final %d-letter word... \n", wordSize);
        setWord(words, numWords, wordSize, finalWord);
    }
    printf("\n");

    // run the algorithm to find the shortest word ladder
    WordNode* myLadder = findShortestWordLadder(words, usedWord, numWords, wordSize, startWord, finalWord);

    // display word ladder and its height if one was found
    if (myLadder == NULL) {
        printf("There is no possible word ladder from %s to %s\n",startWord,finalWord);    
    } else {
        printf("Shortest Word Ladder found!\n");
        printLadder(myLadder);
    }
    printf("Word Ladder height = %d\n",getLadderHeight(myLadder));
    
    // free the heap-allocated memory for the shortest ladder
    freeLadder(myLadder);
    // free the heap-allocated memory for the words array
    freeWords(words,numWords);
    free(usedWord);
    
    return 0;
}