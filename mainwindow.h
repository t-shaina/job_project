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
    QLabel status;
    Start_page* start_page;
    Registration_page* registration_page;
    App_page* app_page;
    Socket* socket_db;

private:
    Ui::MainWindow *ui;
signals:
    void entry_response();
    void delete_response();
public slots:
    void set_username(QString username);
    void resize_window();
    void create_app_page();
    void destroy_app_page();
    void on_create_registration_page();
    void on_destroy_registration_page();
    void on_search_request(QString);
    void on_delete_request(QStringList);
    void on_update_request(QStringList);
    void on_entry_request(QStringList);
    void on_registration_request(QStringList);
    void data_decryption(QString);
};
#endif // MAINWINDOW_H
