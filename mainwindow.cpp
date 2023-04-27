#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QStatusBar>
#include<QString>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , status(new QLabel(this))

{
    ui->setupUi(this);
    statusBar()->addWidget(&status);
    status.setText("Войдите в систему");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::set_username(QString username){
    QString message="Вы вошли как ";
    status.setText(message+=username);
}
