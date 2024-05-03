#include "creator.h"
#include "template_behavour.h"
#include "json_creator.h"
#include "client_socket_adapter.h"

#include <QChar>
#include <QString>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QVariantMap>

Creator::Creator(QApplication* parent){
    main_window = new MainWindow(parent);
    main_window->setWindowTitle("FilmsInfo");
    main_window->show();
    i_adapter = new Client_socket_adapter(this);
    behavour = nullptr;
    QObject::connect(this->main_window, SIGNAL(have_request(QStringList*)), this, SLOT(create_query(QStringList*)));
    QObject::connect(this->i_adapter, SIGNAL(error_with_connection(const QString&)), this->main_window, SLOT(msg_about_connection(const QString&)));
    QObject::connect(this->i_adapter, SIGNAL(have_new_message(QByteArray)), this, SLOT(data_received(QByteArray)));
}

Creator::~Creator(){
    //delete main_window;
    delete i_adapter;
    delete behavour;
}

void Creator::set_host_port(QStringList arguments){
    i_adapter->set_host(arguments.at(0));
    i_adapter->set_port(arguments.at(1));
}
void Creator::create_query(QStringList* data){
    QByteArray array_data = QJsonDocument(Json_creator(data).get_json_data()).toJson();
    i_adapter->sendData(array_data);
}
void Creator::data_received(QByteArray received_data){
    QJsonParseError parse_error;
    QJsonObject object;
    QJsonDocument json_doc = QJsonDocument::fromJson(received_data, &parse_error);
    if (parse_error.error != QJsonParseError::NoError) {
        qWarning() << "Parse error at" << parse_error.offset << ":" << parse_error.errorString();
    }
    else {
        object = json_doc.object();
    }
    int request_code = object.take("RequestCode").toString().toInt();
    int error_code = object.take("ErrorCode").toString().toInt(); //сразу в int не работает
    Behavour_id behavour_id = static_cast<Behavour_id>(request_code);
    QVariantMap data_map = object.toVariantMap();
    behavour = Template_behavour::creating_specific_behavour(behavour_id);
    creating_connect(behavour_id);
    behavour->processing_of_behavour(&data_map, error_code);  
}


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
        QObject::connect(this->behavour, SIGNAL(data_exist(QVariantMap*)), this->main_window, SLOT(msg_data_exist(QVariantMap* )));
        QObject::connect(this->behavour, SIGNAL(insert_successful(QVariantMap*)), this->main_window, SLOT(msg_insert_successful(QVariantMap*)));
        QObject::connect(this->behavour, SIGNAL(insert_failed(QVariantMap*)), this->main_window, SLOT(msg_insert_failed(QVariantMap*)));
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
