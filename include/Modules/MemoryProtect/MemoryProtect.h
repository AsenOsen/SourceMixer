#ifndef MEMORYPROTECT_H
#define MEMORYPROTECT_H

#include "ViolationTable.h"
#include "Modules/MemoryProtect/AllocationEntry.h"
#include "Modules/MemoryProtect/MemoryMap/MemoryMap.h"
#include "Modules/MemoryProtect/MemoryMap/WindowsMemoryMap.h"

#include <vector>

class MemoryProtect
{
    public:
        MemoryProtect();
        virtual ~MemoryProtect();

        static inline void call(ViolationTable* v){

            if(!MemoryProtect::mMap){
                #ifdef _WIN32
                    MemoryProtect::mMap = new WindowsMemoryMap();
                #else
                    MemoryProtect::mMap = new MemoryMap();
                #endif // _WIN32
            }

            MemoryProtect::mMap->performCheck(v);
        }

    protected:

    private:

        static MemoryMap* mMap;
};

#endif // MEMORYPROTECT_H
