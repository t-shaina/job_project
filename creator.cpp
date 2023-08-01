#include "creator.h"
#include "template_behavour.h"
#include"json_creator.h"
#include<QChar>
#include<QString>
#include<QJsonDocument>
#include<QJsonParseError>
#include<QVariantMap>
Creator::Creator(QApplication* parent)
{
    main_window=new MainWindow ();
    main_window->setWindowTitle("FilmsInfo");
    main_window->show();
    i_adapter= new Client_socket_adapter(this);

    QObject::connect(this->main_window, SIGNAL(have_request(QStringList*)), this, SLOT(create_query(QStringList*)));//
    QObject::connect(this->i_adapter, SIGNAL(have_new_message(QByteArray)), this, SLOT(data_received(QByteArray)));

}
Creator::~Creator()
{
    delete main_window;
    //socket->disconnect();
    delete i_adapter;
    delete behavour;
}
void Creator::create_query(QStringList* data){
    qDebug()<<"in create_query";
    QByteArray array_data=QJsonDocument(Json_creator(data).get_json_data()).toJson();
    i_adapter->sendData(array_data);
}
void Creator::data_received(QByteArray received_data){
    QJsonParseError parse_error;
    QByteArray data_array;
    QJsonObject object;
    QJsonDocument json_doc=QJsonDocument::fromJson(received_data, &parse_error);
    if (parse_error.error != QJsonParseError::NoError) {
        qWarning() << "Parse error at" << parse_error.offset << ":" << parse_error.errorString();
    }
    else{
        object=json_doc.object();
    }
    int request_code=object.take("RequestCode").toString().toInt();
    int error_code=object.take("ErrorCode").toString().toInt();//сразу в int не работает
    qDebug()<<"in data_received";
    Behavour_id behavour_id=static_cast<Behavour_id>(request_code);
    QVariantMap data_map=object.toVariantMap();
    //QStringList list_data=decoding_message(&object);
    //qDebug()<<"zero list_data is"<< list_data.at(0);
    behavour=Template_behavour::creating_specific_behavour(behavour_id);
    creating_connect(behavour_id);
    qDebug()<<error_code;
    behavour->processing_of_behavour(&data_map, error_code);


    /*
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
    //сигналы от Update_bahavour
    QObject::connect(this->behavour, SIGNAL(updation_failed()), this->main_window, SLOT(msg_updation_failed()));
    QObject::connect(this->behavour, SIGNAL(updation_successful(QStringlist*)), this->main_window, SLOT(msg_updation_successful(QStringList*)));
    */

}

/*QString Creator::encoding_message(const QStringList* data_list){
    QString encoded_message;
    encoded_message+=data_list->at(0);
    for (int i=1;i<data_list->size();i++){
        QString element=data_list->at(i);
        int size=element.size();
        int size_length=Creator::number_of_tens(size);
        encoded_message+=QString::number(size_length);
        encoded_message+=QString::number(size);
        encoded_message+=element;
    }
    return encoded_message;
}
QStringList Creator::decoding_message(QJsonObject* object){
    QStringList decoded_message;
    //decoded_message.push_front(object.take("RequestCode").toString());
    for(int i=2; i<object->size();i++){
        decoded_message.push_front(object->take("Title").toString());
    }
    return decoded_message;
}*/

void Creator::creating_connect(Behavour_id behavour_id){
    switch(behavour_id){
    case entry_id:
        QObject::connect(this->behavour, SIGNAL(user_not_exist()), this->main_window, SLOT(msg_such_user_not_exist()));
        QObject::connect(this->behavour, SIGNAL(user_exist(QVariantMap*)), this->main_window, SLOT(create_app_page(QVariantMap*)));
        break;
    case delete_id:
        QObject::connect(this->behavour, SIGNAL(deletion_failed()), this->main_window, SLOT(msg_deletion_failed()));
        QObject::connect(this->behavour, SIGNAL(deletion_successful(QVariantMap*)), this->main_window, SLOT(msg_deletion_successful(QVariantMap*)));
        break;
    case select_id:
        QObject::connect(this->behavour, SIGNAL(records_not_exist()), this->main_window, SLOT(msg_records_not_exist()));
        QObject::connect(this->behavour, SIGNAL(records_exist(QVariantMap*)), this->main_window, SLOT(msg_records_exist(QVariantMap*)));
        break;
    case insert_id:
        QObject::connect(this->behavour, SIGNAL(data_exist()), this->main_window, SLOT(msg_data_exist()));
        QObject::connect(this->behavour, SIGNAL(insert_successful(QVariantMap*)), this->main_window, SLOT(msg_insert_successful(QVariantMap*)));
        QObject::connect(this->behavour, SIGNAL(insert_failed()), this->main_window, SLOT(msg_insert_failed()));
        break;
    case registration_id:
        QObject::connect(this->behavour, SIGNAL(registration_failed()), this->main_window, SLOT(msg_registration_failed()));
        QObject::connect(this->behavour, SIGNAL(registration_successful(QVariantMap*)), this->main_window, SLOT(msg_registration_successful(QVariantMap*)));
        break;
    case select_all_id:
        QObject::connect(this->behavour, SIGNAL(all_records_not_exist()), this->main_window, SLOT(msg_all_records_not_exist()));
        QObject::connect(this->behavour, SIGNAL(all_records_exist(QVariantMap*)), this->main_window, SLOT(msg_all_records_exist(QVariantMap*)));
        break;
    case update_id:
        QObject::connect(this->behavour, SIGNAL(updation_failed()), this->main_window, SLOT(msg_updation_failed()));
        QObject::connect(this->behavour, SIGNAL(updation_successful(QVariantMap*)), this->main_window, SLOT(msg_updation_successful(QVariantMap*)));
        break;
    default:
        break;
    }
}
