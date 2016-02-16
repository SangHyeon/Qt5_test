#ifndef DRONE_H
#define DRONE_H

#include "object.h"

class Drone : public Object
{
public:
    Drone() = default;
    virtual void draw() override;
};

#endif // DRONE_H
