#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"start_page.h"
#include"registration_page.h"
#include"app_page.h"
#include <QMainWindow>
#include <QString>
#include<QStringList>
#include<QLabel>
#include<QVariantMap>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QLabel status;
    Start_page* start_page;
    Registration_page* registration_page;
    App_page* app_page;

    //QStringList decoding_message(const QString& encoded_string);
signals:
    void entry_response();
    void delete_response();
    void have_request(QStringList* data);

public slots:
    void set_username(QString username);
    void resize_window();

    void destroy_app_page();
    void creating_registration_page();
    void breaking_registration_page();
    void processing_search_request(QStringList*);
    void processing_delete_request(QStringList*);
    void processing_select_all_request(QStringList*);
    void processing_update_request(QStringList*);
    void processing_insert_request(QStringList*);
    void processing_entry_request(QStringList*);
    void processing_registration_request(QStringList*);
    // слоты обработки входящих сообщений
    void msg_such_user_not_exist();
    void create_app_page(QVariantMap* data);
    void msg_deletion_failed();
    void msg_deletion_successful();
    void msg_records_not_exist();
    void msg_records_exist(QVariantMap* data);
    void msg_data_exist();
    void msg_insert_successful(QVariantMap* data);
    void msg_insert_failed();
    void msg_registration_failed();
    void msg_registration_successful(QVariantMap* data);
    void msg_all_records_not_exist();
    void msg_all_records_exist(QVariantMap* data);
    void msg_updation_failed();
    void msg_updation_successful(QVariantMap* data);
    //void data_decryption(QString);
    //void data_encoding(QStringList* data);


};
#endif // MAINWINDOW_H
