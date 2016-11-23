//
//  bankAccount.cpp
//  Bank Account
//
//  Created by Joel Kennedy on 2016-09-25.
//  Copyright © 2016 Joel Kennedy. All rights reserved.
//

#include <stdio.h>
#include <string>
#include "bankAccount.hpp"

//constructor for bank account. Takes an opening balance and a name for the account
int BankAccount::constructor(double openbal, std::string acctName){
    balance = openbal;
    name = acctName;
    return 0;
}

//deduct function. Takes, as an input, an amount to deduct from the account
int BankAccount::deduct(double deductAmt){
    balance -= deductAmt;
    return 0;
}

//add fuction. Takes as an input, an amount to add to the account
int BankAccount::add(double depositAmt){
    balance += depositAmt;
    return 0;
}

//get amount function. Returns the current balance of an account
double BankAccount::getAmount(){
    return balance;
}

//get acct name function. Return the name of an account.
std::string BankAccount::getAcctName(){
    return name;
}

//set acct name function. Sets the name of an account.
int BankAccount::setAcctName(std::string acName){
    name = acName;
    return 0;
}



