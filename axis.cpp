#include "axis.h"

void Axis::draw()
{
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_BACK, GL_AMBIENT_AND_DIFFUSE);

    GLfloat a[4] = { _material.ambient.r, _material.ambient.g, _material.ambient.b, _material.ambient.a };
    GLfloat d[4] = { _material.diffuse.r, _material.diffuse.g, _material.diffuse.b, _material.diffuse.a };
/*
    Material redColor;
    redColor.ambient = Color4F( 0.7, 0.0, 0.0, 1.0f );
    redColor.diffuse = Color4F( 0.7, 0.0, 0.0, 1.0f );
    redColor.specular = Color4F( 0.7, 0.0, 0.0, 1.0f );
    redColor.shiness = 63.4f;

    Material greenColor;
    greenColor.ambient = Color4F( 0.0, 0.7, 0.0, 1.0f );
    greenColor.diffuse = Color4F( 0.0, 0.7, 0.0, 1.0f );
    greenColor.specular = Color4F( 0.0, 0.7, 0.0, 1.0f );
    greenColor.shiness = 63.4f;

    Material blueColor;
    blueColor.ambient = Color4F( 0.0, 0.0, 0.7, 1.0f );
    blueColor.diffuse = Color4F( 0.0, 0.0, 0.7, 1.0f );
    blueColor.specular = Color4F( 0.0, 0.0, 0.7, 1.0f );
    blueColor.shiness = 63.4f;
*/
    glMaterialfv(GL_FRONT, GL_AMBIENT, a);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, d);
    glMaterialf(GL_FRONT, GL_SHININESS, _material.shiness);

    glPushMatrix();
    glTranslatef(_posx, _posy, _posz);
    glRotatef(_rotx, 1.0f, 0.0f, 0.0f);
    glRotatef(_roty, 0.0f, 1.0f, 0.0f);
    glRotatef(_rotz, 0.0f, 0.0f, 1.0f);

    glScalef(3000, 5, 5);
    glutSolidCube(3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(_posx, _posy, _posz+4500);
    glRotatef(_rotx, 1.0f, 0.0f, 0.0f);
    glRotatef(_roty+90, 0.0f, 1.0f, 0.0f);
    glRotatef(_rotz, 0.0f, 0.0f, 1.0f);

    glScalef(3000, 5, 5);
    glutSolidCube(3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(_posx, _posy-1380, _posz);
    glRotatef(_rotx, 1.0f, 0.0f, 0.0f);
    glRotatef(_roty, 0.0f, 1.0f, 0.0f);

    glRotatef(_rotz+90, 0.0f, 0.0f, 1.0f);

    glScalef(920, 5, 5);
    glutSolidCube(3);
    glPopMatrix();
}
