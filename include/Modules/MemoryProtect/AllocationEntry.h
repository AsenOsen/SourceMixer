#ifndef ALLOCATIONENTRY_H
#define ALLOCATIONENTRY_H


struct AllocationEntry
{
    void* allocBase;
    void* baseAddr;
    int size;
    char protection[4];
    char type[16];
    char moduleName[128];
};

#endif // ALLOCATIONENTRY_H
