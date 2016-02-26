#include "glwidget.h"
#include "cube.h"
#include "axis.h"
#include "drone.h"
#include "ground.h"
#include "target.h"
#include <algorithm>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{   
    connect(&qtimer, SIGNAL(timeout()), this, SLOT(update()));
    qtimer.start(16);

    target_flag = 0;

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
    //ground = 2700

    Material whiteColor;
    whiteColor.ambient = Color4F( 0.3, 0.3, 0.3, 0.3f );
    whiteColor.diffuse = Color4F( 0.3, 0.3, 0.3, 0.3f );
    whiteColor.specular = Color4F( 0.3, 0.3, 0.3, 0.3f );
    whiteColor.shiness = 3.4f;

    Material redColor;
    redColor.ambient = Color4F( 0.3, 0.0, 0.0, 1.0f );
    redColor.diffuse = Color4F( 0.3, 0.0, 0.0, 1.0f );
    redColor.specular = Color4F( 0.3, 0.0, 0.0, 1.0f );
    redColor.shiness = 43.4f;

    Material t_redColor;
    t_redColor.ambient = Color4F( 0.6, 0.0, 0.0, 1.0f );
    t_redColor.diffuse = Color4F( 0.6, 0.0, 0.0, 1.0f );
    t_redColor.specular = Color4F( 0.6, 0.0, 0.0, 1.0f );
    t_redColor.shiness = 63.4f;

    Material greenColor;
    greenColor.ambient = Color4F( 0.0, 0.3, 0.0, 1.0f );
    greenColor.diffuse = Color4F( 0.0, 0.3, 0.0, 1.0f );
    greenColor.specular = Color4F( 0.0, 0.3, 0.0, 1.0f );
    greenColor.shiness = 43.4f;

    Material t_greenColor;
    t_greenColor.ambient = Color4F( 0.0, 0.6, 0.0, 1.0f );
    t_greenColor.diffuse = Color4F( 0.0, 0.6, 0.0, 1.0f );
    t_greenColor.specular = Color4F( 0.0, 0.6, 0.0, 1.0f );
    t_greenColor.shiness = 43.4f;

    Material blueColor;
    blueColor.ambient = Color4F( 0.0, 0.0, 0.3, 1.0f );
    blueColor.diffuse = Color4F( 0.0, 0.0, 0.3, 1.0f );
    blueColor.specular = Color4F( 0.0, 0.0, 0.3, 1.0f );
    blueColor.shiness = 43.4f;

    Material t_blueColor;
    t_blueColor.ambient = Color4F( 0.0, 0.0, 0.6, 1.0f );
    t_blueColor.diffuse = Color4F( 0.0, 0.0, 0.6, 1.0f );
    t_blueColor.specular = Color4F( 0.0, 0.0, 0.6, 1.0f );
    t_blueColor.shiness = 43.4f;

    Material goldColor;
    goldColor.ambient = Color4F( 0.24725f, 0.2245f, 0.0645f, 1.0f );
    goldColor.diffuse = Color4F( 0.34615f, 0.3143f, 0.0903f, 1.0f );
    goldColor.specular = Color4F( 0.797357f, 0.723991f, 0.366065f, 1.0f );
    goldColor.shiness = 63.4f;

    Material t_goldColor;
    t_goldColor.ambient = Color4F( 0.44725f, 0.4245f, 0.0845f, 1.0f );
    t_goldColor.diffuse = Color4F( 0.54615f, 0.5143f, 0.1103f, 1.0f );
    t_goldColor.specular = Color4F( 0.897357f, 0.823991f, 0.566065f, 1.0f );
    t_goldColor.shiness = 63.4f;

    Material bronzeColor;
    bronzeColor.ambient = Color4F( 0.2125f, 0.1275f, 0.054f, 1.0f );
    bronzeColor.diffuse = Color4F( 0.714f, 0.4284f, 0.18144f, 1.0f );
    bronzeColor.specular = Color4F( 0.3935f, 0.2719f, 0.1667f, 1.0f );
    bronzeColor.shiness = 25.6f;

    Axis* xxx = new Axis;
    xxx->setMaterial(bronzeColor);
    xxx->setPosition(0, 0, 0);
    xxx->setRotation(0, 0, 0);

    Drone* d1 = new Drone;
    d1->setMaterial(goldColor);
    d1->setPosition(100,  100, 100);
    d1->setRotation(0, 0, 0);

    Drone* d2 = new Drone;
    d2->setMaterial(redColor);
    d2->setPosition(200,  100, 100);
    d2->setRotation(0, 0, 0);

    Drone* d3 = new Drone;
    d3->setMaterial(greenColor);
    d3->setPosition(300,  100, 100);
    d3->setRotation(0, 0, 0);

    Drone* d4 = new Drone;
    d4->setMaterial(blueColor);
    d4->setPosition(400,  100, 100);
    d4->setRotation(0, 0, 0);

    Target* t1 = new Target;
    t1->setMaterial(t_goldColor);
    t1->setPosition(0, 0, 0);
    t1->setRotation(0, 0, 0);

    Target* t2 = new Target;
    t2->setMaterial(t_redColor);
    t2->setPosition(0, 0, 0);
    t2->setRotation(0, 0, 0);

    Target* t3 = new Target;
    t3->setMaterial(t_greenColor);
    t3->setPosition(0, 0, 0);
    t3->setRotation(0, 0, 0);

    Target* t4 = new Target;
    t4->setMaterial(t_blueColor);
    t4->setPosition(0, 0, 0);
    t4->setRotation(0, 0, 0);

    Cube* c1 = new Cube;
    c1->setMaterial(bronzeColor);
    c1->setPosition(450,  0, 0);
    c1->setRotation(57, 0, 0);

    Cube* c2 = new Cube;
    c2->setMaterial(bronzeColor);
    c2->setPosition(-450,  0, 0);
    c2->setRotation(57,0,0);

    Ground* c3 = new Ground;
    c3->setMaterial(whiteColor);
    c3->setPosition(0,  -2750, 0);
    c3->setRotation(0,0,0);

    objects.push_back(xxx);
    objects.push_back(d1);
    objects.push_back(d2);   
    objects.push_back(d3);
    objects.push_back(d4);
    objects.push_back(t1);
    objects.push_back(t2);
    objects.push_back(t3);
    objects.push_back(t4);
    objects.push_back(c1);
    objects.push_back(c2);
    objects.push_back(c3);


    int w = 800;
    int h = 450;
    //0 : x 1 : z 2 : y
    one[0]=0;
    one[1]=-100;
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
    gluPerspective(60.0f, (float)w / (float)h, 0.5f, 50000.0f);
    gluLookAt(0.0f, 0.0f, 4500, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
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

    for(int i = 0 ; i < (int)objects.size() ; ++ i)
    {
        if(i == 1)
            objects[i]->setPosition(one[0], one[1], one[2]);
        else if(i == 2)
            objects[i]->setPosition(two[0], two[1], two[2]);
        else if(i == 3)
            objects[i]->setPosition(three[0], three[1], three[2]);
        else if(i == 4)
            objects[i]->setPosition(four[0], four[1], four[2]);
        else if(i == 5) {
            if(target_flag == 0)
                continue;
            else {
                objects[i]->setPosition(target_one[0], target_one[1], target_one[2]);
            }
        }
        else if(i == 6) {
            if(target_flag == 0)
                continue;
            else {
                objects[i]->setPosition(target_two[0], target_two[1], target_two[2]);
            }
        }
        else if(i == 7) {
            if(target_flag == 0)
                continue;
            else {
                objects[i]->setPosition(target_three[0], target_three[1], target_three[2]);
            }
        }
        else if(i == 8) {
            if(target_flag == 0)
                continue;
            else {
                objects[i]->setPosition(target_four[0], target_four[1], target_four[2]);
            }
        }
        objects[i]->draw();
    }

}

void GLWidget::resizeGL(int w, int h) {
    this->resize(w, h);
    glViewport(0,0, w, h);
}

void GLWidget::get_position(GLfloat *t_one, GLfloat *t_two, GLfloat *t_three, GLfloat *t_four) {
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

void GLWidget::get_target(GLfloat *t_one, GLfloat *t_two, GLfloat *t_three, GLfloat *t_four) {
    target_one[0]=t_one[0];
    target_one[1]=t_one[1];
    target_one[2]=t_one[2];

    target_two[0]=t_two[0];
    target_two[1]=t_two[1];
    target_two[2]=t_two[2];

    target_three[0]=t_three[0];//130;
    target_three[1]=t_three[1];
    target_three[2]=t_three[2];//110;

    target_four[0]=t_four[0];
    target_four[1]=t_four[1];
    target_four[2]=t_four[2];
}

void GLWidget::set_target(int n) {
    target_flag = n;
}
