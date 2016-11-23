//
//  manager.cpp
//  Bank Account
//
//  Created by Joel Kennedy on 2016-09-25.
//  Copyright © 2016 Joel Kennedy. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "manager.hpp"
#include "customer.hpp"

//constructor for Manager. Takes an ID, password and integet for the next customer ID to open
int Manager::constructor(std::string idNum, std::string pass, int nextID){
    id = idNum;
    password = pass;
    nextCustID = nextID;
    return 0;
}

//open account function to create a new customer "profile"
int Manager::openAccount(){
    //create variables for the function
    Customer c;
    std::string newPass;
    std::string acctName;
    bool valid = false;
    
    //print the new account id from the Manager variable
    std::cout << "New account ID is " << nextCustID << ".\nPlease enter a password for this account.\n";
    //get a password for the customer
    std::cin >> newPass;
    
    //loop until a valid answer is given
    while (!valid){
        //start with a chequing or a savings account
        std::cout << "Would you like a chequing account or savings?\n";
        std::cin >> acctName;
        if (acctName == "chequing" || acctName == "savings"){
            valid = true;
        }
    }
    
    //create a bank account object with the given name
    BankAccount b;
    b.constructor(0.00, acctName);
    
    //create a customer object with the new ID, given password and created bank account
    c.constructor("c" + std::to_string(nextCustID), newPass, b);
    
    //write the customer to memory to save the data and store the result of the function
    int i = c.writeCust("c" + std::to_string(nextCustID));
    
    //if the function returns an error, print an error message
    if (i!=0) {
        std::cout << "Account not created. Please try again later.\n";
        return 1;
    }
    //otherwise, print a message saying that the account is now open and ready to use
    else{
        std::cout << "New account " << nextCustID << " now open.\n";
    }
    
    //increment the next customer ID variable for the next new customer
    nextCustID++;
    
    return 0;
}

//close account function to delete a customer profile if the balance of all accounts are 0. Takes, as input, an customer profile to delete
int Manager::closeAccount(std::string acct){
    //read the given customer from memory
    Customer c;
    int i = c.readCust(acct);
    
    //if there is an error in reading the account, print an error and abort
    if (i == 1){
        std::cout << "Sorry, the customer was not found\n";
        return 1;
    }
    
    //otherwise, check that all accounts on the customer object are empty
    int closed = c.acctsEmpty();
    
    //if they are not empty, print an error message and abort
    if (closed == 1){
        std::cout << "Sorry, one or more of the accounts still contains a balance. Empty all accounts before the closing the account.\n";
        return 2;
    }
    
    //if they are all empty, delete the customer from memory so they can no longer be used.
    if( remove(acct.c_str()) != 0 ){
        perror( "Error deleting file. The customer could not be deleted.\n" );
        return 3;
    }
    
    //print a success message and return
    std::cout << "Account successfully deleted.\n";
    
    return 0;
}

// retrieve password function to get the password of a forgetful customer. Takes a customer ID as input
int Manager::retrievePass(std::string acct){
    //read the given customer from memory
    Customer c;
    int i = c.readCust(acct);
    //if there is a problem in the reading, print an error message and return
    if (i == 1){
        std::cout << "Sorry, the customer was not found\n";
        return 1;
    }
    
    //otherwise, print the password to the screen
    std::cout << "The password for accout " << acct << " is \"" << c.getPass() << "\"\n";
    
    return 0;
}

//check password function checks a passed in password against the stored manager password during log in
int Manager::checkPass(std::string pass){
    //if the passwords are the same return 0
    if (password == pass) {
        return 0;
    }
    //otehrwise return 1
    return 1;
}

//view account function will print info for a passed in customer
int Manager::viewAccount(std::string acct){
    //read the given customer from memory
    Customer c;
    int i = c.readCust(acct);
    //if there is a problem reading the customer, print an error and return
    if (i == 1){
        std::cout << "Sorry, the customer was not found\n";
        return 1;
    }
    
    //otherwise print the customer info from the print customer function
    std::cout << c.print();
    return 0;
}

//print all accounts function prints info on all customers in the bank
int Manager::printAllAccts(){
    //loop through all customers starting from 101 (the lowest customer ID) looping until the nextCustID variable
    for (int i = 101; i<nextCustID; i++) {
        //read the currently looped customer by added "c" as a prefix to the current ID
        Customer c;
        int j = c.readCust("c" + std::to_string(i));
        //if the reading is successful, print the currently looped account
        if (j==0)
            c.print();
    }
    return 0;
}

//change password function for a manager
int Manager::changePassword(){
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

//read manager function loads a passed in Manager object from memory
int Manager::readManager(std::string fileName){
    //attempt to open a file stream
    std::ifstream myfile(fileName);
    //if the file stream isn't open, print an error and return
    if (!myfile){
        return 1;
    }
    //store the ID as the filename
    id = fileName;
    
    //get the first line in the file and store it as the password
    std::string file;
    getline(myfile, file);
    password = file;
    
    //get the second line in the file and store it as the next customer ID
    getline(myfile, file);
    nextCustID = std::stoi(file);
    
    return 0;
}

//write manager function stores a manager object in memory to a passed in filename (the name is the ID)
int Manager::writeManager(std::string filename){
    //attempt to open a file stream
    std::ofstream myfile(filename);
    //if the file stream isn't open, print an error and return
    if (!myfile){
        return 1;
    }
    //otherwise, store the manager password and nextCustID to memory
    myfile << password << "\n";
    myfile << nextCustID << "\n";
    
    //close the file stream
    myfile.close();
    
    return 0;
}
