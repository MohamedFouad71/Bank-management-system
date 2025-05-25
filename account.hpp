#pragma once
#include <string>

class account{

    protected:
    int uid;
    std::string userName;
    std::string password;
    public:

    account();
    account(std::string name , std::string pass);
    void getInfo();
    int getUID();
    std::string getName();
    
};

class admin : public account{ 
    
    static int lastUid; //UID from 1 ~ 100
    public :
    admin();

};

class user : public account{ 

    private :
    double balance;
    static int lastUid; // From 101++

    public :
    user();
    void depose(double value);
    void withdraw(double value);
    double getBalance();
};


