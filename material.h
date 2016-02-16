#ifndef MATERIAL_H
#define MATERIAL_H

#include "color4f.h"

class Material
{
public:

    Material() = default;

    Material(const Material& copy)
    {
       setMaterial(copy.ambient, copy.diffuse, copy.specular, copy.shiness);
    }

    Material& operator=(const Material& copy)
    {
        if ( &copy == this)
            return *this;
        setMaterial(copy.ambient, copy.diffuse, copy.specular, copy.shiness);
        return *this;
    }

    void setMaterial(Color4F a, Color4F d, Color4F s, float shine)
    {
        ambient = a;
        diffuse = d;
        specular = s;
        shiness = shine;
    }


    Color4F ambient;
    Color4F diffuse;
    Color4F specular;
    float shiness;

};

#endif // MATERIAL_H
