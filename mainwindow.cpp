#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "glwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    connect_flag = 0;
    disconnect_flag = 1;
    ui->setupUi(this);

    this->nextBlockSize = 0;
    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(connectToServer()));
    connect(&tcpSocket, SIGNAL(connected()), this, SLOT(onConnectServer()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(sendRequest()));
    connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(&tcpSocket, SIGNAL(disconnected()), this, SLOT(connectionClosedByServer()));
    connect(&tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error()));
    //connect(ui->forward_button, SIGNAL(pressed()), this, SLOT(QAbstractButton::autoRepeat()));

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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    qDebug("Clicked Button!!");
    ui->widget->test_button(one, two, three, four);
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
        tcpSocket.connectToHost("112.108.39.238", 9090);
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
    ui->connectButton->setText("disconnect");

    QByteArray msg = "raw\r\n\r\n";
    //QByteArray JSON = "{ \"op\" : \"subscribe\" , \"topic\" : \"/say_hello_world\"}";
    QByteArray JSON = "{ \"op\" : \"subscribe\" , \"topic\" : \"/imu/data_raw\"}";
    QByteArray ADVER = "{ \"op\" : \"advertise\" , \"topic\" : \"/hello_kun\", \"type\":\"std_msgs/String\"}";
    QByteArray TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"Hello, Donkie\"}}";
    tcpSocket.write(msg, msg.size());
    tcpSocket.write(JSON, JSON.size());
    tcpSocket.write(ADVER, ADVER.size());
    tcpSocket.write(TOPIC, TOPIC.size());

    qDebug("%d", msg.size());
    qDebug("%d", JSON.size());
    qDebug("send message!");
}

void MainWindow::sendRequest() {
    //need modifying
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out<<quint16(0);

    //out<<~~//read the data....
    out.device()->seek(0);

    out<<quint16(block.size() - sizeof(quint16));

    tcpSocket.write(block);//send to socket
}

void MainWindow::readMessage() {
    //read & send JSON msgs
    //qDebug("ready for read data");
    QString line = QString::fromUtf8(tcpSocket.readLine()).trimmed();
    qDebug(line.toUtf8());
    ui->widget->test_button(one, two, three, four);
}

void MainWindow::connectionClosedByServer() {
    ui->connectButton->setText("connect");
    //connect_flag = 0;
    tcpSocket.close();
}

void MainWindow::error() {
    qDebug(tcpSocket.errorString().toUtf8());
    connect_flag = 0;
    qDebug("I'm Here22");
    ui->connectButton->setText("connect");
}

void MainWindow::on_connectButton_clicked()
{
    qDebug() << connect_flag;
    if(connect_flag) {
        qDebug("socket close");

        tcpSocket.close();
        ui->connectButton->setText("connect");
        disconnect_flag = 1;
    }
}

void MainWindow::on_forward_button_pressed()
{
    press_flag = 1;
    qDebug("FUCK");
}

void MainWindow::on_forward_button_released()
{
    qDebug("That");
    press_flag = 0;
}

void MainWindow::mouseIsPressed(QMouseEvent *event) {
    qDebug() <<event->MouseButtonPress;
}

int MainWindow::get_flag() {
    return press_flag;
}
