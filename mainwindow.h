#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "start_page.h"
#include "registration_page.h"
#include "app_page.h"
#include "dialog.h"

#include <QMainWindow>
#include <QString>
#include <QStringList>
#include <QLabel>
#include <QMenuBar>
#include <QVariantMap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:

    MainWindow(QApplication* parent = nullptr);
    ~MainWindow();

private:

    Ui::MainWindow *ui;
    QLabel* status;
    //Dialog* dialog; // в процессе разработки
    Start_page* start_page;
    Registration_page* registration_page;
    App_page* app_page;
    MainWindow(MainWindow const& other)            = delete;
    MainWindow& operator=(MainWindow const& other) = delete;
    MainWindow(MainWindow && other)                = delete;
    MainWindow& operator=(MainWindow && other)     = delete;

signals:

    void entry_response();
    void delete_response();
    void have_request(QStringList* data);
    void window_was_destroyed();

public slots:

    void set_username(QString username);
    void resize_window();
    void msg_incorrect_email_or_password();
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

    void msg_about_connection(const QString&);
    void msg_such_user_not_exist();
    void create_app_page(QVariantMap* data);
    void msg_deletion_failed();
    void msg_deletion_successful(QVariantMap* data);
    void msg_records_not_exist();
    void msg_records_exist(QVariantMap* data);
    void msg_data_exist(QVariantMap* data);
    void msg_insert_successful(QVariantMap* data);
    void msg_insert_failed(QVariantMap* data);
    void msg_registration_failed();
    void msg_registration_successful(QVariantMap* data);
    void msg_all_records_not_exist();
    void msg_all_records_exist(QVariantMap* data);
    void msg_updation_failed();
    void msg_updation_successful(QVariantMap* data);
};

#endif // MAINWINDOW_H
