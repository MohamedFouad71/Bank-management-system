#pragma once
#include <string>
#include "DoublyLinkedList.h"

class account{

    int uid, numberOfUsers;
    std::string name;
    static DoublyLinkedList<int> UIDs;

    public:

    account();
    void getInfo();
    int getUID();
    std::string getName();

};

class admin::account(){ // uid range 1-100

    static int lastUid;

};