#include "mainwindow.h"

#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->m_button_close = new QPushButton("Close", this);
    this->m_button_close->setGeometry(QRect(QPoint(100, 100), QSize(200, 100)));
    connect(m_button_close, &QPushButton::released, this, &MainWindow::handleCloseBtn);
}

MainWindow::~MainWindow() {}

void MainWindow::handleCloseBtn() {
    QApplication::quit();
}