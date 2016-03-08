#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "glwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    connect_flag = 0;
    disconnect_flag = 1;
    manual_flag = 0;
    auto_flag = 0;
    form_flag = 0;
    debug_flag = 0;
    target_flag = 0;
    ip_address = "112.108.39.230";

    ui->setupUi(this);

    this->nextBlockSize = 0;
    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(connectToServer()));
    connect(&tcpSocket, SIGNAL(connected()), this, SLOT(onConnectServer()));
    connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(&tcpSocket, SIGNAL(disconnected()), this, SLOT(connectionClosedByServer()));
    connect(&tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error()));

    //ui->horizontalSlider->setRange(1, 50);
    //ui->horizontalSlider->setValue(10);

    one[0]=0;
    one[1]=0;
    one[2]=0;

    two[0]=0;
    two[1]=0;
    two[2]=0;

    three[0]=0;
    three[1]=0;
    three[2]=0;

    four[0]=0;
    four[1]=0;
    four[2]=0;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::quad_data\
(GLfloat *t_one, GLfloat *t_two, GLfloat *t_three, GLfloat *t_four) {
    one[0]=t_one[0];
    one[1]=t_one[1];
    one[2]=t_one[2];

    two[0]=t_two[0];
    two[1]=t_two[1];
    two[2]=t_two[2];

    three[0]=t_three[0];//130;
    three[1]=t_three[1];
    three[2]=t_three[2];//110;

    four[0]=t_four[0];
    four[1]=t_four[1];
    four[2]=t_four[2];
}


void MainWindow::connectToServer() {

    qDebug() << "In connect To Server "<<connect_flag;
    if(connect_flag == 0) {
        tcpSocket.connectToHost(ip_address, 9090);
    }
    else if(connect_flag == 1 && disconnect_flag == 1) {
        connect_flag = 0;
    }
    //requier to servre for connect
}

//reference
//https://code.google.com/archive/p/brown-ros-pkg/wikis/RosbridgeProtocolMarkdown.wiki
void MainWindow::onConnectServer(){
    qDebug("connect Complete");

    connect_flag = 1;
    disconnect_flag = 0;
    press_flag = 0;
    manual_flag = 0;
    ui->connectButton->setText("disconnect");

    QByteArray msg = "raw\r\n\r\n";
    //QByteArray JSON = "{ \"op\" : \"subscribe\" , \"topic\" : \"/say_hello_world\"}";
    //QByteArray JSON = "{ \"op\" : \"subscribe\" , \"topic\" : \"/FIRST/NASANG\"}";
    //QByteArray JSON2 = "{ \"op\" : \"subscribe\" , \"topic\" : \"/SECOND/NASANG\"}";
    QByteArray JSON = "{ \"op\" : \"subscribe\" , \"topic\" : \"/FIRST/CURRENT_POS\"}";
    QByteArray JSON2 = "{ \"op\" : \"subscribe\" , \"topic\" : \"/SECOND/CURRENT_POS\"}";
    QByteArray JSON3 = "{ \"op\" : \"subscribe\" , \"topic\" : \"/THIRD/CURRENT_POS\"}";
    QByteArray JSON4 = "{ \"op\" : \"subscribe\" , \"topic\" : \"/FOURTH/CURRENT_POS\"}";

    QByteArray TARGET1 = "{ \"op\" : \"subscribe\" , \"topic\" : \"/FIRST/TARGET_POS\"}";
    QByteArray TARGET2 = "{ \"op\" : \"subscribe\" , \"topic\" : \"/SECOND/TARGET_POS\"}";
    QByteArray TARGET3 = "{ \"op\" : \"subscribe\" , \"topic\" : \"/THIRD/TARGET_POS\"}";
    QByteArray TARGET4 = "{ \"op\" : \"subscribe\" , \"topic\" : \"/FOURTH/TARGET_POS\"}";

    QByteArray ADVER = "{ \"op\" : \"advertise\" , \"topic\" : \"/hello_kun\", \"type\":\"std_msgs/String\"}";
    QByteArray ADVER2 = "{ \"op\" : \"advertise\" , \"topic\" : \"/hello_ahn\", \"type\":\"std_msgs/String\"}";
    TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"8\"}}";
    //TOPIC2 = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_ahn\", \"msg\" : {\"data\":\"10\"}}";
    tcpSocket.write(msg, msg.size());
    tcpSocket.write(JSON, JSON.size());
    tcpSocket.write(JSON2, JSON2.size());
    tcpSocket.write(JSON3, JSON3.size());
    tcpSocket.write(JSON4, JSON4.size());

    tcpSocket.write(TARGET1, TARGET1.size());
    tcpSocket.write(TARGET2, TARGET2.size());
    tcpSocket.write(TARGET3, TARGET3.size());
    tcpSocket.write(TARGET4, TARGET4.size());

    tcpSocket.write(ADVER, ADVER.size());
    tcpSocket.write(ADVER2, ADVER2.size());
    tcpSocket.write(TOPIC, TOPIC.size());
    //tcpSocket.write(TOPIC2, TOPIC2.size());

    qDebug("%d", msg.size());
    qDebug("%d", JSON.size());
    qDebug("send message!");

    ui->drone_first->setText(QString("Drone 1 :    %1     %2     %3").arg(one[0]).arg(one[1]).arg(one[2]));
    ui->drone_second->setText(QString("Drone 2 :    %1     %2     %3").arg(two[0]).arg(two[1]).arg(two[2]));
    ui->drone_third->setText(QString("Drone 3 :    %1     %2     %3").arg(three[0]).arg(three[1]).arg(three[2]));
    ui->drone_fourth->setText(QString("Drone 4 :    %1     %2     %3").arg(four[0]).arg(four[1]).arg(four[2]));
}

