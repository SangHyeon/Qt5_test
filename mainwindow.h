#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
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
    //virtual void mousePressEvent(QMouseEvent *event);
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

    void getPosition(QString s);
    //int get_flag();

    //void on_pushButton_2_clicked();

    void on_connectButton_clicked();

    void on_forward_button_pressed();

    void on_forward_button_released();

    void on_right_button_pressed();

    void on_right_button_released();

    void on_left_button_pressed();

    void on_left_button_released();

    void on_back_button_pressed();

    void on_back_button_released();

    void on_up_button_pressed();

    void on_up_button_released();

    void on_down_button_pressed();

    void on_down_button_released();

    void on_take_off_button_clicked();

    void on_landing_button_clicked();

    void on_stop_button_clicked();

    void on_form1_button_clicked();

    void on_form2_button_clicked();

    void on_form3_button_clicked();

    void on_manual_button_clicked();

//    void on_horizontalSlider_valueChanged(int value);

    void on_form4_button_clicked();

    void on_auto_button_clicked();

    void on_debug_button_clicked();

    void on_lineEdit_editingFinished();

    void on_form5_button_clicked();

    void on_target_button_clicked();

private:
    Ui::MainWindow *ui;

    QTcpSocket tcpSocket; //socket
    int nextBlockSize;

    int connect_flag;
    int disconnect_flag;
    int press_flag;
    int manual_flag;
    int auto_flag;
    int form_flag;
    int landing_flag;
    int takeoff_flag;
    int debug_flag;
    int target_flag;

    QString ip_address;

    QByteArray TOPIC;
    //QByteArray TOPIC2;

    GLfloat one[3];
    GLfloat two[3];
    GLfloat three[3];
    GLfloat four[3];

    GLfloat target_one[3];
    GLfloat target_two[3];
    GLfloat target_three[3];
    GLfloat target_four[3];


};

#endif // MAINWINDOW_H
