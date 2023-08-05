#include "billet_widget.h"
#include<QHBoxLayout>
#include<QIcon>
#include<QCommonStyle>
Billet_widget::Billet_widget(QWidget* parent, const QString& data)
    :QGroupBox(parent),
    /*group(new QGroupBox()),*/
    text_label(new QLabel(this)),
    delete_button(new QPushButton(this))
{
    QFont font("Cochin", 0, 0);
    this->setFont(font);//забрать у родителя
    QHBoxLayout* layout= new QHBoxLayout;
    layout->addWidget(text_label);
    layout->addWidget(delete_button);
    text_label->setText(data);
    text_label->setFixedSize(50, 10);
    QCommonStyle style;
    delete_button->setIcon(style.standardIcon(QStyle::SP_TitleBarCloseButton));
    delete_button->setFixedSize(15,15);
    this->setBaseSize(100, 50);
    setLayout(layout);

    this->show();
    connect(delete_button, SIGNAL(clicked()), this, SLOT(on_delete_button_clicked()));

}
void Billet_widget::on_delete_button_clicked(){
    this->~Billet_widget();
}
Billet_widget::~Billet_widget(){

}
QString Billet_widget::text(){
    return text_label->text();
}