void MainWindow::sendRequest() {
    //need modifying
    /* QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out<<quint16(0);

    //out<<~~//read the data....
    out.device()->seek(0);

    out<<quint16(block.size() - sizeof(quint16));

    tcpSocket.write(block);//send to socket*/
}

void MainWindow::readMessage() {
    //read & send JSON m sgs
    //qDebug("ready for read data");
    QString line = QString::fromUtf8(tcpSocket.readLine()).trimmed();
    getPosition(line);
    //{"topic": "/FIRST/CURRENT_POS", "msg": {"y": 3000.0876808544454, "x": 1407.7433628318586, "z": -1780.8053665716345}, "op": "publish"}
    qDebug(line.toUtf8());
    //if(press_flag == 1) {
    //tcpSocket.write(TOPIC, TOPIC.size());
    //qDebug() << "===========fuck==========";
    //}
    ui->widget->get_position(one, two, three, four);
}

void MainWindow::getPosition(QString s) {
    QString tmp = s;
    QString tmp2 = tmp;
    QString tmp3 = tmp;
    QStringList ttt, num, mod;
    int yyy, xxx, zzz, command;

    num = tmp.split("/");
    mod = num[2].split("\"");
    qDebug() << mod[0];


    if(mod[0] == "CURRENT_POS") {//NASANG
        ttt = tmp.split("y");
        tmp = ttt[1];
        ttt = tmp.split(" ");
        tmp = ttt[1];
        ttt = tmp.split(",");
        yyy = ttt[0].toDouble();

        ttt = tmp2.split("x");
        tmp = ttt[1];
        ttt = tmp.split(" ");
        tmp = ttt[1];
        ttt = tmp.split(",");
        xxx = ttt[0].toDouble();

        ttt = tmp3.split("z");
        tmp = ttt[1];
        ttt = tmp.split(" ");
        tmp = ttt[1];
        ttt = tmp.split("}");
        zzz = ttt[0].toDouble();

        if(num[1] == "FIRST") {
            one[0] = xxx*(-1);
            one[2] = yyy;
            one[1] = zzz;

            ui->drone_first->setText(QString("Drone 1 :   %1    %2    %3").arg(one[0]).arg(one[2]).arg(one[1]));

            one[0] = xxx*(-1)*3;
            one[2] = yyy*3;
            one[1] = zzz;
        }
        else if(num[1] == "SECOND") {
            two[0] = xxx*(-1);
            two[2] = yyy;
            two[1] = zzz;

            ui->drone_second->setText(QString("Drone 2 :   %1    %2    %3").arg(two[0]).arg(two[2]).arg(two[1]));

            two[0] = xxx*(-1)*3;
            two[2] = yyy*3;
            two[1] = zzz;
        }
        else if(num[1] == "THIRD") {
            three[0] = xxx*(-1);
            three[2] = yyy;
            three[1] = zzz;

            ui->drone_third->setText(QString("Drone 3 :   %1    %2    %3").arg(three[0]).arg(three[2]).arg(three[1]));

            three[0] = xxx*(-1)*3;
            three[2] = yyy*3;
            three[1] = zzz;
        }
        else if(num[1] == "FOURTH") {
            four[0] = xxx*(-1);
            four[2] = yyy;
            four[1] = zzz;

            ui->drone_fourth->setText(QString("Drone 4 :   %1    %2    %3").arg(four[0]).arg(four[2]).arg(four[1]));

            four[0] = xxx*(-1)*3;
            four[2] = yyy*3;
            four[1] = zzz;

        }
        else {
            qDebug() <<"============POS===============ERROR=============================";
        }


        ui->widget->get_position(one, two, three, four);
    }
    else if(mod[0] == "TARGET_POS") {
        //{"topic": "/FOURTH/TARGET_POS", "msg": {"y": 0.0, "x": 0.0, "z": 0.0, "w": 0.0}, "op": "publish"}
        //{"topic": "/THIRD/TARGET_POS", "msg": {"y": 0.0, "x": 0.0, "z": 0.0, "w": 0.0}, "op": "publish"}
        //{"topic": "/FIRST/TARGET_POS", "msg": {"y": 0.0, "x": 0.0, "z": 0.0, "w": 0.0}, "op": "publish"}
        //{"topic": "/SECOND/TARGET_POS", "msg": {"y": 0.0, "x": 0.0, "z": 0.0, "w": 0.0}, "op": "publish"}
        ttt = tmp.split("y");
        tmp = ttt[1];
        ttt = tmp.split(" ");
        tmp = ttt[1];
        ttt = tmp.split(",");
        yyy = ttt[0].toDouble();

        ttt = tmp2.split("x");
        tmp = ttt[1];
        ttt = tmp.split(" ");
        tmp = ttt[1];
        ttt = tmp.split(",");
        xxx = ttt[0].toDouble();

        ttt = tmp3.split("z");
        tmp = ttt[1];
        ttt = tmp.split(" ");
        tmp = ttt[1];
        ttt = tmp.split(",");
        zzz = ttt[0].toDouble();

        ttt = tmp3.split("w");
        tmp = ttt[1];
        ttt = tmp.split(" ");
        tmp = ttt[1];
        ttt = tmp.split("}");
        command = ttt[0].toDouble();


        //we need only command value of 0, 1, 2
        if(num[1] == "FIRST") {
            if(command == 0) {
                if(xxx == 0 && yyy == 0 && zzz == 0) {
                    target_one[0] = one[0];
                    target_one[2] = one[2];
                    target_one[1] = one[1] + 500;
                }
            }
            else if(command == 1 || command == 4) {
                if(yyy == 0 || zzz == 0) {
                    //target position is current position
                    target_one[0] = one[0];
                    target_one[2] = one[2];
                    target_one[1] = one[1];
                }
                else {
                    target_one[0] = xxx*(-3);
                    target_one[2] = yyy*3;
                    target_one[1] = zzz;
                }
            }
            else
                qDebug() <<"============TARGET=============ERROR=============================";

        }
        else if(num[1] == "SECOND") {
            if(command == 0) {
                if(xxx == 0 && yyy == 0 && zzz == 0) {
                    target_two[0] = two[0];
                    target_two[2] = two[2];
                    target_two[1] = two[1] + 500;
                }
            }
            else if(command == 1 || command == 4) {
                if(yyy == 0 || zzz == 0) {
                    //target position is current position
                    target_two[0] = two[0];
                    target_two[2] = two[2];
                    target_two[1] = two[1];
                }
                else {
                    target_two[0] = xxx*(-3);
                    target_two[2] = yyy*3;
                    target_two[1] = zzz;
                }
            }
            else
                qDebug() <<"============TARGET=============ERROR=============================";
        }
        else if(num[1] == "THIRD") {
            if(command == 0) {
                if(xxx == 0 && yyy == 0 && zzz == 0) {
                    target_three[0] = three[0];
                    target_three[2] = three[2];
                    target_three[1] = three[1] + 500;
                }
            }
            else if(command == 1 || command == 4) {
                if(yyy == 0 || zzz == 0) {
                    //target position is current position
                    target_three[0] = three[0];
                    target_three[2] = three[2];
                    target_three[1] = three[1];
                }
                else {
                    target_three[0] = xxx*(-3);
                    target_three[2] = yyy*3;
                    target_three[1] = zzz;
                }
            }
            else
                qDebug() <<"============TARGET=============ERROR=============================";
        }
        else if(num[1] == "FOURTH") {
            if(command == 0) {
                if(xxx == 0 && yyy == 0 && zzz == 0) {
                    target_four[0] = four[0];
                    target_four[2] = four[2];
                    target_four[1] = four[1] + 500;
                }
            }
            else if(command == 1 || command == 4) {
                if(yyy == 0 || zzz == 0) {
                    //target position is current position
                    target_four[0] = four[0];
                    target_four[2] = four[2];
                    target_four[1] = four[1];
                }
                else {
                    target_four[0] = xxx*(-3);
                    target_four[2] = yyy*3;
                    target_four[1] = zzz;
                }
            }
            else
                qDebug() <<"============TARGET=============ERROR=============================";
        }
        else {
            qDebug() <<"============TARGET NUM=============ERROR=============================";
        }

        ui->widget->get_target(target_one, target_two, target_three, target_four);
    }


    qDebug() << xxx << yyy << zzz;
}

