#ifndef JSON_CREATOR_H
#define JSON_CREATOR_H


#include<QStringList>
#include<QJsonObject>
#include<QJsonArray>
#include<QString>
//enum Json_template_id{entry_id=0, delete_id=1, select_id=2, insert_id=3, registration_id=4, select_all_id=5, update_id=6};
class Json_creator
{

public:
    Json_creator(QStringList* data);
    static QJsonArray creating_directors_or_genre_array(QString data);
    static QJsonArray creating_old_directors_or_genre_array(QString data);// with commas
    static QJsonObject creating_row_object(QStringList* data, int position=2);
    static QJsonObject creating_old_row_object(QStringList* data, int position=8);// with commas
    QJsonObject get_json_data();
    ~Json_creator();
private:
    QJsonObject json_data;
};

#endif // JSON_CREATOR_H
