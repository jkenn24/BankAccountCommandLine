//
//  interface.cpp
//  Bank Account
//
//  Created by Joel Kennedy on 2016-09-27.
//  Copyright © 2016 Joel Kennedy. All rights reserved.
//

#include "interface.hpp"
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include "customer.hpp"
#include "manager.hpp"
#include "technician.hpp"
#include <math.h>
#include <ctime>

bool trace;

//method to write to the trace file
int putTrace(std::string id, std::string message){
    //read the technician to get the trace number
    Technician t;
    t.readTech("t101");
    
    //create a stream file
    std::ofstream outfile;
    
    //create the filename
    std::string str1 = "tracelog_" + std::to_string(t.getCurrentTrace()) + ".txt";
    
    //open the file
    outfile.open(str1, std::ios_base::app);
    
    //create the time object
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    
    //format the time object
    strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
    std::string str(buffer);
    
    //output the message to file
    outfile << id << "\t\t" << str << "\n\t" << message << "\n\n";
    
    return 0;
}

//interface for customer
int customer(std::string inID, std::string inPass){
    //create a technician to get the trace value
    Technician t;
    t.readTech("t101");
    trace = t.isTrace();
    
    //if the trace is set to on, send the sign on message to the trace file
    if (trace) {
        putTrace(inID, "Customer signed on");
    }
    
    // create a boolean for the interface loop
    bool logoff = false;
    
    //while the boolean remains unchanged
    while (!logoff){
        //create a customer
        Customer c;
        c.readCust(inID);
        
        //print menu and get choice from user
        std::string choice;
        std::cout << "Customer main menu. Please choose an option:\n1.Withdraw\n2.Deposit\n3.Check Balance\n4.Transfer\n5.E-Transfer\n6.All Account Info\n7.Change Password\n8.Open a new account\n9.Exit\n";
        std::cin >> choice;
        
        //if choice it a withdrawl
        if (stoi(choice) == 1) {
            //ask for the account to withdraw from
            std::string amt;
            std::cout << "Please enter the account to withdraw from.\n";
            std::cin >> choice;
            //ask for the amount to withdraw and convert to a double
            std::cout << "Please enter the amount to withdraw.\n";
            std::cin >> amt;
            double amount = stod(amt);
            
            //if the amount is negative, multiply by -1 to make it positive
            if (amount < 0) {
                amount = amount*-1.0;
            }
            
            //perform the withdrawl on the customer's account and store the result
            int chk = c.withdrawl(stoi(choice), amount);
            
            //if successful, format and print success message
            if (chk == 0){
                std::cout << "$";
                printf("%.2f", amount);
                std::cout <<" successfully withdrawn from account " << choice <<".\n";
                //if trace is set on, write to the trace file
                if (trace) {
                    putTrace(inID, "Withdrawl from account " + choice + " in the amount of $" + std::to_string(amount));
                }
            }
            
            //otherwise print the appropriate error message
            else if (chk == 1){
                std::cout << "Insufficient funds in account " << choice << ".\n";
            }
            else if (chk == 2){
                std::cout << "Account " << choice << " does not exist or is not setup.\n";
            }
            else if (chk == 4){
                std::cout << "Withdrawl aborted by user\n";
            }
        }
        
        // if the option is a deposit
        else if (stoi(choice) == 2) {
            //ask for the account to deposit to
            std::string amt;
            std::cout << "Please enter the account to deposit to.\n";
            std::cin >> choice;
            //ask for the amount to deposit and convert it to a double
            std::cout << "Please enter the amount to deposit.\n";
            std::cin >> amt;
            double amount = stod(amt);
            
            //if the amount is negative, multiply by -1
            if (amount < 0) {
                amount=amount*-1.0;
            }
            
            //perform the deposit on the customer and store the result
            int chk = c.deposit(stoi(choice), amount);
            
            //if successful, format and print a success message
            if (chk == 0){
                std::cout << "$";
                printf("%.2f", amount);
                std::cout <<" successfully deposited to account " << choice <<".\n";
                //if trace is set on, write to the trace file
                if (trace) {
                    putTrace(inID, "Deposit to account " + choice + " in the amount of $" + std::to_string(amount));
                }
            }
            
            //otherwise print an error messsage
            else if (chk == 2){
                std::cout << "Account " << choice << " does not exist or is not setup.\n";
            }
        }
        
        //if the option is check balance
        else if (stoi(choice) == 3) {
            //ask for an account to check the balance of
            std::cout << "Please enter the account to check the balance of.\n";
            std::cin >> choice;
            
            //get the balance and store the result
            double amt = c.getBalance(stoi(choice));
            
            //if unseuccessful, print an error message
            if (amt == -1){
                std::cout << "Sorry, that account has not been opened yet. Please try with an active account.\n";
            }
            
            //otherwise, print the account balance
            else {
                std::cout << "The balance in account \"" << c.getAcctName(stoi(choice)) << "\" is $";
                printf ("%.2f\n",amt);
                //if trace is set on, write to the trace file
                if (trace) {
                    putTrace(inID, "Balance check for account " + choice);
                }
            }
        }
        
        //if the option is a transfer
        else if (stoi(choice) == 4) {
            //get the account number to transfer from and to
            std::string choice1;
            std::string choice2;
            std::string amt;
            std::cout << "Please enter the account number to transfer FROM.\n";
            std::cin >> choice1;
            std::cout << "Please enter the account number to transfer TO.\n";
            std::cin >> choice2;
            
            //get the amount to transfer
            std::cout << "Please enter the amount to transfer.\n";
            std::cin >> amt;
            
            //perform the transfer and store the result
            int check = c.transfer(stod(choice1), stod(choice2), stod(amt));
            
            //if successful, print a success message
            if (check == 0){
                std::cout << "Transfer Successful.\n$";
                printf("%.2f",stod(amt));
                std::cout << " tranferred from account " << choice1 << " to account " << choice2 << ".\n";
                //if trace is set on, write to the trace file
                if (trace) {
                    putTrace(inID, "Transfer from account " + choice1 + " to account " + choice2 + " in the amount of $" + amt);
                }
            }
            
            //otherwise, print an appropriate error message
            else if (check == 1){
                std::cout << "Insufficient funds.\n";
            }
            else if (check == 2){
                std::cout << "Sorry, the \"transfer to\" account does not exist.\n";
            }
            else if (check == 3){
                std::cout << "Sorry, the \"transfer from\" account does not exist.\n";
            }
            else if (check == 4){
                std::cout << "Transfer aborted by user.\n";
            }
        }
        
        //if the choice is E-transfer
        else if (stoi(choice) == 5) {
            //get the customer ID to transfer to
            std::string tID;
            std::cout << "Please enter ID of the user you wish to transfer money to.\n";
            std::cin >> tID;
            
            //get this customer from memory
            Customer c1;
            int custIN = c1.readCust(tID);
            
            //if the customer cannot be found, print an error and abort the transfer
            if (custIN == 1){
                std::cout << "Sorry, the user entered could not be found.\n";
            }
            else {
                //otherwise, get the account to tranfer from and the amount to tranfer
                std::string choice1;
                std::string amt;
                std::cout << "Please enter the account number you wish to transfer FROM.\n";
                std::cin >> choice1;
                std::cout << "Please enter the amount to transfer.\n";
                std::cin >> amt;
                double amount = stod(amt);
                
                //the the amount is negative, multiply by -1
                if (amount < 0) {
                    amount=amount*-1.0;
                }
                
                //get the balance of the chosen account to make sure it exists
                double balance = c.getBalance(stoi(choice1));
                // if the balance is -1. the account does not exist. Print an error message and abort
                if (balance == -1){
                    std::cout << "Sorry, the account number you chose to transfer from does not exist or is not setup.\n";
                }
                //is the balance is less that the transfer amount, print an error and about the transfer
                else if (balance < amount){
                    std::cout << "Insufficient Funds.\n";
                }
                //otherwise perform the transfer
                else{
                    //take the money out of the first account
                    int chk1 = c.withdrawl(stoi(choice1), amount);
                    // if withdrawl successful, continue with the tranfer
                    if (chk1 == 0){
                        //print a message for the successful withdrawl
                        std::cout << "$";
                        printf("%.2f", amount);
                        std::cout <<" successfully withdrawn from account " << choice1 <<".\n";
                        
                        //deposit money in the transfer account
                        int chk2 = c1.deposit(0, amount);
                        //if successful, print a success message
                        if (chk2 == 0){
                            std::cout << "$";
                            printf("%.2f", amount);
                            std::cout <<" successfully deposited to user " << tID <<".\n";
                            
                            //write the "transfer to" customer into memory to save their new balance
                            int write = c1.writeCust(tID);
                            //if there is a problem, print an error message
                            if (write == 1) {
                                std::cout << "Money sent. The money may not have reached the recipient. Contact your bank manager if this is is the case.\n";
                            }
                            //otherwise, print that the transfer was successful.
                            else{
                                std::cout << "Transfer complete. the money will appear in the reciever's main account. (Account 0)\n";
                            }
                            
                            //if trace is set on, write to the trace file
                            if (trace) {
                                putTrace(inID, "Transfer from user " + inID + " from account " + choice1 + " to user " + tID + " in the amount of $" + std::to_string(amount));
                            }
                        }
                        //if the deposit was unsuccessful
                        else if (chk2 == 2){
                            //print an error message
                            std::cout << "Account " << choice << " does not exist or is not setup.\n";
                            
                            //Put the money taken from the original account back
                            std::cout << "Transfer failed. Refunding money to your account.\n";
                            int chk3 = c.deposit(stoi(choice1), amount);
                            //if the money goes back, print a success message and abort transfer
                            if (chk3 == 0){
                                std::cout << "$";
                                printf("%.2f", amount);
                                std::cout <<" successfully refunded to account " << choice1 <<".\n";
                            }
                            //if the money cannot be re-deposited, print an error message and abort transer
                            else if (chk3 == 2){
                                std::cout << "Account " << choice1 << " does not exist or is not setup.\n";
                                std::cout << "Transfer failed: Money was not refunded. Please contact bank manager.\n";
                            }
                        }
                    }
                    //otherwise, print an apropriate error on the withdrawl and abort transfer
                    else if (chk1 == 1){
                        std::cout << "Insufficient funds in account " << choice1 << ".\n";
                    }
                    else if (chk1 == 2){
                        std::cout << "Account " << choice1 << " does not exist or is not setup.\n";
                    }
                    else if (chk1 == 4){
                        std::cout << "E-Transfer aborted by user.\n";
                    }
                }
            }
        }
        
        //if the option is print all account info
        else if (stoi(choice) == 6) {
            //call the print function for customer
            c.print();
            
            //if trace is set on, write to the trace file
            if (trace) {
                putTrace(inID, "Customer accessed account information");
            }
        }
        
        //if the option is change password
        else if (stoi(choice) == 7) {
            //call the change password function
            c.changePassword();
            
            //if trace is set on, write to the trace file
            if (trace) {
                putTrace(inID, "Customer changed password");
            }
        }
        
        //if the option is open a new account
        else if (stoi(choice) == 8) {
            //call the open new account function
            c.openNewAcct();
            
            //if trace is set on, write to the trace file
            if (trace) {
                putTrace(inID, "Opened a new account");
            }
        }
        
        //if the option is Exit
        else if (stoi(choice) == 9) {
            //print a goodbye message
            std::cout << "Thankyou, Goodbye\n";
            
            //if trace is set on, write to the trace file
            if (trace) {
                putTrace(inID, "Customer signed off");
            }
            
            //set the logoff boolean to true so the menu loop stops
            logoff = true;
        }
        
        //write the customer to save all changes
        int write = c.writeCust(inID);
        //if there is a problem with writing the customer, print an error message
        if (write == 1) {
            std::cout << "Change not made. The data could not be saved. Please contact the manager.\n";
        }
        //if the customer has not logged off, ask for an input to continue to the menu.
        if (!logoff) {
            std::cout << "Press enter to continue.";
            std::cin.ignore();
            std::cin.get();
        }
    }
    return 0;
}


