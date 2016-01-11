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

};

#endif // GLWIDGET_H
