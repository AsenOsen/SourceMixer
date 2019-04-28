#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <stack>
#include <iostream>

#define STATE_MODULEBASE_INIT                 1
#define STATE_MODULEBASE_FAKE_INIT            2
#define STATE_MODULEBASE_CHECKSECURESTATE     3
#define STATE_MODULEBASE_SETUPWORKERS         4


/*
    Stack-based state machine
    Needed for having assurance that security code executes.
*/
class StateMachine
{
    public:
        StateMachine();

        static void pushState(int actionCode){
            // change current state according to actionCode
            StateMachine::_state->push(actionCode);
        }

        static int popState(){
            // change current state according to actionCode
            int top = StateMachine::_state->top();
            StateMachine::_state->pop();
            return top;
        }

        inline static bool checkState(int* actions, int count)
        {
            int* poppedActions = new int[count];
            int j=0;

            for(int i=0; i<count; i++){
                if(StateMachine::_state->top() == actions[i]){
                    poppedActions[j++] = StateMachine::popState();
                } else{
                    for (int i=j-1; i>=0; i--){
                        StateMachine::pushState(poppedActions[i]);
                    }
                    return false;
                }
            }


            return j == count;
        }

        virtual ~StateMachine();

    protected:

    private:
        static std::stack<int>* _state;
};

#endif // STATEMACHINE_H