void MainWindow::connectionClosedByServer() {
    ui->connectButton->setText("connect");
    //connect_flag = 0;
    tcpSocket.close();
}

void MainWindow::error() {
    //qDebug(tcpSocket.errorString().toUtf8());
    connect_flag = 0;
    qDebug("Server Error");
    ui->connectButton->setText("&Connect");
}

void MainWindow::on_connectButton_clicked()
{
    qDebug() << connect_flag;
    if(connect_flag) {
        qDebug("socket close");

        tcpSocket.close();
        ui->connectButton->setText("&Connect");
        disconnect_flag = 1;
    }
}

void MainWindow::on_forward_button_pressed()
{
    if(manual_flag == 0 || form_flag == 0) {
        return;
    }
    press_flag = 1;
    qDebug("FUCK");
    QString tmp = QString("{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"2%1%2\"}}").arg(form_flag).arg(1);
    TOPIC = tmp.toUtf8();
    //qDebug() << TOPIC;
    tcpSocket.write(TOPIC, TOPIC.size());
    //tcpSocket.write(TOPIC2, TOPIC2.size());
}

void MainWindow::on_forward_button_released()
{

    if(manual_flag == 0 || form_flag == 0)
        return;
    qDebug("That");
    QString tmp = QString("{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"2%1%2\"}}").arg(form_flag).arg(0);
    TOPIC = tmp.toUtf8();
    //tcpSocket.write(TOPIC, TOPIC.size());
    press_flag = 0;
}

