#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QListWidget>
#include <QTimer>
#include <QString>

struct Data
{
    float height, temp, pressure;
};

class MainWindow : public QMainWindow
{
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void HandleTimer();
    void OnTimout();

private:
    QPushButton *startBtn, *stopBtn;
    QListWidget *lst;
    QTimer *timer;
    Data d;
};

void UpdBtnStyle(QPushButton *, QString, QString);

namespace ButtonStyles
{
    const QString START_ACTIVE_BG = "darkgreen";
    const QString STOP_ACTIVE_BG = "darkred";
    const QString START_INACTIVE_BG = "green";
    const QString STOP_INACTIVE_BG = "red";
}

#endif