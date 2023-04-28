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
    this->setMaximumSize(500, 350);
    this->setMinimumSize(500, 350);
    statusBar()->addWidget(&status);
    status.setText("Войдите в систему");
    QObject::connect(this->app_page, SIGNAL(step_back()), this, SLOT(destroy_app_page()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::set_username(QString username){
    QString message="Вы вошли как ";
    status.setText(message+=username);
}
void MainWindow::resize_window(){
    this->setMaximumSize(1024, 768);
    this->setMinimumSize(800, 600);
    this->setSizeIncrement(8, 6);
}
void MainWindow:: creat_app_page(){
    App_page app_page=new App_page(this);
}
void MainWindow:: destroy_app_page(){
    delete app_page;
}
