//
//  customer.cpp
//  Bank Account
//
//  Created by Joel Kennedy on 2016-09-25.
//  Copyright © 2016 Joel Kennedy. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include "bankAccount.hpp"
#include "customer.hpp"

//constructor for a customer. Takes an ID, password anf bank account object
int Customer::constructor(std::string idNum,std::string pass, BankAccount ba){
    id = idNum;
    password = pass;
    nextAvAcct = 1;
    accts[0] = ba;
    return 0;
}

//withdrawl function takes a passed in amount out of a passed in bank account number
int Customer::withdrawl(int acctNum, double amt){
    //if the passed in account number is less than the next available account number (ie. valid account)
    if (acctNum < nextAvAcct) {
        //if taking out the amount drops the balance of a chequing account below 1000
        if (accts[acctNum].getAmount() > 1000 && (accts[acctNum].getAmount() - amt) < 1000 && accts[acctNum].getAcctName() == "chequing") {
            //ask the user if they agree to pay the $2.00 service charge.
            bool invalid = false;
            std::string str;
            //Loop until a valid answer is given
            while (!invalid){
                std::cout << "Chequing balance will drop below $1000. Do you want to continue? A charge of $2.00 will apply. (Y/N)";
                std::cin >> str;
                //if the answer is valid, change the boolean to stop the loop
                if (str == "Y" || str == "N"){
                    invalid = true;
                }
            }
            //if they have enough money in the account to pay the amount plus the service charge and they have agreed to pay the service charge. Deduct the amount plus the service charge
            if ((accts[acctNum].getAmount() >= amt + 2.00) && str == "Y") {
                accts[acctNum].deduct(amt+2.00);
                return 0;
            }
            //otherwise, if the customer does not want to pay the charge, abort the withdrawl
            else if(str == "N") return 4;
            //or if the account doesn't have enough money, return
            else return 2;
        }
        //if the withdrawl will not drop a chequing account below $1000, then if check the account has enough money to perform the withdrawl
        else if (accts[acctNum].getAmount() >= amt) {
            //if it does, take the money out and return
            accts[acctNum].deduct(amt);
            return 0;
        }
        //error return if the account doesn't have enough money
        return 1;
    }
    //error return if the account doesn't exist
    return 2;
}

//deposit function adds a passed in amount of money to a passed in account number
int Customer::deposit(int acctNum, double amt){
    //if the account number is less than the next available account number (ie. if it exists)
    if (acctNum < nextAvAcct) {
        //add the amount to the account and return
        accts[acctNum].add(amt);
        return 0;
    }
    //otherwise return
    return 2;
}

//transfer function to move a passed in amount from one passed in account to another
int Customer::transfer(int acctNumFrom, int acctNumTo, double amt){
    //if the first account number is less than the next available account number (ie. if it exists)
    if (acctNumFrom < nextAvAcct) {
        //if the second account number is less than the next available account number (ie. if it exists)
        if (acctNumTo < nextAvAcct) {
            //if taking out the amount drops the balance of a chequing account below 1000
            if (accts[acctNumFrom].getAmount() > 1000 && (accts[acctNumFrom].getAmount() - amt) < 1000 && accts[acctNumFrom].getAcctName() == "chequing") {
                //ask the user if they agree to pay the $2.00 service charge.
                bool invalid = false;
                std::string str;
                //Loop until a valid answer is given
                while (!invalid){
                    std::cout << "Chequing balance will drop below $1000. Do you want to continue? A charge of $2.00 will apply. (Y/N)";
                    std::cin >> str;
                    //if the answer is valid, change the boolean to stop the loop
                    if (str == "Y" || str == "N"){
                        invalid = true;
                    }
                }
                //if they have enough money in the account to pay the amount plus the service charge and they have agreed to pay the service charge. Deduct the amount plus the service charge
                if ((accts[acctNumFrom].getAmount() >= amt + 2.00) && str == "Y") {
                    accts[acctNumFrom].deduct(amt+2.00);
                    return 0;
                }
                //otherwise, if the customer does not want to pay the charge, abort the transfer
                else if(str == "N") return 4;
                //or if the account doesn't have enough money, return
                else return 1;
            }
            //if the transfer will not drop a chequing account below $1000, then if check the account has enough money to perform the withdrawl
            else if (accts[acctNumFrom].getAmount() >= amt) {
                //deduct the money from one account
                accts[acctNumFrom].deduct(amt);
                //and add it to another
                accts[acctNumTo].add(amt);
                return 0;
            }
            //if there is not enough money in the account return 1
            return 1;
        }
        //if account "to" doesn't exist, return 2
        return 2;
    }
    //if account "from" doesn't exist, return 3
    return 3;
    
}

