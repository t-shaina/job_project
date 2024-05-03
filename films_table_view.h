#ifndef FILMSTABLEVIEW_H
#define FILMSTABLEVIEW_H

#include "menu.h"

#include <QObject>
#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>

class FilmsTableView : public QTableView{
    Q_OBJECT

public:

    Menu* menu;
    FilmsTableView(QWidget* parent = nullptr);
    ~FilmsTableView();
    void table_settings(int group_width);

private:

    FilmsTableView(FilmsTableView const& other) = delete;
    FilmsTableView& operator=(FilmsTableView const& other) = delete;
    FilmsTableView(FilmsTableView && other) = delete;
    FilmsTableView& operator=(FilmsTableView && other) = delete;

public slots:

    void keyPressEvent(QKeyEvent* e);
    void mousePressEvent(QMouseEvent* e);

private slots:

    void showContextMenu(QPoint);

signals:

    void enter_pressed();
    void down_pressed();
    void right_mouse_key_pressed();
    void delete_action();
    void update_action();
};

#endif // FILMSTABLEVIEW_H
