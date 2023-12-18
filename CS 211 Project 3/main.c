#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pattern_struct {
  char *pat;   // string pattern - exs: "hello", "-ell-", "-----"
  int count;   // frequency of pattern in the current word list
  int changes; // number of occurences of new letter in this pattern
} Pattern;

//-------------------------------------------------------------------
// TODO - Task II: write addWord() function, which adds a new word to
//      a dynamic heap-allocated array of C-strings; heap-space must
//      be allocated for the new word inside this function, then copy
//      the chars from newWord to the newly allocated heap-space; if
//      adding the new word pushes numWords above maxWords, then
//      realloate the words array with double the capacity
//      parameters:
//          char*** words - array of C-strings passed-by-pointer
//              note: *words is an array of pointers
//                    **words is an array of chars
//                    ***words is a char
//                    (*words)[0] is the 1st C-string in the array
//                    (*words)[1] is the 2nd C-string in the array
//                    (*words)[0][0] is 1st char of 1st C-string
//                    (*words)[1][2] is 3rd char of 2nd C-string
//                    etc.
//          int* numWords - current # of words in *words array
//               note: numWords will increase by 1 here,
//                     so it is passed-by-pointer
//          int* maxWords - current capacity of *words array
//               note: maxWords may increase by x2 here,
//                     so it is passed-by-pointer
//          char* newWord - C-string word to be added to words
//               note: newWord is a C-string, automatically a pointer
//-------------------------------------------------------------------
void addWord(char ***words, int *numWords, int *maxWords, char *newWord) {
  int arrayLenNew = 0;
  arrayLenNew = *numWords + 1;

  if (arrayLenNew > *maxWords) {
    char** temp1 = malloc(sizeof(char*) * 2 * (*maxWords));
    for (int i = 0; i < *numWords; i++) {
      temp1[i] = (*words)[i];
    }

    temp1[*numWords] = malloc(sizeof(char) * (strlen(newWord) + 1));
    strcpy(temp1[*numWords], newWord);
    
    free(*words);
    *words = temp1;
    temp1 = NULL;
    *maxWords *= 2;
  }

  else {
    (*words)[*numWords] = malloc(sizeof(char) * (strlen(newWord) + 1));
    strcpy((*words)[*numWords], newWord);
  }
  (*numWords)++;
}

//-------------------------------------------------------------------
// TODO - Task V: write the strNumMods() function, which
//      returns count of character differences between two strings;
//      includes extra characters in longer string if different lengths
// Exs: str1 = magic, str2 = magic, returns 0
//      str1 = wands, str2 = wants, returns 1
//      str1 = magic, str2 = wands, returns 4
//      str1 = magic, str2 = mag, returns 2
//      str1 = magic, str2 = magicwand, returns 4
//      str1 = magic, str2 = darkmagic, returns 8
//-------------------------------------------------------------------
int strNumMods(char *str1, char *str2) {
  int count = 0;
  int len1 = strlen(str1);
  int len2 = strlen(str2);
  if (len1 > len2) {
    for (int i = 0; i < len1; i++) {
      if (str1[i] != str2[i]) {
        count++;
      }
    }
  } else if (len2 > len1) {
    for (int i = 0; i < len2; i++) {
      if (str1[i] != str2[i]) {
        count++;
      }
    }
  } else {
    for (int i = 0; i < len1; i++) {
      if (str1[i] != str2[i]) {
        count++;
      }
    }
  }

  return count; // modify this
}

//-------------------------------------------------------------------
// TODO - Task VI: write the strDiffInd() function, which
//      returns index of the character where two strings first differ, &
//      returns strlen(str1) = strlen(str2) if no differences
// Exs: str1 = magic, str2 = magic, returns 5
//      str1 = wands, str2 = wants, returns 3
//      str1 = magic, str2 = wands, returns 0
//      str1 = magic, str2 = mag, returns 3
//      str1 = magic, str2 = magicwand, returns 5
//      str1 = magic, str2 = darkmagic, returns 0
//-------------------------------------------------------------------
int strDiffInd(char *str1, char *str2) {
  int count = 0;
  int len1 = strlen(str1);
  int len2 = strlen(str2);
  if (strcmp(str1, str2) == 0) {
    return len1;
  }
  if (len1 > len2) {
    for (int i = 0; i < len1; i++) {
      if (str1[i] != str2[i]) {
        return i;
      }
    }
  } else if (len2 > len1) {
    for (int i = 0; i < len2; i++) {
      if (str1[i] != str2[i]) {
        return i;
      }
    }
  } else {
    for (int i = 0; i < len1; i++) {
      if (str1[i] != str2[i]) {
        return i;
      }
    }
  }

  return 0;
  // return count; //modify this
}

