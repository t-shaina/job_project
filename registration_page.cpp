#include "registration_page.h"
#include<QString>
#include<QStringList>
#include<QLabel>
#include<QVBoxLayout>
#include<QGroupBox>

const QString name_label_text="Введите Имя:";
const QString email_label_text="Введите Email:";
const QString password_label_text="Введите Пароль:";
const QString repeat_password_label_text="Повторите Пароль:";
const QString backbutton_text="Назад";
const QString regbutton_text="Регистрация";
const QString incorrect_repeated_password_text="Пароли не совпадают";

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
    incorrect_repeated_password_msg(new QLabel(edit_repeat_password)),
    back_button(new QPushButton(backbutton_text, this)),
    registration_button(new QPushButton(regbutton_text, this)),
    layout_registration_page(new QGridLayout(this))
{
    layout_registration_page->setVerticalSpacing(30);
    layout_registration_page->setRowMinimumHeight(0, 50);
    layout_registration_page->setRowMinimumHeight(6, 50);
    layout_registration_page->setColumnMinimumWidth(5, 70);
    layout_registration_page->setColumnMinimumWidth(0, 70);
    layout_registration_page->addWidget(label_name, 0, 1, Qt::AlignLeft);
    layout_registration_page->addWidget(label_email, 1, 1, Qt::AlignLeft);
    layout_registration_page->addWidget(label_password, 2, 1, Qt::AlignLeft);
    layout_registration_page->addWidget(label_repeat_password, 3, 1, Qt::AlignLeft);
    layout_registration_page->addWidget(edit_name, 0, 3, Qt::AlignLeft);
    layout_registration_page->addWidget(edit_email, 1, 3, Qt::AlignLeft);
    layout_registration_page->addWidget(edit_password, 2, 3, Qt::AlignLeft);
    layout_registration_page->addWidget(edit_repeat_password, 3, 3, Qt::AlignLeft);
    //layout_registration_page->addWidget(incorrect_repeated_password_msg, 4, 3, Qt::AlignLeft);
    layout_registration_page->addWidget(back_button, 5, 1, Qt::AlignCenter);
    layout_registration_page->addWidget(registration_button, 5, 3, Qt::AlignCenter);

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
    incorrect_repeated_password_msg->setText(incorrect_repeated_password_text);
    incorrect_repeated_password_msg->setVisible(false);
    incorrect_repeated_password_msg->setStyleSheet("color: red; font-size: 10px");


    registration_button->setEnabled(false);

    //edit_email->returnPressed();

    connect(edit_name, SIGNAL(textEdited(QString)), this, SLOT(on_edits_edited()));
    connect(edit_email, SIGNAL(textEdited(QString)), this, SLOT(on_edits_edited()));
    connect(edit_password, SIGNAL(textEdited(QString)), this, SLOT(on_edits_edited()));
    connect(edit_repeat_password, SIGNAL(textEdited(QString)), this, SLOT(on_edits_edited()));
    connect(back_button, SIGNAL(clicked()), this, SLOT(on_back_button_clicked()));
    connect(registration_button, SIGNAL(clicked()), this, SLOT(on_registration_button_clicked()));

    edit_name->setFocus();
    connect(edit_name, SIGNAL(returnPressed()), this, SLOT(on_name_return_pressed()));
    connect(edit_email, SIGNAL(returnPressed()), this, SLOT(on_email_return_pressed()));
    connect(edit_password, SIGNAL(returnPressed()), this, SLOT(on_password_return_pressed()));
    connect(edit_repeat_password, SIGNAL(returnPressed()), this, SLOT(on_repeat_password_return_pressed()));

}

void Registration_page::on_edits_edited(){
    if(!is_edits_are_correct()){
        registration_button->setEnabled(false);
    }
    else registration_button->setEnabled(true);

    if (edit_password->text() ==edit_repeat_password->text()){
        incorrect_repeated_password_msg->setVisible(false);
    }
}
void Registration_page::on_back_button_clicked(){
    emit step_back();
}
void Registration_page::on_registration_button_clicked(){
    if (edit_password->text() !=edit_repeat_password->text()){
        incorrect_repeated_password_msg->setVisible(true);
    }
    else {
        QStringList registration_list=QStringList()<<edit_name->text()<<edit_email->text()<<edit_password->text();

        emit registration_request(&registration_list);
    }
}
bool Registration_page::is_edits_are_correct(){
    if(edit_name->text().isEmpty()||edit_email->text().isEmpty()||
        edit_password->text().isEmpty()||edit_repeat_password->text().isEmpty()||
        edit_password->text().length()!=6 ||edit_repeat_password->text().length()!=6){
        return false;
    }
    else return true;
}
void Registration_page::on_name_return_pressed(){
    if(is_edits_are_correct())
        on_registration_button_clicked();
    else edit_email->setFocus();
}
void Registration_page::on_email_return_pressed(){
    if(is_edits_are_correct())
        on_registration_button_clicked();
    else edit_password->setFocus();
}
void Registration_page::on_password_return_pressed(){
    if(is_edits_are_correct())
        on_registration_button_clicked();
    else edit_repeat_password->setFocus();
}
void Registration_page::on_repeat_password_return_pressed(){
    if(is_edits_are_correct())
        on_registration_button_clicked();
    else edit_name->setFocus();
}
