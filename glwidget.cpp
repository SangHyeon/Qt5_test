#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    connect(&qtimer, SIGNAL(timeout()), this, SLOT(update()));
    qtimer.start(16);
}

void GLWidget::initializeGL() {
    int w=800;
    int h = 800;
    x=y=z=0;
    glClearColor(1, 1, 0, 1);
    glMatrixMode(GL_PROJECTION);
       glViewport(0,0, w, h);
       gluPerspective(60.0f, (float)w / (float)h, 5.0f, 50000.0f);
       gluLookAt(0.0f, 0.0f, 800, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
       glMatrixMode(GL_MODELVIEW);
}

void GLWidget::paintGL() {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
       glClear(GL_COLOR_BUFFER_BIT);

       // Draw Scene

       // ui->render();

       // for(auto &d : copters)
       //    copter->render();

       glLoadIdentity();
       glRotatef(45.0f,1.0f,0.0f,0.0f);
       glRotatef(-45.0f,0.0f,1.0f,0.0f);
       glRotatef(0.0f,0.0f,0.0f,1.0f);

       // x
       glBegin(GL_LINES);
       {
          glColor3d(255,0,0);
          glVertex3f(0.0f, 0.0f, 0.0f);
          glVertex3f(300, 0.0f, 0.0f);
       }
       glEnd();

       // y
       glBegin(GL_LINES);
       {
          glColor3d(0, 255, 0);
          glVertex3f(0.0f, 0.0f, 0.0f);
          glVertex3f(0.0f, 300, 0.0f);
       }
       glEnd();

       // z
       glBegin(GL_LINES);
       {
          glColor3d(0, 0, 255);
          glVertex3f(0.0f, 0.0f, 0.0f);
          glVertex3f(0.0f, 0.0f, 300);
       }
       glEnd();

       glPointSize(10);
       glBegin(GL_POINTS);
       {

           glColor3f(255, 0, 0);
           glVertex3f(30+x, -45, 55);
           glColor3f(0, 255, 0);
           glVertex3f(-30, 45+y, 55);
           glColor3f(255, 255, 255);
           glVertex3f(-30, 45+y, 55+z);
           glColor3f(0, 0, 255);
           glVertex3f(30, 45, -55+z);
       }
       glEnd();
       if(x==300)
           x=y=z=0;
       else {
           x+=1;
           y+=1;
           z+=1;
       }

}

void GLWidget::resizeGL(int w, int h) {

}
