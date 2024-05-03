#include "push_button.h"
#include<QKeyEvent>

PushButton::PushButton(const QString &text, QWidget *parent)
    :QPushButton(text, parent){

}

PushButton::PushButton(QWidget *parent)
    :QPushButton(parent){

}

void PushButton::keyPressEvent(QKeyEvent* event){
    QPushButton::keyPressEvent(event);
    switch (event->key()) {
    case Qt::Key_Enter:
        emit enter_pressed();
        break;
    case Qt::Key_Down:
        emit down_pressed();
        break;
    case Qt::Key_Up:
        emit up_pressed();
        break;
    case Qt::Key_Right:
        emit right_pressed();
        break;
    case Qt::Key_Left:
        emit left_pressed();
        break;
    default:
        break;
    }
}
