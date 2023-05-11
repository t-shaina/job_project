#include "start_page.h"
#include "app_page.h"
#include "socket.h"
#include<QString>
#include <QProcess>
#include<QObject>
#include<QStringList>

const QString email_label_text="Email:";
const QString password_label_text="Пароль:";
const QString entrbutton_text="Вход";
Start_page::Start_page(QWidget *parent)
    :QWidget(parent),
    label_email(new QLabel(email_label_text,this)),
    label_password(new QLabel(password_label_text, this)),
    edit_email(new QLineEdit(this)),
    edit_password(new QLineEdit(this)),
    button_entry(new QPushButton(entrbutton_text, this)),
    layout_page1(new QGridLayout(this))

{

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

    connect(button_entry, SIGNAL(clicked()), this, SLOT(on_button_entry_clicked()));
}

Start_page::~Start_page(){};

void Start_page::set_start_page_visible(bool flag){
    label_email->setVisible(flag);
    label_password->setVisible(flag);
    edit_email->setVisible(flag);
    edit_password->setVisible(flag);
    button_entry->setVisible(flag);
}
//void Start_page::logged_in(QString username){};
void Start_page::on_button_entry_clicked(){
    QString email=edit_email->text();
    QString password=edit_password->text();
    QString list_query;
    list_query.append("0");
    list_query.append(" ");
    list_query.append(email);
    list_query.append(" ");
    list_query.append(password);

    //Socket socket_to_db(this);
    //socket_to_db.sendQuery(list_query);

    //if logged in
    emit entry_request(email+" "+password);
    //set_start_page_visible(false);
    //App_page app_page(this);


}
