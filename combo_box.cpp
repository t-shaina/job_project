#include "combo_box.h"
#include<QKeyEvent>
ComboBox::ComboBox(QWidget* parent):QComboBox(parent)
{

}
void ComboBox::keyPressEvent(QKeyEvent *event){
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

