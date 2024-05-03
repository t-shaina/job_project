#include "app_page.h"
#include "symbols_inspector.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QScrollArea>
#include <QAbstractItemView>
#include <QStringList>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringListModel>
#include <QRegularExpression>
#include <QColor>

static int required_fields_flag = 0;

App_page::App_page(QWidget *parent)
    :QWidget(parent),
    delete_rows_list(new QList<int>),
    update_rows_list(new QList<int>){
    app_page_painter = new App_page_painter(parent);

    connect(app_page_painter->back_button, SIGNAL(clicked()), this, SLOT(on_back_button_clicked()));
    connect(app_page_painter->delete_button, SIGNAL(clicked()), this, SLOT(on_delete_button_clicked()));
    connect(app_page_painter->show_all_button, SIGNAL(clicked()), this, SLOT(on_show_all_button_clicked()));
    connect(app_page_painter->search_button, SIGNAL(clicked()), this, SLOT(on_search_button_clicked()));
    connect(app_page_painter->accept_button, SIGNAL(clicked()), this, SLOT(on_accept_button_clicked()));

    connect(this, SIGNAL( director_scroll_was_changed()), this->app_page_painter, SLOT(on_name_director_genre_data_edit_changed()));
    connect(this, SIGNAL(genre_scroll_was_changed()), this->app_page_painter, SLOT(on_name_director_genre_data_edit_changed()));

    //switches

    connect(app_page_painter->search_edit, SIGNAL(returnPressed()), this, SLOT(on_search_button_clicked()));
    connect(app_page_painter->delete_button, SIGNAL(enter_pressed()), this, SLOT(on_delete_button_clicked()));
    connect(app_page_painter->show_all_button, SIGNAL(enter_pressed()), this, SLOT(on_show_all_button_clicked()));
    connect(app_page_painter->search_button, SIGNAL(enter_pressed()), this, SLOT(on_search_button_clicked()));
    connect(app_page_painter->accept_button, SIGNAL(enter_pressed()), this, SLOT(on_accept_button_clicked()));
    connect(app_page_painter->back_button, SIGNAL(enter_pressed()), this, SLOT(on_back_button_clicked()));
    connect(app_page_painter->table, SIGNAL(delete_action()),this, SLOT(on_delete_button_clicked()));
}

App_page::~App_page(){
    delete delete_rows_list;
    delete update_rows_list;
    delete app_page_painter;   
}

void App_page::on_back_button_clicked(){
    emit step_out();    
}

void App_page::add_to_delete_list(){
    QStandardItemModel* model = static_cast<QStandardItemModel*>(app_page_painter->table->model());
    QItemSelectionModel* select_model = app_page_painter->table->selectionModel();
    QModelIndex current_index = select_model->currentIndex();
    int row = current_index.row();
    for (int i = 0; i < model->columnCount(); i++){
        QStandardItem* item = model->item(row, i);
        item->setEnabled(false);
    }
    delete_rows_list->push_back(row);
}

void App_page::remove_from_delete_list(int row){
    QStandardItemModel* model = static_cast<QStandardItemModel*>(app_page_painter->table->model());
    for (int i = 0; i < model->columnCount(); i++){
        QStandardItem* item = model->item(row, i);
        item->setEnabled(true);
    }
    delete_rows_list->removeOne(row);
}

void App_page::add_to_update_list(){
    QStandardItemModel* model = static_cast<QStandardItemModel*>(app_page_painter->table->model());
    int row = app_page_painter->update_model_index.row();
    for (int i = 0; i < model->columnCount(); i++){
        QStandardItem* item = model->item(row, i);
        item->setSelectable(false);
    }
    update_rows_list->push_back(row);
}

void App_page::remove_from_update_list(int row){
    QStandardItemModel* model = static_cast<QStandardItemModel*>(app_page_painter->table->model());
    for(int i = 0; i < model->columnCount(); i++){
        QStandardItem* item = model->item(row, i);
        item->setSelectable(true);
    }
    update_rows_list->removeOne(row);
}
int App_page::find_row_in_list(QList<int>* list, const QJsonObject& object_row){
    int row = -1;
    QStandardItemModel* model = static_cast<QStandardItemModel*>(app_page_painter->table->model());
    QVariantMap object_map = object_row.toVariantMap();
    QList<int>::iterator end = list->end();
    QString title = object_map.take("Title").toString();
    QString directors = jsonarray_to_str(object_map.take("Directors").toJsonArray());
    QString year = object_map.take("Year").toString();
    int current_row = 0;
    for(QList<int>::iterator i = list->begin(); i < end; i++, current_row++){
        if (model->item(*i, 0)->text() == title     &&
            model->item(*i, 1)->text() == directors &&
            model->item(*i, 3)->text() == year){
            return current_row;
            break;
        }
    }
    return row;
}

