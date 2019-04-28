#include "Modules/MemoryProtect/MemoryMap/WindowsMemoryMap.h"
#include "Modules/MemoryProtect/MemoryMap/MemoryMap.h"
#include "ModuleBase.h"
#include "Decision.h"
#include "ViolationTable.h"
#include "Toolkit/SHA256.h"

#include <windows.h>
#include <tlhelp32.h>

#include <iostream>
using namespace std;

WindowsMemoryMap::WindowsMemoryMap() : MemoryMap()
{
    this->previousMap = new std::map<int, AllocationEntry*>();
    this->xHashes = new std::map<int, string>();
}

WindowsMemoryMap::~WindowsMemoryMap()
{
    //dtor
}

AllocationEntry* createMemEntry(MEMORY_BASIC_INFORMATION pMemInfo)
{
    if(pMemInfo.State != MEM_FREE){
        AllocationEntry* entry = new AllocationEntry();
        entry->allocBase = pMemInfo.AllocationBase;
        entry->baseAddr = pMemInfo.BaseAddress;
        entry->size = pMemInfo.RegionSize;

        switch(pMemInfo.Protect){
            case PAGE_EXECUTE:
                strcpy(entry->protection, "--x");
                break;
            case PAGE_EXECUTE_READ:
                strcpy(entry->protection, "r-x");
                break;
            case PAGE_EXECUTE_READWRITE:
                strcpy(entry->protection, "rwx");
                break;
            case PAGE_READONLY:
                return NULL;
                strcpy(entry->protection, "r--");
                break;
            case PAGE_READWRITE:
                return NULL;
                strcpy(entry->protection, "rw-");
                break;
            case PAGE_NOACCESS:
                return NULL;
                strcpy(entry->protection, "---");
                break;
            default:
                return NULL;
                strcpy(entry->protection, "???");
                break;
        }

        strcpy(entry->type, (pMemInfo.Type == MEM_PRIVATE ? "private" : (pMemInfo.Type == MEM_IMAGE ? "image" : (pMemInfo.Type == MEM_MAPPED ? "mapped" : "UNKNOWN_TYPE"))));
        return entry;
    }

    return NULL;
}

std::vector<AllocationEntry*> getMemoryMap()
{
    HANDLE h = GetCurrentProcess();
    SYSTEM_INFO info;
    GetSystemInfo(&info);

    MEMORY_BASIC_INFORMATION pMemInfo;
    void* regionStart = info.lpMinimumApplicationAddress;
    std::vector<AllocationEntry*> entries;

    while(regionStart < info.lpMaximumApplicationAddress){
        VirtualQueryEx(h, regionStart, &pMemInfo, sizeof(pMemInfo));
        regionStart = pMemInfo.BaseAddress + pMemInfo.RegionSize;

        AllocationEntry* entry = createMemEntry(pMemInfo);
        if(entry)
            entries.push_back(entry);
    }

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
    MODULEENTRY32 me32;
    me32.dwSize = sizeof(MODULEENTRY32);

    if(Module32First( snapshot, &me32 )) {
        do{
            DWORD address = (DWORD)me32.modBaseAddr;
            for(int i=0; i<entries.size(); i++)
                if((DWORD)(entries[i]->baseAddr) >= address && (DWORD)(entries[i]->baseAddr+entries[i]->size) <= (address+me32.modBaseSize))
                    strcpy(entries[i]->moduleName, me32.szExePath);

        } while(Module32Next(snapshot, &me32));
    }

    return entries;
}

void WindowsMemoryMap::performCheck(ViolationTable *v)
{
    std::vector<AllocationEntry*> maps = getMemoryMap();

    if(this->previousMap->size() > 0){
        for(std::vector<AllocationEntry*>::iterator entry = maps.begin(); entry != maps.end(); ++entry){

            if(!*entry)
                continue;

            std::map<int, AllocationEntry*>::iterator prev =
                this->previousMap->find((int)(*entry)->baseAddr);

            /*cout << "AllocBase: " << (*entry)->allocBase << endl;
            cout << "RegionSiz: " << std::hex << (*entry)->size << endl;
            cout << "BaseAddrs: " << (*entry)->baseAddr << endl;
            cout << "Type     : " << (*entry)->type << endl;
            cout << "Module   : " << (*entry)->moduleName << endl;
            cout << "Protect  : " << (*entry)->protection << endl;
            cout << endl;*/

            if(!strstr((*entry)->type, "image") && prev == this->previousMap->end()){
                v->blackBox.memoryRegionAppeaared+=1;
            }

            if(prev != this->previousMap->end()){
                if (strcmp(prev->second->protection, (*entry)->protection) != 0){
                    v->blackBox.memoryProtectionChanged+=1;
                }

                if(strstr((*entry)->protection, "x")){
                    unsigned char* xRegion = new unsigned char[(*entry)->size];
                    memcpy(xRegion, (*entry)->baseAddr, (*entry)->size);
                    string xRegionHash = sha256(xRegion, (*entry)->size);

                    std::map<int,  string>::iterator xOldRegionHash = this->xHashes->find((int)(*entry)->baseAddr);
                    if(xOldRegionHash == this->xHashes->end())
                         this->xHashes->insert({(int)(*entry)->baseAddr, xRegionHash});
                    else if(xOldRegionHash->second != xRegionHash){
                        v->blackBox.memoryExecutableModified += 1;
                        xOldRegionHash->second = xRegionHash;
                    }
                }
            }
        }
    }

    this->previousMap->clear();
    for(std::vector<AllocationEntry*>::iterator entry = maps.begin(); entry != maps.end(); ++entry){
        this->previousMap->insert({(int)(*entry)->baseAddr, *entry});
        if(strstr((*entry)->protection, "x") && strstr((*entry)->protection, "w"))
            v->blackBox.memoryWritebleXRegion++;
    }
}
