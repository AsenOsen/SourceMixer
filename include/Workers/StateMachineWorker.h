#ifndef STATEMACHINEWORKER_H
#define STATEMACHINEWORKER_H

#include "Workers/Worker.h"

class StateMachineWorker : public Worker
{
    public:
        StateMachineWorker();
        virtual ~StateMachineWorker();
        virtual WORKER_FUNCTION delegate();
        virtual void postTask(WORKER_FUNCTION task);

    protected:

    private:
};

#endif // STATEMACHINEWORKER_H
