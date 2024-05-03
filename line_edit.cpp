#include "line_edit.h"
#include<QKeyEvent>

LineEdit::LineEdit(QWidget* parent)
    :QLineEdit(parent){
    this->setEnabled(true);
    this->setReadOnly(false);
    this->setUpdatesEnabled(true);
}

void LineEdit::keyPressEvent(QKeyEvent* event){
    QLineEdit::keyPressEvent(event);
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
