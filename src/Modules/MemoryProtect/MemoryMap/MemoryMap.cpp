#include "Modules/MemoryProtect/MemoryMap/MemoryMap.h"
#include "Modules/MemoryProtect/AllocationEntry.h"
#include "ViolationTable.h"

MemoryMap::MemoryMap()
{
    //ctor
}

MemoryMap::~MemoryMap()
{
    //dtor
}

void MemoryMap::performCheck(ViolationTable *v)
{
    return;
}
