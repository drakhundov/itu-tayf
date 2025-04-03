#ifndef SAT_H
#define SAT_H

#include "Data.h"

class Satellite
{
public:
    Satellite();
    void UpdateData();
    Data GetData() const;

private:
    Data data;
};

#endif