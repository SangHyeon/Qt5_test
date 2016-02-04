#include "glwidget.h"
//#include "ui_mainwindow.h"

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

void GLWidget::initializeGL() {

    int w = 800;
    int h = 450;

    one[0]=130;
    one[1]=140;
    one[2]=190;

    two[0]=110;
    two[1]=170;
    two[2]=130;

    three[0]=0;//130;
    three[1]=140;
    three[2]=0;//110;

    four[0]=170;
    four[1]=140;
    four[2]=160;

    GLfloat MyLightPosition[] = {1.0, 2.0, 3.0, 1.0};
    GLfloat MyLightDirection[] = {3.0, 4.0, 3.0};       // 빛의 방향
    //GLfloat MySpotAngle[] = {50.0};                     // 조명각
    GLfloat MyLightDiffuse[] = {1.0, 0.0, 0.0, 1.0};    // 확산반사 입사광은 주로 적색

    glClearColor(1, 1, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);


    glLightfv(GL_LIGHT0, GL_POSITION, MyLightPosition);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, MyLightDirection);  // 방향 설정
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0);     // 승수 설정
    glLightfv(GL_LIGHT0, GL_DIFFUSE, MyLightDiffuse);

    glEnable(GL_COLOR_MATERIAL);
    glMatrixMode(GL_PROJECTION);
       glViewport(0,0, w, h);
       gluPerspective(30.0f, (float)w / (float)h, 0.5f, 50000.0f);
       gluLookAt(0.0f, 0.0f, 800, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
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
    glEnable(GL_CULL_FACE);
    //glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    //glLoadIdentity(); //좌표계를 리셋합니다.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); //좌표계를 리셋합니다.
    glTranslatef(transrationX,transrationY,0.0);
    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);
    glRotatef(rotationZ, 0.0, 0.0, 1.0);
    glScalef(scaling,scaling,scaling);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
       glClear(GL_COLOR_BUFFER_BIT);

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

        glPushMatrix();
             glColor3f(255, 0, 0);
             glTranslatef(one[0], one[2], one[1]);
             glScalef(3, 3, 3);
             glutSolidSphere(5, 50, 50);
             //glutSolidCube(5);
        glPopMatrix();
        //glFlush();

        glPushMatrix();
             glColor3f(0, 255, 0);
             glTranslatef(two[0], two[2], two[1]);
             glScalef(3, 3, 3);
             glutSolidCube(5);
        glPopMatrix();

        glPushMatrix();
             glColor3f(255, 255, 255);
             glTranslatef(three[0], three[2], three[1]);
             glScalef(3, 3, 3);
             glutSolidCube(5);
        glPopMatrix();

        glPushMatrix();
             glColor3f(0, 0, 255);
             glTranslatef(four[0], four[2], four[1]);
             glScalef(3, 3, 3);
             glutSolidCube(5);
        glPopMatrix();


       if(four[1] == 300) {
           one[0]=130;
           one[1]=140;
           one[2]=190;

           two[0]=110;
           two[1]=170;
           two[2]=130;

           three[0]=0;//130;
           three[1]=140;
           three[2]=0;//110;

           four[0]=170;
           four[1]=140;
           four[2]=160;
       }
       else {
           one[0]++;
           one[1]++;
           one[2]++;

           two[0]++;
           two[1]++;
           two[2]++;

           three[0]++;//130;
           three[1]++;
           three[2]++;//110;

           four[0]++;
           four[1]++;
           four[2]++;
       }

       glFlush();



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
