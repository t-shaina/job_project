#ifndef START_PAGE_H
#define START_PAGE_H

#include "line_edit.h"
#include "push_button.h"

#include <QWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QStringList>

class Start_page : public QWidget{
    Q_OBJECT

public:

    explicit Start_page(QWidget* parent = nullptr);
    ~Start_page();
    void set_start_page_visible(bool flag);

private:

    QLabel* label_email;
    QLabel* label_password;
    LineEdit* edit_email;
    LineEdit* edit_password;
    PushButton* button_entry;
    PushButton* button_registration;
    QGridLayout* layout_page1;

    Start_page(Start_page const & other)            = delete;
    Start_page& operator=(Start_page const & other) = delete;
    Start_page(Start_page && other)                 = delete;
    Start_page& operator=(Start_page && other)      = delete;

private slots:

    void on_email_password_edit_edited();
    void on_email_return_pressed();
    void on_password_return_pressed();
    bool is_email_password_edits_is_correct();
    inline void set_focus_to_button_entry(){button_entry->setFocus();}
    inline void set_focus_to_button_registration(){button_registration->setFocus();}
    inline void set_focus_to_edit_email(){edit_email->setFocus();}
    inline void set_focus_to_edit_password(){edit_password->setFocus();}

signals:

    void entry_request(QStringList*);
    void create_registration_page();
    void incorrect_email_or_password();

public slots:

    void on_button_entry_clicked();
    void on_button_registration_clicked();
};

#endif // START_PAGE_H
