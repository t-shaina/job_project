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
    virtual  void processing_of_behavour(QVariantMap* data, int error_code)=0;
    //virtual void creating_connect(Template_behavour* behavour)=0;
    //void decoding_element(QStringList* data_list, const QStringList::iterator iter_to_element);
    static Template_behavour* creating_specific_behavour(Behavour_id  id);

};
class Entry_behavour:public Template_behavour{
    Q_OBJECT
private:
    void processing_of_behavour(QVariantMap* data, int error_code);
public slots:
    //void creating_connect(Template_behavour* behavour);
signals:
    void user_not_exist();
    void user_exist(QVariantMap* data);

};
class Delete_behavour:public Template_behavour{
    Q_OBJECT
private:
    void processing_of_behavour(QVariantMap* data, int error_code);
public slots:
    //void creating_connect(Template_behavour* behavour);
signals:   
    void deletion_failed();
    void deletion_successful();
};
class Select_behavour:public Template_behavour{
    Q_OBJECT
private:
    void processing_of_behavour(QVariantMap* data, int error_code);
public slots:
    //void creating_connect(Template_behavour* behavour);
signals:
    void records_exist(QVariantMap* data);
    void records_not_exist();
};
class Insert_behavour:public Template_behavour{
    Q_OBJECT
private:
    void processing_of_behavour(QVariantMap* data, int error_code);
public slots:
    //void creating_connect(Template_behavour* behavour);
signals:
    void data_exist();
    void insert_successful(QVariantMap* data);
    void insert_failed();
};

class Registration_behavour:public Template_behavour{
    Q_OBJECT
private:
    void processing_of_behavour(QVariantMap* data, int error_code);
public slots:
    //void creating_connect(Template_behavour* behavour);
signals:
    void registration_failed();
    void registration_successful(QVariantMap* data);
};

class Select_all_behavour:public Template_behavour{
    Q_OBJECT
private:
    void processing_of_behavour(QVariantMap* data, int error_code);
public slots:
    //void creating_connect(Template_behavour* behavour);
signals:
    void all_records_not_exist();
    void all_records_exist(QVariantMap* data);

};

class Update_behavour:public Template_behavour{
    Q_OBJECT
private:
    void processing_of_behavour(QVariantMap* data, int error_code);
public slots:
    //void creating_connect(Template_behavour* behavour);
signals:
    void updation_failed();
    void updation_successful(QVariantMap* data);
};
#endif // Template_behavour_H
