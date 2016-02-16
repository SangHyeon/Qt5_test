#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <GL/glu.h>
#include <QTimer>
#include <QMouseEvent>
#include <math.h>
#include <GL/glut.h>
#include <QDebug>

#include <vector>

class Object;

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    virtual ~GLWidget();
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void test_button(GLfloat *t_one, GLfloat *t_two, GLfloat *t_three, GLfloat *t_four);

signals:

public slots:

private:
    QTimer qtimer;
    //float x, y, z;
    GLfloat one[3];
    GLfloat two[3];
    GLfloat three[3];
    GLfloat four[3];

    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;
    GLfloat transrationX;
    GLfloat transrationY;
    GLfloat transrationZ;
    GLfloat scaling;
    QPoint lastPos;

    std::vector<Object*> objects;

};

#endif // GLWIDGET_H
