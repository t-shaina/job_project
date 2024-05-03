#include "json_creator.h"
#include <QString>

Json_creator::Json_creator(QStringList* data){
    switch (data->at(0).toInt()) {
    case 0:
        json_data["RequestCode"] = data->at(0);
        json_data["Email"]       = data->at(1);
        json_data["Password"]    = data->at(2);
        break;
    case 1:
        json_data["RequestCode"] = data->at(0);
        json_data["Email"]       = data->at(1);
        json_data["Row"]         = Json_creator::creating_row_object(data, 2);
        break;
    case 2:
        json_data["RequestCode"] = data->at(0);
         json_data["Email"]      = data->at(1);
        json_data["SearchWord"]  = data->at(2);
        break;
    case 3:
        json_data["RequestCode"] = data->at(0);
        json_data["Email"]       = data->at(1);
        json_data["Row"]         = Json_creator::creating_row_object(data, 2);
        break;
    case 4:
        json_data["RequestCode"] = data->at(0);
        json_data["Name"]        = data->at(1);
        json_data["Email"]       = data->at(2);
        json_data["Password"]    = data->at(3);
        break;
    case 5:
        json_data["RequestCode"] = data->at(0);
        json_data["Email"]       = data->at(1);
        break;
    case 6:
        json_data["RequestCode"] = data->at(0);
        json_data["Email"]       = data->at(1);
        json_data["Row_new"]     = Json_creator::creating_row_object(data, 2);
        json_data["Row_old"]     = Json_creator::creating_old_row_object(data, 8); // с седьмого элемента начинается строка старых данных
        break;
    default:
        break;
    }
}


QJsonObject Json_creator::get_json_data(){
    return this->json_data;
}

QJsonArray Json_creator::creating_directors_or_genre_array(QString data){
    data.push_back(' ');
    QJsonArray data_array;
    QString word;
    for (int i = 0; i < data.size(); i++){
        if (data.at(i) == ' '){
            data_array.push_back(word);
            word.clear();
        }
        else word += data.at(i);
    }
    return data_array;
}

QJsonArray Json_creator::creating_old_directors_or_genre_array(QString data){
    data.push_back(',');
    QJsonArray data_array;
    QString word;
    for (int i = 0; i < data.size(); i++){
        if (data.at(i) == ','){
            i++;
            data_array.push_back(word);
            word.clear();
        }
        else word += data.at(i);
    }
    return data_array;
}

QJsonObject Json_creator::creating_row_object(QStringList* data, int position){
    QJsonObject json_row_data;
    json_row_data["Title"]     = data->at(position);
    json_row_data["Directors"] = Json_creator::creating_directors_or_genre_array(data->at(++position));
    json_row_data["Genres"]    = Json_creator::creating_directors_or_genre_array(data->at(++position));
    json_row_data["Year"]      = data->at(++position);
    json_row_data["Rating"]    = data->at(++position);
    json_row_data["Status"]    = data->at(++position);
    return json_row_data;
}

QJsonObject Json_creator::creating_old_row_object(QStringList* data, int position){
    QJsonObject json_row_data;
    json_row_data["Title"]     = data->at(position);
    json_row_data["Directors"] = Json_creator::creating_old_directors_or_genre_array(data->at(++position));
    json_row_data["Genres"]    = Json_creator::creating_old_directors_or_genre_array(data->at(++position));
    json_row_data["Year"]      = data->at(++position);
    json_row_data["Rating"]    = data->at(++position);
    json_row_data["Status"]    = data->at(++position);
    return json_row_data;
}
