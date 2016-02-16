#ifndef COLOR4F_H
#define COLOR4F_H

#include "glwidget.h"

class Color4F
{

public:

    Color4F() = default;

    Color4F(float r, float g, float b, float a)
    {
        setColor(r, g, b, a);
    }

    Color4F(const Color4F& copy)
    {
        setColor(copy.r, copy.g, copy.b, copy.a);
    }

    Color4F& operator=(const Color4F& copy)
    {
        if ( this == &copy )
            return *this;
        setColor(copy.r, copy.g, copy.b, copy.a);
        return *this;
    }

    void setColor(float rr, float gg, float bb, float aa)
    {
        r = rr;
        g = gg;
        b = bb;
        a = aa;
    }

    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;

};

#endif // COLOR4F_H
