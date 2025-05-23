#pragma once
#include <string>
#include "DoublyLinkedList.h"

class account{

    int uid;
    std::string userName;

    public:

    account();
    void getInfo();
    int getUID();
    std::string getName();
    
};

// UID from 1 - 1000;
class admin : public account{ 
    
    static int lastUid = 1;
    public :
    admin();
    void createUser(bool admin = false , std::string name);

};

class user : public account{

    private :
    double balance;
    
    public :
    void depose(double value);
    void withdraw(double value);
    double getBalance();
};
