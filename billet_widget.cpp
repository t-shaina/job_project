#include "billet_widget.h"

#include <QIcon>
#include <QCommonStyle>

Billet_widget::Billet_widget(QWidget* parent, const QString& data)
    :QGroupBox(parent),
    text_label(new QLabel(this)),
    delete_button(new QPushButton(this)){

    QFont font("Cochin", 0, 0);
    font.setPixelSize(14);
    this->setFont(font);
    layout = new QHBoxLayout();
    layout->addWidget(text_label);
    layout->addWidget(delete_button);
    layout->setContentsMargins(0,0,0,0);
    text_label->setText(data);
    text_label->setScaledContents(true);
    text_label->setFixedHeight(15);
    QCommonStyle style;
    delete_button->setIcon(style.standardIcon(QStyle::SP_DockWidgetCloseButton/*SP_TitleBarCloseButton*/));
    delete_button->setFixedSize(13,13);
    this->setFixedSize(text_label->width()+delete_button->width(), text_label->height());
    this->setStyleSheet("QGroupBox{border: 1px;}");
    setLayout(layout);
    this->show();
    connect(delete_button, SIGNAL(clicked()), this, SLOT(on_delete_button_clicked()));
    emit widget_was_constructed();
}

Billet_widget::Billet_widget(const Billet_widget& b_w){
    text_label    = b_w.text_label;
    delete_button = b_w.delete_button;
}
Billet_widget& Billet_widget::operator=(const Billet_widget& b_w){
    if (&b_w != this){
        text_label    = b_w.text_label;
        delete_button = b_w.delete_button;
    }
    return *this;
}

bool Billet_widget::operator==(const Billet_widget& b_w)const{
    if (text_label == b_w.text_label || delete_button == b_w.delete_button)
        return true;
    else return false;
}

void Billet_widget::on_delete_button_clicked(){
    emit widget_was_deleted(this->text());
}

Billet_widget::~Billet_widget(){
    delete layout;
}

QString Billet_widget::text()const{
    return text_label->text();
}
