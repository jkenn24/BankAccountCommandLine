//
//  technician.cpp
//  Bank Account
//
//  Created by Joel Kennedy on 2016-09-25.
//  Copyright © 2016 Joel Kennedy. All rights reserved.
//

#include <stdio.h>
#include "technician.hpp"
#include <fstream>
#include <iostream>
#include <string>

// constructor for technician. takes an ID number, a password and a boolean trace.
int Technician::constructor(std::string idNum, std::string pass, bool trace){
    id = idNum;
    password = pass;
    tracelog = trace;
    return 0;
}

// sets the trace boolean to true, so the system traces through each operation
int Technician::setTraceOn(){
    tracelog = true;
    return 0;
}

// sets the trace boolean to false, so the system trace stops
int Technician::setTraceOff(){
    tracelog = false;
    return 0;
}

//returns a boolean. true if trace is on, false if not.
bool Technician::isTrace(){
    return tracelog;
}

//gets the next trace number for the trace output file.
int Technician::getNextTrace(){
    nextTrace++;
    return nextTrace - 1;
}

//returns the current trace number for the trace output file.
int Technician::getCurrentTrace(){
    return nextTrace - 1;
}

//method checks the passed in password against the one for the technician. returns 0 if they match, 1 otherwise
int Technician::checkPass(std::string pass){
    if (password == pass) {
        return 0;
    }
    return 1;
}

//change password function for a technician
int Technician::changePassword(){
    //password variables
    std::string oldPass;
    std::string newPass1;
    std::string newPass2;
    
    //get the old password
    std::cout << "Please enter your old password:";
    std::cin >> oldPass;
    
    //if incorrect, return
    if (oldPass != password){
        std::cout << "The password is not correct.\n";
        return 1;
    }
    
    //otherwise ask for the new password twice (to verify spelling)
    std::cout <<"Please enter new password:";
    std::cin >> newPass1;
    std::cout <<"Please re-enter new password:";
    std::cin >> newPass2;
    
    //if the passwords don't match, print error and return
    if (newPass1 != newPass2){
        std::cout << "The passwords do not match.\n";
        return 1;
    }
    
    //otherwise, set the password to the new password and print a success message
    password = newPass1;
    std::cout <<"Password successfully changed.\n";
    return 0;
}

//reads a technician from a file. Returns 1 if there is a problem accessing the file. 0 if successful.
int Technician::readTech(std::string fileName){
    std::ifstream myfile(fileName);
    
    //if the file can't be accessed, return 1
    if (!myfile){
        return 1;
    }
    
    //otherwise, the set the id to the passed in file name
    id = fileName;
    
    //read the next line which is the password and store it
    std::string file;
    getline(myfile, file);
    password = file;
    
    //read the next line which is a boolean and store it as the trace
    getline(myfile, file);
    if (file == "1") {
        tracelog = true;
    }
    else{
        tracelog = false;
    }
    
    //read the next line which is the next trace number and store it
    getline(myfile, file);
    nextTrace = stoi(file);
    
    return 0;
}

//writes a technician to a file returns 0 if successful, 1 if there is a problem creating the file
int Technician::writeTech(std::string filename){
    std::ofstream myfile(filename);
    
    //if the file can't be accessed, return 1
    if (!myfile){
        return 1;
    }
    
    //write password to the file
    myfile << password << "\n";
    //write tracelog to the file
    myfile << tracelog << "\n";
    //write nexttrace number to the file
    myfile << nextTrace << "\n";
    
    myfile.close();
    
    return 0;
}
