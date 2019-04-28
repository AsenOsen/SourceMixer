#ifndef ALTERNATIVETABLE_H
#define ALTERNATIVETABLE_H

#include "Alternative.h"

class AlternativeTable
{
    public:
        AlternativeTable(Alternative* alternatives, unsigned int count, int id);
        virtual ~AlternativeTable();

        Alternative* getAlternatives(){
            return this->alternatives;
        }

        int getCount(){
            return this->count;
        }

        int getId(){
            return this->identity;
        }

    protected:

    private:
        Alternative* alternatives;
        unsigned int count;
        int identity;
};

#endif // ALTERNATIVETABLE_H
