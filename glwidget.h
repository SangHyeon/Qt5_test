#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <glu.h>
#include <QTimer>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

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

};

#endif // GLWIDGET_H
