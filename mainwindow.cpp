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
    //QObject::connect(this->start_page, SIGNAL(entry_request(QStringList*)), this, SLOT(set_username(QString)));//
    //QObject::connect(this->start_page, SIGNAL(entry_request(QStringlist*)), this, SLOT(resize_window()));
    //QObject::connect(this->start_page, SIGNAL(entry_request(QStringList*)), this, SLOT(create_app_page()));
    QObject::connect(this->start_page, SIGNAL(entry_request(QStringList*)), this, SLOT(processing_entry_request(QStringList*)));
    QObject::connect(this->start_page, SIGNAL(create_registration_page()), this, SLOT(creating_registration_page()));

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

void MainWindow:: destroy_app_page(){
    this->app_page->~App_page();
    this->start_page->set_start_page_visible(true);
    this->setFixedSize(500, 350);
    status.setText("Войдите в систему");
}
void MainWindow::creating_registration_page(){
    this->start_page->set_start_page_visible(false);
    this->registration_page=new Registration_page(this);
    QObject::connect(this->registration_page, SIGNAL(step_back()), this, SLOT(breaking_registration_page()));
    QObject::connect(this->registration_page, SIGNAL(registration_request(QStringList*)), this, SLOT(processing_registration_request(QStringList*)));
    status.setText("Зарегестрируйтесь");
}
void MainWindow:: breaking_registration_page(){
    this->registration_page->~Registration_page();
    this->start_page->set_start_page_visible(true);//need7
    this->setFixedSize(500, 350);
    status.setText("Войдите в систему");
}
void MainWindow::processing_entry_request(QStringList* entry_list){
    entry_list->push_front("0");
    qDebug()<< entry_list->at(0)<<entry_list->at(1)<<entry_list->at(2);
    emit have_request(entry_list);
}
void MainWindow::processing_search_request(QStringList* search_list){
    search_list->push_front("2");
    emit have_request(search_list);
}
void MainWindow::processing_delete_request(QStringList* delete_list){
    delete_list->push_front("1");
    emit have_request(delete_list);
}
void MainWindow::processing_select_all_request(QStringList* email){
    email->push_front("5");
    emit have_request(email);
}
void MainWindow::processing_update_request(QStringList* update_list){//do
    /*QString* encoded_update_list=new QString();
    for(int i=0; i<this->app_page->row_data->size();i++){
        *encoded_update_list+=static_cast<char>(this->app_page->row_data->at(i).size());
        *encoded_update_list+=this->app_page->row_data->at(i);
    }
    for(int i=0; i<update_list.size();i++){
        *encoded_update_list+=static_cast<char>(update_list.at(i).size());
        *encoded_update_list+=update_list.at(i);
    }*/
    update_list->push_front("6");
    emit have_request(update_list);
}
void MainWindow::processing_insert_request(QStringList* insert_list){
    insert_list->push_front("3");
    emit have_request(insert_list);
}

void MainWindow::processing_registration_request(QStringList* registration_list){
    registration_list->push_front("4");
    emit have_request(registration_list);
}
void MainWindow::msg_such_user_not_exist(){
    status.setText("Пользователя с таким email не существует или неверный пароль");
}
void MainWindow:: create_app_page(QVariantMap* data){
    //App_page app_page=new App_page(this);
    //this->start_page->set_start_page_visible(false);
    qDebug()<<"in create_app_page";
    this->app_page=new App_page(this);
    this->resize_window();
    QObject::connect(this->app_page, SIGNAL(step_out()), this, SLOT(destroy_app_page()));
    QObject::connect(this->app_page, SIGNAL(search_request(QStringList*)), this, SLOT(processing_search_request(QStringList*)));
    QObject::connect(this->app_page, SIGNAL(select_all_request(QStringList*)), this, SLOT(processing_select_all_request(QStringList*)));
    QObject::connect(this->app_page, SIGNAL(delete_request(QStringList*)), this, SLOT(processing_delete_request(QStringList*)));
    QObject::connect(this->app_page, SIGNAL(update_request(QStringList*)), this, SLOT(processing_update_request(QStringList*)));
    QObject::connect(this->app_page, SIGNAL(insert_request(QStringList*)), this, SLOT(processing_insert_request(QStringList*)));
    QString* service_msg=new QString("Вы вошли как: ");
    service_msg->append(data->take("Name").toString());
    service_msg->append(" ");
    status.setText(service_msg->append(data->take("Email").toString()));
    this->app_page->email=status.text();
    this->app_page->insert_rows_in_table(data);
}
void MainWindow::msg_deletion_failed(){
    status.setText("Удаление строки не удалось");
}
void MainWindow::msg_deletion_successful(){
    status.setText("Строка удалена");
    this->app_page->remove_row_in_table();
}
void MainWindow::msg_records_not_exist(){
    status.setText("По запросу ничего не найдено");
}
void MainWindow::msg_records_exist(QVariantMap* data){
    this->app_page->insert_rows_in_table(data);
}
void MainWindow::msg_data_exist(){
    status.setText("Такой фильм уже существует, проверьте корректность введенных данных");
}
void MainWindow::msg_insert_successful(QVariantMap* data){
    status.setText("Вставка прошла успешно");
    this->app_page->insert_row_in_table(data);
}
void MainWindow::msg_insert_failed(){
    status.setText("Строка не была добавлена");
}
void MainWindow::msg_registration_failed(){
    status.setText("Такой пользователь уже зарегестрирован");
}
void MainWindow::msg_registration_successful(QVariantMap* data){
    create_app_page(data);
}
void MainWindow::msg_all_records_not_exist(){
    status.setText("Ошибка обновления данных");
}
void MainWindow::msg_all_records_exist(QVariantMap* data){
    this->app_page->insert_rows_in_table(data);
}
void MainWindow::msg_updation_failed(){
    status.setText("Ошибка обновления записи");
}
void MainWindow::msg_updation_successful(QVariantMap* data){
    status.setText("Запись обновлена");
    this->app_page->update_row_in_table(data);
}
