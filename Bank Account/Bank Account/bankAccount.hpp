//
//  bankAccount.hpp
//  Bank Account
//
//  Class for a bank account, has an balance and a name.
//  Methods defined in cpp file.
//
//  Created by Joel Kennedy on 2016-09-25.
//  Copyright © 2016 Joel Kennedy. All rights reserved.
//

#ifndef bankAccount_h
#define bankAccount_h

class BankAccount{
    double balance;
    std::string name;

public:
    int constructor(double openbal, std::string acctName);
    
    int deduct(double deductAmt);
    
    int add(double depositAmt);
    
    double getAmount();
    
    std::string getAcctName();
    
    int setAcctName(std::string acName);
};

#endif /* bankAccount_h */


//Recent Transactions
