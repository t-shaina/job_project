#include "dialog.h"
#include<QGroupBox>

Dialog::Dialog(QWidget *parent)
    :QDialog(parent)
    ,close_button (new PushButton("Закрыть", this))
    ,cancel_button(new PushButton("Отмена", this))
    ,label        (new QLabel("Вы хотите закрыть приложение?", this)){
    this->setWindowModality(Qt::WindowModal);
    this->setWindowModified(false);
    this->setFixedSize(250, 175);
    QVBoxLayout* v_layout;
    QHBoxLayout* h_layout;
    QGroupBox* h_group;
    label->setEnabled(false);
    h_layout->addWidget(cancel_button, Qt::AlignCenter);
    h_layout->addWidget(close_button, Qt::AlignCenter);
    h_group->setLayout(h_layout);
    v_layout->addWidget(label, Qt::AlignCenter);
    v_layout->addWidget(h_group, Qt::AlignCenter);
    setLayout(v_layout);
    this->show();
}

Dialog::~Dialog(){
    delete close_button;
    delete cancel_button;
}