void App_page::on_delete_button_clicked(){
    QStringList delete_list;
    QStandardItemModel* model = static_cast<QStandardItemModel*>(app_page_painter->table->model());
    QItemSelectionModel* select_model = app_page_painter->table->selectionModel();
    QModelIndex index = select_model->currentIndex();
    int row = index.row();
    for (int i = 0; i < model->columnCount(); i++){
        QModelIndex column_index = model->index(row, i);
        delete_list.push_back(column_index.data().toString());
    }
    this->add_to_delete_list();
    delete_list.push_front(this->email);
    emit delete_request(&delete_list);
}

void App_page::on_show_all_button_clicked(){
    QStringList data = QStringList();
    data << this->email;
    emit select_all_request(&data);
}

void App_page::on_search_button_clicked(){
    QStringList data = QStringList();
    Symbols_inspector symbols_inspector;
    data << this->email;
    data << symbols_inspector.removing_last_spaces(this->app_page_painter->search_edit->text());
    emit search_request(&data);
}

void App_page::on_accept_button_clicked(){
    if (has_invalid_symbols()){
        qDebug() << "in invalid symbol founded branch";
    }
    else {
        QString genres    = app_page_painter->widgets_list_to_string(app_page_painter->genre_billet_widgets);
        QString directors = app_page_painter->widgets_list_to_string(app_page_painter->director_billet_widgets);
        QStringList insert_list = QStringList()<<this->email
                                               <<app_page_painter->name_edit->toPlainText()
                                               <<directors
                                               <<genres
                                               <<app_page_painter->date_edit->text()
                                               <<app_page_painter->rating_spin_box->text()
                                               <<app_page_painter->status_combo_box->currentText();
        if (app_page_painter->redact_transfer_state){
            this->add_to_update_list();
            insert_list << *app_page_painter->row_to_update;
            emit  update_request(&insert_list);
        }
        else {
            emit insert_request(&insert_list);
        }
        this->app_page_painter->set_all_combo_box_enabled(true);
        app_page_painter->name_invalid_symbol_label->setVisible(false);
        app_page_painter->name_edit->clear();
        app_page_painter->director_invalid_symbol_label->setVisible(false);
        app_page_painter->director_billet_widgets->clear();
        app_page_painter->genre_billet_widgets->clear();
        app_page_painter->date_invalid_symbol_label->setVisible(false);
        app_page_painter->redact_transfer_state=false;
        app_page_painter->accept_button->setText("Добавить");
        emit genre_scroll_was_changed();
        emit director_scroll_was_changed();
    }
}

bool App_page::has_invalid_symbols(){
    Symbols_inspector symbols_inspector = Symbols_inspector();
    bool state = false;
    QRegularExpression name_r_expr("(_+)|([^\\wа-яё\\!\\:\\.\\,\\-\\s]+)|([\\!\\:\\.\\,\\-]{2,})", QRegularExpression::CaseInsensitiveOption); //подумать над переносом строки и табуляцией
    QRegularExpression date_r_expr("([^\\d]+)", QRegularExpression::CaseInsensitiveOption);
    if (symbols_inspector.finding_invalid_symbols(app_page_painter->name_edit, name_r_expr)){
        state = true;
        app_page_painter->name_invalid_symbol_label->setVisible(true);
    }
    if (symbols_inspector.finding_invalid_symbols(app_page_painter->date_edit, date_r_expr) || app_page_painter->date_edit->text().size() != 4){
        state = true;
        app_page_painter->date_invalid_symbol_label->setVisible(true);
    }
    return state;
}

QStandardItemModel* App_page::get_table_model(){
    QStandardItemModel* model = static_cast<QStandardItemModel*>(app_page_painter->table->model());
    return model;
}

void App_page::filling_in_table(QJsonArray* array_data, int row_position){
    QStandardItemModel* model = static_cast<QStandardItemModel*>(app_page_painter->table->model());
    int counter = row_position;
    QJsonArray::iterator array_iter = array_data->begin();
    for (; array_iter != array_data->end(); array_iter++){
        QJsonObject row_object = array_iter->toObject();
        QVariantMap row_data = row_object.toVariantMap();
        for (int column = 0; column < model->columnCount(); column++){
            QString string_of_item = QString();
            QJsonArray array_object;
            Symbols_inspector symbols_inspector;
            switch (column) {
            case 0:
                string_of_item = symbols_inspector.removing_last_spaces(row_data.take("Title").toString());
                break;
            case 1:
                array_object = row_data.take("Directors").toJsonArray();
                string_of_item = jsonarray_to_str(array_object);
                break;
            case 2:
                array_object = row_data.take("Genres").toJsonArray();
                string_of_item = jsonarray_to_str(array_object);
                break;
            case 3:
                string_of_item = row_data.take("Year").toString();
                break;
            case 4:
                string_of_item = row_data.take("Rating").toString();
                break;
            case 5:
                string_of_item = symbols_inspector.removing_last_spaces(row_data.take("Status").toString());
                break;
            default:
                break;
            }
            qDebug() << "in filling in table string is" << string_of_item;
            QStandardItem* item = new QStandardItem(string_of_item);
            if (column == 3 || column ==4)item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            model->setItem(row_position, column, item);
        }
        counter++;
        row_position++;
    }
    filling_in_director_combo_box(array_data);
}

