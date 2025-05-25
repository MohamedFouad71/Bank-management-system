#include <iostream>
#include "account.hpp"
using namespace std;

int admin::lastUid = 1;
int user::lastUid = 100;


account::account() : userName("Unkown"){}
account::account(string name, string pass) : userName(name) , password(pass) {}

admin::admin(){
    if (lastUid == 100){
        cerr<<"\nYou have exceeded the admin limit, 100 admin already exists\n";
    }
    else{
        uid = lastUid++;
    }
}

user::user(){
    if (lastUid == 100){
        cerr<<"\nYou have exceeded the admin limit, 100 admin already exists\n";
    }
    else{
        uid = lastUid++;
    }
}