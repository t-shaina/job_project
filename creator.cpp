#include "creator.h"
#include "template_behavour.h"
#include<QChar>
#include<QString>
Creator::Creator(QApplication* parent)
{
    main_window=new MainWindow ();
    main_window->setWindowTitle("FilmsInfo");
    main_window->show();
    socket= new Socket();
    QObject::connect(this->main_window, SIGNAL(have_request(QStringList*)), this, SLOT(create_query(QStringList*)));//
    QObject::connect(this->socket, SIGNAL(new_data_received()), this, SLOT(data_received()));


}
Creator::~Creator()
{
    delete main_window;
    socket->disconnect();
    delete socket;
    delete behavour;
}
void Creator::create_query(QStringList* data){
    socket->sendData(data);
}
void Creator::data_received(){
    Behavour_id behavour_id=static_cast<Behavour_id>(socket->received_data->at(0).data()->digitValue());
    //Template_behavour* behavour;
    behavour=Template_behavour::creating_specific_behavour(behavour_id);
    behavour->processing_of_behavour(socket->received_data);
    //сигналы от Entry_behavour
    QObject::connect(this->behavour, SIGNAL(user_not_exist()), this->main_window, SLOT(msg_such_user_not_exist()));
    QObject::connect(this->behavour, SIGNAL(user_exist(QStringList*)), this->main_window, SLOT(create_app_page(QStringList*)));
    //сигналы от Delete_bahavour
    QObject::connect(this->behavour, SIGNAL(deletion_failed()), this->main_window, SLOT(msg_deletion_failed()));
    QObject::connect(this->behavour, SIGNAL(deletion_successful()), this->main_window, SLOT(msg_deletion_successful()));
    //сигналы от Select_bahavour
    QObject::connect(this->behavour, SIGNAL(records_not_exist()), this->main_window, SLOT(msg_records_not_exist()));
    QObject::connect(this->behavour, SIGNAL(records_exist(QStringlist*)), this->main_window, SLOT(msg_records_exist(QStringList*)));
    //сигналы от Insert_bahavour
    QObject::connect(this->behavour, SIGNAL(data_exist()), this->main_window, SLOT(msg_data_exist()));
    QObject::connect(this->behavour, SIGNAL(insert_successful(data)), this->main_window, SLOT(msg_insert_successful(data)));
    QObject::connect(this->behavour, SIGNAL(insert_failed()), this->main_window, SLOT(msg_insert_failed()));
    //сигналы от Registration_bahavour
    QObject::connect(this->behavour, SIGNAL(registration_failed()), this->main_window, SLOT(msg_registration_failed()));
    QObject::connect(this->behavour, SIGNAL(registration_successful(QStringlist*)), this->main_window, SLOT(msg_registration_successful(QStringList*)));
    //сигналы от Select_all_bahavour
    QObject::connect(this->behavour, SIGNAL(all_records_not_exist()), this->main_window, SLOT(msg_all_records_not_exist()));
    QObject::connect(this->behavour, SIGNAL(all_records_exist(QStringlist*)), this->main_window, SLOT(msg_all_records_exist(QStringList*)));
    //сигналы от Update_all_bahavour
    QObject::connect(this->behavour, SIGNAL(updation_failed()), this->main_window, SLOT(msg_updation_failed()));
    QObject::connect(this->behavour, SIGNAL(updation_successful(QStringlist*)), this->main_window, SLOT(msg_updation_successful(QStringList*)));
}
