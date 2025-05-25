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
    virtual ~account();
    int getUid();
    std::string getUserName();
    std::string getPassword();

};

class admin : public account{ 
    
    static int lastUid; //UID from 1 ~ 100
    public :
    admin();
    admin(std::string name , std::string pass);
    void addUser();
    void removeUser();
    void viewUsers();
};

class user : public account{ 

    private :
    double balance{0.0};
    static int lastUid; // From 101++

    public :

    user();
    user(std::string name , std::string pass);
    void depose(double value);
    void withdraw(double value);
    double getBalance() const;
    void viewInfo() const;   
};


