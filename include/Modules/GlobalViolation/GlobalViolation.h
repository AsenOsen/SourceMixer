#ifndef GLOBALVIOLATION_H
#define GLOBALVIOLATION_H

#include "ViolationTable.h"

class GlobalViolation
{
    public:
        GlobalViolation();
        virtual ~GlobalViolation();

        static inline void call(ViolationTable* v){

            v->blackBox.debugBreakPointDetected+=ViolationTable::global->securityWorkerLongCycle;
            ViolationTable::global->securityWorkerLongCycle = 0;

            v->blackBox.instrumentationDetected+=ViolationTable::global->threadsRunTooLate;
            v->grayBox.sandboxDetected+=ViolationTable::global->threadsRunTooLate;
            ViolationTable::global->threadsRunTooLate = 0;

        }

    protected:

    private:
};

#endif // GLOBALVIOLATION_H
