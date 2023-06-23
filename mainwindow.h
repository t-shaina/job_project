#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"start_page.h"
#include"registration_page.h"
#include"app_page.h"
#include"socket.h"
#include <QMainWindow>
#include <QString>
#include<QStringList>
#include<QLabel>

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
    void on_create_registration_page();
    void on_destroy_registration_page();
    void on_search_request(QStringList*);
    void on_delete_request(QStringList*);
    void on_select_all_request(QStringList*);
    void on_update_request(QStringList*);
    void on_insert_request(QStringList*);
    void on_entry_request(QStringList*);
    void on_registration_request(QStringList*);
    // слоты обработки входящих сообщений
    void msg_such_user_not_exist();
    void create_app_page(QStringList*);
    //void data_decryption(QString);
    //void data_encoding(QStringList* data);


};
#endif // MAINWINDOW_H
