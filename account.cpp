#include <iostream>
#include "account.hpp"
#include "termcolor.hpp"
using namespace std;


// ############################# Account Class ##########################################
account::account() :uid(-1) , userName("Unknown") , password(""){}
account::account(string name, string pass) : userName(name) , password(pass) {}

account::~account() {
    cout << termcolor::yellow << "Account with UID " << uid << " is being deleted.\n" << termcolor::reset;
}

int account::getUid()
{
    return uid;
}

std::string account::getUserName()
{
    return userName;
}

std::string account::getPassword()
{
    return password;
}

//############################### Admin Class ###########################################

int admin::lastUid = 0;

admin::admin() : account() {
    if (lastUid == 100){
        cerr<<termcolor::red<<"\nYou have exceeded the admin limit, 100 admin already exists\n"
        <<termcolor::reset;
        uid = -1;
    }
    else{
        uid = ++lastUid;
    }
    
}

admin::admin(string name, string pass) : account(name, pass) {
    if (lastUid == 100) {
        cerr << termcolor::red << "\nYou have exceeded the admin limit, 100 admins already exist\n" << termcolor::reset;
        uid = -1;
    } else {
        uid = ++lastUid;
    }
}


//####################################### User Class #############################################

int user::lastUid = 100;
user::user() : account(), balance(0.0) {
    uid = ++lastUid;
}

user::user(string name , string pass) : account(name , pass) {
    uid = ++lastUid;
    balance = 0.0;
}

void user::depose(double value)
{
    if (value <= 0){
        cerr<<termcolor::red<<"Invalid value\n"<<termcolor::reset;
    }
    else {
        balance += value;
        cout<<termcolor::green<<"Successfully Added "<<termcolor::bright_yellow<<value<<termcolor::green
        <<" To Your Account!! Your Current Balance is : "<<termcolor::bright_yellow<<balance<<termcolor::reset;

    }
}

void user::withdraw(double value){

    if (value <= 0){
        cerr<<termcolor::red<<"\nInvalid value\n"<<termcolor::reset;
    }
    else if (balance < value){
        cerr<<termcolor::red<<"\nInsufficient balance\n"<<termcolor::reset;
    }
    else {
        balance -= value;
        cout<<termcolor::green<<"Successfully Withdrawn "<<termcolor::bright_yellow<<value<<termcolor::green
        <<" From Your Account!! Your Current Balance is : "<<termcolor::bright_yellow<<balance<<termcolor::reset;
    }
}

void user::viewInfo() const{

    if (uid <= 0) {
        cerr << termcolor::red << "\nError: Invalid user information\n" << termcolor::reset;
        return;
    }

    cout << termcolor::blue
         << "\n==================== User Information ====================\n"
         << "Name    : " << userName << endl
         << "UID     : " << uid << endl
         << "Balance : " << balance << endl
         << "=========================================================\n"
         << termcolor::reset;
}