#ifndef CUBE_H
#define CUBE_H

#include "object.h"

class Cube :  public Object
{

public:
    Cube() = default;
    virtual void draw() override;
};

#endif // DRONE_H
