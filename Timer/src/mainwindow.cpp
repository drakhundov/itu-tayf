#include "mainwindow.h"

#include <ctime>
#include <sstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->startBtn = new QPushButton("START", this);
    this->startBtn->resize(100, 30);
    this->startBtn->move(50, 50);
    connect(this->startBtn, &QPushButton::clicked, this, &MainWindow::HandleTimer);
    UpdBtnStyle(this->startBtn, "color", "white");
    UpdBtnStyle(this->startBtn, "background-color", ButtonStyles::START_INACTIVE_BG);

    this->stopBtn = new QPushButton("STOP", this);
    this->stopBtn->resize(100, 30);
    this->stopBtn->move(150, 50);
    connect(this->stopBtn, &QPushButton::clicked, this, &MainWindow::HandleTimer);
    UpdBtnStyle(this->stopBtn, "color", "white");
    UpdBtnStyle(this->stopBtn, "background-color", ButtonStyles::STOP_INACTIVE_BG);

    this->lst = new QListWidget(this);
    this->lst->move(50, 100);
    this->lst->resize(200, 150);

    this->timer = new QTimer(this);
    connect(this->timer, &QTimer::timeout, this, &MainWindow::OnTimout);

    srand(time(nullptr));

    this->d = {};
}

void MainWindow::HandleTimer()
{
    QPushButton *pushedBtn = qobject_cast<QPushButton *>(sender());
    if (pushedBtn == this->startBtn && !this->timer->isActive())
    {
        UpdBtnStyle(this->startBtn, "background-color", ButtonStyles::START_ACTIVE_BG);
        UpdBtnStyle(this->stopBtn, "background-color", ButtonStyles::STOP_INACTIVE_BG);
        this->timer->start(1000);
    }
    else if (pushedBtn == this->stopBtn && this->timer->isActive())
    {
        UpdBtnStyle(this->startBtn, "background-color", ButtonStyles::START_INACTIVE_BG);
        UpdBtnStyle(this->stopBtn, "background-color", ButtonStyles::STOP_ACTIVE_BG);
        this->timer->stop();
    }
}

void MainWindow::OnTimout()
{
    this->d.height += (rand() % 2) * 0.1;
    this->d.temp += (rand() % 4) * 0.1;
    this->d.pressure += (rand() % 2) * 0.1;
    std::ostringstream oss;
    oss << "h: " << this->d.height << "m, t: " << this->d.temp << "C, p: " << this->d.pressure << "hPa";
    this->lst->addItem(QString::fromStdString(oss.str()));
}

void UpdBtnStyle(QPushButton *btn, QString param, QString styleVal)
{
    QString finStyle = btn->styleSheet();
    QString newStyle = param + ":" + styleVal + ";";
    int pos;
    if ((pos = finStyle.indexOf(param)) != -1)
    {
        int endPos = finStyle.indexOf(";", pos);
        if (endPos != -1)
        {
            finStyle.replace(pos, endPos - pos + 1, newStyle);
        }
        else
        {
            finStyle.replace(pos, finStyle.length() - pos, newStyle);
        }
    }
    else
    {
        if (!finStyle.isEmpty() && !finStyle.endsWith(";"))
        {
            finStyle.append(";");
        }
        finStyle.append(newStyle);
    }
    btn->setStyleSheet(finStyle);
}

MainWindow::~MainWindow() {}