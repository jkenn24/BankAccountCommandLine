//
//  interface.hpp
//  Bank Account
//
//  Created by Joel Kennedy on 2016-09-27.
//  Copyright © 2016 Joel Kennedy. All rights reserved.
//

#ifndef interface_hpp
#define interface_hpp

#include <string>

int customer(std::string inID, std::string inPass);
int manager(std::string inID, std::string inPass);
int technician(std::string inID, std::string inPass);

#endif /* interface_hpp */
