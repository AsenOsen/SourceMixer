#ifndef MEMORYMAP_H
#define MEMORYMAP_H

#include <vector>
#include "ViolationTable.h"
#include "Modules/MemoryProtect/AllocationEntry.h"

class MemoryMap
{
    public:
        MemoryMap();
        virtual ~MemoryMap();
        virtual void performCheck(ViolationTable *v);

    protected:

    private:
};

#endif // MEMORYMAP_H
