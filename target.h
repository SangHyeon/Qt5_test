#ifndef TARGET_H
#define TARGET_H

#include "object.h"

class Target : public Object
{
public:
    Target() = default;
    virtual void draw() override;
};

#endif // TARGET_H
