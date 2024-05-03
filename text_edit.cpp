#include "text_edit.h"
#include <QKeyEvent>

TextEdit::TextEdit(QWidget* parent)
    :QTextEdit(parent){
    this->setEnabled(true);
    this->setReadOnly(false);
    this->setUpdatesEnabled(true);
}

void TextEdit::keyPressEvent(QKeyEvent* event){
    QTextEdit::keyPressEvent(event);
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
    default:
        break;
    }
}
