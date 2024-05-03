#ifndef JSON_CREATOR_H
#define JSON_CREATOR_H

#include <QStringList>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>

class Json_creator{

public:

    Json_creator(QStringList* data);
    static QJsonArray creating_directors_or_genre_array(QString data);
    static QJsonArray creating_old_directors_or_genre_array(QString data);
    static QJsonObject creating_row_object(QStringList* data, int position = 2);
    static QJsonObject creating_old_row_object(QStringList* data, int position = 8);
    QJsonObject get_json_data();

private:

    QJsonObject json_data;
};

#endif // JSON_CREATOR_H
