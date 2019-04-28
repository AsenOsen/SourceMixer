#include "Workers/StateMachineWorker.h"

#include <thread>
#include <chrono>
#include <iostream>

namespace StateMachineWorkerNS{
    static void workerFunc();
}

StateMachineWorker::StateMachineWorker()
{
    //ctor
}

StateMachineWorker::~StateMachineWorker()
{
    //dtor
}

WORKER_FUNCTION StateMachineWorker::delegate()
{
    return StateMachineWorkerNS::workerFunc;
}

void StateMachineWorker::postTask(WORKER_FUNCTION task)
{

}

void StateMachineWorkerNS::workerFunc()
{
    // check securityThreadWorking
    // check current stateCode
    // "ping" state "state_checked"

    while(1){
        //std::cout << "Stater!" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
