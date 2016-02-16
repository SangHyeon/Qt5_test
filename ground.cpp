#include "ground.h"

void Ground::draw()
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

    for(int i=0; i<=50; i++) {
        glPushMatrix();
        glTranslatef(_posx, _posy, _posz+i*200);
        glRotatef(_rotx, 1.0f, 0.0f, 0.0f);
        glRotatef(_roty, 0.0f, 1.0f, 0.0f);
        glRotatef(_rotz, 0.0f, 0.0f, 1.0f);

        glScalef(100, 0, 0);
        glutWireCube(100);

        glPopMatrix();
    }

    for(int i=0; i<=50; i++) {
        glPushMatrix();
        glTranslatef((_posx-5000)+i*200, _posy, _posz+5000);
        glRotatef(_rotx, 1.0f, 0.0f, 0.0f);
        glRotatef(_roty+90, 0.0f, 1.0f, 0.0f);
        glRotatef(_rotz, 0.0f, 0.0f, 1.0f);

        glScalef(100, 0, 0);
        glutWireCube(100);

        glPopMatrix();
    }
}