//interface for manager
int manager(std::string inID, std::string inPass){
    //read the technician from memory to get the trace state
    Technician t;
    t.readTech("t101");
    trace = t.isTrace();
    
    //if trace is set on, write to the trace file
    if (trace) {
        putTrace(inID, "Manager signed on");
    }
    
    //boolean for loop
    bool logoff = false;
    //loop until the customer logs off
    while (!logoff){
        //read the manager from memory
        Manager m;
        m.readManager(inID);
        
        //print the menu and get an option from the user
        std::string choice;
        std::string acct;
        std::cout << "Manager main menu. Please choose an option:\n1.Open Account\n2.Close Account\n3.Get Customer Info\n4.Get all Customer info\n5.Get a Customer Password\n6.Change my Password\n7.Exit\n";
        std::cin >> choice;
        
        //if the choice is open an account
        if (stoi(choice) == 1) {
            //call the open account function
            int i = m.openAccount();
            
            //if trace is set on, and the manager successfully opens an account, write to the trace file
            if (i==0 && trace) {
                putTrace(inID, "Manager opened and new account");
            }
        }
        
        //if the choice is close account
        else if (stoi(choice) == 2){
            //get an account to close
            std::cout << "Please enter an account ID to close.\n";
            std::cin >> acct;
            
            //call the close account function
            int i = m.closeAccount(acct);
            
            //if trace is set on, and the manager successfully closes an account, write to the trace file
            if (i==0 && trace) {
                putTrace(inID, "Manager closed account " + acct);
            }
        }
        
        //if the choice is print customer info
        else if (stoi(choice) == 3){
            //get an account to print
            std::cout << "Please enter the customer ID you wish to view\n";
            std::cin >> acct;
            //read the customer
            Customer c;
            int j = c.readCust(acct);
            //if read successfully, print the customer
            if (j==0){
                c.print();
                //if trace is set on, write to the trace file
                if (trace) {
                    putTrace(inID, "Manager printed account infor for customer " + acct);
                }
            }
            //if not read successfully, print an error message
            else{
                std::cout << "Sorry, the customer you have requested cannot be found.\n";
            }
        }
        
        //if the choice is print all accounts
        else if (stoi(choice) == 4){
            //call the print all accounts function
            m.printAllAccts();
            //if trace is set on, write to the trace file
            if (trace) {
                putTrace(inID, "Manager retrieved all account info");
            }
        }
        
        else if (stoi(choice) == 5){
            //get an account to retrieve password for
            std::cout << "Please enter the customer ID you wish to view\n";
            std::cin >> acct;
            //read the customer
            Customer c;
            int j = c.readCust(acct);
            //if read successfully, print the customer password
            if (j==0){
                std::cout << "The password for customer " + acct + " is \"" + c.getPass() + "\"\n";
                //if trace is set on, write to the trace file
                if (trace) {
                    putTrace(inID, "Manager printed the password for account " + acct);
                }
            }
            //if not read successfully, print an error message
            else{
                std::cout << "Sorry, the customer you have requested cannot be found.\n";
            }
            
        }
        
        //if the option is change password
        else if (stoi(choice) == 6) {
            //call the change password function
            m.changePassword();
            
            //if trace is set on, write to the trace file
            if (trace) {
                putTrace(inID, "Manager changed password");
            }
        }
        
        //if the customer chooses to exit
        else if (stoi(choice) == 7){
            //print a goodbye message
            std::cout << "Thankyou, goodbye\n";
            //change the bool value so the menu loop will stop
            logoff = true;
            //if trace is set on, write to the trace file
            if (trace) {
                putTrace(inID, "Manager signed off");
            }
        }
        
        //write the manager to save changes
        int write = m.writeManager(inID);
        //if not successfully written, print an error message
        if (write == 1) {
            std::cout << "Change not made. The data could not be saved.\n";
        }
        
        //if the customer hasn't chosen to exit, wait for input to continue to menu
        if (!logoff) {
            std::cout << "Press enter to continue.";
            std::cin.ignore();
            std::cin.get();
        }
        
    }
    return 0;
}


