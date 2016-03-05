#ifndef MOVE_GROUND_H
#define MOVE_GROUND_H

#include "object.h"

class move_ground : public Object
{
public:
    move_ground() = default;
    virtual void draw() override;
};

#endif // MOVE_GROUND_H
