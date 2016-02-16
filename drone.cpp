#include "drone.h"

void Drone::draw()
{
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_BACK, GL_AMBIENT_AND_DIFFUSE);

    GLfloat a[4] = { _material.ambient.r, _material.ambient.g, _material.ambient.b, _material.ambient.a };
    GLfloat d[4] = { _material.diffuse.r, _material.diffuse.g, _material.diffuse.b, _material.diffuse.a };
    //GLfloat s[4] = { _material.specular.r, _material.specular.g, _material.specular.b, _material.specular.a };

    glMaterialfv(GL_FRONT, GL_AMBIENT, a);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, d);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, s);
    glMaterialf(GL_FRONT, GL_SHININESS, _material.shiness);

    // (S = scale, R = rotation, T = translate)
    // SRT = 공전
    // STR = 자전
    /*glPushMatrix();
    glTranslatef(_posx, _posy, _posz);
    glRotatef(_rotx, 1.0f, 0.0f, 0.0f);
    glRotatef(_roty, 0.0f, 1.0f, 0.0f);
    glRotatef(_rotz, 0.0f, 0.0f, 1.0f);

    glScalef(20, 3, 20);
    glutSolidCube(5);

    glPopMatrix();*/

    glPushMatrix();
    glTranslatef(_posx+200, _posy+10, _posz);
    glRotatef(_rotx, 1.0f, 0.0f, 0.0f);
    glRotatef(_roty, 0.0f, 1.0f, 0.0f);
    glRotatef(_rotz, 0.0f, 0.0f, 1.0f);

    glScalef(18, 1, 18);
    glutSolidSphere(5, 100, 100);

    glPopMatrix();

    glPushMatrix();
    glTranslatef(_posx-200, _posy+10, _posz);
    glRotatef(_rotx, 1.0f, 0.0f, 0.0f);
    glRotatef(_roty, 0.0f, 1.0f, 0.0f);
    glRotatef(_rotz, 0.0f, 0.0f, 1.0f);

    glScalef(18, 1, 18);
    glutSolidSphere(5, 100, 100);

    glPopMatrix();

    glPushMatrix();
    glTranslatef(_posx, _posy+10, _posz+200);
    glRotatef(_rotx, 1.0f, 0.0f, 0.0f);
    glRotatef(_roty, 0.0f, 1.0f, 0.0f);
    glRotatef(_rotz, 0.0f, 0.0f, 1.0f);

    glScalef(18, 1, 18);
    glutSolidSphere(5, 100, 100);

    glPopMatrix();

    glPushMatrix();
    glTranslatef(_posx, _posy+10, _posz-200);
    glRotatef(_rotx, 1.0f, 0.0f, 0.0f);
    glRotatef(_roty, 0.0f, 1.0f, 0.0f);
    glRotatef(_rotz, 0.0f, 0.0f, 1.0f);

    glScalef(18, 1, 18);
    glutSolidSphere(5, 100, 100);

    glPopMatrix();

    glPushMatrix();
    glTranslatef(_posx, _posy, _posz);
    glRotatef(_rotx, 1.0f, 0.0f, 0.0f);
    glRotatef(_roty, 0.0f, 1.0f, 0.0f);
    glRotatef(_rotz, 0.0f, 0.0f, 1.0f);

    glScalef(5, 2, 80);
    glutSolidCube(5);

    glPopMatrix();

    glPushMatrix();
    glTranslatef(_posx, _posy, _posz);
    glRotatef(_rotx, 1.0f, 0.0f, 0.0f);
    glRotatef(_roty, 0.0f, 1.0f, 0.0f);
    glRotatef(_rotz, 0.0f, 0.0f, 1.0f);

    glScalef(80, 2, 5);
    glutSolidCube(5);

    glPopMatrix();
}