//change password function for a customer
int Customer::changePassword(){
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

//open new account function opens a new Bank account on a customer profile
int Customer::openNewAcct(){
    int acctNum;
    std::string newName;
    
    //if the max number of accounts (20) hasn't been reached yet, then the account number is the next available account stored in the variable and then incremented for the next account
    if (nextAvAcct < 20) {
        acctNum = nextAvAcct;
        nextAvAcct++;
    }
    //otherwise the max amount of accounts has been reached. print an error and return
    else{
        std::cout << "Sorry, you are at the max. number of accounts.\n";
        return 1;
    }
    
    //if the customer only has their first account open (account 0) and that account is a chequing account, then we will open a savings account as their second account
    if (acctNum == 1 && accts[0].getAcctName() == "chequing"){
        newName = "savings";
    }
    //if the customer only has their first account open (account 0) and that account is a savings account, then we will open a chequing account as their second account
    else if (acctNum == 1 && accts[0].getAcctName() == "savings"){
        newName = "chequing";
    }
    //Otherwise, if the account being opened is account 2 or higher, get the account name from the customer
    else{
        std::cout << "Please enter a name for this account\n";
        std::cin >> newName;
    }
    
    //print the new account number to the customer
    std::cout <<"New account number is " << acctNum << "\n";
    
    //create the new bank account object with a balance of $0 and add it to the customer's bank account array
    BankAccount acct;
    acct.constructor(0.00, newName);
    accts[acctNum] = acct;
    
    //print a message that the account is now open and ready to use adn return
    std::cout << "Account \"" << newName << "\" now open.\n";
    return 0;
}

//get balance function returns the balance of the passed in account number
double Customer::getBalance(int acctNum){
    //if the first account number is less than the next available account number (ie. if it exists)
    if (acctNum < nextAvAcct) {
        //return the balance of that account
        return accts[acctNum].getAmount();
    }
    //otherwise return -1
    return -1;
}

//check password function compares the customer password against the passed one to verify login info
int Customer::checkPass(std::string pass){
    //if the passwords are the same, return 0
    if (password == pass) {
        return 0;
    }
    //otherwise return 1
    return 1;
}

//getAcctName function returns a string with the name of the passed in account
std::string Customer::getAcctName(int acctNum){
    //if the first account number is less than the next available account number (ie. if it exists)
    if (acctNum < nextAvAcct) {
        //return the name of the account
        return accts[acctNum].getAcctName();
    }
    //otherwise return a nullptr
    return nullptr;
}

//accounts empty function checks if all accounts are empty
int Customer::acctsEmpty(){
    //loop through all accounts starting from zero and going to the next available account
    for (int i = 0; i<nextAvAcct; i++) {
        //if the current account is not empty, return 1
        if (accts[i].getAmount() != 0.00) {
            return 1;
        }
    }
    //otherwise, if not accounts have a non-zero balance, then all accounts are empty. Return 0
    return 0;
}

//get pass function returns the customer's password
std::string Customer::getPass(){
    return password;
}

//print function prints a customer's info
int Customer::print(){
    std::cout << "Customer: " << id << "\n";
    //loop through all accounts starting from zero and going to the next available account
    for (int i = 0; i<nextAvAcct; i++) {
        //print the account name and the balance of the current account
        printf("\t%15.15s\t\t$%.2f\n", accts[i].getAcctName().c_str(), accts[i].getAmount());
    }
    return 0;
}

//write customer stores a customer object to memory under the passed in filename
int Customer::writeCust(std::string filename){
    //attempt to open the file
    std::ofstream myfile(filename);
    //if there is a problem opening the file return 1
    if (!myfile){
        return 1;
    }
    //store the password in the file
    myfile << password << "\n";
    //store the next availabel account in the file
    myfile << nextAvAcct << "\n";
    //loop through all currently open accounts
    for (int i = 0; i<nextAvAcct; i++) {
        //get a new line character so that the file can be read easily
        char a = (char)10;
        //store the account name and balance separated by a space and ending with a new line
        myfile << accts[i].getAmount() << " " << accts[i].getAcctName()<< a;
    }
    //close the file
    myfile.close();
    return 0;
}

//read customer loads a customer object from memory under the passed in filename
int Customer::readCust(std::string fileName){
    //attempt to open the file
    std::ifstream myfile(fileName);
    //if there is a problem opening the file return 1
    if (!myfile){
        return 1;
    }
    //the id is the filename
    id = fileName;
    
    //the first line is the password
    std::string file;
    getline(myfile, file);
    password = file;
    
    //the second line is the next available account
    getline(myfile, file);
    nextAvAcct = std::stoi(file);
    
    //each following line represents one bank account
    for (int j = 0; j<nextAvAcct; j++) {
        std::string balance("");
        std::string name("");
        
        //the first clump of characters before the " " (space) character is the amount in the account. Loop until a space is read and add each character read into the balance string
        for (int i = myfile.get(); i != 32; ) {
            balance = balance + (char)i;
            i = myfile.get();
        }
        //the second clump of characters before the new line character (32) is the name of the account. Loop until a newline character is read and add each character read into the name string
        for (int i = myfile.get(); i != 10; ) {
            name = name + (char)i;
            i = myfile.get();
        }
        //create a bank account with the amount and balance read and add the bank account to the array of accounts
        BankAccount b;
        b.constructor(stod(balance), name);
        accts[j] = b;
    }
    
    //close the file stream
    myfile.close();
    return 0;
}
