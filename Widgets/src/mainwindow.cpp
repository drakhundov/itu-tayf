#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->btn = new QPushButton("Add", this);
    this->btn->setGeometry(400, 200, 200, 100);
    this->lnedit = new QLineEdit(this);
    this->lnedit->setGeometry(100, 200, 200, 100);
    this->lstwig = new QListWidget(this);
    this->lstwig->setGeometry(400, 300, 200, 500);
    connect(this->btn, &QPushButton::released, this, &MainWindow::addItem);
}

MainWindow::~MainWindow() {}

void MainWindow::addItem()
{
    this->lstwig->addItem(this->lnedit->text());
    this->lnedit->setText("");
}
