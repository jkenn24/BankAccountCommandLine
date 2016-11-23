//
//  customer.hpp
//  Bank Account
//
//  Class for a customer, has an ID, password, array of bank accounts, and counter for the next account.
//  Methods defined in cpp file.
//
//  Created by Joel Kennedy on 2016-09-27.
//  Copyright © 2016 Joel Kennedy. All rights reserved.
//

#ifndef customer_h
#define customer_h

#include "bankAccount.hpp"
#include <string>

class Customer{
    std::string id;
    std::string password;
    std::string fileLoc = "/Bank Account/Customer/";
    int nextAvAcct;
    BankAccount accts[20];
    
public:
    int constructor(std::string idNum,std::string password, BankAccount ba);
    
    int withdrawl(int acctNum, double amt);
    
    int deposit(int acctNum, double amt);
    
    int transfer(int acctNumFrom, int acctNumTo, double amt);
    
    int changePassword();
    
    std::string getPass();
    
    int openNewAcct();
    
    double getBalance(int acctNum);
    
    int checkPass(std::string pass);
    
    int acctsEmpty();
    
    std::string getAcctName(int acctNum);
    
    int print();
    
    int writeCust(std::string fileName);
        
    int readCust(std::string fileName);
    
};


#endif /* customer_h */
