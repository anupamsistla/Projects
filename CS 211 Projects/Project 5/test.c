#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct WordNode_struct {
    char* myWord; 
    struct WordNode_struct* next; 
} WordNode;

typedef struct LadderNode_struct {
    WordNode* topWord;
    struct LadderNode_struct* next; 
} LadderNode;

int countWordsOfLength(char* filename, int wordSize) {
    int count =0;
    FILE* myFile = NULL;
    myFile = fopen(filename, "r");
    if(myFile == NULL){
        return -1;
    }
    char tempWord[50];
    while(!feof(myFile)){
        fscanf(myFile, "%s", tempWord);
        if(strlen(tempWord) == wordSize){
            count++;
        }
    }
    fclose(myFile);
    return count; 
}

bool buildWordArray(char* filename, char** words, int numWords, int wordSize) {
    int fileWordCount = 0;
    FILE* myFile = NULL;
    myFile = fopen(filename, "r");
    if(myFile == NULL){
        return false;
    }
    char tempWord[50];
    while(!feof(myFile)){
        fscanf(myFile, " %s", tempWord);
        if(fileWordCount > numWords){
            fclose(myFile);
            return false;
        }
        if(strlen(tempWord) == wordSize){
            strcpy(words[fileWordCount], tempWord);
            fileWordCount++;
        }
    }
    fclose(myFile);
    if(fileWordCount == numWords){
        return true;
    }
    return false;
}

int findWord(char** words, char* aWord, int loInd, int hiInd) {
    while(loInd <= hiInd){
        int mid = loInd + (hiInd-loInd)/2;
        if(strcmp(words[mid], aWord) == 0){
            return mid;
        }

        if(strcmp(words[mid], aWord) < 0){
            loInd = mid + 1;
        }
        
        else{
            hiInd = mid - 1;
        }
    }
    return -1;
}

void freeWords(char** words, int numWords) {
    for(int i=0; i<numWords; i++){
        free(words[i]);
    }
    free(words);
}

void insertWordAtFront(WordNode** ladder, char* newWord) {
    WordNode* newNode = malloc(sizeof(WordNode));  
    newNode->myWord = newWord;

    if(*ladder == NULL){
        newNode->next = NULL;
        *ladder = newNode;
        return;
    }

    newNode->next = *ladder;
    *ladder = newNode;
}

int getLadderHeight(WordNode* ladder) {
    int ladderSize = 0;
    WordNode* currNode = ladder;
    while(currNode!= NULL){
        ladderSize++;
        currNode = currNode->next;
    }
    return ladderSize; 
}

WordNode* copyLadder(WordNode* ladder) {
    WordNode* currNode = ladder;
    WordNode* copy = NULL;
    if(ladder == NULL || currNode == NULL){
        return NULL;
    }

    copy = malloc(sizeof(WordNode));
    copy->myWord = currNode->myWord;
    copy->next = copyLadder(currNode->next);

    return copy;
}

void freeLadder(WordNode* ladder) {
    WordNode* currNode = ladder;
    WordNode* wordToDelete = NULL;
    while(currNode != NULL){
        wordToDelete = currNode;
        currNode = currNode->next;
        free(wordToDelete);
    }
}

void insertLadderAtBack(LadderNode** list, WordNode* newLadder) {
    LadderNode* currNode = *list;
    LadderNode* newNode = malloc(sizeof(LadderNode));
    newNode->topWord = newLadder;
    if(currNode == NULL){
        *list = newNode;
        newNode->next = NULL;
        return;
    }
    
    while(currNode->next != NULL){
        currNode = currNode->next;
    }
    currNode->next = newNode;
    newNode->next = NULL;
}

WordNode* popLadderFromFront(LadderNode** list) {
    if(*list == NULL){
        return NULL;
    }
    LadderNode* nodeToPop = *list;
    WordNode* temp = nodeToPop->topWord;
    *list = (*list)->next;
    free(nodeToPop);
    return temp;
}

void freeLadderList(LadderNode* myList) {
    while(myList != NULL){
        LadderNode* NodeToDelete = myList;
        myList = myList->next;
        freeLadder(NodeToDelete->topWord);
        free(NodeToDelete);
    }
}

