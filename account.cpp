#include "account.hpp"
#include "termcolor.hpp"
#include "DoublyLinkedList.hpp"
#include <iostream>
#include <limits>

using namespace std;


extern DoublyLinkedList<user> userHashTable[52][52];

int mazeHashing(std::string &name , int characterPosition , bool nothing = false){

    const char character = name.at(characterPosition);
    if (character >= 'A' && character <= 'Z') // checking if the character is uppercase
    {
        return int(character) - 65 ;
    }
    else {
        return int(character) - 71 ; // Start from index 26 for more searching effectioncy
    }
}

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
    cout<<"Created temporary user with uid "<<uid<<std::endl;
}

user::user(string name , string pass) : account(name , pass) {
    uid = ++lastUid;
    balance = 0.0;
}

void user::depose()
{
    double value;
    cout<<termcolor::blue<<"Amount of money : "<<termcolor::bright_blue;

    if (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << termcolor::red << "\nInvalid input: Not a number\n" << termcolor::reset;
        return;
    }

    if (value <= 0){
        cerr<<termcolor::red<<"Invalid value\n"<<termcolor::reset;
    }
    else {
        balance += value;
        cout<<termcolor::green<<"Successfully Added "<<termcolor::bright_yellow<<value<<termcolor::green
        <<" To Your Account!! Your Current Balance is : "<<termcolor::bright_yellow<<to_string(balance)<<termcolor::reset<<endl;
    }
    
}

void user::withdraw(){

    double value;
    cout<<termcolor::blue<<"Amount of money : "<<termcolor::bright_blue;

    if (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << termcolor::red << "\nInvalid input: Not a number\n" << termcolor::reset;
        return;
    }


    if (value <= 0){
        cerr<<termcolor::red<<"\nInvalid value\n"<<termcolor::reset;
    }
    else if (balance < value){
        cerr<<termcolor::red<<"\nInsufficient balance\n"<<termcolor::reset;
    }
    else {
        balance -= value;
        cout<<termcolor::green<<"Successfully Withdrawn "<<termcolor::bright_yellow<<value<<termcolor::green
        <<" From Your Account!! Your Current Balance is : "<<termcolor::bright_yellow<<to_string(balance)<<termcolor::reset<<std::endl;
    }
}

void user::changeUsername()
{
    cout<<termcolor::blue<<"New Username : "<<termcolor::bright_blue<<endl;
    string uname;
    cin>>uname;
    
    if (uname.length() < 6){
        cerr<<termcolor::red<<"\nToo Short\n";
        return;
    }
    else{
        cerr << termcolor::red << "\nError: First two characters must be alphabetic\n" ;
        return;
    }

    try
    {
        int index1 = mazeHashing(uname, 0), index2 =mazeHashing(uname , 1);
        DoublyLinkedList<user> *searchedList = &(userHashTable[index1][index2]);
        searchedList->searchAccount(uname);
        cerr<<termcolor::red<<"Username Already Used!!\n";
    }
    catch(...) // if not found
    {
        this->userName = uname;
    }

}

void user::changePassword()
{
    string newPass;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<termcolor::blue<<"New Password : ";
    getline(cin , newPass);

    // Validate password length
    if (newPass.size() < 8) {
        cerr << termcolor::red << "\nToo Short, Minimum 8 characters\n"<<termcolor::reset;
    }
    else{
        password = newPass;
        cout<<termcolor::green<<"Password Reset !!\n"<<termcolor::reset;
    }
}

double user::getBalance() const
{
    return balance;
}

void user::viewInfo() const{

    if (uid <= 0) {
        cerr << termcolor::red << "\nError: Invalid user information\n" << termcolor::reset;
        return;
    }

    cout << termcolor::green
         << "\n==================== User Information ====================\n"
         << "Name    : " << userName << endl
         << "UID     : " << uid << endl
         << "Balance : " << balance << endl
         << "=========================================================\n"
         << termcolor::reset;
}