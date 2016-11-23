//
//  manager.hpp
//  Bank Account
//
//  Class for a manager, has an ID, password, and a counter for the next customer ID.
//  Methods defined in cpp file.
//
//  Created by Joel Kennedy on 2016-09-30.
//  Copyright © 2016 Joel Kennedy. All rights reserved.
//

#ifndef manager_h
#define manager_h

#include <string>

class Manager{
    std::string id;
    std::string password;
    int nextCustID;
    std::string fileLoc = "/Bank Account/Manager/";
public:
    int constructor(std::string idNum, std::string pass, int nextID);
    
    int openAccount();
    
    int closeAccount(std::string acct);
    
    int retrievePass(std::string acct);
    
    int viewAccount(std::string acct);
    
    int checkPass(std::string pass);
    
    int changePassword();
    
    int printAllAccts();
    
    int readManager(std::string fileName);
    
    int writeManager(std::string filename);
    
    
};

#endif /* manager_h */
