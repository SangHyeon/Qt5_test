#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <GL/glu.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void quad_data(GLfloat *t_one, GLfloat *t_two, GLfloat *t_three, GLfloat *t_four);

public slots:
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    GLfloat one[3];
    GLfloat two[3];
    GLfloat three[3];
    GLfloat four[3];

};

#endif // MAINWINDOW_H
