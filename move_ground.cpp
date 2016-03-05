#include "move_ground.h"

void move_ground::draw() {
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_BACK, GL_AMBIENT_AND_DIFFUSE);

    GLfloat a[4] = { _material.ambient.r, _material.ambient.g, _material.ambient.b, _material.ambient.a };
    GLfloat d[4] = { _material.diffuse.r, _material.diffuse.g, _material.diffuse.b, _material.diffuse.a };
    glMaterialfv(GL_FRONT, GL_AMBIENT, a);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, d);
    glMaterialf(GL_FRONT, GL_SHININESS, _material.shiness);

    glPushMatrix();
    glTranslatef(_posx, _posy-30, _posz);
    glRotatef(_rotx+90, 1.0f, 0.0f, 0.0f);
    glRotatef(_roty, 0.0f, 1.0f, 0.0f);
    glRotatef(_rotz, 0.0f, 0.0f, 1.0f);

    glScalef(100, 100, 0.5);
    glutSolidCube(100);

    glPopMatrix();
}
