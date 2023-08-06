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
    font.setPixelSize(14);
    this->setFont(font);//забрать у родителя
    QHBoxLayout* layout= new QHBoxLayout;
    layout->addWidget(text_label);
    layout->addWidget(delete_button);
    layout->setContentsMargins(0,0,0,0);
    text_label->setText(data);
    text_label->setScaledContents(true);
    text_label->setFixedHeight(15);
    QCommonStyle style;
    delete_button->setIcon(style.standardIcon(QStyle::SP_TitleBarCloseButton));
    delete_button->setFixedSize(13,13);
    this->setFixedSize(text_label->width()+delete_button->width(), text_label->height());
    this->setStyleSheet("QGroupBox{border: 1px;}");
    setLayout(layout);

    this->show();
    connect(delete_button, SIGNAL(clicked()), this, SLOT(on_delete_button_clicked()));
    qDebug()<<"in billet_widget constructor";
}
void Billet_widget::on_delete_button_clicked(){
    this->~Billet_widget();
}
Billet_widget::~Billet_widget(){
    emit widget_was_deleted(this->text());
    qDebug()<<"in billet_widget destructor";
}
QString Billet_widget::text(){
    return text_label->text();
}
