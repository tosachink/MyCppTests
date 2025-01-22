// Author: Sachin Keskar
// Jan 2025

#include <stdio.h>
#include <malloc.h>

void newanddelete()
{
	int* p = new int;
	delete[] p;
}

void arrmismatch(int a[7])
{
	int i = 0;
	for (i = 0; i <= 7; i++)
		a[i] = i * 2;

}
bool overflowchecktest(unsigned short x, unsigned short y) {
	// BAD: comparison is always false due to type promotion
	return (x + y < x);
}

void testallocation(int allocations, int size)
{
	for (int count = 0; count < allocations; count++)
	{
		char* path = new char[size];
	}
}