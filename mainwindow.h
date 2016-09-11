#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QThread>
#include <stdio.h>
#include <lcm/windows/WinPorting.h>
#include <lcm/lcm-cpp.hpp>
#include <include/pose_t.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_publishBtn_clicked();

    void mainloop();

    void pushlish();


    void on_RecBtn_clicked();

    void on_clearBtn_clicked();

    void on_stopBtn_clicked();

Q_SIGNALS:
    void stop();

private:
    Ui::MainWindow *ui;

    QTimer *timer;
    QThread* thread;

    QTimer *timer1;


    lcm::LCM *lcm;



    void handleMessage(const lcm::ReceiveBuffer* rbuf,
                    const std::string& chan,
                    const pose_t* msg);
};

#endif // MAINWINDOW_H
