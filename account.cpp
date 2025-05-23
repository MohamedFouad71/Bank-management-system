#pragma once
#include <iostream>
#include "account.hpp"

admin::admin(std::string n){
    if (lastUid == 1000){
        std::cerr<<"Can't have more than 1000 admin\n";
    }
    else{
        uid = lastUid++;
        userName = n;
    }
}