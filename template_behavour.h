#ifndef Template_behavour_H
#define Template_behavour_H

#include <QObject>

enum Behavour_id{entry_id=0, delete_id=1, select_id=2, insert_id=3, registration_id=4, select_all_id=5, update_id=6};

class Template_behavour:public QObject
{
    Q_OBJECT
public:
    Template_behavour();
    virtual ~Template_behavour();
    virtual  void processing_of_behavour(QStringList* data)=0;
    //void decoding_element(QStringList* data_list, const QStringList::iterator iter_to_element);
    static Template_behavour* creating_specific_behavour(Behavour_id  id);
};
class Entry_behavour:public Template_behavour{
    Q_OBJECT
private:
    void processing_of_behavour(QStringList* data);
signals:
    void user_not_exist();
    void user_exist(QStringList* data);

};
class Delete_behavour:public Template_behavour{
    Q_OBJECT
private:
    void processing_of_behavour(QStringList* data);
signals:
    void deletion_failed();
    void deletion_successful();
};
class Select_behavour:public Template_behavour{
    Q_OBJECT
private:

    void processing_of_behavour(QStringList* data);
signals:
    void records_exist(QStringList* data);
    void records_not_exist();
};
class Insert_behavour:public Template_behavour{
    Q_OBJECT
private:
    void processing_of_behavour(QStringList* data);
signals:
    void data_exist();
    void insert_successful(QStringList* data);
    void insert_failed();
};
class Registration_behavour:public Template_behavour{
    Q_OBJECT
private:
    void processing_of_behavour(QStringList* data);
signals:
    void registration_failed();
    void registration_successful(QStringList* data);
};
class Select_all_behavour:public Template_behavour{
    Q_OBJECT
private:
    void processing_of_behavour(QStringList* data);
signals:
    void all_records_not_exist();
    void all_records_exist(QStringList* data);
};
class Update_behavour:public Template_behavour{
    Q_OBJECT
private:
    void processing_of_behavour(QStringList* data);
signals:
    void updation_failed();
    void updation_successful(QStringList* data);
};
#endif // Template_behavour_H