QString App_page::jsonarray_to_str(const QJsonArray& array_object){
    QString result_string;
    int size = array_object.size();
    Symbols_inspector symbols_inspector;
    for (int i = 0; i < size - 1; i++){
        QString element = symbols_inspector.removing_last_spaces(array_object.at(i).toString());
        element +=  ", ";
        result_string += element;
    }
    result_string += symbols_inspector.removing_last_spaces(array_object.at(size - 1).toString());
    return result_string;
}

void App_page::remove_row_in_table(QJsonArray* data){
    qDebug() << "in remove row in table";
    QStandardItemModel* model = static_cast<QStandardItemModel*>(app_page_painter->table->model());
    int row = find_row_in_list(delete_rows_list, data->at(0).toObject());
    if (row > 0){
        model->removeRow(row);
        this->remove_from_delete_list(row);
    }
    else qDebug() << "incorrect number of row in remove row in table";
}

void App_page::filling_page_with_data(QJsonArray* data){
    QStandardItemModel* model = static_cast<QStandardItemModel*>(app_page_painter->table->model());
    model->clear();
    this->app_page_painter->main_table_settings();
    filling_in_table(data, 0);
}

void App_page::filling_in_director_combo_box(QJsonArray* data){
    QJsonArray::iterator array_iter = data->begin();
    for (; array_iter != data->end(); array_iter++){
        QJsonObject row_object = array_iter->toObject();
        QVariantMap row_data = row_object.toVariantMap();
        QJsonArray array_directors_object;
        array_directors_object = row_data.take("Directors").toJsonArray();
        app_page_painter->filling_in_director_combo_box(array_directors_object);
    }
}

void App_page::insert_row_in_table(QJsonArray* data){
    QStandardItemModel* model = static_cast<QStandardItemModel*>(app_page_painter->table->model());
    int current_number_of_rows = model->rowCount();
    filling_in_table(data, current_number_of_rows);
}

void App_page::update_row_in_table(QJsonObject* data_new_object, QJsonObject* data_old_object){
    QStandardItemModel* model = static_cast<QStandardItemModel*>(app_page_painter->table->model());
    int row = -1;
    QVariantMap row_old_data = data_old_object->toVariantMap();
    QList<int>::iterator end = update_rows_list->end();
    QString deleted_title     = row_old_data.take("Title").toString();
    QString deleted_directors = jsonarray_to_str(row_old_data.take("Directors").toJsonArray());
    QString deleted_year      = row_old_data.take("Year").toString();
    for (QList<int>::iterator i = update_rows_list->begin(); i < end; i++){ //считается, что пул режиссеров мог снять один title за один год
        if (model->item(*i, 0)->text() == deleted_title &&
            model->item(*i, 1)->text() == deleted_directors &&
            model->item(*i, 3)->text() == deleted_year){
            row =* i;
            break;
        }
    }
    this->remove_from_update_list(row);
    QVariantMap row_new_data = data_new_object->toVariantMap();
    for (int column = 0; column < model->columnCount(); column++){
        QString string_of_item = QString();
        QJsonArray array_object;
        Symbols_inspector symbols_inspector;
        switch (column){
        case 0:
            string_of_item = symbols_inspector.removing_last_spaces(row_new_data.take("Title").toString());
            break;
        case 1:
            array_object = row_new_data.take("Directors").toJsonArray();
            string_of_item = jsonarray_to_str(array_object);
            break;
        case 2:
            array_object = row_new_data.take("Genres").toJsonArray();
            string_of_item = jsonarray_to_str(array_object);
            break;
        case 3:
            string_of_item = row_new_data.take("Year").toString();
            break;
        case 4:
            string_of_item = row_new_data.take("Rating").toString();
            break;
        case 5:
            string_of_item = row_new_data.take("Status").toString();
            break;
        default:
            break;
            }
        QStandardItem item = QStandardItem(string_of_item);
        if (column == 3 || column == 4)item.setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        model->setItem(row, column, &item);
    }
    app_page_painter->filling_in_director_combo_box(row_new_data.take("Directors").toJsonArray());
}
