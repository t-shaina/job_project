#include "spin_box.h"
#include <QKeyEvent>

SpinBox::SpinBox(QWidget* parent)
    : QSpinBox(parent){

}

void SpinBox::keyPressEvent(QKeyEvent* event){
    switch (event->key()) {
    case Qt::Key_Enter:
        QSpinBox::keyPressEvent(event);
        emit enter_pressed();
        break;
    case Qt::Key_Down:
        emit down_pressed();
        break;
    case Qt::Key_Up:
        emit up_pressed();
        break;
    default:
        QSpinBox::keyPressEvent(event);
        break;
    }
}
