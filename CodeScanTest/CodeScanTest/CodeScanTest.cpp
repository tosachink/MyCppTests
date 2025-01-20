// CodeScanTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Test code for Code scanning
// Author: Sachin Keskar
// Jan 2025

#include <iostream>
#include <tchar.h>
#include "commonfunctions.h"

int main()
{
    printf("Hello World!");

    // New and delete test
    newanddelete();

    // arr mimatch test
    int myarr[2];
    arrmismatch(myarr);

    // overflow check
    overflowchecktest(30000, 40000);

    // allocation test
    testallocation(10, 30);

}


