#ifndef _MYALLOC1_
#define _MYALLOC1_
//---------------------------------------------

#include <cstdlib>
#include <iostream>
class myAllocator1 {
public:
    void* allocate(size_t size);
    void deallocate(void* ptr);

private:
    struct obj {
        obj* next;
    };

private:
    const int CHUNK = 20; // 每次分配的大小
    obj* freeList;        // 自由链表
};

void* myAllocator1::allocate(size_t size)
{
    obj* ptr = nullptr;
    if (nullptr == freeList) {
        size_t chunk = CHUNK * size;
        freeList = ptr = (obj*)malloc(chunk);
        if (nullptr == freeList)
            return nullptr;
        for (int i = 0; i < (CHUNK - 1); ++i)
            ptr->next = (obj*)(((char*)ptr) + size), ptr = ptr->next;
        ptr->next = nullptr;
    }
    ptr = freeList;
    freeList = freeList->next;
    return ptr;
}

void myAllocator1::deallocate(void* ptr)
{
    ((obj*)ptr)->next = freeList;
    freeList = ((obj*)ptr);
}

#define DECLARE_MYALLOCATOR1()                                             \
private:                                                                   \
    static myAllocator1 myallocator;                                       \
                                                                           \
public:                                                                    \
    void* operator new(size_t size) { return myallocator.allocate(size); } \
    void operator delete(void* ptr) { myallocator.deallocate(ptr); }

#define IMPLEMENT_MYALLOCATOR1(class_name) \
    myAllocator1 class_name::myallocator;

//-----------------------------------------------
#endif
