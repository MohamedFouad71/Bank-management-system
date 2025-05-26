#pragma once
#include "account.hpp"


void login();
void create(bool admin = false);
void userLogin();
bool userMainPage(user *LoggedInUser);