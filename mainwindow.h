#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"app_page.h"
#include <QMainWindow>
#include <QString>
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
    App_page* app_page;
private:
    Ui::MainWindow *ui;

public slots:
    void set_username(QString username);
    void resize_window();
    void creat_app_page();
    void destroy_app_page();
};
#endif // MAINWINDOW_H
