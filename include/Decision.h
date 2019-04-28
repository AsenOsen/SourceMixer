#ifndef DECISION_H
#define DECISION_H

#include <iostream>
#include <string.h>

#define DECISION_DECIDE(violations)\
    do{\
        if(violations->blackBox.memoryExecutableModified > 0){\
            ModuleBase::substitute();\
            std::cout << "Substituted." << std::endl;\
        }\
    } while(false)\


class Decision
{

    public:
        Decision();
        ~Decision();



};

#endif // DECISION_H
