#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <GL/glu.h>
#include <QTcpSocket>

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

protected:
    //void changeEvent(QEvent *e);

private slots:
    void connectToServer();
    void onConnectServer();
    void sendRequest();
    void readMessage();
    void connectionClosedByServer();
    void error();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    QTcpSocket tcpSocket; //socket
    int nextBlockSize;

    GLfloat one[3];
    GLfloat two[3];
    GLfloat three[3];
    GLfloat four[3];

};

#endif // MAINWINDOW_H
