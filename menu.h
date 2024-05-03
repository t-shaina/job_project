#ifndef MENU_H
#define MENU_H

#include <QObject>
#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QStringList>
#include <QPoint>

class Menu: public QMenu{
    Q_OBJECT

public:

    Menu(QStringList actions_list, QWidget* parent = nullptr);
    Menu(QString action1, QString action2, QWidget* parent = nullptr);
    QAction* execute_menu();
};

#endif // MENU_H
