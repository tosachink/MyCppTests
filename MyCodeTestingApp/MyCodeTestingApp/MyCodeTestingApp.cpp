// MyCodeTestingApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <tchar.h>


bool login(const char* kpszUserName, const char* kpszPassword)
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

bool checkOverflow(unsigned short x, unsigned short y) {
    // BAD: comparison is always false due to type promotion
    return (x + y < x);
}

void foo(int a[10]) {
    int i = 0;
    for (i = 0; i < 10; i++) {
        a[i] = i * 2;
    }
}

void newanddelete()
{
    int* p = new int;
    delete[] p;
}

int main()
{

    int my_arr[5];
    foo(my_arr);


    char pszUserName[20] = { 0 };
    char pszUserPass[20] = { 0 };
    printf("\n Enter User Name:");
    scanf("%s", pszUserName);

    printf("\n Enter User Password:");
    scanf("%s", pszUserPass);

    if (login(pszUserName, pszUserPass))
        printf("\n Login Succeeded");
    else
        printf("\n Login Failed");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
