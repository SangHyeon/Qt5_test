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
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void get_position(GLfloat *t_one, GLfloat *t_two, GLfloat *t_three, GLfloat *t_four);
    void get_target(GLfloat *t_one, GLfloat *t_two, GLfloat *t_three, GLfloat *t_four);
    void set_target(int n);
    void set_move(int n);

    void unProject(int xCursor, int yCursor);

signals:

public slots:

private:
    int target_flag;
    int move_flag;
    int drag_flag;
    QTimer qtimer;
    GLdouble wx, wy, wz;
    GLfloat one[3];
    GLfloat two[3];
    GLfloat three[3];
    GLfloat four[3];

    GLfloat target_one[3];
    GLfloat target_two[3];
    GLfloat target_three[3];
    GLfloat target_four[3];

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