// void checkLetterGuess(char letter){
//   if(isalpha(letter)){
//     if(toupper(letter)){
//       printf("Invalid letter...\n");
//     }
//   }
// }

int main(int argc, char *argv[]) {

  printf("Welcome to the (Evil) Word Guessing Game!\n\n");

  bool solved = false;
  bool statsMode = false;
  bool wordListMode = false;
  bool letterListMode = false;
  bool patternListMode = false;
  bool verboseMode = false;
  bool flag = false;

  int wordSize = 5;
  int numGuesses = 26;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-n") == 0) {
      if (i == argc - 1) {
        printf("Dictionary has no words of length [wordSize].\n");
        printf("Terminating program...");
        // wordSize = 5;
        return 0;
      } else {
        wordSize = atoi(argv[i + 1]);
        i++;
        if (wordSize < 2) {
          printf("Invalid word size.\n");
          printf("Terminating program...");
          return 0;
        }
      }
    }

    else if (strcmp(argv[i], "-g") == 0) {
      numGuesses = atoi(argv[i + 1]);
      i++;
      if (numGuesses < 0) {
        printf("Invalid number of guesses.\n");
        printf("Terminating program...");
        return 0;
      }
    }

    else if (strcmp(argv[i], "-s") == 0) {
      statsMode = true;
    }

    else if (strcmp(argv[i], "-w") == 0) {
      wordListMode = true;
    }

    else if (strcmp(argv[i], "-l") == 0) {
      letterListMode = true;
    }

    else if (strcmp(argv[i], "-p") == 0) {
      patternListMode = true;
    }

    else if (strcmp(argv[i], "-v") == 0) {
      verboseMode = true;
      statsMode = true;
      wordListMode = true;
      letterListMode = true;
      patternListMode = true;
    } else {
      flag = true;
    }
  }

  if (flag) {
    printf("Invalid command-line argument.\n");
    printf("Terminating program...");
    return 0;
  }

  printf("Game Settings:\n");
  printf("  Word Size = %d\n", wordSize);
  printf("  Number of Guesses = %d\n", numGuesses);
  printf("  View Stats Mode = ");

  if (!statsMode) {
    printf("OFF\n");
  } else {
    printf("ON\n");
  }

  printf("  View Word List Mode = ");
  if (!wordListMode) {
    printf("OFF\n");
  } else {
    printf("ON\n");
  }

  printf("  View Letter List Mode = ");
  if (!letterListMode) {
    printf("OFF\n");
  } else {
    printf("ON\n");
  }

  printf("  View Pattern List Mode = ");
  if (!patternListMode) {
    printf("OFF\n");
  } else {
    printf("ON\n");
  }

  //-------------------------------------------------------------------
  // TODO - Task I: handle command-line arguments
  // command-line arguments:
  //  [-n wordSize] = sets number of characters in word to be guessed;
  //                  if dictionary has no words of length wordSize,
  //                  then print:
  //                    "Dictionary has no words of length [wordSize]."
  //                    "Terminating program..."
  //                  default wordSize = 5
  // [-g numGuesses] = sets number of unsuccessful letter guesses;
  //                   numGuesses must be a positive integer,
  //                   otherwise print
  //                     "Invalid number of guesses."
  //                     "Terminating program..."
  //                   default numGuesses = 26
  //                   (note: 26 guesses guarantees player can win)
  // [-s] = stats mode, which includes printing of dictionary
  //                    statistics AND number of possible words
  //                    remaining during gameplay.
  //                    default is OFF
  // [-w] = word list mode, which includes a print out of the full
  //                        list of possible words before every guess.
  //                        default is OFF
  // [-l] = letter list mode, which prints out a list of previously
  //                          guessed letters before each new guess
  //                          default is OFF
  // [-p] = pattern list mode, which prints out a list of all patterns
  //                           in the word list, together with the
  //                           frequency of each pattern and the
  //                           number of changes in the pattern due to
  //                           the current guess
  //                           default is OFF
  // [-v] = verbose mode, which turns ON stats mode, word list mode,
  //                      letter list mode, AND pattern list mode
  // [-x] = extension mode, which is an optional extra credit
  //                        extension doing something interesting with
  //                        the evil word game, e.g. optimizing the
  //                        algorithm to predict future guesses
  //-------------------------------------------------------------------

  //-------------------------------------------------------------------
  // TODO - Task III: file-read the word list from dictionary.txt,
  //                  storing only words of length set by wordSize
  //                  (a command-line argument) in a dynamically
  //                  growing heap-allocated array of C-strings:
  //                      - the word list should be a dynamic array of
  //                        pointers, initially with maximum size 4,
  //                        doubling in maximum size whenever more
  //                        space is needed
  //                      - each element of the word list array should
  //                        point to a heap-allocated C-string that
  //                        can store a word containing exactly
  //                        wordSize lower-case letters
  //-------------------------------------------------------------------
  char largestWord[100];
  int largestWordLen;
  int wordCount = 0;
  int wordArrCount = 0;
  int capacity = 4;
  int maxCapacity = 0;
  char fileWord[100];
  int maxLen = 0;
  char** wordList = (char**)malloc(capacity * sizeof(char*));
  FILE *myfile = NULL;


  myfile = fopen("dictionary.txt", "r");


  while (!feof(myfile)) {
    fscanf(myfile, "%s", fileWord);
    // wordCount++;
    if (strlen(fileWord) > maxLen) {
      maxLen = strlen(fileWord);
      strcpy(largestWord, fileWord);
    }

    if (strlen(fileWord) == wordSize) {
      wordArrCount++;
      addWord(&wordList, &maxCapacity, &capacity, fileWord);
    }
    wordCount++;
  }

  fclose(myfile);

  largestWordLen = strlen(largestWord);
  if (statsMode) {
    printf("The dictionary contains %d words total.\n", wordCount);
    printf("The longest word %s has %d chars.\n", largestWord, largestWordLen);
    printf("The dictionary contains %d words of length %d.\n", wordArrCount,
           wordSize);
    printf("Max size of the dynamic words array is %d.", capacity);
  }

  if (wordListMode) {
    printf("Words of length %d:\n", wordSize);
    if (wordArrCount != 0) {
      for (int i = 0; i < maxCapacity; i++) {
        printf("  %s\n", wordList[i]);
      }
    } 
    else {
      printf("Dictionary has no words of length %d.\n", wordSize);
      printf("Terminating program...");
      return 0;
    }
  }

  int updatedNumWords = 0;
  bool solve = false;
  int letterIndex = 0;
  char finalPattern[50];
  for (int i = 0; i < wordSize; i++) {
    finalPattern[i] = '-';
  }
  finalPattern[wordSize] = '\0';

  printf("The word pattern is: %s\n", finalPattern);
  printf("\n");

  int letterChanges = 0;
  char Guess;
  bool letterGuess[26];
  for(int i =0; i<26; i++){
    letterGuess[i] = false;
  }
  bool isInvalid = false;

  int maxPatternSize = 4;
  Pattern *pattern = malloc(sizeof(Pattern) * maxPatternSize);
  char guessArray[wordSize+1];
  int numPatterns = 0;
  bool newPattern = true;
  bool notCorrectLetter = true;
  int pointer = 0;

  while (numGuesses != 0 && !solve) {
    do {
      if (!isInvalid) {
        printf("Number of guesses remaining: %d\n", numGuesses);
      }

      if (letterListMode == true) {
        printf("Previously guessed letters: ");
        for (int i = 0; i < 26; i++) {
          int dispLetter = i;
          if (letterGuess[i]) {
            int correctLetter = dispLetter + 'a';
            printf("%c ", correctLetter);
          }
        }
        printf("\n");
      }

      printf("Guess a letter (# to end game): ");
      scanf(" %c", &Guess);
      letterIndex = Guess - 'a';
      if (Guess == '#') {
        printf("Terminating game...\n");
        return 0;
      }

      else if (letterIndex < 0 || letterIndex > 25) {
        printf("Invalid letter...\n");
        isInvalid = true;
      } else if (letterGuess[letterIndex] == true) {
        printf("Letter previously guessed...\n");
        isInvalid = true;
      }

    } while ((letterIndex < 0 || letterIndex > 25) ||
             (letterGuess[letterIndex] == true));
    pointer = 0;
    isInvalid = false;

    letterGuess[letterIndex] = true;
    for (int i = 0; i < wordArrCount; i++) {
      letterChanges = 0;
      strcpy(guessArray, finalPattern);
      for (int j = 0; j < strlen(wordList[i]); j++) {
        if (wordList[i][j] == Guess) {
          guessArray[j] = Guess;
          letterChanges++;
        }
      }

      newPattern = true;
      for (int k = 0; k < numPatterns; k++) {
        newPattern = true;

        if (numPatterns > 0) {
          if (strcmp(pattern[k].pat, guessArray) == 0) {
            pattern[k].count++;
            pattern[k].changes = letterChanges;
            newPattern = false;
            break;
          }
        }
      }

      if (newPattern) {
        int tempArrLen = numPatterns + 1;
        if (tempArrLen > maxPatternSize) {
          maxPatternSize *= 2;
          Pattern *temp = malloc(sizeof(Pattern) * maxPatternSize);
          for (int m = 0; m < numPatterns; m++) {
            temp[m] = pattern[m];
          }
          temp[numPatterns].pat = malloc(sizeof(char) * (wordSize + 1));
          strcpy(temp[numPatterns].pat, guessArray);
          temp[numPatterns].count = 0;
          free(pattern);
          pattern = temp;
          temp = NULL;
        }

        else {
          pattern[numPatterns].pat = malloc(sizeof(char) * (wordSize + 1));
          strcpy(pattern[numPatterns].pat, guessArray);
          pattern[numPatterns].count = 0;
        }
        pattern[numPatterns].count++;
        pattern[numPatterns].changes = letterChanges;
        numPatterns++;
      }
    }
    if (patternListMode == true) {
      printf("All patterns for letter %c: \n", Guess);
      for (int i = 0; i < numPatterns; i++) {
        printf("  %s count = %d changes = %d\n", pattern[i].pat,
               pattern[i].count, pattern[i].changes);
      }
    }

    int maxCount = pattern[0].count;
    //int maxCount =0;

    int maxIndex = 0;
    for (int i = 1; i < numPatterns; i++) {
      if (pattern[i].count > maxCount) {
        maxCount = pattern[i].count;
        maxIndex = i;
      } else if (pattern[i].count == maxCount) {
        if (pattern[i].changes < pattern[maxIndex].changes) {
          maxIndex = i;
        } else if (pattern[i].changes == pattern[maxIndex].changes) {
          int tempIndex = 0;
          char *tempFinalWord = finalPattern;
          char *currentPattern = pattern[i].pat;
          char *maxPattern = pattern[maxIndex].pat;
          while (strDiffInd(tempFinalWord, currentPattern) ==
                 strDiffInd(tempFinalWord, maxPattern)) {
            tempIndex = strDiffInd(tempFinalWord, currentPattern);
            tempFinalWord = &(finalPattern[tempIndex + 1]);

            currentPattern = &(pattern[i].pat[tempIndex + 1]);

            maxPattern = &(pattern[maxIndex].pat[tempIndex + 1]);
          }
          if (strDiffInd(tempFinalWord, currentPattern) <
              strDiffInd(tempFinalWord, maxPattern)) {
            maxIndex = i;
          }
        }
      }
    }

    char oldFinalWord[50];
    char tempStr[50];
    int index = 0;

    strcpy(oldFinalWord, finalPattern);
    strcpy(finalPattern, pattern[maxIndex].pat);

    char** updatedArray =
        (char**)malloc(sizeof(char *) * pattern[maxIndex].count);

    for (int i = 0; i < wordArrCount; i++) {
      strcpy(tempStr, oldFinalWord);
      for (int j = 0; j < strlen(wordList[i]); j++) {
        if (wordList[i][j] == Guess) {
          tempStr[j] = Guess;
        }
      }
      if (strcmp(tempStr, finalPattern) == 0) {
        updatedArray[index] = wordList[i];
        index++;
      } 
      else {
        free(wordList[i]);
      }
    }
    free(wordList);
    wordList = updatedArray;
    wordArrCount = index;
    
    if (pattern[maxIndex].changes != 0) {
      printf("\nGood guess! The word has at least one %c.\n", Guess);
    } else {
      printf("\nOops, there are no %c's. You used a guess.\n", Guess);
      numGuesses--;
    }
    if (statsMode == true) {
      printf("Number of possible words remaining: %d\n", index);
    }

    if (wordListMode == true) {
      printf("Possible words are now:\n");
      for (int i = 0; i < index; i++) {
        printf("  %s\n", updatedArray[i]);
      }
    }

    printf("The word pattern is: %s\n\n", finalPattern);

    if (strchr(finalPattern, '-') == NULL) {
      printf("You solved the word!\n");
      printf("The word is: %s\n", finalPattern);
      printf("Game over.\n");
      solved = true;
      break;
    }

    if (numGuesses == 0) {
      printf("\nYou ran out of guesses and did not solve the word.\n");
      printf("The word is: %s\n", wordList[0]);
      printf("Game over.\n");
    }

    for (int i = 0; i < numPatterns; i++) {
      free(pattern[i].pat);
    }

    free(pattern);
    
    maxPatternSize = 4;
    
    pattern = malloc(sizeof(Pattern) * maxPatternSize);

    numPatterns = 0;
    newPattern = true;

  
    updatedArray = NULL;
    maxCount = 0;
  }
  
  for (int i = 0; i < numPatterns; i++) {
    free(pattern[i].pat);
  }
  free(pattern);

  for (int i = 0; i < wordArrCount; i++) {
    free(wordList[i]);
  }
  
  free(wordList);
  return 0;
}


