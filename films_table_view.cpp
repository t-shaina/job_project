#include "films_table_view.h"
#include "qevent.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QHeaderView>
#include <QScrollBar>

const QStringList headers = QStringList() << "Название"
                                          << "Режиссер"
                                          << "Жанр"
                                          << "Год"
                                          << "Рейтинг"
                                          << "Статус";
const QStringList actions = QStringList() << "Удалить строку"
                                          << "Редактировать строку";
const int column_count = 6;

FilmsTableView::FilmsTableView(QWidget* parent)
    :QTableView(parent){
    menu = nullptr;
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(showContextMenu(QPoint)));
}

FilmsTableView::~FilmsTableView(){
    delete menu;
}

void FilmsTableView::keyPressEvent(QKeyEvent *event){
    QTableView::keyPressEvent(event);
    switch (event->key()) {
    case Qt::Key_Enter:
        emit enter_pressed();
        break;
    case Qt::Key_Down:
        emit down_pressed();
        break;
    default:
        break;
    }
}

void FilmsTableView::mousePressEvent(QMouseEvent *event){
    QTableView::mousePressEvent(event);
    switch (event->button()) {
    case Qt::RightButton:
        emit right_mouse_key_pressed();
        break;
    default:
        break;
    }
}

void FilmsTableView::table_settings(int table_group_width){
    QStandardItemModel* model = new QStandardItemModel(0, 6, this);
    this->setModel(model);
    this->setShowGrid(true);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    model->setColumnCount(column_count);
    model->setHorizontalHeaderLabels(headers);
    this->setColumnWidth(0, table_group_width * 0.20);
    this->setColumnWidth(1, table_group_width * 0.20);
    this->setColumnWidth(2, table_group_width * 0.20);
    this->setColumnWidth(3, table_group_width * 0.07);
    this->setColumnWidth(4, table_group_width * 0.10);
    int status_column_width = this->width() - verticalHeader()->width()
                                            - columnWidth(0)
                                            - columnWidth(1)
                                            - columnWidth(2)
                                            - columnWidth(3)
                                            - columnWidth(4)
                                            - verticalScrollBar()->width();
    this->setColumnWidth(5, status_column_width);
    this->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    this->columnViewportPosition(0);
}

void FilmsTableView::showContextMenu(QPoint point){
    this->menu = new Menu("Удалить строку", "Редактировать строку", this);
    QAction* current_action = menu->execute_menu();
    menu = nullptr;
    if (current_action->text() == "Удалить строку")
        emit delete_action();
    if (current_action->text() == "Редактировать строку")
        emit update_action();
}
