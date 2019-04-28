#ifndef MODULEBASE_H
#define MODULEBASE_H

#include "Alternative/Alternative.h"
#include "Alternative/AlternativeTable.h"
#include "Workers/Worker.h"
#include "Workers/SecurityWorker.h"
#include "ViolationTable.h"
#include "Decision.h"

#include <iostream>
#include <ctime>
#include <chrono>
#include <map>
#include <thread>
#include <mutex>

/*Оригинальная точка входа*/
#define MODULEBASE_INIT(table)\
    do{\
        /*Добавление альтернатив в настоящую таблицу*/ \
        if(table)\
            ModuleBase::workflowAlternatives->insert({((AlternativeTable*)table)->getId(), table});\
        /*Передача управления управляющей подсистеме модуля*/ \
        MODULEBASE_CHECK_SECURE_STATE()\
    } while(false)

/*Ложная точка входа*/
#define MODULEBASE_FAKE_INIT(table)\
    do{\
        std::map<int, AlternativeTable*> fakeAlternativesMap;\
        /*Добавление альтернатив в ложную таблицу*/ \
        if(table)\
            fakeAlternativesMap.insert({ ((AlternativeTable*)table)->getId(), (AlternativeTable*)table });\
        /*Передача управления управляющей подсистеме модуля*/ \
        MODULEBASE_CHECK_SECURE_STATE()\
    }while(false)

#define MODULEBASE_CHECK_SECURE_STATE()\
    do{\
        if(ModuleBase::firstRun){\
            ModuleBase::setupWorkers();\
            ModuleBase::firstRun = false;\
            if(ModuleBase::getElapsedSinceAppStart() > 1000){\
                ViolationTable::global->threadsRunTooLate++;\
            }\
        }\
        MODULEBASE_CALL_SECURITY_MODULES();\
    } while(false);

#include "Modules/MemoryProtect/MemoryProtect.h"
#include "Modules/GlobalViolation/GlobalViolation.h"
#define MODULEBASE_CALL_SECURITY_MODULES()\
    do{\
        ViolationTable* v = new ViolationTable();\
        MemoryProtect::call(v);\
        GlobalViolation::call(v);\
        DECISION_DECIDE(v);\
        \
    } while(false);\

using namespace std;

class ModuleBase
{
    public:

        ModuleBase();
        virtual ~ModuleBase();

        inline static long getElapsedSinceAppStart()
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>(
                                    std::chrono::system_clock::now().time_since_epoch()).count() - ModuleBase::appStartTime;
        }

        static std::map<int, AlternativeTable*> *workflowAlternatives;
        static mutex* _initMutex;
        static bool firstRun;
        static long appStartTime;


        inline static void setupWorkers()
        {
            Worker *workers[] = {
                new SecurityWorker()
            };

            for(int i=0; i<sizeof(workers)/sizeof(Worker); i++){
                std::thread t(workers[i]->delegate());
                t.detach();
            }
        }

        inline static void substitute()
        {
            for(
                std::map<int, AlternativeTable*>::iterator it = ModuleBase::workflowAlternatives->begin();
                it != ModuleBase::workflowAlternatives->end(); it++){

                    Alternative* alternativesFlow = it->second->getAlternatives();
                    int sz = it->second->getCount();

                    if(rand() % 2){
                        for(int i=0; i<sz; i++){
                                void** tmp = *(alternativesFlow[i].actual);
                                *(alternativesFlow[i].actual) = *(alternativesFlow[i].alternative);
                                *(alternativesFlow[i].alternative) = tmp;
                        }
                    }
                }
        }
};

#endif // MODULEBASE_H
