#include "Workers/SecurityWorker.h"

#include <thread>
#include <chrono>
#include <iostream>

#include "Modules/MemoryProtect/MemoryProtect.h"
#include "ModuleBase.h"
#include "ViolationTable.h"

namespace SecurityWorkerNS{
    static void workerFunc();
    static long lastExecute = -1;
}

SecurityWorker::SecurityWorker()
{
    //ctor
}

SecurityWorker::~SecurityWorker()
{
    //dtor
}

WORKER_FUNCTION SecurityWorker::delegate(){
     return SecurityWorkerNS::workerFunc;
}

void SecurityWorker::postTask(WORKER_FUNCTION task)
{

}

static void SecurityWorkerNS::workerFunc()
{
    SecurityWorkerNS::lastExecute =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    while(1){
        long now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

        if(now - SecurityWorkerNS::lastExecute >= 1500){
            ViolationTable::global->securityWorkerLongCycle++;
        }

        SecurityWorkerNS::lastExecute = now;
        MODULEBASE_CALL_SECURITY_MODULES();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
