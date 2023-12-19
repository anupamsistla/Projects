/// Name: Anupam Sai Sistla
//  UIN: 659340448
//  NetID: Asistl2

// You cannot use any libraries beyond the ones we have given below.
// You must use output streams, file streams, vectors, and strings.
// You are not allowed to use any other containers or objects.
// You may not use structs, pointers, or dynamic memory allocations.

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>

using namespace std;

// Function prototypes for all the glorious function decomposition

void printMenu() //function used to print the main menu
{
    cout << "Library Management Menu" << endl;
    cout << "-----------------------" << endl;
    cout << "A - Add Item To Library" << endl;
    cout << "C - Clear The Library Of All Entries" << endl;
    cout << "D - Display Library Entries" << endl;    
    cout << "I - List Invalid Library Entries" << endl;
    cout << "L - Load Library From File" << endl;    
    cout << "O - Output Library To File" << endl;
    cout << "P - Print Out Checkout Stats" << endl;
    cout << "R - Remove A Library Entry" << endl;      
    cout << "S - Search For A Library Entry" << endl;    
    cout << "X - Exit Program" << endl;
}

void changeStatus(vector<string>& bookStatus){ //function to change the status of the books from an integer value to its relevant string value
  for(int i =0 ; i<bookStatus.size(); i++){
    if(bookStatus.at(i) == "0" || bookStatus.at(i) == "In Library"){
      bookStatus.at(i) = "In Library"; //example of changing integer to a string. As the bookStatus is a vector of string there is no need for stoi() function
    }
    else if(bookStatus.at(i) == "1" || bookStatus.at(i) == "Checked Out"){
      bookStatus.at(i) = "Checked Out";
    }
    else if(bookStatus.at(i) == "2" || bookStatus.at(i) == "On Loan"){
      bookStatus.at(i) = "On Loan";
    }
    else if(bookStatus.at(i) == "3" || bookStatus.at(i) == "Unknown State"){
      bookStatus.at(i) = "Unknown State";
    }
    else{
      bookStatus.at(i) = "Invalid State";
    }
  }
}

bool CheckISBN(string ISBN, vector<string>& bookName, vector<string>& bookISBN, vector<string>& bookStatus){ //function used to check the validity of the ISBN number. This function uses a formula to do this operation
  bool valid = false;
  int temp =0;
  int sum = 0;
  vector<int> integerbookISBN; //load the string ISBN number into an integer vector for ease of calculation
  for(int i =0; i<ISBN.size(); i++){
    if(ISBN.at(i) == '-'){
      continue;
    }
    else{
      temp = ISBN.at(i) - '0';
      integerbookISBN.push_back(temp);
    }
  }
  if(integerbookISBN.size() < 13 || integerbookISBN.size()>13){ //checks if the isbn size is equal to 13, if not return false
    valid = false;
    return valid;
  }
  for(int i =0 ; i<integerbookISBN.size()-1; i++){
    if(i%2 == 1){
      sum = sum + integerbookISBN.at(i)*3;
    }
    else{
      sum = sum + integerbookISBN.at(i);
    }
  }

  int verifySum = 10-(sum%10); //formula for checking validity of ISBN
  if(verifySum == 10){
    verifySum = 0;
  }
  if(verifySum == integerbookISBN.at(integerbookISBN.size()-1)){
    
    valid = true;
  }
  return valid;
}

void ListInvalidEntries(vector<string>& bookName, vector<string>& bookISBN, vector<string>& bookStatus){ //function used to display the invalid entries
  changeStatus(bookStatus);
  bool NoInvalidEntries = false;
  cout << "The Following Library Entries Have Invalid Data" << endl;
  cout << "-----------------------------------------------" << endl;
  if(bookName.size() == 0){ //there is no need to pass through the loop if there are no books loaded into the vector
    cout << "The library has no books.";
  }
  else{
  for(int i =0; i<bookISBN.size(); i++){
    if(bookStatus.at(i) == "Invalid State" || CheckISBN(bookISBN.at(i), bookName, bookISBN, bookStatus) == false){ //used to check the status and the validity of the ISBN
      cout << bookName.at(i) << " --- " << bookISBN.at(i) << " --- " << bookStatus.at(i) << endl;
      NoInvalidEntries = true; //returns true as if there is an element with "Invalid State" as its status or/and has an invalid ISBN.
    }
    }
  }
  if(NoInvalidEntries == false && bookName.size() != 0){ //if there are no books, there are no invalid entries. Also, if the check returns false, there are no invalid entries
      cout << "The library has no invalid entries.";
    }
}