WordNode* findShortestWordLadder(char** words, bool* usedWord, int numWords, int wordSize, char* startWord, char* finalWord){
    LadderNode* myList = NULL;
    WordNode* myLadder = NULL;
    int indexOfStartWord = findWord(words, startWord, 0, numWords-1);
    usedWord[indexOfStartWord] = true;

    insertWordAtFront(&myLadder, startWord);
    insertLadderAtBack(&myList, myLadder);
    char tempWord[50];

    while(myList != NULL){
        myLadder = popLadderFromFront(&myList);
        for(int i =0; i<wordSize; i++){
            for(int j =0; j<26; j++){
                strcpy(tempWord, myLadder->myWord);
                tempWord[i] = 'a' + j;
                int indexOfWord = findWord(words, tempWord, 0, numWords-1);
                
                if(indexOfWord != -1 && !usedWord[indexOfWord]){
                    usedWord[indexOfWord] = true;
                    if(strcmp(tempWord, finalWord) == 0){
                        insertWordAtFront(&myLadder, words[indexOfWord]);
                        freeLadderList(myList);
                        return myLadder;
                    }
                    else{
                        WordNode* nextLadder = copyLadder(myLadder);
                        insertWordAtFront(&nextLadder, words[indexOfWord]);
                        insertLadderAtBack(&myList, nextLadder);
                    }
                }
            }
        }
        freeLadder(myLadder);
    }
    
    freeLadderList(myList);
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


//-----------------------------------------------------
// The primary application is fully provided in main(); 
//  no changes should be made to main()
//-----------------------------------------------------
int main() {
    srand((int)time(0));
    
    int testData = 0;
    bool allTestsPassed = false;
    printf("Testing countWordsOfLength - SMALL\n\n");
    testData = countWordsOfLength("sampleDict.txt", 4);
    if(testData == 4){
        printf("TEST CASE PASSED !!\nExpected 4, got: %d\n\n", testData);
    }
    else{
        printf("TEST CASE FAILED\nExpected 4, got: %d\n\n", testData);
    }
    
    printf("Testing countWordsOfLength - NO WORDS IN DICTIONARY\n\n");
    testData = countWordsOfLength("simple3.txt",10);
    if(testData == 0){
        printf("TEST CASE PASSED !!\nExpected 0, got: %d\n\n", testData);
    }
    else{
        printf("TEST CASE FAILED\nExpected 0, got: %d\n\n", testData);
    }

    printf("Testing countWordsOfLength - LARGE\n\n");
    testData = countWordsOfLength("dictionary.txt", 3);
    if(testData == 962){
        printf("TEST CASE PASSED !!\nExpected 962, got: %d\n\n", testData);
    }
    else{
        printf("TEST CASE FAILED\nExpected 962, got: %d\n\n", testData);
    }

    printf("Testing buildWordArray-SMALL\n\n");
    bool buildWord= false;
     char** words = (char**)malloc(4*sizeof(char*));
    for (int i = 0; i < 4; ++i) {
        words[i] = (char*)malloc((5)*sizeof(char));
    }

    buildWord = buildWordArray("sampleDict.txt", words, 4, 4);
    if(!buildWord){
        printf("TEST CASE FAILED\nExpected TRUE, got: FALSE\nTesting with FILE: sampleDict.txt, numWords: 4, wordSize: 4\n\n");
    }
    else{
        printf("TEST CASE PASSED\nExpected TRUE, got: TRUE\n\n");

    }

    printf("TESTING buildWordArray NO WORDS\n\n");
    buildWord = buildWordArray("simple5.txt", words, 10, 0);
   if(!buildWord){
        printf("TEST CASE PASSED\nExpected TRUE, got: TRUE\n\n");
    }
    else{
        printf("TEST CASE FAILED\nExpected TRUE, got: FALSE\nTesting with FILE: simple5.txt, numWords: 10, wordSize: 0\n\n");

    }
    
    words = malloc(962*sizeof(char*));
    for (int i = 0; i < 962; ++i) {
        words[i] = (char*)malloc((3)*sizeof(char));
    }
    
    printf("TESTING buildWordArray LARGE WORD ARRAY\n\n");
    buildWord = buildWordArray("dictionary.txt", words, 962, 3);
       if(!buildWord){
        printf("TEST CASE FAILED\nExpected TRUE, got: FALSE\nTesting with FILE: dictionary.txt, numWords: 962, wordSize: 3\n\n");
    }
    else{
        printf("TEST CASE PASSED\nExpected TRUE, got: TRUE\n\n");
    }
    
    printf("TESTING findWord - FOUND WORD\n\n");
    words = (char**)malloc(6*sizeof(char*));
    for (int i = 0; i < 6; ++i) {
        words[i] = (char*)malloc((5)*sizeof(char));
    }
    strcpy(words[0], "Anupam");
    strcpy(words[1], "George");
    strcpy(words[2], "Bobbyy");
    strcpy(words[3], "Millyy");
    strcpy(words[4], "Nathan");
    strcpy(words[5], "Mikeyy");
    int index = 0;
    index = findWord(words, "Anupam", 0, 5);
    if(index != 0){
        printf("TEST CASE FAILED\nExpected 0, got: %d\n\n", index);
    }
    else{
        printf("TEST CASE PASSED\nExpected 0, got: %d\n\n", 0);
    }

    printf("TESTING findWord - Wrong Word\n\n");
    index = findWord(words, "Jimmyy", 0, 5);
    if(index != -1){
        printf("TEST CASE FAILED\nExpected -1, got: %d\n\n", index);
    }
    else{
        printf("TEST CASE PASSED\nExpected -1, got: %d\n\n", index);
    }


    printf("TESTING insertWordAtFront - Empty List\n\n");
   
    WordNode** testLadder;
    
    char* wordToInsert1 = "Priya";
    
    insertWordAtFront(testLadder, wordToInsert1);

    int size = 0;
    size = getLadderHeight(*testLadder);
    if(size != 1){
        printf("TEST CASE FAILED\nExpected 1, got: %d\n\n", size);
    }
    else{
        printf("TEST CASE PASSED\nExpected 1, got: %d\n\n", size);
    }
    
    printf("TESTING insertWordAtFront - Non-Empty List\n\n");
    char* wordToInsert2 = "Connor";
    char* wordToInsert3 = "Khabib";
    char* wordToInsert4 = "Dana";
    char* wordToInsert5 = "Joe";

    insertWordAtFront(testLadder, wordToInsert2);
    insertWordAtFront(testLadder, wordToInsert3);
    insertWordAtFront(testLadder, wordToInsert4);
    insertWordAtFront(testLadder, wordToInsert5);
    size = getLadderHeight(*testLadder);
    if(size != 5){
        printf("TEST CASE FAILED\nExpected 5, got: %d\n\n", size);
    }
    else{
        printf("TEST CASE PASSED\nExpected 5, got: %d\n\n", size);
    }


    printf("TESTING COPY LADDER -EMPTY\n\n");
    WordNode* emptyLadder;
    WordNode* newLadder = copyLadder(emptyLadder);
    if(newLadder != NULL){
        printf("TEST CASE FAILED, Ladder Empty so new ladder should be NULL\n\n");
    }
    else{
        printf("TEST CASE PASSED!! \n\n");
    } 
    
     newLadder = copyLadder(*testLadder);
    WordNode* temp1 = *testLadder;
    WordNode* temp2 = newLadder;
    printf("TESTING COPY LADDER -NON EMPTY LIST\n\n");
    while(temp1 != NULL && temp2 != NULL){
    if(strcmp(temp1->myWord, temp2->myWord) != 0){
            printf("TEST CASE FAILED, Expected: %s, Got %s \n\n", temp1->myWord, temp2->myWord);
            break;
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    printf("TEST CASE PASSED!!\n\n");


    printf("TESTING insertLadderAtBack - EMPTY ADJACENCY LIST \n\n");
    LadderNode* testList = NULL;
    insertLadderAtBack(&testList, *testLadder);
   
    int count  = 0;
    LadderNode* currNode = testList;
    while(currNode != NULL){
        count++;
        currNode = currNode->next;
    }
    if(count !=1){
        printf("TEST CASE FAILED, Expected: 1, Got: %d\n\n", count);
    }
    else{
        printf("TEST CASE PASSED !!!\n\n");
    }

    printf("TESTING insertLadderAtBack - INSERTING MULTIPLE LADDERS INTO LIST \n\n");
    insertLadderAtBack(&testList, *testLadder);
    insertLadderAtBack(&testList, *testLadder);
    insertLadderAtBack(&testList, *testLadder);
    insertLadderAtBack(&testList, *testLadder);
    insertLadderAtBack(&testList, *testLadder);
    currNode = testList;
    while(currNode != NULL){
        count++;
        currNode = currNode->next;
    }
    if(count != 7){
        printf("TEST CASE FAILED, Expected: 6, Got: %d\n\n", count);
    }
    else{
        printf("TEST CASE PASSED !!!\n\n");
    }

    printf("TESTING popLadderFromFront - EMPTY ADJACENCY LIST\n\n");
    LadderNode* popLadder = NULL;
    WordNode* Node1 = popLadderFromFront(&popLadder);
    if(Node1!= NULL){
        printf("TEST CASE FAILED - Popped From Empty Ladder, Node1 Should Be NULL\n\n");
    }
    else{
        printf("TEST CASE PASSED!!\n\n");
    }

    printf("TESTING popLadderFromFront - NON EMPTY ADJACENCY LIST\n\n");
    insertLadderAtBack(&popLadder, *testLadder);
    insertLadderAtBack(&popLadder, *testLadder);
    insertLadderAtBack(&popLadder, *testLadder);
    Node1 = popLadderFromFront(&popLadder);
    if(strcmp(Node1->myWord, (*testLadder)->myWord) != 0){
        printf("TEST CASE FAILED, Expected, Priya, Got %s\n\n", Node1->myWord);
    }
    else{
        printf("TEST CASE PASSED!! \n\n");
    }

    printf("TESTING FIND SHORTEST LADDER - SMALL FILE \n\n");
    int testWordSize = 3;
    words = (char**)malloc(7*sizeof(char*));
    for (int i = 0; i < 7; ++i) {
        words[i] = (char*)malloc((4)*sizeof(char));
    }

    bool status = buildWordArray("sampleDict.txt",words,7,3);
    bool* usedWord = (bool*)malloc(7*sizeof(bool));
    for (int i = 0; i < 7; ++i) {
        usedWord[i] = false;
    }

    char startWord[] = "tap";
    char finalWord[] = "tar";

    WordNode* myShortestLadder = findShortestWordLadder(words, usedWord, 7, 3, startWord, finalWord);
    if(getLadderHeight(myShortestLadder) != 2){
        printf("TEST CASE FAILED, Expected 2, Got %d : FILE: sampleDict.txt\n\n",getLadderHeight(myShortestLadder));
    }
    else{
        printf("TEST CASE PASSED!!!\n\n");
    }


    printf("TESTING FIND SHORTEST LADDER - LARGE FILE FILE \n\n");
    testWordSize = 4;
    words = (char**)malloc(3862*sizeof(char*));
    for (int i = 0; i < 3862; ++i) {
        words[i] = (char*)malloc((4)*sizeof(char));
    }
    status = buildWordArray("dictionary.txt",words,3862,4);
    usedWord = (bool*)malloc(2862*sizeof(bool));
    for (int i = 0; i < 3862; ++i) {
        usedWord[i] = false;
    }

    char startWord1[] = "hope";
    char finalWord2[] = "shop";

    myShortestLadder = findShortestWordLadder(words, usedWord, 3862, 4, startWord1, finalWord2);
    if(getLadderHeight(myShortestLadder) != 7){
        printf("TEST CASE FAILED, Expected 7, Got %d\n\n",getLadderHeight(myShortestLadder));
    }
    else{
        printf("TEST CASE PASSED!!!\n\n");
    }

    printf("TESTING getLadderHeight EMPTY LIST\n\n");

    WordNode* testLadderHeight = NULL;

    size = 0;
    size = getLadderHeight(testLadderHeight);
    if(size != 0){
        printf("TEST CASE FAILED\nExpected 0, got: %d\n\n", size);
    }
    else{
        printf("TEST CASE PASSED!!!\nExpected 0, got: %d\n\n", size);
    }
    
    printf("TESTING getLadderHeight- Non-Empty List\n\n");
    char* word1 = "Priya";
    char* word2 = "Connor";
    char* word3 = "Khabib";
    char* word4 = "Dana";
    char* word5 = "Joe";
    
    insertWordAtFront(&testLadderHeight, word1);
    insertWordAtFront(&testLadderHeight, word2);
    insertWordAtFront(&testLadderHeight, word3);
    insertWordAtFront(&testLadderHeight, word4);
    insertWordAtFront(&testLadderHeight, word5);
    size = getLadderHeight(testLadderHeight);

    if(size != 5){
        printf("TEST CASE FAILED\nExpected 5, got: %d\n\n", size);
    }
    else{
        printf("TEST CASE PASSED!!!\nExpected 5, got: %d\n\n", size);
    }

    return 0;
}