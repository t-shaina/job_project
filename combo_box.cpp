#include "combo_box.h"
#include <QKeyEvent>

ComboBox::ComboBox(QWidget* parent)
    :QComboBox(parent){

}

void ComboBox::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Return:
        QComboBox::keyPressEvent(event);
        emit return_pressed();
        break;
    case Qt::Key_Enter:
        QComboBox::keyPressEvent(event);
        emit enter_pressed();
        break;
    case Qt::Key_Down:
        emit down_pressed();
        break;
    case Qt::Key_Up:
        emit up_pressed();
        break;
    case Qt::Key_Right:       
        QComboBox::keyPressEvent(event);
        emit right_pressed();
        break;
    case Qt::Key_Left:
        QComboBox::keyPressEvent(event);
        emit left_pressed();
        break;
    default:       
        QComboBox::keyPressEvent(event);
        break;
    }

}
EditComboBox::EditComboBox(QWidget* parent)
    :QComboBox(parent){
    this->setEditable(true);
}

void EditComboBox::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Return:
        emit return_pressed();
        break;
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
        QComboBox::keyPressEvent(event);
        emit right_pressed();
        break;
    case Qt::Key_Left:
        QComboBox::keyPressEvent(event);
        emit left_pressed();
        break;
    default:
        QComboBox::keyPressEvent(event);
        break;
    }
}