void MainWindow::on_right_button_pressed()
{
    if(manual_flag == 0 || form_flag == 0)
        return;
    press_flag = 1;
    QString tmp = QString("{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"2%1%2\"}}").arg(form_flag).arg(4);
    TOPIC = tmp.toUtf8();
    tcpSocket.write(TOPIC, TOPIC.size());
    //tcpSocket.write(TOPIC2, TOPIC2.size());
}

void MainWindow::on_right_button_released()
{

    if(manual_flag == 0 || form_flag == 0)
        return;
    QString tmp = QString("{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"2%1%2\"}}").arg(form_flag).arg(0);
    TOPIC = tmp.toUtf8();
    //tcpSocket.write(TOPIC, TOPIC.size());
    press_flag = 0;
}

void MainWindow::on_left_button_pressed()
{
    if(manual_flag == 0 || form_flag == 0)
        return;
    press_flag = 1;
    QString tmp = QString("{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"2%1%2\"}}").arg(form_flag).arg(3);
    TOPIC = tmp.toUtf8();
    tcpSocket.write(TOPIC, TOPIC.size());
    //tcpSocket.write(TOPIC2, TOPIC2.size());
}

void MainWindow::on_left_button_released()
{

    if(manual_flag == 0 || form_flag == 0)
        return;
    QString tmp = QString("{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"2%1%2\"}}").arg(form_flag).arg(0);
    TOPIC = tmp.toUtf8();
    //tcpSocket.write(TOPIC, TOPIC.size());
    press_flag = 0;
}

