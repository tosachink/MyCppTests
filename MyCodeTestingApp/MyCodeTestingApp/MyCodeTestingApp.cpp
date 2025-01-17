// MyCodeTestingApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <tchar.h>


bool mylogin(const char* kpszUserName, const char* kpszPassword)
{
    bool retval = false;
    if (0 != _tcslen(kpszUserName) && 0 != _tcslen(kpszPassword))
    {
        if(0 == _tcsicmp(kpszUserName, "sachin") && (0 == _tcsicmp(kpszPassword, "Pa55W0rd!"))) {
            retval = true;
        }
    }
    return retval;
}

bool mycheckOverflow(unsigned short x, unsigned short y) {
    // BAD: comparison is always false due to type promotion
    return (x + y < x);
}

void myfoo(int a[10]) {
    int i = 0;
    for (i = 0; i < 10; i++) {
        a[i] = i * 2;
    }
}

void mynewanddelete()
{
    int* p = new int;
    delete[] p;
}


int main()
{

    int my_arr[5];
    myfoo(my_arr);

    char pszUserName[20] = { 0 };
    char pszUserPass[20] = { 0 };
    printf("\n Enter User Name:");
    scanf("%s", pszUserName);

    printf("\n Enter User Password:");
    scanf("%s", pszUserPass);

    if (mylogin(pszUserName, pszUserPass))
        printf("\n Login Succeeded");
    else
        printf("\n Login Failed");
}


