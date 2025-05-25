#include "functions.hpp"
#include "termcolor.hpp"
#include "hash.hpp"
#include <iostream>
#include <string>
#include <limits> // Added for input validation

using namespace std;

DoublyLinkedList<account> hashTable[52][52];

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
    int index1 = mazeHashing(username, 0) , index2 = mazeHashing(username, 1);
    hashTable [index1][index2].insertLast(newAccount);
    cout<<termcolor::green<<"\nUser Created Successfully\n"<<termcolor::reset;
    
}

void login() {
    while (true) {
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
    }
}