void MainWindow::on_back_button_pressed()
{

    if(manual_flag == 0 || form_flag == 0)
        return;
    press_flag = 1;
    QString tmp = QString("{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"2%1%2\"}}").arg(form_flag).arg(2);
    TOPIC = tmp.toUtf8();
    tcpSocket.write(TOPIC, TOPIC.size());
    //tcpSocket.write(TOPIC2, TOPIC2.size());
}

void MainWindow::on_back_button_released()
{

    if(manual_flag == 0 || form_flag == 0)
        return;
    QString tmp = QString("{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"2%1%2\"}}").arg(form_flag).arg(0);
    TOPIC = tmp.toUtf8();
    //tcpSocket.write(TOPIC, TOPIC.size());
    press_flag = 0;
}

void MainWindow::on_up_button_pressed()
{
    if(manual_flag == 0 || form_flag == 0)
        return;
    press_flag = 1;
    QString tmp = QString("{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"2%1%2\"}}").arg(form_flag).arg(5);
    TOPIC = tmp.toUtf8();
    tcpSocket.write(TOPIC, TOPIC.size());
    //tcpSocket.write(TOPIC2, TOPIC2.size());
}

void MainWindow::on_up_button_released()
{

    if(manual_flag == 0 || form_flag == 0)
        return;
    QString tmp = QString("{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"2%1%2\"}}").arg(form_flag).arg(0);
    TOPIC = tmp.toUtf8();
    //tcpSocket.write(TOPIC, TOPIC.size());
    press_flag = 0;
}

void MainWindow::on_down_button_pressed()
{
    if(manual_flag == 0 || form_flag == 0)
        return;
    press_flag = 1;
    QString tmp = QString("{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"2%1%2\"}}").arg(form_flag).arg(6);
    TOPIC = tmp.toUtf8();
    tcpSocket.write(TOPIC, TOPIC.size());
    //tcpSocket.write(TOPIC2, TOPIC2.size());
}

void MainWindow::on_down_button_released()
{
    if(manual_flag == 0 || form_flag == 0)
        return;
    QString tmp = QString("{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"2%1%2\"}}").arg(form_flag).arg(0);
    TOPIC = tmp.toUtf8();
    //tcpSocket.write(TOPIC, TOPIC.size());
    press_flag = 0;
}

