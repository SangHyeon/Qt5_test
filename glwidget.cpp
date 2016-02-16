#include "glwidget.h"
//#include "ui_mainwindow.h"

#include "cube.h"
#include <algorithm>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{   
    connect(&qtimer, SIGNAL(timeout()), this, SLOT(update()));
    qtimer.start(16);

    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
    scaling = 1.0f;
    rotationX = 0.0;
    rotationY = 0.0;
    rotationZ = 0.0;
    transrationX = 0.0;
    transrationY = 0.0;
    transrationZ = 0.0;
}

GLWidget::~GLWidget()
{
    for(int i = 0 ; i < objects.size() ; ++ i)
    {
        delete objects[i];
        objects[i] = NULL;
    }

    objects.clear();
}

void GLWidget::initializeGL()
{
    Material goldColor;
    goldColor.ambient = Color4F( 0.24725f, 0.2245f, 0.0645f, 1.0f );
    goldColor.diffuse = Color4F( 0.34615f, 0.3143f, 0.0903f, 1.0f );
    goldColor.specular = Color4F( 0.797357f, 0.723991f, 0.366065f, 1.0f );
    goldColor.shiness = 83.4f;

    Material bronzeColor;
    bronzeColor.ambient = Color4F( 0.2125f, 0.1275f, 0.054f, 1.0f );
    bronzeColor.diffuse = Color4F( 0.714f, 0.4284f, 0.18144f, 1.0f );
    bronzeColor.specular = Color4F( 0.3935f, 0.2719f, 0.1667f, 1.0f );
    bronzeColor.shiness = 25.6f;


    Cube* c1 = new Cube;
    c1->setMaterial(goldColor);
    c1->setPosition(100,  100, 100);
    c1->setRotation(45,0,0);

    Cube* c2 = new Cube;
    c2->setMaterial(bronzeColor);
    c2->setPosition(200,  100, 100);
    c2->setRotation(45,0,0);

    objects.push_back(c1);
    objects.push_back(c2);


    int w = 800;
    int h = 450;

    one[0]=0;
    one[1]=0;
    one[2]=0;

    two[0]=0;
    two[1]=0;
    two[2]=0;

    three[0]=0;
    three[1]=0;
    three[2]=0;

    four[0]=0;
    four[1]=0;
    four[2]=0;

    GLfloat LightPos[] = { 5000.0f, 5000.0f, 6000.0f, 1.0 };
    GLfloat LightDir[] = { 0.0f, 0.0f, -1.0f, 1.0 };

    GLfloat AmbientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat DiffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat SpecularLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, LightDir);

    glEnable(GL_COLOR_MATERIAL);
    glMatrixMode(GL_PROJECTION);
    glViewport(0,0, w, h);
    gluPerspective(30.0f, (float)w / (float)h, 0.5f, 50000.0f);
    gluLookAt(45.0f, 45.0f, 1500, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    glMatrixMode(GL_MODELVIEW);

}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    GLfloat dx = GLfloat(event->x() - lastPos.x()) / width();
    GLfloat dy = GLfloat(event->y() - lastPos.y()) / height();
    if (event->buttons() & Qt::LeftButton) {
        rotationX += 180 * dy;
        rotationY += 180 * dx;
        updateGL();
    } else if (event->buttons() & Qt::RightButton) {
        transrationX += dx*200;
        transrationY -= dy*200;
        updateGL();
    } else if (event->buttons() & Qt::MidButton) {
        rotationZ  += 200*dx;
        updateGL();
    }
    lastPos = event->pos();
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    double numDegrees = -event->delta()/8.0;
    double numSteps = numDegrees/15.0;
    scaling *= pow(1.125,numSteps);
    updateGL();
}

int h = 450;

void GLWidget::paintGL() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); //좌표계를 리셋합니다.
    glTranslatef(transrationX,transrationY,0.0);
    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);
    glRotatef(rotationZ, 0.0, 0.0, 1.0);
    glScalef(scaling,scaling,scaling);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


    glBegin(GL_LINES);
    {
        glColor3d(255,0,0);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(3000, 0.0f, 0.0f);
    }
    glEnd();

    // y
    glBegin(GL_LINES);
    {
        glColor3d(0, 255, 0);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 3000, 0.0f);
    }
    glEnd();

    // z
    glBegin(GL_LINES);
    {
        glColor3d(0, 0, 255);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 3000);
    }
    glEnd();


    for(int i = 0 ; i < (int)objects.size() ; ++ i)
    {

        objects[i]->setPosition(objects[i]->getPositionX() + 1,
                                objects[i]->getPositionY() + 1,
                                objects[i]->getPositionZ() + 1);

        objects[i]->setRotation(objects[i]->getRotationX() + 1.1f,
                                objects[i]->getRotationY() + 1.1f,
                                objects[i]->getRotationZ() + 1.1f);



        objects[i]->draw();
    }

}

void GLWidget::resizeGL(int w, int h) {
    this->resize(w, h);
    glViewport(0,0, w, h);
}

void GLWidget::test_button(GLfloat *t_one, GLfloat *t_two, GLfloat *t_three, GLfloat *t_four) {
    one[0]=t_one[0];
    one[1]=t_one[1];
    one[2]=t_one[2];

    two[0]=t_two[0];
    two[1]=t_two[1];
    two[2]=t_two[2];

    three[0]=t_three[0];//130;
    three[1]=t_three[1];
    three[2]=t_three[2];//110;

    four[0]=t_four[0];
    four[1]=t_four[1];
    four[2]=t_four[2];
}
