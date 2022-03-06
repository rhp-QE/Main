#include "myalloc1.h"
#include <cstdio>
#include <iostream>
using namespace ::std;

class node {
    DECLARE_MYALLOCATOR1();
    int* ptr = nullptr;
    int val = 1;
};
IMPLEMENT_MYALLOCATOR1(node);
int main()
{
    node* ptr[100];
    cout << sizeof(node) << endl;
    for (int i = 0; i < 100; ++i)
        ptr[i] = new node;
    for (int i = 0; i < 10; ++i)
        cout << ptr[i] << endl;

    return 0;
}
