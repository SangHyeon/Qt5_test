#ifndef OBJECT_H
#define OBJECT_H

#include "glwidget.h"
#include "material.h"

class Object
{

public:

    Object() = default;

    virtual ~Object() = default;
    virtual void draw() = 0;

    void setMaterial(const Material& m)
    {
        _material = m;
    }

    void setPosition(float x, float y, float z)
    {
        _posx = x;
        _posy = y;
        _posz = z;
    }

    void setRotation(float x, float y, float z)
    {
        _rotx = x;
        _roty = y;
        _rotz = z;
    }

    float getPositionX() const { return _posx; }
    float getPositionY() const { return _posy; }
    float getPositionZ() const { return _posz; }

    float getRotationX() const { return _rotx; }
    float getRotationY() const { return _roty; }
    float getRotationZ() const { return _rotz; }

protected:

    Material _material;

    // TODO
    // Vec3 _rotation;
    // Vec3 _transx;


    float _rotx;
    float _roty;
    float _rotz;

    float _posx;
    float _posy;
    float _posz;

};

#endif // OBJECT_H
