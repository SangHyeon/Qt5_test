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
    ui->setupUi(this);

    this->nextBlockSize = 0;
    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(connectToServer()));
    connect(&tcpSocket, SIGNAL(connected()), this, SLOT(onConnectServer()));
    //connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(sendRequest()));
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
/*
void MainWindow::on_pushButton_2_clicked()
{
    qDebug("Clicked Button!!");
    ui->widget->test_button(one, two, three, four);
}
*/
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
        tcpSocket.connectToHost("112.108.39.236", 9090);
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
    QByteArray JSON = "{ \"op\" : \"subscribe\" , \"topic\" : \"/FIRST/CURRENT_POS\"}";
    QByteArray JSON2 = "{ \"op\" : \"subscribe\" , \"topic\" : \"/SECOND/CURRENT_POS\"}";
    QByteArray ADVER = "{ \"op\" : \"advertise\" , \"topic\" : \"/hello_kun\", \"type\":\"std_msgs/String\"}";
    TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"4\"}}";
    tcpSocket.write(msg, msg.size());
    tcpSocket.write(JSON, JSON.size());
    tcpSocket.write(JSON2, JSON2.size());
    tcpSocket.write(ADVER, ADVER.size());
    tcpSocket.write(TOPIC, TOPIC.size());

    qDebug("%d", msg.size());
    qDebug("%d", JSON.size());
    qDebug("send message!");
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
    if(press_flag == 1) {
        //tcpSocket.write(TOPIC, TOPIC.size());
        //qDebug() << "===========fuck==========";
    }
    ui->widget->test_button(one, two, three, four);
}

void MainWindow::getPosition(QString s) {
    //qDebug(s.toUtf8());
    //test code
    //QString tmp = "{\"topic\": \"/FIRST/CURRENT_POS\", \"msg\": {\"y\": 3000.0876808544454, \"x\": 1407.7433628318586, \"z\": -1780.8053665716345}, \"op\": \"publish\"}";
    //qDebug() <<"asdfad"<<s<<"======";
    QString tmp = s;
    QString tmp2 = tmp;
    QString tmp3 = tmp;
    QStringList ttt, num;
    int yyy, xxx, zzz;

    num = tmp.split("/");
    //    if(num[1] == "FIRST")
    //        qDebug() << num[1];

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
        one[0] = xxx*(-1)*3;
        one[2] = yyy*3;
        one[1] = zzz;
    }
    else if(num[1] == "SECOND") {
        two[0] = xxx*(-1)*3;
        two[2] = yyy*3;
        two[1] = zzz;
    }

    ui->widget->test_button(one, two, three, four);

    qDebug() << xxx << yyy << zzz;
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
    if(manual_flag == 0) {
        return;
    }
    press_flag = 1;
    qDebug("FUCK");
    TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"2001000\"}}";
    tcpSocket.write(TOPIC, TOPIC.size());
}

void MainWindow::on_forward_button_released()
{

    if(manual_flag == 0)
        return;
    qDebug("That");
    //TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"4\"}}";
    //tcpSocket.write(TOPIC, TOPIC.size());
    press_flag = 0;
}
/*
void MainWindow::mouseIsPressed(QMouseEvent *event) {
    qDebug() <<event->MouseButtonPress;
}

int MainWindow::get_flag() {
    return press_flag;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    Q_UNUSED(event);
    qDebug() << "pressssssssss";
}
*/

void MainWindow::on_right_button_pressed()
{

    if(manual_flag == 0)
        return;
    press_flag = 1;
    TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"2000010\"}}";
    tcpSocket.write(TOPIC, TOPIC.size());
}

void MainWindow::on_right_button_released()
{

    if(manual_flag == 0)
        return;
    //TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"4\"}}";
    press_flag = 0;
    //tcpSocket.write(TOPIC, TOPIC.size());
}

void MainWindow::on_left_button_pressed()
{

    if(manual_flag == 0)
        return;
    press_flag = 1;
    TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"2000001\"}}";
    tcpSocket.write(TOPIC, TOPIC.size());
}

void MainWindow::on_left_button_released()
{

    if(manual_flag == 0)
        return;
    //TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"4\"}}";
    press_flag = 0;
    //tcpSocket.write(TOPIC, TOPIC.size());
}

void MainWindow::on_back_button_pressed()
{

    if(manual_flag == 0)
        return;
    press_flag = 1;
    TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"2000100\"}}";
    tcpSocket.write(TOPIC, TOPIC.size());
}

void MainWindow::on_back_button_released()
{

    if(manual_flag == 0)
        return;
    //TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"4\"}}";
    press_flag = 0;
    //tcpSocket.write(TOPIC, TOPIC.size());
}

void MainWindow::on_up_button_pressed()
{

    if(manual_flag == 0)
        return;
    press_flag = 1;
    TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"2100000\"}}";
    tcpSocket.write(TOPIC, TOPIC.size());
}

void MainWindow::on_up_button_released()
{

    if(manual_flag == 0)
        return;
    //TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"4\"}}";
    press_flag = 0;
    //tcpSocket.write(TOPIC, TOPIC.size());
}

void MainWindow::on_down_button_pressed()
{

    if(manual_flag == 0)
        return;
    press_flag = 1;
    TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"2010000\"}}";
    tcpSocket.write(TOPIC, TOPIC.size());
}

void MainWindow::on_down_button_released()
{

    if(manual_flag == 0)
        return;
    //TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"4\"}}";
    press_flag = 0;
    //tcpSocket.write(TOPIC, TOPIC.size());
}

void MainWindow::on_take_off_button_clicked()
{
    TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"0\"}}";
    tcpSocket.write(TOPIC, TOPIC.size());
}

void MainWindow::on_landing_button_clicked()
{
    manual_flag = 0;
    TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"3\"}}";
    tcpSocket.write(TOPIC, TOPIC.size());
}

void MainWindow::on_stop_button_clicked()
{
    manual_flag = 0;
    TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"4\"}}";
    tcpSocket.write(TOPIC, TOPIC.size());
}

void MainWindow::on_form1_button_clicked()
{
    TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"11\"}}";
    tcpSocket.write(TOPIC, TOPIC.size());
}

void MainWindow::on_form2_button_clicked()
{
    TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"12\"}}";
    tcpSocket.write(TOPIC, TOPIC.size());
}

void MainWindow::on_form3_button_clicked()
{
    TOPIC = "{ \"op\" : \"publish\" , \"topic\" : \"/hello_kun\", \"msg\" : {\"data\":\"13\"}}";
    tcpSocket.write(TOPIC, TOPIC.size());
}

void MainWindow::on_manual_button_clicked()
{
    manual_flag = 1;
}
