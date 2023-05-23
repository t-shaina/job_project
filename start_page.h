#ifndef START_PAGE_H
#define START_PAGE_H

#include <QWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include<QString>
class Start_page: public QWidget
{
    Q_OBJECT

public:
    explicit Start_page(QWidget *parent = nullptr);
    ~Start_page();
    void set_start_page_visible(bool flag);
private:

    QLabel* label_email;
    QLabel* label_password;
    QLineEdit* edit_email;
    QLineEdit* edit_password;
    QPushButton* button_entry;
    QPushButton* button_registration;
    QGridLayout* layout_page1;
private slots:
    void on_email_password_edit_edited();

signals:
    void entry_request(QString);
    void create_registration_page();
public slots:
    void on_button_entry_clicked();
    void on_button_registration_clicked();


};

#endif // START_PAGE_H
