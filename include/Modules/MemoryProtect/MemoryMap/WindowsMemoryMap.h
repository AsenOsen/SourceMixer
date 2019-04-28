#ifndef WINDOWSMEMORYMAP_H
#define WINDOWSMEMORYMAP_H

#include "Modules/MemoryProtect/AllocationEntry.h"
#include "Modules/MemoryProtect/MemoryMap/MemoryMap.h"
#include "ViolationTable.h"

#include <map>
#include <string>

class WindowsMemoryMap : public MemoryMap
{
    public:
        WindowsMemoryMap();
        virtual ~WindowsMemoryMap();
        virtual void performCheck(ViolationTable* v);

    protected:

    private:
        std::map<int, AllocationEntry*>* previousMap;
        std::map<int, std::string>* xHashes;
};

#endif // WINDOWSMEMORYMAP_H
