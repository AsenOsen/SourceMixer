#include "StateMachine.h"

StateMachine::StateMachine()
{
    //ctor
}

StateMachine::~StateMachine()
{
    //dtor
}

std::stack<int>* StateMachine::_state = new std::stack<int>();
