#ifndef REGISTRATION_PAGE_H
#define REGISTRATION_PAGE_H

#include "line_edit.h"
#include "push_button.h"

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QStringList>

class Registration_page : public QWidget{
    Q_OBJECT

public:

    Registration_page(QWidget* parent = nullptr);
    ~Registration_page();

private:

    QLabel* label_name;
    QLabel* label_email;
    QLabel* label_password;
    QLabel* label_repeat_password;
    LineEdit* edit_name;
    LineEdit* edit_email;
    LineEdit* edit_password;
    LineEdit* edit_repeat_password;
    QLabel* incorrect_repeated_password_msg;
    QGridLayout* layout_registration_page;
    PushButton* back_button;
    PushButton* registration_button;

    Registration_page(Registration_page const & other)            = delete;
    Registration_page& operator=(Registration_page const & other) = delete;
    Registration_page(Registration_page && other)                 = delete;
    Registration_page& operator=(Registration_page && other)      = delete;

private slots:

    void on_edits_edited();
    void on_back_button_clicked();
    void on_registration_button_clicked();
    bool is_edits_are_correct();
    void on_name_return_pressed();
    void on_email_return_pressed();
    void on_password_return_pressed();
    void on_repeat_password_return_pressed();
    inline void set_focus_to_edit_name(){edit_name->setFocus();}
    inline void set_focus_to_edit_email(){edit_email->setFocus();}
    inline void set_focus_to_edit_password(){edit_password->setFocus();}
    inline void set_focus_to_edit_repeat_password(){edit_repeat_password->setFocus();}
    inline void set_focus_to_back_button(){back_button->setFocus();}
    inline void set_focus_to_registration_button(){registration_button->setFocus();}

signals:

    void step_back();
    void registration_request(QStringList*);
};

#endif // REGISTRATION_PAGE_H
