#include "films_table_view.h"
#include "qevent.h"
#include<QKeyEvent>
#include<QMouseEvent>
#include<QStandardItemModel>
#include<QHeaderView>
#include<QScrollBar>
const QStringList headers= QStringList()<<"Название"<<"Режиссер"<<"Жанр"<<"Год"<<"Рейтинг"<<"Статус";
const QStringList actions= QStringList()<<"Удалить строку"<<"Редактировать строку";

FilmsTableView::FilmsTableView(QWidget* parent):QTableView(parent)
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(showContextMenu(QPoint)));
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
    //qDebug()<<"in main table settings";
    //table->setHorizontalHeader();
    QStandardItemModel* model=new QStandardItemModel(0, 6, this);
    this->setModel(model);
    this->setShowGrid(true);
    this->setSelectionMode(QAbstractItemView::SingleSelection);//мб несколько shift
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    model->setColumnCount(6);
    model->setHorizontalHeaderLabels(headers);

    this->setColumnWidth(0, table_group_width*0.20);
    this->setColumnWidth(1, table_group_width*0.20);
    this->setColumnWidth(2, table_group_width*0.20);
    this->setColumnWidth(3, table_group_width*0.07);
    this->setColumnWidth(4, table_group_width*0.10);
    int status_column_width=this->width()-verticalHeader()->width()-columnWidth(0)-columnWidth(1)-columnWidth(2)-columnWidth(3)-columnWidth(4)-verticalScrollBar()->width();
    this->setColumnWidth(5, status_column_width);
    this->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    this->columnViewportPosition(0);
    //this->verticalHeader()->setSectionHidden(0, 0);
}
void FilmsTableView::showContextMenu(QPoint point){
    this->menu=new Menu("Удалить строку", "Редактировать строку", this);
    //connect(menu, SIGNAL(action(QAction*)), this, SLOT(on_action()));
    QAction* current_action=menu->execute_menu();
    menu=nullptr;
    if(current_action->text()=="Удалить строку")
        emit delete_action();
    if(current_action->text()=="Редактировать строку")
        emit update_action();
}
