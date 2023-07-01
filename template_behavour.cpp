#include "template_behavour.h"

Template_behavour::Template_behavour()
{}
Template_behavour::~Template_behavour()
{}
Template_behavour* Template_behavour::creating_specific_behavour( Behavour_id  id){
    Template_behavour* behavour;
    switch(id){
    case entry_id:
        behavour=new Entry_behavour();
        break;
    case delete_id:
        behavour=new Delete_behavour();
        break;
    case select_id:
        behavour=new Select_behavour();
        break;
    case insert_id:
        behavour=new Update_behavour();
        break;
    case registration_id:
        behavour=new Registration_behavour();
        break;
    case select_all_id:
        behavour=new Select_all_behavour();
        break;
    case update_id:
        behavour=new Update_behavour();
        break;
    default:
        behavour=nullptr;
        break;
    }
    return behavour;
}

/*void Template_behavour::decoding_element(QStringList* data_list, const QStringList::iterator iter_to_element){
    QString element;
    int length=0;
    for(int i=0; i<iter_to_element->size()-length-1; i+=length){
        length=iter_to_element->at(i).digitValue();
        element.push_back(iter_to_element->sliced(i+1, length));
        element.push_back(' ');
    }
    const QStringList::iterator current_position=data_list->erase(iter_to_element);
    data_list->insert(current_position, element);
}*/
void Entry_behavour::processing_of_behavour(QStringList* data){
    if (data->at(0)=="NO"){
        emit user_not_exist();
    }
    else {
        data->removeFirst();//подразумевается удаление кода ошибки перепроверить состояние контейнера после
        emit user_exist(data);
    }
}
void Delete_behavour::processing_of_behavour(QStringList* data){
    if (data->at(0)=="NO"){
        emit deletion_failed();
    }
    else emit deletion_successful();

}
void Select_behavour::processing_of_behavour(QStringList* data){
    if (data->size()>1){
        emit records_exist(data);
    }
    else
        emit records_not_exist();
}
void Insert_behavour::processing_of_behavour(QStringList* data){
    if (data->at(0)=="EXIST"){
        emit data_exist();
    }
    else if(data->at(0)=="OK"){
        data->removeFirst();
        emit insert_successful(data);
    }
    else emit insert_failed();
}

void Registration_behavour::processing_of_behavour(QStringList* data){
    if (data->at(0)=="EXIST"){
        emit registration_failed();
    }
    else emit registration_successful(data);
}
void Select_all_behavour::processing_of_behavour(QStringList* data){
    if (data->size()>1){
        emit all_records_exist(data);
    }
    else
        emit all_records_not_exist();
}
void Update_behavour::processing_of_behavour(QStringList* data){
    if (data->at(0)=="NO"){
        emit updation_failed();
    }
    else emit updation_successful(data);

}