void PrintCheckoutStatus(vector<string>& bookStatus){ //function to print out the statuses of books in loaded/added into the relevant vectors
  changeStatus(bookStatus); //function used to change the statuses of the books before the Checkout Status is displayed
  vector<string> InLib;
  vector<string> CheckOut;
  vector<string> OnLoan;
  vector<string> UnknownState;
  vector<string> Other;
  for(int i =0 ; i< bookStatus.size(); i++){
    if(bookStatus.at(i) == "In Library"){
       InLib.push_back(bookStatus.at(i));
     }
    else if(bookStatus.at(i) == "Checked Out"){
      CheckOut.push_back(bookStatus.at(i));
    }
    else if(bookStatus.at(i) == "On Loan"){
      OnLoan.push_back(bookStatus.at(i));
    }
    else if(bookStatus.at(i) == "Unknown State"){
      UnknownState.push_back(bookStatus.at(i));
    }
    else{
      Other.push_back(bookStatus.at(i));
    }
  }
  //Prints the library statistics to the user
  cout << "Your Current Library's Stats" << endl;
  cout << "----------------------------" << endl;
  cout << "Total Books: " << bookStatus.size() << endl;
  cout << "   In Library: " << InLib.size() << endl;
  cout << "   Checked Out: " << CheckOut.size() << endl;
  cout << "   On Loan: " << OnLoan.size() << endl;
  cout << "   Unknown: " << UnknownState.size() << endl;
  cout << "   Other: " << Other.size() << endl;
}

void loadLibrary(string FileName, vector<string>&bookName, vector<string>&bookISBN, vector<string>& bookStatus){ //function to load the items from the database into the relevant vectors.
 string bookitems; //stores the entire line
 string BookName; //stores the book name from the bookitems string
 string BookISBN; //stroes book ISBN from the bookitems string
 string BookStatus; //stores book status from the book status string
 int count = 0;
 ifstream infile(FileName); //function to access the file stream
 if(!infile.is_open()){ //check to see if the file is open, if the user enters an invalid file name, the computer will prompt the below message
   cout << "Could not find the database file." << endl;
 }
 else{
   while(getline(infile, bookitems)){ //uses to get a line from the file and store in the book items string
     size_t pos1 = 0;
     size_t pos2 = bookitems.find(','); //this finds the first occurance of a comma
     if(pos2 == string::npos){ //if the above comma doesn't exist, it is safe to assume that there is no Book ISBN or Book Status
       BookISBN = "000-0-00-000000-0"; 
       BookName = bookitems;
       BookStatus = "0";
     }
     else{
       BookName = bookitems.substr(pos1, pos2); //if the above check passes, store the Book Name using the substr() function
       pos1 = pos2 +2; //set the first index to the second index and add by two to account for the comma and white space in the string
       pos2 = bookitems.find(',', pos1); //used to find the second occurance of the comma
       if(pos2 == string::npos){ //This is used to account for the scenario where there could be an ISBN but no status
         BookISBN = bookitems.substr(pos1); // in that case, we could make a sub-string of the new updted pos1 to the end of the string
         BookStatus = "0"; // since there is no book status, we can set the status as "0"
       }
       else{ //This is the best case scenario, as it means that there is a book name, book ISBN and book status
         BookISBN = bookitems.substr(pos1, pos2-pos1); //we can use the substr function to get the book ISBN 
         BookStatus = bookitems.substr(pos2+2); // get the book status by using the substr() function from pos2+2 till the end of the string
       }
     }
     bookName.push_back(BookName); //push the book name into its relevant vector
     bookISBN.push_back(BookISBN); //push the book isbn into its relevant vector
     bookStatus.push_back(BookStatus); //push the book status into its relevant vector
     count ++;
   }
   cout << "Read in " <<  count << " lines from the file." << endl;
   }


}


void OutputToFile(vector<string>& bookName, vector<string>& bookISBN, vector<string>& bookStatus){ //function to output to a file
  string userInput;
  cout << "Where should the database output to? " << endl;
  getline(cin, userInput);
  int count =0;
  ofstream outfile;
  outfile.open(userInput); //function to open the file
  for(int i =0 ; i<bookName.size(); i++){
    outfile << bookName.at(i) << ", " << bookISBN.at(i) << ", " << bookStatus.at(i) << endl; // used to write to the file
    count ++;
  }
  outfile.close(); // used to close the file
  cout <<  count << " lines of data written to " << userInput << endl << endl;
}


