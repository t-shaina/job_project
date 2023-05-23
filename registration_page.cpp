#include "registration_page.h"
#include<QString>

const QString name_label_text="Введите имя:";
const QString email_label_text="Введите Email:";
const QString password_label_text="Введите Пароль:";
const QString repeat_password_label_text="Повторите Пароль:";
const QString backbutton_text="Назад";
const QString regbutton_text="Регистрация";

Registration_page::Registration_page(QWidget *parent)
    :QWidget(parent),
    label_name(new QLabel(name_label_text,this)),
    label_email(new QLabel(email_label_text,this)),
    label_password(new QLabel(password_label_text, this)),
    label_repeat_password(new QLabel(repeat_password_label_text, this)),
    edit_name(new QLineEdit(this)),
    edit_email(new QLineEdit(this)),
    edit_password(new QLineEdit(this)),
    edit_repeat_password(new QLineEdit(this)),
    back_button(new QPushButton(backbutton_text, this)),
    registration_button(new QPushButton(regbutton_text, this)),
    layout_registration_page(new QGridLayout(this))
{
    layout_registration_page->setVerticalSpacing(30);
    layout_registration_page->setRowMinimumHeight(0, 50);
    layout_registration_page->setRowMinimumHeight(6, 50);
    layout_registration_page->setColumnMinimumWidth(5, 70);
    layout_registration_page->setColumnMinimumWidth(0, 70);
    layout_registration_page->addWidget(label_name, 0, 2, Qt::AlignLeft);
    layout_registration_page->addWidget(label_email, 1, 2, Qt::AlignLeft);
    layout_registration_page->addWidget(label_password, 2, 2, Qt::AlignLeft);
    layout_registration_page->addWidget(label_repeat_password, 3, 2, Qt::AlignLeft);
    layout_registration_page->addWidget(edit_name, 0, 4, Qt::AlignLeft);
    layout_registration_page->addWidget(edit_email, 1, 4, Qt::AlignLeft);
    layout_registration_page->addWidget(edit_password, 2, 4, Qt::AlignLeft);
    layout_registration_page->addWidget(edit_repeat_password, 3, 4, Qt::AlignLeft);
    layout_registration_page->addWidget(back_button, 4, 2, Qt::AlignCenter);
    layout_registration_page->addWidget(registration_button, 4, 4, Qt::AlignCenter);

    setLayout(layout_registration_page);
    this->show();
    this->setFixedSize(500,350);
    this->resize(500,500);
    label_email->resize(200,70);
    label_password->resize(200,70);
    edit_password->resize(200,70);
    edit_repeat_password->resize(200,70);
    edit_email->resize(200,70);
    edit_name->resize(200,70);
    back_button->resize(100, 50);
    registration_button->resize(100, 50);
    edit_password->setEchoMode(QLineEdit::Password);
    edit_repeat_password->setEchoMode(QLineEdit::Password);
    registration_button->setEnabled(false);

    connect(edit_name, SIGNAL(textEdited(QString)), this, SLOT(on_edits_edited()));
    connect(edit_email, SIGNAL(textEdited(QString)), this, SLOT(on_edits_edited()));
    connect(edit_password, SIGNAL(textEdited(QString)), this, SLOT(on_edits_edited()));
    connect(edit_repeat_password, SIGNAL(textEdited(QString)), this, SLOT(on_edits_edited()));
    connect(back_button, SIGNAL(clicked()), this, SLOT(on_back_button_clicked()));

}
void Registration_page::on_edits_edited(){
    if(edit_name->text().isEmpty()||
        edit_email->text().isEmpty()||
        edit_password->text().isEmpty()||
        edit_repeat_password->text().isEmpty()||
        (edit_password->text() !=edit_repeat_password->text())||
        edit_password->text().length()!=6)
        button_entry->setEnabled(false);
    else button_entry->setEnabled(true);

}
void Registration_page::on_back_button_clicked(){
    emit step_back();
}
