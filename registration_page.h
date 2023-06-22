#ifndef REGISTRATION_PAGE_H
#define REGISTRATION_PAGE_H

#include <QObject>
#include <QWidget>
#include<QPushButton>
#include<QLabel>
#include<QGridLayout>
#include<QLineEdit>
#include<QStringList>
class Registration_page: public QWidget
{
    Q_OBJECT
public:
    Registration_page(QWidget* parent=nullptr);

private:
    QLabel* label_name;
    QLabel* label_email;
    QLabel* label_password;
    QLabel* label_repeat_password;
    QLineEdit* edit_name;
    QLineEdit* edit_email;
    QLineEdit* edit_password;
    QLineEdit* edit_repeat_password;
    QLabel* incorrect_repeated_password_msg;
    QPushButton* button_entry;
    QPushButton* button_registration;
    QGridLayout* layout_registration_page;
    QPushButton* back_button;
    QPushButton* registration_button;
private slots:
    void on_edits_edited();
    void on_back_button_clicked();
    void on_registration_button_clicked();
signals:
    void step_back();
    void registration_request(QStringList*);


};

#endif // REGISTRATION_PAGE_H