bool SearchLibraryBookName(vector<string>&bookName, vector<string>&bookISBN, vector<string>&bookStatus){ //function used to search the book name vector for a specific book name entered by the user
  changeStatus(bookStatus); //used to change the status of the books
  bool found = false;
  string BookName;
  getline(cin, BookName);
  cout << "The Following Are Your Search Results" << endl;
  cout << "-------------------------------------" << endl;
  for(int i =bookName.size()-1 ; i>=0; i--){
    if(BookName == bookName.at(i)){
      cout << bookName.at(i) << " --- " << bookISBN.at(i) << " --- " << bookStatus.at(i) << endl;
      found = true; //return true if the book is found
      return found;
    }
  }
  return found; // return false if the book is not found
}

bool SearchLibraryBookISBN(vector<string>&bookName, vector<string>&bookISBN, vector<string>&bookStatus){ //function to search for specific book isbn entered by the user
  changeStatus(bookStatus); //function used to change the status of the books
  bool found = false;
  string BookISBN;
  getline(cin, BookISBN);
  cout << "The Following Are Your Search Results" << endl;
  cout << "-------------------------------------" << endl;
  for(int i =bookISBN.size()-1 ; i>=0; i--){
    if(BookISBN == bookISBN.at(i)){
      cout << bookName.at(i) << " --- " << bookISBN.at(i) << " --- " << bookStatus.at(i) << endl;
      found = true; 
      return found; //returns true if the book is found
    }
  }
  return found; //return false if the book is not found
} 

bool BookRemoveName(vector<string>&bookName, vector<string>&bookISBN, vector<string>&bookStatus){ //function to remove book from the library by name
  changeStatus(bookStatus); //function to change the book statuses
  string BookName;
  bool found = false;
  cout << "Enter the book name: " << endl;
  getline(cin, BookName);
  cout << "The Following Entry Was Removed From The Library" << endl;
  cout << "------------------------------------------------" << endl;
  for(int i =bookName.size()-1; i >= 0; i--){
    if(BookName == bookName.at(i)){
      cout << bookName.at(i) << " --- " << bookISBN.at(i) << " --- " << bookStatus.at(i) << endl;
      bookName.erase(bookName.begin()+i); //erase book name from bookName vector
      bookISBN.erase(bookISBN.begin()+i); //erase book isbn from bookISBN vector
      bookStatus.erase(bookStatus.begin()+i); //remove book ISBN from bookISBN vector
      found = true;
      return found; //returns true if the book name is found
    }
  }
  return found; // returns false if the book name is not found
}

bool BookRemoveISBN(vector<string>&bookName, vector<string>&bookISBN, vector<string>&bookStatus){ //function used to remove book by ISBN
  changeStatus(bookStatus); //function to change the statuses of the books loaded into the library
  string BookISBN;
  bool found = false;
  cout << "Enter the book 13-digit ISBN (with dashes): " << endl;
  getline(cin, BookISBN);
  cout << "The Following Entry Was Removed From The Library" << endl;
  cout << "------------------------------------------------" << endl;
  for(int i =bookISBN.size()-1 ; i>=0; i--){
    if(BookISBN == bookISBN.at(i)){
      cout << bookName.at(i) << " --- " << bookISBN.at(i) << " --- " << bookStatus.at(i) << endl;
      bookName.erase(bookName.begin()+i); //remove relevant book name from the bookName vector
      bookISBN.erase(bookISBN.begin()+i); //remove relevant bookISBN from the book isbn vector
      bookStatus.erase(bookStatus.begin()+i); //remove the relevant book status from the book status vector
      found = true; 
      return found; //returns found as true if the book isbn is found in the library
    }
  }
  return found; //returns false if the book isbn is not found in the library
}


