#include "creator.h"
#include "template_behavour.h"
#include<QChar>
#include<QString>
Creator::Creator(QApplication* parent)
{
    main_window=new MainWindow ();
    main_window->setWindowTitle("FilmsInfo");
    main_window->show();
    i_adapter= new Client_socket_adapter(this);
    QObject::connect(this->main_window, SIGNAL(have_request(QStringList*)), this, SLOT(create_query(QStringList*)));//
    QObject::connect(this->i_adapter, SIGNAL(have_new_message(QString)), this, SLOT(data_received(QString)));


}
Creator::~Creator()
{
    delete main_window;
    //socket->disconnect();
    delete i_adapter;
    delete behavour;
}
void Creator::create_query(QStringList* data){
    QString string_data=encoding_message(data);
    qDebug()<<"in create_query list_data "<< data->at(0)<<data->at(1)<<data->at(2);
    qDebug()<<"in create_query string_data "<< string_data;
    i_adapter->sendData(string_data);
}
void Creator::data_received(QString received_data){
    Behavour_id behavour_id=static_cast<Behavour_id>(received_data.at(0).digitValue());
    QStringList list_data=decoding_message(received_data);
    //Template_behavour* behavour;
    behavour=Template_behavour::creating_specific_behavour(behavour_id);
    behavour->processing_of_behavour(&list_data);
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
QString Creator::encoding_message(const QStringList* data){
    QString* encoded_message=new QString(data->at(0));
    for (int i=1;i<data->size();i++){
        *encoded_message+=QString::number(data->at(i).size());
        *encoded_message+=data->at(i);
    }
    return *encoded_message;
}
QStringList Creator::decoding_message(const QString& message){
    QStringList data;
    int length=0;
    data.push_back(message.at(0));
    for (int i=1; i<message.size()-length-1;i+=length){//мб тут с условием выхода из for
        length=message.at(i).digitValue();
        data.push_back(message.sliced(i+1, length));
    }
    return data;
}
