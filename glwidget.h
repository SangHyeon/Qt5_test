#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <glu.h>
#include <QTimer>
#include <QMouseEvent>
#include <math.h>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

signals:

public slots:

private:
    QTimer qtimer;
    float x, y, z;
    //0 : x, 1 : y, 2 : z
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

};

#endif // GLWIDGET_H
