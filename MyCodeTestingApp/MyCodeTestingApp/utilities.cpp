#include <tchar.h>
#include "utilities.h"

// These are  tests added for validation

bool _mylogin(const char* kpszUserName, const char* kpszPassword)
{
    bool retval = false;
    if (0 != _tcslen(kpszUserName) && 0 != _tcslen(kpszPassword))
    {
        if (0 == _tcsicmp(kpszUserName, "sachin") && (0 == _tcsicmp(kpszPassword, "Pa55W0rd!"))) {
            retval = true;
        }
    }
    return retval;
}

bool _mycheckOverflow(unsigned short x, unsigned short y) {
    // BAD: comparison is always false due to type promotion
    return (x + y < x);
}

void _myfoo(int a[10]) {
    int i = 0;
    for (i = 0; i < 10; i++) {
        a[i] = i * 2;
    }
}

void _mynewanddelete()
{
    int* p = new int;
    delete[] p;
}

bool _isNull(void* p)
{
    return p = NULL;
}