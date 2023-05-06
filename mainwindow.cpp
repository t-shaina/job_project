#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFont>
#include<QStatusBar>
#include<QString>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , status(new QLabel(this))

{
    ui->setupUi(this);
    this->setFixedSize(500, 350);
    QFont main_window_font("Cochin", 0, 0);
    this->setFont(main_window_font);
    statusBar()->addWidget(&status);
    status.setText("Войдите в систему");
    this->start_page=new Start_page(this);
    this->socket_db=new Socket(this);
    QObject::connect(this->start_page, SIGNAL(entry_request(QString)), this, SLOT(set_username(QString)));
    QObject::connect(this->start_page, SIGNAL(entry_request(QString)), this, SLOT(resize_window()));
    QObject::connect(this->start_page, SIGNAL(entry_request(QString)), this, SLOT(creat_app_page()));
    //QObject::connect(this->app_page, SIGNAL(step_back()), this, SLOT(destroy_app_page()));
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
    //this->setMaximumSize(1024, 768);
    //this->setMinimumSize(912, 684);
    this->setSizeIncrement(8, 6);
    this->setFixedSize(1280, 800);
}
void MainWindow:: creat_app_page(){
    //App_page app_page=new App_page(this);
    this->app_page=new App_page(this);
    QObject::connect(this->app_page, SIGNAL(step_back()), this, SLOT(destroy_app_page()));
    QObject::connect(this->app_page, SIGNAL(search_request(QString*)), this, SLOT(on_search_request(QString*)));
    QObject::connect(this->app_page, SIGNAL(delete_request(QStringList*)), this, SLOT(on_delete_request(QStringList)));
    QObject::connect(this->app_page, SIGNAL(update_request(QStringList*)), this, SLOT(on_update_request(QStringList)));
}
void MainWindow:: destroy_app_page(){
    this->app_page->~App_page();
    this->start_page->set_start_page_visible(true);
    this->setFixedSize(500, 350);
    status.setText("Войдите в систему");
}
void MainWindow::on_search_request(QString search_string){
    this->socket_db->sendData("2"+search_string);
}
void MainWindow::on_delete_request(QStringList delete_list){
    this->socket_db->sendData("1");

}
void MainWindow::on_update_request(QStringList update_list){

}