void MainWindow::on_take_off_button_clicked()
{
    takeoff_flag = 1;
    landing_flag = 0;
    auto_flag = 0;
    form_flag = 0;
    manual_flag = 0;
    TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"0\"}}";
    tcpSocket.write(TOPIC, TOPIC.size());
    ui->drone_mode->setText(QString("MODE : TAKE OFF"));
}

void MainWindow::on_landing_button_clicked()
{
    landing_flag = 1;
    form_flag = 0;
    manual_flag = 0;
    auto_flag = 0;
    takeoff_flag = 0;
    TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"3\"}}";
    tcpSocket.write(TOPIC, TOPIC.size());
    ui->drone_mode->setText(QString("MODE : LANDING"));
}

void MainWindow::on_stop_button_clicked()
{
    manual_flag = 0;
    auto_flag = 0;
    landing_flag = 0;
    takeoff_flag = 0;
    TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"5\"}}";
    tcpSocket.write(TOPIC, TOPIC.size());
    ui->drone_mode->setText(QString("MODE : STOP"));
}

//mode 1 button
void MainWindow::on_form1_button_clicked()
{
    if(manual_flag == 0)
        return;
    form_flag = 1;
    TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"217\"}}";
    tcpSocket.write(TOPIC, TOPIC.size());
}

//mode 2 button
void MainWindow::on_form2_button_clicked()
{
    if(manual_flag == 0)
        return;
    form_flag = 2;
    TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"227\"}}";
    tcpSocket.write(TOPIC, TOPIC.size());
}

void MainWindow::on_form3_button_clicked() //scenario 1
{
    if(auto_flag == 0)
        return;
    TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"11\"}}";
    tcpSocket.write(TOPIC, TOPIC.size());
}

void MainWindow::on_form4_button_clicked() //scenario 2
{
    if(auto_flag == 0)
        return;
    TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"12\"}}";
    tcpSocket.write(TOPIC, TOPIC.size());
}

void MainWindow::on_manual_button_clicked()
{
    manual_flag = 1;
    form_flag = 0;
    auto_flag = 0;
    landing_flag = 0;
    takeoff_flag = 0;
    ui->drone_mode->setText(QString("MODE : MANUAL"));
}

//void MainWindow::on_horizontalSlider_valueChanged(int value)
//{
//    ui->drone_speed->setText(QString("SPEED :    %1").arg(value));
//    QString tmp = QString("{ \"op\" : \"publish\" , \"topic\" : \"/hello_ahn\", \"msg\" : {\"data\":\"%1\"}}").arg(value);
//    TOPIC2 = tmp.toUtf8();
//}

void MainWindow::on_auto_button_clicked()
{
    manual_flag = 0;
    auto_flag = 1;
    form_flag = 0;
    landing_flag = 0;
    takeoff_flag = 0;
    ui->drone_mode->setText(QString("MODE : AUTO"));
}

void MainWindow::on_debug_button_clicked()
{
    if(debug_flag == 0 && manual_flag == 1) {
        debug_flag = 1;
        ui->widget->set_move(debug_flag);
        ui->debug_button->setText("Move_OFF");
    }
    else {
        debug_flag = 0;
        ui->widget->set_move(debug_flag);
        ui->debug_button->setText("Move_ON");
    }
}

void MainWindow::on_lineEdit_editingFinished()
{
    ip_address = ui->lineEdit->displayText();
}

void MainWindow::on_form5_button_clicked()
{
    if(auto_flag == 0)
        return;
    TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"13\"}}";
    tcpSocket.write(TOPIC, TOPIC.size());
}

void MainWindow::on_target_button_clicked()
{
    if(target_flag == 0 ) {//&& manual_flag == 1) {
        target_flag = 1;
        ui->widget->set_target(target_flag);
        ui->target_button->setText("Target_OFF");
    }
    else {
        target_flag = 0;
        ui->widget->set_target(target_flag);
        ui->target_button->setText("Target_ON");
    }
}
