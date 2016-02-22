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

    // //////////////////////////////////////
    // drone crash zone
    /*glPushMatrix();
    glTranslatef(_posx+200, _posy+50, _posz);
    glRotatef(_rotx+90, 1.0f, 0.0f, 0.0f);
    glRotatef(_roty, 0.0f, 1.0f, 0.0f);
    glRotatef(_rotz, 0.0f, 0.0f, 1.0f);

    glScalef(100, 100, 100);
    // tong radian useless ?
    //glutSolidTorus(0.275, 0.85, 10, 15);
    glutSolidTorus(0.065, 0.85, 100, 150);
    //glutWireSphere(300, 7, 7);

    glPopMatrix();*/
    // ///////////////////////////////////////

    ///////////////////////////////////////////////

    //propeler
    p_roty += 37;
    glPushMatrix();
    glTranslatef(_posx+140, _posy+10, _posz-140);
    glRotatef(_rotx, 1.0f, 0.0f, 0.0f);
    glRotatef(p_roty, 0.0f, 1.0f, 0.0f);
    glRotatef(_rotz, 0.0f, 0.0f, 1.0f);


    glScalef(16, 1, 3);

    //glScalef(100, 100, 100);
    //glutSolidTorus(0.065, 0.85, 50, 75);
    glutSolidSphere(5, 100, 100);

    glPopMatrix();

    glPushMatrix();
    glTranslatef(_posx+140, _posy+10, _posz+140);
    glRotatef(_rotx, 1.0f, 0.0f, 0.0f);
    glRotatef(p_roty*(-1), 0.0f, 1.0f, 0.0f);
    glRotatef(_rotz, 0.0f, 0.0f, 1.0f);


    glScalef(16, 1, 3);
    //glScalef(100, 100, 100);
    //glutSolidTorus(0.065, 0.85, 50, 75);
    glutSolidSphere(5, 100, 100);

    glPopMatrix();

    glPushMatrix();
    glTranslatef(_posx-140, _posy+10, _posz+140);
    glRotatef(_rotx, 1.0f, 0.0f, 0.0f);
    glRotatef(p_roty, 0.0f, 1.0f, 0.0f);
    glRotatef(_rotz, 0.0f, 0.0f, 1.0f);


    glScalef(16, 1, 3);
    //glScalef(100, 100, 100);
    //glutSolidTorus(0.065, 0.85, 50, 75);
    glutSolidSphere(5, 100, 100);

    glPopMatrix();

    glPushMatrix();
    glTranslatef(_posx-140, _posy+10, _posz-140);
    glRotatef(_rotx, 1.0f, 0.0f, 0.0f);
    glRotatef(p_roty*(-1), 0.0f, 1.0f, 0.0f);
    glRotatef(_rotz, 0.0f, 0.0f, 1.0f);


    glScalef(16, 1, 3);
    //glScalef(100, 100, 100);
    //glutSolidTorus(0.065, 0.85, 50, 75);
    glutSolidSphere(5, 100, 100);

    glPopMatrix();

    ///////////////////////////////////////////////
    //draw cones
    glPushMatrix();
    glTranslatef(_posx+140, _posy+13, _posz-140);
    glRotatef(_rotx-90, 1.0f, 0.0f, 0.0f);
    glRotatef(_roty, 0.0f, 1.0f, 0.0f);
    glRotatef(_rotz, 0.0f, 0.0f, 1.0f);

    glScalef(3, 3, 3);
    glutSolidCone(4, 3, 30, 30);

    glPopMatrix();

    glPushMatrix();
    glTranslatef(_posx+140, _posy+13, _posz+140);
    glRotatef(_rotx-90, 1.0f, 0.0f, 0.0f);
    glRotatef(_roty, 0.0f, 1.0f, 0.0f);
    glRotatef(_rotz, 0.0f, 0.0f, 1.0f);

    glScalef(3, 3, 3);
    glutSolidCone(4, 3, 30, 30);

    glPopMatrix();

    glPushMatrix();
    glTranslatef(_posx-140, _posy+13, _posz+140);
    glRotatef(_rotx-90, 1.0f, 0.0f, 0.0f);
    glRotatef(_roty, 0.0f, 1.0f, 0.0f);
    glRotatef(_rotz, 0.0f, 0.0f, 1.0f);

    glScalef(3, 3, 3);
    glutSolidCone(4, 3, 30, 30);

    glPopMatrix();

    glPushMatrix();
    glTranslatef(_posx-140, _posy+13, _posz-140);
    glRotatef(_rotx-90, 1.0f, 0.0f, 0.0f);
    glRotatef(_roty, 0.0f, 1.0f, 0.0f);
    glRotatef(_rotz, 0.0f, 0.0f, 1.0f);

    glScalef(3, 3, 3);
    glutSolidCone(4, 3, 30, 30);

    glPopMatrix();


    ///////////////////////////////////////////////

    //torus
    glPushMatrix();
    glTranslatef(_posx+140, _posy+10, _posz-140);
    glRotatef(_rotx+90, 1.0f, 0.0f, 0.0f);
    glRotatef(_roty, 0.0f, 1.0f, 0.0f);
    glRotatef(_rotz, 0.0f, 0.0f, 1.0f);


    //glScalef(18, 1, 18);
    glScalef(100, 100, 100);
    glutSolidTorus(0.065, 0.85, 50, 75);
    //glutSolidSphere(5, 100, 100);

    glPopMatrix();

    glPushMatrix();
    glTranslatef(_posx-140, _posy+10, _posz+140);
    glRotatef(_rotx+90, 1.0f, 0.0f, 0.0f);
    glRotatef(_roty, 0.0f, 1.0f, 0.0f);
    glRotatef(_rotz, 0.0f, 0.0f, 1.0f);

    //glScalef(18, 1, 18);
    glScalef(100, 100, 100);
    glutSolidTorus(0.065, 0.85, 50, 75);
    //glutSolidSphere(5, 100, 100);

    glPopMatrix();

    glPushMatrix();
    glTranslatef(_posx+140, _posy+10, _posz+140);
    glRotatef(_rotx+90, 1.0f, 0.0f, 0.0f);
    glRotatef(_roty, 0.0f, 1.0f, 0.0f);
    glRotatef(_rotz, 0.0f, 0.0f, 1.0f);

    //glScalef(18, 1, 18);
    glScalef(100, 100, 100);
    glutSolidTorus(0.065, 0.85, 50, 75);
    //glutSolidSphere(5, 100, 100);

    glPopMatrix();

    glPushMatrix();
    glTranslatef(_posx-140, _posy+10, _posz-140);
    glRotatef(_rotx+90, 1.0f, 0.0f, 0.0f);
    glRotatef(_roty, 0.0f, 1.0f, 0.0f);
    glRotatef(_rotz, 0.0f, 0.0f, 1.0f);

    //glScalef(18, 1, 18);
    glScalef(100, 100, 100);
    glutSolidTorus(0.065, 0.85, 50, 75);
    //glutSolidSphere(5, 100, 100);

    glPopMatrix();

    ///////////////////////////////////////////////

    //body
    glPushMatrix();
    glTranslatef(_posx, _posy, _posz);
    glRotatef(_rotx, 1.0f, 0.0f, 0.0f);
    glRotatef(_roty+45, 0.0f, 1.0f, 0.0f);
    glRotatef(_rotz, 0.0f, 0.0f, 1.0f);

    glScalef(5, 2, 80);
    glutSolidCube(5);

    glPopMatrix();

    glPushMatrix();
    glTranslatef(_posx, _posy, _posz);
    glRotatef(_rotx, 1.0f, 0.0f, 0.0f);
    glRotatef(_roty+45, 0.0f, 1.0f, 0.0f);
    glRotatef(_rotz, 0.0f, 0.0f, 1.0f);

    glScalef(80, 2, 5);
    glutSolidCube(5);

    glPopMatrix();
}

