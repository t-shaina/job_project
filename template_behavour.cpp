#include "template_behavour.h"
#include<QDebug>

Template_behavour::Template_behavour(){

}

Template_behavour::~Template_behavour(){

}

Template_behavour* Template_behavour::creating_specific_behavour(Behavour_id  id){
    Template_behavour* behavour;
    switch(id){
    case entry_id:
        behavour = new Entry_behavour();
        break;
    case delete_id:
        behavour = new Delete_behavour();
        break;
    case select_id:
        behavour = new Select_behavour();
        break;
    case insert_id:
        behavour = new Insert_behavour();
        break;
    case registration_id:
        behavour = new Registration_behavour();
        break;
    case select_all_id:
        behavour = new Select_all_behavour();
        break;
    case update_id:
        behavour = new Update_behavour();
        break;
    default:
        behavour = nullptr;
        break;
    }
    return behavour;
}


void Entry_behavour::processing_of_behavour(QVariantMap* data, int error_code){
    if (error_code == 1){
        emit user_not_exist();
    }
    else {
        emit user_exist(data);
    }
}

void Delete_behavour::processing_of_behavour(QVariantMap* data, int error_code){
    if (error_code == 1){
        emit deletion_failed();
    }
    else {
        emit deletion_successful(data);
    }

}

void Select_behavour::processing_of_behavour(QVariantMap* data, int error_code){
    if (error_code == 0){
        emit records_exist(data);
    }
    else {
        emit records_not_exist();
    }
}

void Insert_behavour::processing_of_behavour(QVariantMap* data, int error_code){
    if (error_code == 1){
        emit data_exist(data);
    }
    else if (error_code == 0){
        emit insert_successful(data);
    }
    else emit insert_failed(data);
}

void Registration_behavour::processing_of_behavour(QVariantMap* data, int error_code){
    if (error_code == 1){
        emit registration_failed();
    }
    else emit registration_successful(data);
}

void Select_all_behavour::processing_of_behavour(QVariantMap* data, int error_code){
    if (error_code == 0){
        qDebug() << "select all successfull";
        emit all_records_exist(data);
    }
    else {
        qDebug() << "select all failed";
        emit all_records_not_exist();
    }
}

void Update_behavour::processing_of_behavour(QVariantMap* data, int error_code){
    if (error_code == 1){
        qDebug() << "updation failed";
        emit updation_failed();
    }
    else {
        qDebug() << "updation successfull";
        emit updation_successful(data);
    }
}

