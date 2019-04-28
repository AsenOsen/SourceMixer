#include "Alternative/AlternativeTable.h"

AlternativeTable::AlternativeTable(Alternative* alternatives, unsigned int count, int id) :
    alternatives(alternatives), count(count), identity(id)
{
    //ctor
}

AlternativeTable::~AlternativeTable()
{
    //dtor
}
