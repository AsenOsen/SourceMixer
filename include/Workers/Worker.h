#ifndef WORKER_H
#define WORKER_H

typedef void (*WORKER_FUNCTION)();

class Worker
{
    public:
        Worker();
        virtual ~Worker();
        virtual WORKER_FUNCTION delegate() = 0;
        /*
            StateMachine state changeable task
        */
        virtual void postTask(WORKER_FUNCTION task) = 0;

    protected:

    private:
};

#endif // WORKER_H
