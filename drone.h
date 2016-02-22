#ifndef DRONE_H
#define DRONE_H

#include "object.h"

class Drone : public Object
{
public:
    Drone() {
        p_roty = _roty;
    }

    virtual void draw() override;

private:
    float p_roty;
};

#endif // DRONE_H
