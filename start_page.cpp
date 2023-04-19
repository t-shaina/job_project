#include "start_page.h"
#include "socket.h"
#include<QString>
#include <QProcess>
#include<QObject>
#include<QStringList>
Start_page::Start_page(QWidget *parent)
    : QGroupBox(parent),
    label_email(new QLabel("Email:",this)),
    label_password(new QLabel("Пароль:", this)),
    edit_email(new QLineEdit(this)),
    edit_password(new QLineEdit(this)),
    button_entry(new QPushButton("Вход", this)),
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

void Start_page::on_button_entry_clicked(){
    QString email=edit_email->text();
    QString password=edit_password->text();
    QString list_query;
    list_query.append("0");
    list_query.append(" ");
    list_query.append(email);
    list_query.append(" ");
    list_query.append(password);

    QObject* parent;
    Socket* socket_to_db(parent);
    socket_to_db.sendQuery(list_query);




}
