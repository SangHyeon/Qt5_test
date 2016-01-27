#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "glwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->nextBlockSize = 0;
    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(connectToServer()));
    connect(&tcpSocket, SIGNAL(connected()), this, SLOT(onConnectServer()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(sendRequest()));
    connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(&tcpSocket, SIGNAL(disconnected()), this, SLOT(connectionClosedByServer()));
    connect(&tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error()));

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
    tcpSocket.connectToHost("112.108.39.164", 8080);
    //requier to servre for connect
}

void MainWindow::onConnectServer(){
    qDebug("connect Complete");
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
    qDebug("ready for read data");
    //while(tcpSocket.canReadLine()) {
    QString line = QString::fromUtf8(tcpSocket.readLine()).trimmed();
    qDebug(line.toUtf8());
    ui->widget->test_button(one, two, three, four);
    //}

    //QDataStream in(&tcpSocket);

    /*while(true) {
        if(nextBlockSize == 0) {
            if(tcpSocket.bytesAvailable() < sizeof(quint16))
                continue;//...?!
            else
                in>>nextBlockSize;
            continue;
        }
        else if(tcpSocket.bytesAvailable() < nextBlockSize)
            continue;
        else if(tcpSocket.bytesAvailable() >= nextBlockSize) {
            QString strBuf;
            in >> strBuf;

            qDebug(strBuf.toUtf8());
            //strBuf has data

            this->nextBlockSize = 0;

            break;
        }
    }*/
}

void MainWindow::connectionClosedByServer() {
    tcpSocket.close();
}

void MainWindow::error() {
    qDebug(tcpSocket.errorString().toUtf8());
}
