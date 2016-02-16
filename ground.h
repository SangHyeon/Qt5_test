#ifndef GROUND_H
#define GROUND_H
#include "object.h"

class Ground : public Object
{
public:
    Ground() = default;
    virtual void draw() override;
};

#endif // GROUND_H
