#include <iostream>
#include "ModuleBase.h"

ModuleBase::ModuleBase()
{
    //ctor
}

ModuleBase::~ModuleBase()
{
    //dtor
}

bool ModuleBase::firstRun = true;
std::map<int, AlternativeTable*>* ModuleBase::workflowAlternatives = new map<int, AlternativeTable*>();
mutex* ModuleBase::_initMutex = new mutex();
long ModuleBase::appStartTime = ModuleBase::getElapsedSinceAppStart();
