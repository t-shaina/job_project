#include "start_page.h"

#include <QStringList>
#include <QProcess>
#include <QObject>
#include <QStringList>

const QString email_label_text    = "Email:";
const QString password_label_text = "Пароль:";
const QString entrbutton_text     = "Вход";
const QString regbutton_text      = "Регистрация";

Start_page::Start_page(QWidget *parent)
    :QWidget(parent),
    label_email        (new QLabel(email_label_text,this)),
    label_password     (new QLabel(password_label_text, this)),
    edit_email         (new LineEdit(this)),
    edit_password      (new LineEdit(this)),
    button_entry       (new PushButton(entrbutton_text, this)),
    button_registration(new PushButton(regbutton_text, this)),
    layout_page1       (new QGridLayout(this)){

    layout_page1->setVerticalSpacing(50);
    layout_page1->setVerticalSpacing(50);
    layout_page1->setRowMinimumHeight(0, 50);
    layout_page1->setRowMinimumHeight(6, 50);
    layout_page1->setColumnMinimumWidth(5, 70);
    layout_page1->setColumnMinimumWidth(0, 70);
    layout_page1->addWidget(label_email, 1, 2, Qt::AlignCenter);
    layout_page1->addWidget(label_password, 3, 2, Qt::AlignCenter);
    layout_page1->addWidget(edit_email, 1, 4, Qt::AlignLeft);
    layout_page1->addWidget(edit_password, 3, 4, Qt::AlignLeft);
    layout_page1->addWidget(button_registration, 5, 2, Qt::AlignCenter);
    layout_page1->addWidget(button_entry, 5, 4, Qt::AlignCenter);

    setLayout(layout_page1);
    this->show();
    this->setFixedSize(500,350);
    this->resize(500,500);
    label_email->resize(200,70);
    label_password->resize(200,70);
    edit_password->resize(200,70);
    edit_email->resize(200,70);
    button_entry->resize(100, 50);
    button_registration->resize(100, 50);
    edit_password->setEchoMode(QLineEdit::Password);
    button_entry->setEnabled(false);

    connect(button_registration, SIGNAL(clicked()), this, SLOT(on_button_registration_clicked()));
    connect(button_entry, SIGNAL(clicked()), this, SLOT(on_button_entry_clicked()));
    connect(edit_email, SIGNAL(textEdited(QString)), this, SLOT(on_email_password_edit_edited()));
    connect(edit_password, SIGNAL(textEdited(QString)), this, SLOT(on_email_password_edit_edited()));

    edit_email->setFocus();
    connect(edit_email, SIGNAL(returnPressed()), this, SLOT(on_email_return_pressed()));
    connect(edit_email, SIGNAL(down_pressed()), this, SLOT(set_focus_to_edit_password()));
    connect(edit_password, SIGNAL(down_pressed()), this, SLOT(set_focus_to_button_entry()));
    connect(edit_password, SIGNAL(up_pressed()), this, SLOT(set_focus_to_edit_email()));
    connect(edit_password, SIGNAL(returnPressed()), this, SLOT(on_button_entry_clicked()));
    connect(button_registration, SIGNAL(enter_pressed()), this, SLOT(on_button_registration_clicked()));
    connect(button_registration, SIGNAL(right_pressed()), this, SLOT(set_focus_to_button_entry()));
    connect(button_entry, SIGNAL(enter_pressed()), this, SLOT(on_button_entry_clicked()));
    connect(button_entry, SIGNAL(up_pressed()), this, SLOT(set_focus_to_edit_password()));
}

Start_page::~Start_page(){
    delete edit_email;
    delete edit_password;
    delete button_entry;
    delete button_registration;
 }

void Start_page::set_start_page_visible(bool flag){
    label_email->setVisible(flag);
    label_password->setVisible(flag);
    edit_email->setVisible(flag);
    edit_password->setVisible(flag);
    button_entry->setVisible(flag);
    button_registration->setVisible(flag);
}

void Start_page::on_button_entry_clicked(){
    if (is_email_password_edits_is_correct()){
        QStringList entry_list = QStringList() << edit_email->text()
                                               << edit_password->text();
        emit entry_request(&entry_list);
    }
    else
        emit incorrect_email_or_password();
}

void Start_page::on_email_password_edit_edited(){
    if (!is_email_password_edits_is_correct())
        button_entry->setEnabled(false);
    else button_entry->setEnabled(true);
}

void Start_page::on_button_registration_clicked(){
    emit create_registration_page();
}

void Start_page::on_email_return_pressed(){
    if (is_email_password_edits_is_correct())
        on_button_entry_clicked();
    else edit_password->setFocus();
}

void Start_page::on_password_return_pressed(){
    if (is_email_password_edits_is_correct())
        on_button_entry_clicked();
    else edit_email->setFocus();
}

bool Start_page::is_email_password_edits_is_correct(){
    if(edit_email->text().isEmpty()    ||
        edit_password->text().isEmpty()||
        edit_password->text().length() !=6)
        return false;
    else return true;
}
