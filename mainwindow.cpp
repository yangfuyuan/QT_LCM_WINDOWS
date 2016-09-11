#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBoxTime->setEnabled(true);
    ui->comboBoxTime->setEditable(true);
    ui->comboBoxTime->setCurrentText("1000");
    ui->stopBtn->setEnabled(false);

    QRegExp rx("^[0-9]{1,10}$");
    QValidator *validator = new QRegExpValidator(rx,0);
    ui->comboBoxTime->setValidator(validator);

    timer = new QTimer();
    timer1 = new QTimer(this);

    thread = new QThread(this);
    thread->start();

    //timer->setInterval(100);
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(mainloop()), Qt::DirectConnection);
    connect(this, SIGNAL(stop()), timer, SLOT(stop()));
    timer->start(10);
    timer->moveToThread(thread);

    connect(timer1, SIGNAL(timeout()), this, SLOT(pushlish()));


    qRegisterMetaType<QTextCursor>("QTextCursor");

    lcm = new lcm::LCM("udpm://239.255.76.67:7667?ttl=1");
     if(!lcm->good())
     return;


}

MainWindow::~MainWindow()
{
    if(thread->isRunning()){
        thread->quit();
        thread->terminate();

    }


    if(timer->isActive())
        Q_EMIT stop();

    delete thread;
    delete timer;
    if(timer1->isActive())
        timer1->stop();
    delete timer1;
    delete ui;
    delete lcm;

}

void MainWindow::mainloop()
{
    while(true)
        lcm->handle();
}

void MainWindow::handleMessage(const lcm::ReceiveBuffer *rbuf, const std::__cxx11::string &chan, const pose_t *msg)
{
    Q_UNUSED(rbuf);

//    qDebug()<<"Received message on channel:"<<chan.c_str();
//    qDebug()<<"timestamp:"<<msg->utime;
//    qDebug()<<"x:"<<msg->xyt[0];
//    qDebug()<<"Y:"<<msg->xyt[1];
//    qDebug()<<"theta:"<<msg->xyt[2];

    QString str = tr("Received message on channel:%1\ntimestamp:%2\nx:%3\ny:%4\ntheta:%5").arg(chan.c_str()).arg(msg->utime).arg(msg->xyt[0]).arg(msg->xyt[1]).arg(msg->xyt[2]);
    ui->textEdit->append(str);
    ui->textEdit->ensureCursorVisible();


}


void MainWindow::on_publishBtn_clicked()
{
    timer1->start(ui->comboBoxTime->currentText().toInt());
    ui->comboBoxTime->setEnabled(false);
    ui->stopBtn->setEnabled(true);
    ui->publishBtn->setEnabled(false);

}

void MainWindow::pushlish()
{
    static int i =0;
    pose_t pose;
    pose.xyt[0] = 1;
    pose.xyt[1] = 1;
    pose.xyt[2] = 0;
    pose.utime = i;
    lcm->publish("POSE", &pose);
    i++;
}

void MainWindow::on_RecBtn_clicked()
{
     lcm->subscribe("POSE", &MainWindow::handleMessage, this);

}

void MainWindow::on_clearBtn_clicked()
{
    ui->textEdit->clear();
    ui->textEdit->ensureCursorVisible();

}

void MainWindow::on_stopBtn_clicked()
{
    timer1->stop();
    ui->comboBoxTime->setEnabled(true);
    ui->publishBtn->setEnabled(true);
    ui->stopBtn->setEnabled(false);

}