//interface for technician
int technician(std::string inID, std::string inPass){
    //read the technician to check the trace state
    Technician t;
    t.readTech(inID);
    trace = t.isTrace();
    
    //if trace is set on, write to the trace file
    if (trace) {
        putTrace(inID, "Technician signed on");
    }
    
    //boolean for menu loop
    bool logoff = false;
    //while the technician doesn't choose to Exit
    while (!logoff){
        //read the technician to check the trace state
        Technician t;
        t.readTech(inID);
        trace = t.isTrace();
        
        //print the menu and get the choice of the technician
        std::string choice;
        std::cout << "Technician main menu. Please choose an option:\n1.Check Trace State\n2.Toggle Execution Trace Off\n3.Toggle Execution Trace On\n4.Change Password\n5.Exit\n";
        std::cin >> choice;
        
        //if the choice is to check the trace state
        if (stoi(choice) == 1){
            //get the trace state
            bool trace = t.isTrace();
            //if trace is on, print the "trace on" message
            if (trace == true) {
                std::cout << "Trace is currently on.\n";
            }
            //otherwise print the "trace off" message
            else{
                std::cout << "Trace is currently off.\n";
            }
            //if trace is set on, write to the trace file
            if (trace) {
                putTrace(inID, "Technician checked the trace state");
            }
        }
        
        //if the customer wants to toggel the trace off
        else if (stoi(choice) == 2){
            //if trace is set on, write to the trace file and get the next trace number
            if (trace) {
                putTrace(inID, "Technician toggled trace off");
                t.getNextTrace();
            }
            //call the toggle trace off function and print the "off" message
            t.setTraceOff();
            trace = false;
            std::cout << "Trace is now off.\n";
        }
        
        //if the customer wants to toggel the trace on
        else if (stoi(choice) == 3){
            //call the set trace on function adn print the "on" message
            t.setTraceOn();
            trace = true;
            std::cout << "Trace is now on.\n";
            //if trace is set on, write to the trace file
            if (trace) {
                putTrace(inID, "Technician togged trace on");
            }
        }
        
        //if the option is change password
        else if (stoi(choice) == 4) {
            //call the change password function
            t.changePassword();
            
            //if trace is set on, write to the trace file
            if (trace) {
                putTrace(inID, "Technician changed password");
            }
        }
        
        //if the technician chooses to exit
        else if (stoi(choice) == 5){
            //if trace is set on, write to the trace file
            if (trace) {
                putTrace(inID, "Technician signed off");
            }
            //print goodbye message
            std::cout << "Thankyou, goodbye\n";
            //change the bool to stop the menu loop
            logoff = true;
        }
        
        //write the technician to save changes
        int write = t.writeTech(inID);
        //if not successfully written, print an error message
        if (write == 1) {
            std::cout << "Change not made. The data could not be saved.\n";
        }
        
        //if the customer hasn't chosen to exit, wait for input to continue to menu
        if (!logoff) {
            std::cout << "Press enter to continue.";
            std::cin.ignore();
            std::cin.get();
        }
        
    }
    return 0;
}
