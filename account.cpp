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

std::string account::getUserName ()const
{
    return userName;
}

std::string account::getPassword ()const
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

void user::changeUsername() // Comments Were Written by AI
{
    // Store the current (old) username
    string oldName = userName;

    // Prompt for new username
    cout << termcolor::blue << "New Username: " << termcolor::bright_blue;
    string newName;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> newName;

    // Check for minimum length
    if (newName.length() < 6) {
        cerr << termcolor::red << "\nToo Short\n" << termcolor::reset;
        return;
    }

    // Check if the first two characters are alphabetic
    if (!isalpha(newName[0]) || !isalpha(newName[1])) {
        cerr << termcolor::red << "\nError: First two characters must be alphabetic\n" << termcolor::reset;
        return;
    }

    // Check if the new username already exists in the hash table
    try {
        int newI1 = mazeHashing(newName, 0);
        int newI2 = mazeHashing(newName, 1);
        DoublyLinkedList<user>* targetList = &userHashTable[newI1][newI2];

        // Try to find the user by new name — will throw if not found
        targetList->searchAccount(newName);

        // If it doesn't throw, that means username already exists
        cerr << termcolor::red << "Username Already Used!!\n" << termcolor::reset;
        return;
    }
    catch (...) {
        // Username is available — proceed with the change

        // 1. Remove the user from the old position in the hash table
        int oldI1 = mazeHashing(oldName, 0);
        int oldI2 = mazeHashing(oldName, 1);
        DoublyLinkedList<user>* oldList = &userHashTable[oldI1][oldI2];
        int userIndex = oldList->linearSearch(*this);
        oldList->removeAt(userIndex);

        // 2. Update the username
        this->userName = newName;

        // 3. Insert the user back into the correct position for the new name
        int newI1 = mazeHashing(newName, 0);
        int newI2 = mazeHashing(newName, 1);
        DoublyLinkedList<user>* newList = &userHashTable[newI1][newI2];
        newList->insertLast(*this);
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