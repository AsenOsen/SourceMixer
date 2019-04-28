#ifndef SECURITYWORKER_H
#define SECURITYWORKER_H

#include "Workers/Worker.h"

class SecurityWorker : public Worker
{
    public:
        SecurityWorker();
        virtual ~SecurityWorker();
        virtual WORKER_FUNCTION delegate();
        virtual void postTask(WORKER_FUNCTION task);

    protected:

    private:
};

#endif // SECURITYWORKER_H