int main(){
  string command;
  //The below vectors operate as parallel vectors
  vector<string> bookName; //vector that contains all of the book names
  vector<string> bookISBN; //vector that contains all of the book isbns
  vector<string> bookStatus; //vector that contains all of the book isbns.

  string fileName;

  cout << "Welcome to the Library Management System" << endl;
  cout << "----------------------------------------" << endl;
  cout << endl;
  do{
    printMenu();
    cout << endl << "Enter a command (case does not matter): " << endl;
    getline(cin, command);
    if(command == "D" || command == "d"){// used to display the the entries in the library to the user
      changeStatus(bookStatus); //function to change the book status
      cout << "Your Current Library" << endl;
      cout << "--------------------" << endl;
      if(bookName.size() == 0){ //indicates that the library has no books
        cout << "The library has no books." << endl;
        }
      else{
        for(int i =0; i<bookName.size(); i++){
          cout << bookName.at(i)  << " --- " << bookISBN.at(i) << " --- " <<bookStatus.at(i) << endl;
          }
        }
      cout << endl;
    }
    else if(command == "L" || command == "l"){
      cout <<  "What database to read from? " << endl;
      cin >> fileName;
      cin.ignore();
      loadLibrary(fileName, bookName, bookISBN, bookStatus); //call the load library function which stores the data from the file into the relevant vectors
      cout << endl;
    }

    else if(command == "C" || command == "c"){ //function to clear all entries in the library
      bookName.clear(); //clears all book names in the bookName vector
      bookISBN.clear(); //clears all book ISBN's in the bookISBN vector
      bookStatus.clear(); //clears all bookStatus's in the bookStatus vector
      cout << "Your library is now empty." << endl;
      cout << endl;
    }
    else if(command == "R" || command == "r"){
      bool result;
      int input;
      cout << "Would you like remove by (1) name or (2) ISBN." << endl;
      cout << "Enter the numeric choice: " << endl;
      cin >> input;
      cin.ignore();
      if(input == 1){
        result = BookRemoveName(bookName, bookISBN, bookStatus); // call the BookRemoveName function if the user decides to remove by name
        if(result == false){ // since the BookRemoveName function is a bool function, if the book name that the user entered is not present in the library, then the computer prompts the below message
          cout << "No matching entry found in the library." << endl;
        }
      }
      else if(input == 2){
        result = BookRemoveISBN(bookName, bookISBN, bookStatus); //call the BookRemoveISBN function if the user decides to remove by ISBN
        if(result == false){// since the BookRemoveISBN function is a bool function, if the book ISBN that the user entered is not present in the library, then the computer prompts the below message
          cout << "No matching entry found in the library." << endl;
        }
      }
      else{
        cout << "Invalid remove by choice option." << endl; // if the user enters something other than 1 or 2
      }
      cout << endl;
    }

    else if(command == "A" || command == "a"){ // used for adding a new entry
      string userBookName;
      string userBookISBN;
      cout << "What is the book title? " << endl;
      getline(cin, userBookName);
      if(userBookName.find(",") != string::npos){
        cout << "The book title cannot contain commas.";
      }
      else{
      cout << "What is the 13-digit ISBN (with hyphens)? " << endl;
      getline(cin, userBookISBN);
      bookName.push_back(userBookName); //push the user entered book name into the bookName vector
      bookISBN.push_back(userBookISBN);//push the user entered book ISBN into the bookISBN vector
      bookStatus.push_back("0"); //push the user entered book status into the bookStatus vector
      cout << "The Following Entry Was Added" << endl;
      cout << "-----------------------------" << endl;
      cout << userBookName << " --- " << userBookISBN << " --- " << "In Library";
      }
      cout << endl;
      cout << endl;
    }

    else if(command == "S" || command == "s"){ //if the user choses to search for an entry
      bool searchResult;
      int choice;
      string BookName;
      string BookISBN;
      cout << "Would you like to search by (1) name or (2) ISBN." << endl;
      cout << "Enter the numeric choice: " << endl;
      cin >> choice;
      cin.ignore();
      if(choice == 1){ //user chooses to search by name
        cout << "Enter the book name: " << endl;
        searchResult = SearchLibraryBookName(bookName, bookISBN, bookStatus); //calls the SearchLibraryBookName function to check if the book name that the user entered is valid, if yes, then print then add the book to the library and print the confirmation.
        if(searchResult == false){ // if the function returns false, it means that the book name doesn't exist in the library
          cout << "No matching entry found in the library." << endl;
          }
      }
      else if(choice == 2){ //user chooses to search by IBSN
        cout << "Enter the book 13-digit ISBN (with dashes): " << endl;
        searchResult = SearchLibraryBookISBN(bookName, bookISBN, bookStatus);//calls the SearchLibraryBookISBN function to check if the book ISBN that the user entered is valid, if yes, then print then add the book to the library and print the confirmation.
        if(searchResult == false){// if the function returns false, it means that the book ISBN doesn't exist in the library
          cout << "No matching entry found in the library." << endl;
        }
      }
      else{
        cout << "Invalid search by choice option." << endl;
      }
      cout << endl;
    }

    else if(command == "P" || command == "p"){ //if the user decides to print the checkout status's of the books
      PrintCheckoutStatus(bookStatus);

      cout << endl;
    }

    else if(command == "O" || command == "o"){ //if the user chooses to output to a file
      OutputToFile(bookName, bookISBN, bookStatus);
    }

    else if(command == "I" || command == "i"){ //if the user chooses to list the various invalid entries in the library eg: invalid isbn number or if "invalid state" in status vector
      string userISBN;
      ListInvalidEntries(bookName, bookISBN, bookStatus); // calls the function that lists all of the invalid entries
      cout << endl;
      cout << endl;
    }
  } while (!(command == "x" || command == "X")); //terminates the program

    return 0;
}

// Function definitions for all the glorious function decomposition
// Tip: alphabetical order makes it easy to find things if you have
//      a lot of function decomposition.

/// @brief print out the main menu of the management system

