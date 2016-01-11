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
       glRotatef(40.0f,1.0f,0.0f,0.0f);
       glRotatef(-40.0f,0.0f,1.0f,0.0f);
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

       /*glPointSize(10);
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
       */

       /*
        * read the drone data
        */
        GLfloat point_size[4];



        point_size[0] = (one[0]+one[1]+one[2])/60+10;
        point_size[1] = (two[0]+two[1]+two[2])/60+10;
        point_size[2] = (three[0]+three[1]+three[2])/60+10;
        point_size[3] = (four[0]+four[1]+four[2])/60+10;

       glPointSize(point_size[0]);
       glBegin(GL_POINTS);
       {
           glColor3f(255, 0, 0);
           glVertex3f(one[0], one[2], one[1]);
       }
       glEnd();

       glPointSize(point_size[1]);
       glBegin(GL_POINTS);
       {
           glColor3f(0, 255, 0);
           glVertex3f(two[0], two[2], two[1]);
       }
       glEnd();

       glPointSize(point_size[2]);
       glBegin(GL_POINTS);
       {
           glColor3f(255, 255, 255);
           glVertex3f(three[0], three[2], three[1]);
       }
       glEnd();

       glPointSize(point_size[3]);
       glBegin(GL_POINTS);
       {
           glColor3f(0, 0, 255);
           glVertex3f(four[0], four[2], four[1]);
       }
       glEnd();


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

}

void GLWidget::resizeGL(int w, int h) {

}
