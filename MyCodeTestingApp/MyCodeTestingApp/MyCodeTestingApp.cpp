// MyCodeTestingApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <tchar.h>
#include "utilities.h"

int main()
{

    int my_arr[5];
    _myfoo(my_arr);

    char pszUserName[20] = { 0 };
    char pszUserPass[20] = { 0 };
    printf("\n Enter User Name:");
    scanf_s("%s", pszUserName, (unsigned)_countof(pszUserName));

    printf("\n Enter User Password:");
    scanf_s("%s", pszUserPass, (unsigned)_countof(pszUserPass));

   if (_mylogin(pszUserName, pszUserPass))
        printf("\n Login Succeeded");
    else
        printf("\n Login Failed");
}


