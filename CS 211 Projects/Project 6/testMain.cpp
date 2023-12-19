#include <iostream>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <string>

using namespace std;


void parseString(string name){
    for(size_t i =0; i<name.size(); i++){
        if(name[i] != 'N' && name[i] != 'S' &&  name[i] != 'E' && name[i] != 'W'){
            cout << "hello" << endl;
        }
        else if(name[i] == 'N'){
            cout << "hello1" << endl;
        }
        else if(name[i] == 'W'){
            cout << "hello2" << endl;
        }
    }
}

int main(){
    string name  = "NWA";
    parseString(name);

    return 0;
}