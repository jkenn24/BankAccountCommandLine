//
//  technician.hpp
//  Bank Account
//
//  Class for a technician, has an ID, password, boolean tracelog, and a counter for the next tracelog.
//  Methods defined in cpp file.
//
//  Created by Joel Kennedy on 2016-09-30.
//  Copyright © 2016 Joel Kennedy. All rights reserved.
//

#ifndef technician_h
#define technician_h

#include <string>

class Technician{
    std::string id;
    std::string password;
    int nextTrace;
    bool tracelog;
public:
    int constructor(std::string idNum, std::string pass, bool trace);
    
    int writeTech(std::string filename);
    
    int readTech(std::string fileName);
    
    int changePassword();
    
    bool isTrace();
    
    int checkPass(std::string pass);
    
    int setTraceOn();
    
    int setTraceOff();
    
    int getNextTrace();
    
    int getCurrentTrace();
    
};

#endif /* technician_h */
