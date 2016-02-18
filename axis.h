#ifndef AXIS_H
#define AXIS_H

#include "object.h"

class Axis : public Object
{
public:
    Axis() = default;
    virtual void draw() override;
};

#endif // AXIS_H
