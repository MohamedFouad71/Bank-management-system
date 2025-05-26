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

void login() {
    do {
        cout << termcolor::blue << "\nWelcome to Our Bank\n\n";
        cout << termcolor::yellow << "1 - Create user\n";
        cout << termcolor::yellow << "2 - Login as user\n";
        cout << termcolor::yellow << "3 - Exit\n" << termcolor::reset;
        
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
                userLogin();
                break;
            case 3:
                cout << "Exiting...\n";
                exit(0);
            default:
                cerr << termcolor::red << "Invalid choice!\n" << termcolor::reset;
        } 
    } while (true);
}

void userLogin()
{
    for (size_t i = 0; i<2; i++){//##############################
        clearScreen();
        Sleep(100);
        cout << termcolor::bold << termcolor::green 
        << "\n==================================\n"
        << "          USER LOGIN\n"
        << "==================================\n"
        << termcolor::reset;
        Sleep(100);
    }

    // Uname Input
    cout << termcolor::blue<<"Username : "<<termcolor::bright_blue;
    string uname;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, uname);

    // Searching For User
    int index1 = mazeHashing(uname, 0), index2 =mazeHashing(uname , 1);
    user *loggedInUser;
    try
    {
        DoublyLinkedList<user> *searchedList = &(userHashTable[index1][index2]);
        loggedInUser = searchedList->searchAccount(uname) ;
    }
    catch(...) // if not found
    {
        cerr <<termcolor::red<<"Username Not Found\n"<<termcolor::reset;
        return;
    }

    string password;

    for (size_t counter = 0; counter<5 ; counter++){

        // Getting Password
        cout<<termcolor::blue<<"Password : "<<termcolor::bright_blue;
        getline(cin, password);

        if (password == loggedInUser->getPassword()){

            for (size_t i = 0; i < 2; i++){
                clearScreen();
                cout<<termcolor::green<<"Successfully Logged In !!\n";
                Sleep(1000);
                clearScreen();
            }
            cout<<termcolor::green<<"Successfully Logged In !!\n";
            bool run = true;
            while(run){
                run = userMainPage(loggedInUser);
            }
            
            return;
        }

        cout<<termcolor::red<<"wrong Password , Try again\n";
        cout<<termcolor::blue<<"\nPassword : "<<termcolor::bright_blue;
        getline(cin, password);

    }

    // three wrong attempts
    std::cout<<termcolor::bold<<termcolor::red<<"Too Many Wrong attempts!!\n"<<termcolor::reset;

}

bool userMainPage(user *LoggedInUser){

    cout<<termcolor::blue
    <<"\n==================================================================\n"
    <<"                       Choose an Option                           "
    <<"\n==================================================================\n"
    <<termcolor::yellow
    <<"1 - View Balance\n"
    <<"2 - View Info\n"
    <<"3 - Withdraw Money\n"
    <<"4 - Depose Money\n"
    <<"5 - Change Password\n"
    <<"6 - Change Username\n"
    <<"7 - Previous Page\n"
    <<termcolor::blue
    <<"Choice : ";
    unsigned short int choice;

    while (!(cin >> choice)) { // Handle non-numeric input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << termcolor::red << "\nInvalid input!\n" << termcolor::reset;

        cout<<termcolor::blue<<"Choice : ";
    }

    switch (choice)
    {
    case 1 :
        cout<<termcolor::green<<"Your Current Balance is "<< LoggedInUser->getBalance() << endl << termcolor::reset;
        break;
    case 2 :
        clearScreen();
        LoggedInUser->viewInfo();
        Sleep(3000);
        break;
    case 3 :
        LoggedInUser->withdraw();
        Sleep(3000);
        break;
    case 4 :
        LoggedInUser->depose();
        Sleep(3000);
        break;
    case 5 : 
        LoggedInUser->changePassword();
        Sleep(3000);
        break;
    case 6 :
        LoggedInUser->changeUsername();
        break;
    case 7 :;
        return false; // Don't repeat
    default :
        cout<<termcolor::red<<"Invalid Choice\n"<<termcolor::reset<<endl;
    }
    return true ;
}

void create(bool adminstrator) {

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string username;
    while (true) {
        cout << termcolor::blue << "Username: " << termcolor::bright_blue;
        getline(cin, username);

        if (username.length() < 6) {
            cerr << termcolor::red << "\nToo short: Username must be at least 6 characters\n";
            continue;
        }

        if (!isalpha(username[0]) || !isalpha(username[1])) {
            cerr << termcolor::red << "\nError: First two characters must be alphabetic\n";
            continue;
        }

        // Check if username already exists
        int index1 = mazeHashing(username, 0), index2 = mazeHashing(username, 1);
        try {
            user* existingUser = userHashTable[index1][index2].searchAccount(username);
            // If found, it means username already exists
            cerr << termcolor::red << "Username already exists\n" << termcolor::reset;
            continue;
        } catch (...) {
            // Not found: safe to proceed
            break;
        }
    }

    // Password input
    string password;
    cout << termcolor::blue << "\nTip: Include uppercase, lowercase, numbers, and special characters for better security.\n";
    while (true) {
        cout << termcolor::blue << "Password: " << termcolor::bright_blue;
        getline(cin, password);

        if (password.length() < 8) {
            cerr << termcolor::red << "\nShort password: Minimum 8 characters required\n";
            continue;
        }

        break;
    }

    // Add to hash table
    if (adminstrator) {
        admin newAdmin(username, password);
        int index = adminHash(newAdmin);
        adminHashTable[index].insertLast(newAdmin);
    } else {
        user newUser(username, password);
        int index1 = mazeHashing(username, 0), index2 = mazeHashing(username, 1);
        userHashTable[index1][index2].insertLast(newUser);
    }

    clearScreen();
    cout << termcolor::green << "\n User created successfully!\n" << termcolor::reset;
    Sleep(3000);
}
