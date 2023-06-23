#include "template_behavour.h"

Template_behavour::Template_behavour()
{}
Template_behavour::~Template_behavour()
{}
void Template_behavour::creating_specific_behavour(Template_behavour* behavour, Behavour_id  id){
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

}
void Template_behavour::decoding_element(QStringList* data_list, const QStringList::iterator iter_to_element){
    QString element;
    int length=0;
    for(int i=0; i<iter_to_element->size()-length-1; i+=length){
        length=iter_to_element->at(i).digitValue();
        element.push_back(iter_to_element->sliced(i+1, length));
        element.push_back(' ');
    }
    const QStringList::iterator current_position=data_list->erase(iter_to_element);
    data_list->insert(current_position, element);
}
void Entry_behavour::processing_of_behavour(QStringList* data){
    if (data->at(0)=="NO"){
        emit user_not_exist();
    }
    else {
        QStringList::iterator i=data->begin();
        decoding_element(data, i++);// decoding name_email
        decoding_element(data, i+=2);//decoding directors
        decoding_element(data, i++);//decoding genres
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

}
void Insert_behavour::processing_of_behavour(QStringList* data){
    if (data->at(0)=="EXIST"){
        emit data_exist();
    }
    else if(data->at(0)=="OK")emit insert_successful();
}

void Registration_behavour::processing_of_behavour(QStringList* data){
    if (data->at(0)=="EXIST"){
        emit user_exist();
    }
}
void Select_all_behavour::processing_of_behavour(QStringList* data){

}
void Update_behavour::processing_of_behavour(QStringList* data){
    if (data->at(0)=="NO"){
        emit updation_failed();
    }
    else emit updation_successful();

}
