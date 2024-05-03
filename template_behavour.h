#ifndef Template_behavour_H
#define Template_behavour_H

#include <QObject>

enum Behavour_id{
    entry_id,
    delete_id,
    select_id,
    insert_id,
    registration_id,
    select_all_id,
    update_id
};

class Template_behavour : public QObject{
    Q_OBJECT

public:

    Template_behavour();
    virtual ~Template_behavour();
    virtual  void processing_of_behavour(QVariantMap* data, int error_code)=0;
    static Template_behavour* creating_specific_behavour(Behavour_id  id);
};

class Entry_behavour : public Template_behavour{
    Q_OBJECT

private:

    void processing_of_behavour(QVariantMap* data, int error_code);

public:

    virtual ~Entry_behavour(){};

signals:

    void user_not_exist();
    void user_exist(QVariantMap* data);
};

class Delete_behavour : public Template_behavour{
    Q_OBJECT

private:

    void processing_of_behavour(QVariantMap* data, int error_code);

public:

    virtual ~Delete_behavour(){};

signals:

    void deletion_failed();
    void deletion_successful(QVariantMap* data);
};

class Select_behavour : public Template_behavour{
    Q_OBJECT

private:

    void processing_of_behavour(QVariantMap* data, int error_code);

public:

    virtual ~Select_behavour(){};

signals:

    void records_exist(QVariantMap* data);
    void records_not_exist();
};

class Insert_behavour : public Template_behavour{
    Q_OBJECT

private:

    void processing_of_behavour(QVariantMap* data, int error_code);

public:

    virtual ~Insert_behavour(){};

signals:

    void data_exist(QVariantMap* data);
    void insert_successful(QVariantMap* data);
    void insert_failed(QVariantMap* data);
};

class Registration_behavour : public Template_behavour{
    Q_OBJECT

private:

    void processing_of_behavour(QVariantMap* data, int error_code);
public:

    virtual ~Registration_behavour(){};

signals:

    void registration_failed();
    void registration_successful(QVariantMap* data);
};

class Select_all_behavour : public Template_behavour{
    Q_OBJECT

private:

    void processing_of_behavour(QVariantMap* data, int error_code);

public:

    virtual ~Select_all_behavour(){};

signals:

    void all_records_not_exist();
    void all_records_exist(QVariantMap* data);
};

class Update_behavour:public Template_behavour{
    Q_OBJECT

private:

    void processing_of_behavour(QVariantMap* data, int error_code);

public:

    virtual ~Update_behavour(){};

signals:

    void updation_failed();
    void updation_successful(QVariantMap* data);
};

#endif // Template_behavour_H
