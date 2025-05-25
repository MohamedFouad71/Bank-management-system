#include "functions.hpp"
#include "termcolor.hpp"
#include "hash.hpp"
#include <windows.h>
#include <iostream>
#include <string>
#include <limits> // Added for input validation

using namespace std;

DoublyLinkedList <user> userHashTable[52][52];
DoublyLinkedList <admin> adminHashTable [100];

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[2J\033[1;1H";
#endif
}

void create(bool adminstrator) {

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string username;
    cout << termcolor::blue<<"Username: "<<termcolor::bright_blue;
    getline(cin, username);

    // Validate username - first two chars must be letters
    while (username.length() < 6 || !isalpha(username[0]) || !isalpha(username[1])) {

        if (username.length() < 6){
            cerr<<termcolor::red<<"\nToo Short\n";
        }
        else{
            cerr << termcolor::red << "\nError: First two characters must be alphabetic\n" ;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << termcolor::blue<<"Username: "<<termcolor::bright_blue;
        getline(cin , username);
    }

    
    string password;
    cout <<termcolor::blue<<"\nTry including uppercase, lowercase, special characters and numbers for more protection\n";
    cout << termcolor::blue << "Password: "<<termcolor::bright_blue;
    getline(cin, password);
    
    // Validate password length
    while (password.size() < 8) {
        cerr << termcolor::red << "\nShort password, minimum 8 characters\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout <<termcolor::blue<< "Password: "<<termcolor::bright_blue;
        getline(cin, password);
    }

    // adding to hash table

    if (adminstrator) {

        admin newAdmin(username, password);
        int index = adminHash(newAdmin);
        adminHashTable [index].insertLast(newAdmin);
        
    } else {

        int index1 = mazeHashing(username, 0) , index2 = mazeHashing(username, 1);
        user newUser = user(username, password);
        userHashTable [index1][index2].insertLast(newUser);
    }
    
    
    clearScreen();
    cout<<termcolor::green<<"\nUser Created Successfully\n"<<termcolor::reset;
    Sleep(3000);
}

void login() {
    do {
        cout << termcolor::blue << "\nWelcome to Our Bank\n\n";
        cout << termcolor::yellow << "1 - Create user\n";
        cout << termcolor::yellow << "2 - Login as user\n";
        cout << termcolor::yellow << "3 - Login as admin\n";
        cout << termcolor::yellow << "4 - Exit\n" << termcolor::reset;
        
        unsigned short choice;
        cout <<termcolor::blue<< "\nEnter choice: "<<termcolor::bright_blue;
        
        if (!(cin >> choice)) { // Handle non-numeric input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << termcolor::red << "Invalid input!\n" << termcolor::reset;
            continue;
        }

        switch (choice) {
            case 1:
                create();
                break;
            case 2:
                // Future user login implementation
                break;
            case 3:
                create(true); // Admin account creation
                break;
            case 4:
                cout << "Exiting...\n";
                return;
            default:
                cerr << termcolor::red << "Invalid choice!\n" << termcolor::reset;
        } 
    } while (true);
}

void userLogin()
{
    cout<<termcolor::green<<"User Login";
    cout << termcolor::blue<<"Username: "<<termcolor::bright_blue;
    string uname;
    getline(cin, uname);
    int index1 = mazeHashing(uname, 1), index2 =mazeHashing(uname , 2);
    user loggedInUser;
    try
    {
        DoublyLinkedList<user> searchedList = userHashTable[index1][index2];
        loggedInUser = searchedList.twoPointerSearch(uname) ;
    }
    catch(const exception& e)
    {
        cerr <<termcolor::red<<"Username Not Found\n"<<termcolor::reset;
        return;
    }

    string password;

    for (size_t counter = 0; counter<5 ; counter++){

        cout<<termcolor::blue<<"Password : ";
        getline(cin, password);
        if (password == loggedInUser.getPassword()){

            for (size_t i = 0; i < 2; i++){
                clearScreen();
                cout<<termcolor::green<<"Successfully Logged In !!\n";
                Sleep(1000);
            }
            cout<<termcolor::green<<"Successfully Logged In !!\n";

            return;
        }

        cout<<termcolor::red<<"wrong Password , Try again\n";
        cout<<termcolor::blue<<"Password : ";
        getline(cin, password);

    }

    // three wrong attempts
    std::cout<<termcolor::bold<<termcolor::red<<"Too Many Wrong attempts!!\n"<<termcolor::reset;

}
