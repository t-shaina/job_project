#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFont>
#include<QStatusBar>
#include<QString>
#include <stdlib.h>
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
    QObject::connect(this->start_page, SIGNAL(entry_request(QStringList)), this, SLOT(set_username(QString)));//
    QObject::connect(this->start_page, SIGNAL(entry_request(QStringlist)), this, SLOT(resize_window()));
    QObject::connect(this->start_page, SIGNAL(entry_request(QStringList)), this, SLOT(create_app_page()));
    QObject::connect(this->start_page, SIGNAL(entry_request(QStringList)), this, SLOT(on_entry_request(QStringList)));
    QObject::connect(this->start_page, SIGNAL(create_registration_page()), this, SLOT(on_create_registration_page()));
    QObject::connect(this->socket_db, SIGNAL(new_data_received(QString)), this, SLOT(data_decryption(QString)));
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
void MainWindow:: create_app_page(){
    //App_page app_page=new App_page(this);
    //this->start_page->set_start_page_visible(false);
    this->app_page=new App_page(this);
    this->resize_window();
    QObject::connect(this->app_page, SIGNAL(step_back()), this, SLOT(destroy_app_page()));
    QObject::connect(this->app_page, SIGNAL(search_request(QString*)), this, SLOT(on_search_request(QString*)));
    QObject::connect(this->app_page, SIGNAL(select_all_request(QString*)), this, SLOT(on_select_all_request(QString*)));
    QObject::connect(this->app_page, SIGNAL(delete_request(QStringList*)), this, SLOT(on_delete_request(QStringList)));
    QObject::connect(this->app_page, SIGNAL(update_request(QStringList*)), this, SLOT(on_update_request(QStringList)));
    QObject::connect(this->app_page, SIGNAL(insert_request(QStringList*)), this, SLOT(on_insert_request(QStringList)));
    status.setText("Вы вошли как: ");

}
void MainWindow:: destroy_app_page(){
    this->app_page->~App_page();
    this->start_page->set_start_page_visible(true);
    this->setFixedSize(500, 350);
    status.setText("Войдите в систему");
}
void MainWindow::on_create_registration_page(){
    this->start_page->set_start_page_visible(false);
    this->registration_page=new Registration_page(this);
    QObject::connect(this->registration_page, SIGNAL(step_back()), this, SLOT(on_destroy_registration_page()));
    QObject::connect(this->registration_page, SIGNAL(registration_request(QStringList)), this, SLOT(on_registration_request(QStringList)));
    status.setText("Зарегестрируйтесь");
}
void MainWindow:: on_destroy_registration_page(){
    this->registration_page->~Registration_page();
    this->start_page->set_start_page_visible(true);//need7
    this->setFixedSize(500, 350);
    status.setText("Войдите в систему");
}
void MainWindow::on_entry_request(QStringList entry_list){
    QString* encoded_entry_list=new QString();
    for(int i=0; i<entry_list.size();i++){
        *encoded_entry_list+=static_cast<char>(entry_list.at(i).size());
        *encoded_entry_list+=entry_list.at(i);
    }
    this->socket_db->sendData("0"+*encoded_entry_list);
}
void MainWindow::on_search_request(QString search_string){
    this->socket_db->sendData("2"+search_string);
}
void MainWindow::on_delete_request(QStringList delete_list){
    QString* encoded_delete_list=new QString();
    for(int i=0; i<delete_list.size();i++){
        *encoded_delete_list+=static_cast<char>(delete_list.at(i).size());
        *encoded_delete_list+=delete_list.at(i);
    }
    this->socket_db->sendData("1"+*encoded_delete_list);
}
void MainWindow::on_select_all_request(QString email){
    this->socket_db->sendData("5"+email);
}
void MainWindow::on_update_request(QStringList update_list){//do
    QString* encoded_update_list=new QString();
    for(int i=0; i<this->app_page->row_data->size();i++){
        *encoded_update_list+=static_cast<char>(this->app_page->row_data->at(i).size());
        *encoded_update_list+=this->app_page->row_data->at(i);
    }
    for(int i=0; i<update_list.size();i++){
        *encoded_update_list+=static_cast<char>(update_list.at(i).size());
        *encoded_update_list+=update_list.at(i);
    }
    this->socket_db->sendData("6"+*encoded_update_list);
}
void MainWindow::on_insert_request(QStringList insert_list){
    QString* encoded_update_list=new QString();
    for(int i=0; i<insert_list.size();i++){
        *encoded_update_list+=static_cast<char>(insert_list.at(i).size());
        *encoded_update_list+=insert_list.at(i);
    }
    this->socket_db->sendData("3"+*encoded_update_list);
}
void MainWindow::data_decryption(QString data){
    if (data.at(0)=='0') emit entry_response();
        else if(data.at(0)=='1') emit delete_response();
}
void MainWindow::on_registration_request(QStringList registration_list){
    QString* encoded_registration_list=new QString();
    for(int i=0; i<registration_list.size();i++){
        *encoded_registration_list+=static_cast<char>(registration_list.at(i).size());
        *encoded_registration_list+=registration_list.at(i);
        }
        this->socket_db->sendData("4"+*encoded_registration_list);
}
