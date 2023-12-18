/*
Name: Anupam Sai Sistla
UIN: 659340448
NetID: Asistl2
Project - 2: Food Web Analysis With Dynamic Memory 
The goal of this project is to make a food web, similar to the one in our environment. It maps organisms to their various prey and vice-versa. It displays important information about the organisms in the web such as the names of the producers and the vore types. The application is also able to completely remove an organism from the ecosystem if it goes extinct. The technical functionalities of the project include: Dynamic Memory Allocation, Structs, Arrays and Pass By Reference Variables
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Org_struct { //struct of organisms, with name, prey array and number of prey
    char name[20]; 
    int* prey; //dynamic array of indices  
    int numPrey;
} Org;


void buildWeb(Org* web, int numOrg, int predInd, int preyInd){//function to build and allocate memory for web, through organisms entered by user
  if(web[predInd].numPrey == 0){ //checks the number of prey at the predator index of the web array
    int* temp2 = malloc(sizeof(int)); //malloc new memory for 
    temp2[0] = preyInd; //set prey index in the predators prey arry
    web[predInd].prey = temp2; //change web pointer to point to new array
    web[predInd].numPrey +=1; //increment numPrey by 1
  }
  else{
    int* temp1 = malloc((web[predInd].numPrey+1)*sizeof(int)); //create new array with one space extra
    for(int i= 0; i<web[predInd].numPrey; i++){
      temp1[i] = web[predInd].prey[i]; //copy all array elements from old array to new array
    }
    temp1[web[predInd].numPrey] = preyInd; //set prey index in the new array
    free(web[predInd].prey); //free the pointer to old array
    web[predInd].prey = temp1; //change web pointer to point to new array
    web[predInd].numPrey +=1; //increment numPrey by one to account for new prey
  }
}

void printWeb(Org* web, int numOrg){ //function to print the web
  for(int i =0; i<numOrg; i++){//loop through web
    if(web[i].numPrey == 0){ //if prey = zero, output the predator
      printf("  %s\n", web[i].name);
    }
    else{
      printf("  %s", web[i].name); //output predator
      for(int j =0 ; j<web[i].numPrey; j++){ //loop through predators prey array and print prey
        if(j>0){
          printf(", %s", web[web[i].prey[j]].name);
        }
        else{
        printf(" eats %s", web[web[i].prey[j]].name);
        }
      }
      printf("\n");
    }
  }
}

void apexPredator(Org* web, int numOrgs){ //finds the apex predator in the web
  int tempIndex; // store temporary index
  char apexPredator[20];
  int count;
  int countForArr = 0;
  for(int i =0; i<numOrgs;i++){ //loop through web
    tempIndex = i; //pick an index and store in temporary index
    bool isApex = true; //check if apex is found
    for(int j =0; j<numOrgs; j++){ //loop through web again
      for(int k =0; k<web[j].numPrey; k++){ //loop through organisms prey array
        if(tempIndex != web[j].prey[k]){ //check if the predator occurs in anyother predators prey array.
          continue;
        }
        else{ //if predator found, set isApex to false and break to continue iteration
          isApex = false;
          break;
        }
    }
    if(isApex == false){ //break if apex is not found
      break;
    }  
  }
  if(isApex == true){ //if apex is found print the apex predator
    printf("  %s\n", web[i].name);
    }
  }
}

void producers(Org* web, int numOrgs){ //Function to find the producers in the web
  for(int i =0; i<numOrgs; i++){//loop through web
    if(web[i].numPrey ==0){ //if the organism has no prey, it is a producer
      printf("  %s\n", web[i].name); //print producer
    }
  }
}

void mostFlexibleEaters(Org* web, int numOrgs){ //function to organims that eat the most organisms
  int max = web[0].numPrey; //set max to first element in web
  for(int i =0; i<numOrgs; i++){ //loop through web
    if(web[i].numPrey > max){
      max = web[i].numPrey; //update max if larger numPrey is found
    }
  }
  for(int i =0; i<numOrgs; i++){
    if(web[i].numPrey == max){//find the organism with the largest number of prey i.e., the most flexible eater
      printf("  %s\n", web[i].name);
    }
  }
}

void tastiestFood(Org* web, int numOrgs){//Function to find the organism that is eaten the most
  char names[numOrgs][20]; //stoe name of an organism per loop iteration->allows using parallel arrays to map an organisms name to its occurance
  int occurances[numOrgs]; //stores occurances of organisms in other organisms prey array
  int count;
  int tempIndex;
  for(int i =0; i<numOrgs; i++){
    count = 0;
    strcpy(names[i], web[i].name); //copy name of organism in web
    tempIndex =i; //get index of the organism
    for(int j =0; j<numOrgs; j++){ //loop through web
      for(int k =0; k<web[j].numPrey; k++){ //loop through an organisms prey array
        if(tempIndex == web[j].prey[k]){ //check if the organism occurs in another organisms prey array
          count++;
        }
      }
    }
    occurances[i] = count; //store the number of occurances
  }
  int max = occurances[0]; //store the first element as max
  for(int i=0; i<numOrgs; i++){ //loop through the occurances array 
    if(occurances[i] > max){ //find the new max
      max = occurances[i];
    }
  }
  for(int i =0; i<numOrgs; i++){ //loop to find the organism that occurs the most number of times
    if(occurances[i] == max){
      printf("  %s\n", names[i]); //output the name of the organism that occurs the most times
    }
  }
  
}

void foodWebHeights(Org* web, int numOrgs){ //function to find the heights of all the elements in the web
  int* heights = malloc(numOrgs*sizeof(int)); //malloc new memory for heights of all organisms
  for(int i =0; i<numOrgs; i++){ //set all heights to zero
    heights[i] = 0;
  }
  bool changes = true; //checks to see if changes were made to the organisms height
  int index =0;
  int updatedHeight = 0;
  while(changes){ //assume changes need to be made
    changes = false; //set changes to false 
    for(int i =0; i<numOrgs; i++){ //loop through web
      int maxHeight = -1; //set the maximum height to -1 for easy readability
      for(int j =0; j<web[i].numPrey; j++){//loop through an organisms prey array
        index = web[i].prey[j]; //set index to be the index of an organism in the prey array
        if(heights[index] > maxHeight){ //find the maximum height in the organisms prey array
          maxHeight = heights[index];
        }
      }
      if(maxHeight+1 != heights[i]){
        heights[i] = maxHeight +1; //set height to one more than maximum prey height
        changes = true; //update to change has been made
      }
      else{ //if no change, then continue
        continue;
      }
    }
  }
  for(int i =0; i<numOrgs; i++){ //looop through both web and heights in a parallel array like format to display name and associated height
    printf("  %s: %i\n", web[i].name, heights[i]);
  }
  free(heights); //free allocated memory for heights
}

void voreTypes(Org* web, int numOrgs){ //function to classify organisms based on what they eat
  printf("  Producers:\n");
  for(int i =0; i<numOrgs ; i++){
    if(web[i].numPrey == 0){ //Producers are those who don't eat anything
      printf("    %s\n", web[i].name);
    }
  }

  printf("  Herbivores:\n");
  bool isHerbivore;
  bool Carnivore;
  for(int i =0; i<numOrgs; i++){
    isHerbivore = false;
    Carnivore = false;
    for(int j =0; j<web[i].numPrey; j++){
      if(web[web[i].prey[j]].numPrey == 0){ //if a producer occurs in their prey flag as true
        isHerbivore = true;
      }
      else{//flag carnivore as true if organism eats non-producers
        Carnivore = true;
      }
    }
    if(isHerbivore && !Carnivore){ //if the organism only eats producers it is a herbivore 
      printf("    %s\n", web[i].name);
    }
  }
  
  printf("  Omnivores:\n");
  bool Herbivore, isCarnivore;
  for(int i =0; i<numOrgs; i++){ //loop through the web 
    Herbivore = false;
    isCarnivore = false;
    for(int j = 0; j < web[i].numPrey; j++){ //loop through the organisms prey array
      if(web[web[i].prey[j]].numPrey == 0){ //check if a producer occurs in the organisms prey
        Herbivore = true;
      }
      else{ //check if the organism eats non producers
        isCarnivore = true;
      }
    }
    
    if(Herbivore && isCarnivore){ //if it eats producers and non producers it is an omnivore 
      printf("    %s\n", web[i].name);
    }
  }

  printf("  Carnivores:\n");
  for(int i =0; i<numOrgs; i++){
    bool Carnivore = true;
    if(web[i].numPrey > 0){ //makes sure that organism is not a producer
      for(int j =0; j<web[i].numPrey; j++){ //loop through organisms prey array
        if(web[web[i].prey[j]].numPrey == 0){ //if a producer occurs in the prey then it is an omnivore/herbivore and not a carnivore
          Carnivore = false;
          break;
        }
      }

      if(Carnivore == true){ //if all the organisms prey are non-producers then it is a carnivore
          printf("    %s\n", web[i].name);
      }
    }
  }
}

void extinction(Org** web, int* numOrgs, int index) { //function to remove organism from web if it goes extinct
  int temp =0;
  if(*numOrgs == 1){ //Edge case-1: if there is only one organism in the web
    free((*web)[index].prey); //free the associated prey array
    free(*web); //free the web itself
    *web = NULL;
    *numOrgs = 0; //update the number of organisms
    return;
  }

  free((*web)[index].prey); //free the organism's prey array at the web[index]
  Org* pointerToWeb = malloc((*numOrgs-1)*sizeof(Org)); // allocate new memory for web with numOrgs-1 to take in account extinct organism
  for(int i =0; i<*numOrgs; i++){ //loop through web
    if(i == index){ //skip extinct organism
      continue;
    }
    else{
      pointerToWeb[temp] = (*web)[i]; //copy all elements from old web to new web
      temp++;
    }
  }
  free(*web); //free old pointer to web
  *web = pointerToWeb; //make web point to the new array
  *numOrgs = *numOrgs-1; //update the number of organisms

  int* pointerToPrey; //pointer to allocate new memory for organisms prey array
  for(int i=0; i<*numOrgs; i++){ //loop through the web
    for(int j =0; j<(*web)[i].numPrey; j++){ //loop through the organisms prey array
      if((*web)[i].prey[j] == index){//extinct species encountered in another organisms prey array
        if((*web)[i].numPrey == 1){ //Edge case-2: if the number of prey for organism with the extinct species as its prey only has one prey element
          (*web)[i].prey = NULL; //set prey array to null
          (*web)[i].numPrey--; //decrement the number of prey of that particular organism
        }
        else if((*web)[i].numPrey  > 1){
          pointerToPrey = malloc(((*web)[i].numPrey-1)*sizeof(int)); //allocate new memory for organisms prey array
          temp = 0;
          for(int k =0; k<(*web)[i].numPrey; k++){ 
            if((*web)[i].prey[k] == index){ //skip extinct index
              continue;
            }
            else{
              pointerToPrey[temp] = (*web)[i].prey[k]; //copy all prey elements from old array to new array
              temp++;
            }
          }
        free((*web)[i].prey); //free the old organisms prey array
        (*web)[i].prey = pointerToPrey; //organisms prey array pointer to point to the new array
        (*web)[i].numPrey--; //decrement number of prey 
        }
      }
    }
  }
  
  for(int i =0; i<*numOrgs; i++){//loop throught the web
    for(int j =0; j<(*web)[i].numPrey; j++){ //loop through an organisms prey array
      if((*web)[i].prey[j] > index){ //for elements with index greater than extinct index
        (*web)[i].prey[j]--; //decrement the index to account for shifting
      }
    }
  }
}

int main(void) {
    int numOrgs;
    printf("Welcome to the Food Web Application\n");
    printf("--------------------------------\n");
    printf("Enter number of organisms:\n");
    scanf("%d",&numOrgs);

    Org* web = NULL;
    if(numOrgs > 0) { //Do not malloc an empty array, leave it pointing to NULL
        web = (Org*)malloc(numOrgs*sizeof(Org));
    }
    
    printf("Enter names for %d organisms:\n", numOrgs);
    for (int i = 0; i < numOrgs; ++i) {
        scanf("%s",web[i].name);
        web[i].prey = NULL;
        web[i].numPrey = 0;
    }
    printf("Enter number of predator/prey relations:\n");
    int numRels;
    scanf("%d",&numRels);

    printf("Enter the pair of indices for the %d predator/prey relations\n",numRels);
    printf("the format is [predator index] [prey index]:\n");
    
    int predInd, preyInd;
    for (int i = 0; i < numRels; ++i) {
        scanf("%d %d",&predInd, &preyInd);
        buildWeb(web,numOrgs,predInd,preyInd);
    }
    printf("--------------------------------\n\n");

    printf("Food Web Predators & Prey:\n");
    //print the Food Web Organisms with what they eat (i.e. prey)
    printWeb(web, numOrgs);
    printf("\n");
  
    printf("Apex Predators:\n");
    //identify and print the organisms not eaten by any others
    apexPredator(web, numOrgs);
    printf("\n");

    printf("Producers:\n");
    //identify and print the organisms that eat no other organisms
    producers(web, numOrgs);
    printf("\n");

    printf("Most Flexible Eaters:\n");
    //identity and print the organism(s) with the most prey
    mostFlexibleEaters(web, numOrgs);
  printf("\n");

    printf("Tastiest Food:\n");
    //identity and print organism(s) eaten by the most other organisms
  tastiestFood(web, numOrgs);
    printf("\n");

    printf("Food Web Heights:\n");
    //calculate and print the length of the longest chain from a producer to each organism
    foodWebHeights(web, numOrgs);
    printf("\n");

    printf("Vore Types:\n");
    voreTypes(web, numOrgs);
    // classify all organisms and print each group (producers, herbivores, omnivores, & carnivores)
    printf("\n");

    printf("--------------------------------\n");
    int extInd;
    printf("Enter extinct species index:\n");
    scanf("%d",&extInd);
    printf("Species Extinction: %s\n", web[extInd].name);
    extinction(&web,&numOrgs,extInd); //call extinction function for extinct organism
    printf("--------------------------------\n\n");


    printf("UPDATED Food Web Predators & Prey:\n");
    //print the UPDATED Food Web Organisms with what they eat (i.e. prey), AFTER THE EXTINCTION
    printWeb(web, numOrgs);
    printf("\n");

    printf("UPDATED Apex Predators:\n");
    //AFTER THE EXTINCTION, identify and print the organisms not eaten by any other
    apexPredator(web, numOrgs);
    printf("\n");

    printf("UPDATED Producers:\n");
    //AFTER THE EXTINCTION, identify and print the organisms that eat no other organisms
    producers(web, numOrgs);
    printf("\n");

    printf("UPDATED Most Flexible Eaters:\n");
    //TODO: AFTER THE EXTINCTION, identity and print the organism(s) with the most prey
    mostFlexibleEaters(web, numOrgs);
    printf("\n");

    printf("UPDATED Tastiest Food:\n");
    //AFTER THE EXTINCTION, identity and print organism(s) eaten by the most other organisms
    tastiestFood(web, numOrgs);
    printf("\n");

    printf("UPDATED Food Web Heights:\n");
    //AFTER THE EXTINCTION, calculate and print the length of the longest chain from a producer to each organism
    foodWebHeights(web, numOrgs);
    printf("\n");

    printf("UPDATED Vore Types:\n");
    voreTypes(web, numOrgs);
    //AFTER THE EXTINCTION, classify all organisms and print each group (producers, herbivores, omnivores, & carnivores)
    printf("\n");
    printf("--------------------------------\n");

    for(int i=0; i<numOrgs; i++){
      free((web)[i].prey); //free all malloc memory for prey array 
    }
    free(web); //free the web array itself
    return 0;
}
