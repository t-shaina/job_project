#include "menu.h"

Menu::Menu(QStringList actions_list, QWidget* parent)
    :QMenu(parent){
    int size = actions_list.size();
    for (int i = 0; i < size; ++i){
        QAction action = QAction(actions_list.at(i), this);
        this->addAction(&action);
        if (i < size - 1)
        this->addSeparator();
    }
}

Menu::Menu(QString action1_, QString action2_, QWidget* parent)
    :QMenu(parent){
    QAction action1 = QAction(action1_, this);
    this->addAction(&action1);
    this->addSeparator();
    QAction action2 = QAction(action2_, this);
    this->addAction(&action2);
    this->addSeparator();
}

QAction* Menu::execute_menu(){
    QAction* selectedItem = this->exec(QCursor::pos());
    return selectedItem;
}
