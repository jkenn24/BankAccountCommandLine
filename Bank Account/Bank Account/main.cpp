//
//  main.cpp
//  Bank Account
//
//  Created by Joel Kennedy on 2016-09-21.
//  Copyright © 2016 Joel Kennedy. All rights reserved.
//

#include <string>
#include <iostream>
#include "interface.hpp"
#include "customer.hpp"
#include "manager.hpp"
#include "technician.hpp"
#include "bankAccount.hpp"


#include <unistd.h>
#include <string>
#include <iostream>

int main(int argc, const char * argv[]) {
    char buffer[100];
    std::cout << "Current directory is: " << getcwd( buffer, 1000) << "\n";
   // char * dir = getpwd(NULL, 0); // Platform-dependent, see reference link below
    //printf("Current dir: %s", dir);
    
    // Variables for input
    std::string id;
    std::string pass;
    std::string response;
    
    //Print menu and get response
    std::cout << "Hello, Welcome to the 3307 Bank of C\nPlease choose an option:\n1.Log-in\n2.Exit\n";
    std::cin >> response;
    
    //If they want to log in
    if (stoi(response) == 1) {
        //loop until valid login is given
        bool valid = false;
        while (!valid) {
            //get id and password
            std::cout << "Please enter your user ID and press enter:";
            std::cin >> id;
            std::cout << "Please enter your account password:";
            std::cin >> pass;
            
            //if it's a customer log in
            if (id[0] == 'c' || id[0] == 'C'){
                //read the given customer from memory
                Customer c;
                int i = c.readCust(id);
                //if the record is found, check the password
                if (i != 1) {
                    int j = c.checkPass(pass);
                    //if the password is valid, direct the customer to the main menu
                    if (j == 0) {
                        valid = true;
                        std::cout << "Logging in\n";
                        customer(id, pass);
                    }
                }
                
            }
            
            //if it's a manager log in
            else if (id[0] == 'm' || id[0] == 'M'){
                //read the given manager from memory
                Manager m;
                int i = m.readManager(id);
                //if the record is found, check the password
                if (i != 1) {
                    int j = m.checkPass(pass);
                    //if the password is valid, direct the manager to the main menu
                    if (j == 0) {
                        valid = true;
                        std::cout << "Logging in\n";
                        manager(id, pass);
                    }
                }
            }
            
            //if it's a technician log in
            else if (id[0] == 't' || id[0] == 'T'){
                //read the given technician from memory
                Technician t;
                int i = t.readTech(id);
                //if the record is found, check the password
                if (i != 1) {
                    int j = t.checkPass(pass);
                    //if the password is valid, direct the manager to the main menu
                    if (j == 0) {
                        valid = true;
                        std::cout << "Logging in\n";
                        technician(id, pass);
                    }
                }
            }
            //if the valid flag was not changed, loop back for a new id and password
            if (!valid)
                std::cout << "ID or password incorrect.\n";
        }
    }
    
    //If they choose to Exit the program, return control back to OS
    if (stoi(response) == 2) {
        std::cout << "Thankyou, Goodbye.\n";
        return 0;
    }
    
    return 0;
}
