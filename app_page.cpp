#include "app_page.h"

#include<QGridLayout>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QGroupBox>
#include <QLabel>
#include<QScrollArea>
#include<QDate>
#include<QHeaderView>
#include<QAbstractItemView>
#include<QStringList>
#include<QString>
#include<QJsonObject>
#include<QJsonArray>
#include<QStringListModel>
#include<QRegularExpression>
#include<QColor>
#include<QCommonStyle>
const int width_window=1280;
const int height_window=800;
const int l_margin=10;
const int t_margin=30;
const int r_margin=10;
const int b_margin=30;
const int inside_margin=10;
const int inside_spacing=10;
const int v_spacing=30;
const int h_spacing=30;
const int edit_group_v_spacing=20;
const int navigation_group_hight=50;
const int table_magrin=5;
const int main_buttons_width=100;
const int main_buttons_height=30;
const QStringList genre_list=QStringList()<<"Комедия"<<"Мелодрама"<<"Мультфильм"<<"Ужасы"<<"Фантастика"<<"Триллер"
                                              <<"Боевик"<<"Детектив"<<"Фентези"<<"Исторический"<<"Драма"<<"Документальный"
                                              <<"Криминал"<<"Биография"<<"Вестерн"<<"Мюзиклы"<<"Короткометражка";

const QStringList headers= QStringList()<<"Название"<<"Режиссер"<<"Жанр"<<"Год"<<"Рейтинг"<<"Статус";
const QStringList sort_list=QStringList()<<"Год"<<"Рейтинг"<<"Статус";
const QStringList status_list=QStringList()<<"Просмотрено"<<"Собираюсь смотреть"<<"Не рекомендую";
static int required_fields_flag =0;

App_page::App_page(QWidget *parent)
    :QWidget(parent),
    //page_group(new QGroupBox(this)),
    genre_billet_widgets(new QList<QSharedPointer<Billet_widget>>),
    director_billet_widgets(new QList<QSharedPointer<Billet_widget>>),
    directors_list(new QStringList()),
    row_to_update(new QStringList()),
    delete_rows_list(new QList<int>),
    update_rows_list(new QList<int>),
    redact_transfer_state(false),
    layout_page(new QGridLayout(this)),
    table_group(new QGroupBox(this)),
    /*scroll_table_group(new QGroupBox(table_group)),*/
    delete_sort_group(new QGroupBox(table_group)),
    sort_group(new QGroupBox(delete_sort_group)),
    search_group(new QGroupBox(this)),
    settings_group(new QGroupBox(this)),
    edit_group(new QGroupBox(this)),
    navigation_group(new QGroupBox(this)),
    /*table_scroll(new QScrollArea(table_group)),*/
    /*edit_scroll(new QScrollArea()),*/
    name_group(new QGroupBox(edit_group)),
    director_group(new QGroupBox(edit_group)),
    genre_group(new QGroupBox(edit_group)),
    date_group(new QGroupBox(edit_group)),
    clear_group(new QGroupBox(this)),
    table(new QTableView(this)),
    delete_button(new QPushButton("Удалить", this)),
    redact_button(new QPushButton("Редактировать", this)),
    show_all_button(new QPushButton("Показать все", this)),
    sort_label(new QLabel("Сортировать по", this)),
    sort_combo_box(new QComboBox(this)),
    sort_button(new QPushButton("Сортировать",this)),
    search_edit(new QLineEdit(this)),
    search_button(new QPushButton("Поиск", this)),
    name_label (new QLabel("Название", this)),
    name_invalid_symbol_label(new QLabel("Введен недопустимый символ",this)),
    name_edit (new QTextEdit(this)),
    director_label (new QLabel("Режиссер", this)),
    director_invalid_symbol_label(new QLabel("Введен недопустимый символ",this)),
    director_combo_box(new QComboBox(this)),
    director_add_button(new QPushButton(this)),
    director_scroll(new QScrollArea(this)),
    director_scroll_group(new QGroupBox(director_scroll)),
    genre_label (new QLabel("Жанр", this)),
    genre_scroll(new QScrollArea(this)),
    genre_scroll_group(new QGroupBox(genre_scroll)),
    genre_combo_box(new QComboBox(this)),
    date_edit(new QLineEdit(this)),
    date_invalid_symbol_label(new QLabel("Введен недопустимый символ",this)),
    date_label (new QLabel("Год создания", this)),
    date_slider(new QSlider(this)),
    rating_label (new QLabel("Рейтинг", this)),
    rating_spin_box(new QSpinBox(this)),
    status_label (new QLabel("Статус", this)),
    status_combo_box(new QComboBox(this)),
    accept_button (new QPushButton("Добавить", this)),
    clear_button(new QPushButton("Очистить", this)),
    back_button (new QPushButton("Выйти", this))
{

    QVBoxLayout* table_group_layout=new QVBoxLayout;
    //QVBoxLayout* scroll_table_group_layout=new QVBoxLayout;
    QHBoxLayout* delete_sort_group_layout=new QHBoxLayout;
    QHBoxLayout* sort_group_layout=new QHBoxLayout;
    QHBoxLayout* search_group_layout=new QHBoxLayout;
    QHBoxLayout* navigation_group_layout=new QHBoxLayout;
    QVBoxLayout* settings_group_layout=new QVBoxLayout;
    QGridLayout* edit_group_layout=new QGridLayout;
    QVBoxLayout* name_group_layout=new QVBoxLayout;
    QVBoxLayout* director_group_layout=new QVBoxLayout;
    QVBoxLayout* director_scroll_layout=new QVBoxLayout;
    QVBoxLayout* genre_group_layout=new QVBoxLayout;
    QVBoxLayout* genre_scroll_layout=new QVBoxLayout;//this
    QVBoxLayout* date_group_layout=new QVBoxLayout;
    QHBoxLayout* clear_group_layout=new QHBoxLayout;

    table_group_layout->addWidget(table);
    //scroll_table_group_layout->addWidget(table_scroll);
    delete_sort_group_layout->addWidget(delete_button, Qt::AlignLeft);
    delete_sort_group_layout->addWidget(redact_button, Qt::AlignLeft);
    delete_sort_group_layout->addWidget(show_all_button, Qt::AlignLeft);
    delete_sort_group_layout->addWidget(sort_group, Qt::AlignRight);
    table_group_layout->addWidget(delete_sort_group);
    sort_group_layout->addWidget(sort_label);
    sort_group_layout->addWidget(sort_combo_box);
    sort_group_layout->addWidget(sort_button);
    search_group_layout->addWidget(search_edit, Qt::AlignRight);
    search_group_layout->addWidget(search_button, Qt::AlignCenter);
    settings_group_layout->addWidget(edit_group);
    settings_group_layout->addWidget(clear_group);
    edit_group_layout->addWidget(name_label, 0,0, Qt::AlignLeft|Qt::AlignTop);
    edit_group_layout->addWidget(name_group, 0,1, Qt::AlignCenter|Qt::AlignTop);
    edit_group_layout->addWidget(director_label, 1,0, Qt::AlignLeft|Qt::AlignTop);
    edit_group_layout->addWidget(director_group, 1,1, Qt::AlignCenter|Qt::AlignTop);
    edit_group_layout->addWidget(genre_label, 2,0, Qt::AlignLeft|Qt::AlignTop);
    edit_group_layout->addWidget(genre_group, 2,1, Qt::AlignCenter|Qt::AlignTop);
    edit_group_layout->addWidget(date_label, 3,0, Qt::AlignLeft|Qt::AlignTop);
    edit_group_layout->addWidget(date_group, 3,1, Qt::AlignCenter|Qt::AlignTop);
    edit_group_layout->addWidget(rating_label, 4,0, Qt::AlignLeft|Qt::AlignTop);
    edit_group_layout->addWidget(rating_spin_box, 4,1, Qt::AlignCenter|Qt::AlignTop);
    edit_group_layout->addWidget(status_label, 5,0, Qt::AlignLeft|Qt::AlignTop);
    edit_group_layout->addWidget(status_combo_box, 5,1, Qt::AlignCenter|Qt::AlignTop);

    name_group_layout->addWidget(name_edit, Qt::AlignCenter);
    name_group_layout->addWidget(name_invalid_symbol_label, Qt::AlignCenter);


    director_group_layout->addWidget(director_combo_box, Qt::AlignCenter);
    director_group_layout->addWidget(director_add_button, Qt::AlignCenter);
    director_group_layout->addWidget(director_scroll, Qt::AlignCenter);
    director_group_layout->addWidget(director_invalid_symbol_label, Qt::AlignCenter);
    genre_group_layout->addWidget(genre_combo_box, Qt::AlignCenter);
    genre_group_layout->addWidget(genre_scroll, Qt::AlignCenter);
    date_group_layout->addWidget(date_slider, Qt::AlignCenter);
    date_group_layout->addWidget(date_edit, Qt::AlignCenter);
    date_group_layout->addWidget(date_invalid_symbol_label, Qt::AlignCenter);
    clear_group_layout->addWidget(accept_button, Qt::AlignCenter);
    clear_group_layout->addWidget(clear_button, Qt::AlignCenter);
    navigation_group_layout->addWidget(back_button, Qt::AlignRight);

    delete_sort_group->setLayout(delete_sort_group_layout);
    sort_group->setLayout(sort_group_layout);
    search_group->setLayout(search_group_layout);
    table_group->setLayout(table_group_layout);
    settings_group->setLayout(settings_group_layout);
    edit_group->setLayout(edit_group_layout);
    name_group->setLayout(name_group_layout);
    director_group->setLayout(director_group_layout);
    director_scroll->setLayout(director_scroll_layout);
    genre_group->setLayout(genre_group_layout);
    genre_scroll->setLayout(genre_scroll_layout);
    date_group->setLayout(date_group_layout);
    clear_group->setLayout(clear_group_layout);
    navigation_group->setLayout(navigation_group_layout);

    layout_page->addWidget(table_group, 0,0, Qt::AlignLeft|Qt::AlignTop);
    layout_page->addWidget(search_group, 1,0, Qt::AlignLeft|Qt::AlignBottom);
    layout_page->addWidget(settings_group, 0,1, Qt::AlignRight|Qt::AlignTop);
    layout_page->addWidget(navigation_group, 1,1, Qt::AlignRight|Qt::AlignBottom);

    setLayout(layout_page);
    this->show();
    //this->setFixedSize(500,350);
    this->resize(width_window,height_window);
    this->setMaximumHeight(height_window);
    this->setMaximumWidth(width_window);
    //edit_group_layout->setRowMinimumHeight(6, 30);
    table_group_layout->setContentsMargins(inside_margin, inside_margin, inside_margin, inside_margin);
    table_group_layout->insertSpacing(1, inside_spacing);
    settings_group_layout->setContentsMargins(inside_margin, inside_margin, inside_margin, inside_margin);
    settings_group_layout->insertSpacing(1, inside_spacing);
    delete_sort_group_layout->setContentsMargins(0,0,0,0);
    name_group_layout->setContentsMargins(0,0,0,0);
    director_group_layout->setContentsMargins(0,0,0,0);
    genre_group_layout->setContentsMargins(0,0,0,0);
    date_group_layout->setContentsMargins(0,0,0,0);
    sort_group->setStyleSheet("QGroupBox{border: 0px;}");
    navigation_group->setStyleSheet("QGroupBox{border: 0px;}");
    search_group->setStyleSheet("QGroupBox{border: 0px;}");
    date_group->setStyleSheet("QGroupBox{border: 0px;}");

    edit_group_layout->setVerticalSpacing(edit_group_v_spacing);
    edit_group_layout->setColumnMinimumWidth(1, (width_window-l_margin-r_margin-v_spacing)*0.15);

    main_scroll_group_settings(director_scroll, director_scroll_group, director_scroll_layout);
    main_scroll_group_settings(genre_scroll, genre_scroll_group, genre_scroll_layout);

    base_settings();

    //connect(sort_combo_box, SIGNAL(activated(int)), this, SLOT(set_search_edit(int)));
    connect(genre_combo_box, SIGNAL(activated(int)), this, SLOT(set_genre_scroll(int)));
    connect(director_combo_box, SIGNAL(activated(int)), this, SLOT(set_director_scroll(int)));
    connect(date_slider, SIGNAL(valueChanged(int)), this, SLOT(set_date_edit(int)));

    connect(back_button, SIGNAL(clicked()), this, SLOT(on_back_button_clicked()));
    connect(delete_button, SIGNAL(clicked()), this, SLOT(on_delete_button_clicked()));
    connect(redact_button, SIGNAL(clicked()), this, SLOT(on_redact_button_clicked()));
    connect(show_all_button, SIGNAL(clicked()), this, SLOT(on_show_all_button_clicked()));
    connect(sort_button, SIGNAL(clicked()), this, SLOT(on_sort_button_clicked()));
    connect(search_button, SIGNAL(clicked()), this, SLOT(on_search_button_clicked()));
    connect(director_add_button, SIGNAL(clicked()), this, SLOT(on_director_add_button_clicked()));
    connect(accept_button, SIGNAL(clicked()), this, SLOT(on_accept_button_clicked()));
    connect(clear_button, SIGNAL(clicked()), this, SLOT(on_clear_button_clicked()));

    connect(table, SIGNAL(clicked(QModelIndex)), this, SLOT(on_table_row_selected(QModelIndex)));
    connect(search_edit, SIGNAL(textEdited(QString)), this, SLOT(on_search_edit_edited()));
    connect(name_edit, SIGNAL(textChanged()), this, SLOT(on_name_director_genre_data_edit_changed()));
    connect(director_scroll, SIGNAL( director_scroll_was_changed()), this, SLOT(on_name_director_genre_data_edit_changed()));
    QObject::connect(this, SIGNAL(genre_scroll_was_changed()), this, SLOT(on_name_director_genre_data_edit_changed()));
    connect(director_combo_box, SIGNAL(editTextChanged(QString)), this, SLOT(on_director_combo_box_text_changed()));
    connect(date_edit, SIGNAL(textChanged(QString)), this, SLOT(on_name_director_genre_data_edit_changed()));
    connect(date_edit, SIGNAL(textEdited(QString)), this, SLOT(set_date_slider_position()));

}

void App_page::on_back_button_clicked(){
    //email.clear();
    emit step_out();    
}
void App_page::on_sort_button_clicked(){
    int sort_id=sort_combo_box->currentIndex();
    QStandardItemModel* model=static_cast<QStandardItemModel*>(table->model());
    model->sort(sort_id+3, Qt::AscendingOrder);

}
void App_page::set_search_edit(int search_id){
    //
}
void App_page::set_date_edit(int data_value){
    QString text=QString::number(data_value);
    date_edit->setText(text);
}
void App_page::set_director_scroll(int director_id){
    QString text=directors_list->at(director_id);
    //QStandardItemModel* director_model=static_cast<QStandardItemModel*>(director_combo_box->model());
    //director_model->item(director_id)->setEnabled(false);
    set_scroll(director_combo_box, director_scroll_group, text, director_billet_widgets);
    emit director_scroll_was_changed();

    /*QString text=director_combo_box->itemText(director_id);
    if(director_edit->toPlainText().isEmpty()){
        director_edit->setText(director_edit->toPlainText()+text);
    }
    else director_edit->setText(director_edit->toPlainText()+" "+text);*/
}
void App_page::set_genre_scroll(int genre_id){
    QString text=genre_list.at(genre_id);
    //QStandardItemModel* genre_model=static_cast<QStandardItemModel*>(genre_combo_box->model());
    //genre_model->item(genre_id)->setEnabled(false);
    set_scroll(director_combo_box, genre_scroll_group, text, genre_billet_widgets);
    emit genre_scroll_was_changed();
}
void App_page::set_scroll(QComboBox* combo_box, QGroupBox* group, const QString& text, QList<QSharedPointer<Billet_widget>>* list){
    QString element;
    int size=text.size();
    for(int i=0; i<size;i++){
        if(i==size-1||text.at(i)==','/*||text.at(i)==' '*/){
            if(i==size-1)
                element+=text.at(i);
            if(text.at(i)==',')
                i++;
            this->set_combo_box_enabled(combo_box, element, false);
            Billet_widget* widget=new Billet_widget(group, element);
            QSharedPointer<Billet_widget> widget_ptr(widget, &QObject::deleteLater);
            group->layout()->addWidget(widget_ptr.get());
            list->push_back(widget_ptr);
            QObject::connect(widget, SIGNAL(widget_was_deleted(QString)), this, SLOT(on_widget_was_deleted(QString)));
            //emit genre_scroll_was_changed();
            element.clear();
        }
        else
            element+=text.at(i);
    }
}
void App_page::set_date_slider_position(){
    int year=date_edit->text().toInt();
    int current_year=QDate().currentDate().year();
    if(year<=current_year)
        date_slider->setSliderPosition(year);
    else date_slider->setSliderPosition(current_year);
}
void App_page::on_widget_was_deleted(QString text){
    Billet_widget* widget=static_cast<Billet_widget*>(sender());
    QGroupBox* parent=qobject_cast<QGroupBox*>(widget->parent());
    QSharedPointer<Billet_widget> widget_ptr=static_cast<QSharedPointer<Billet_widget>>(widget);
    if(parent==genre_scroll_group){
        genre_billet_widgets->removeOne(widget_ptr);
        set_combo_box_enabled(genre_combo_box, text, true);
        emit genre_scroll_was_changed();
    }
    else {
        director_billet_widgets->removeOne(widget_ptr);
        set_combo_box_enabled(director_combo_box, text, true);
        emit director_scroll_was_changed();
    }
}
void App_page::set_combo_box_enabled(QComboBox* combo_box, QString text, bool enabled){
    QStandardItemModel* model=static_cast<QStandardItemModel*>(combo_box->model());
    QList<QStandardItem*> items=model->findItems(text);
    for(QStandardItem* item:items){
        item->setEnabled(enabled);
    }
}
void App_page::set_all_combo_box_enabled(QComboBox* combo_box, QList<QSharedPointer<Billet_widget>>* list){
    QSharedPointer<Billet_widget> widget_ptr;
    foreach(widget_ptr, *list){
        QComboBox* parent=qobject_cast<QComboBox*>(widget_ptr->parent());
        this->set_combo_box_enabled(combo_box, widget_ptr->text(), true);
    }
}
void App_page::add_to_delete_list(){
    QStandardItemModel* model=static_cast<QStandardItemModel*>(table->model());
    QItemSelectionModel* select_model=table->selectionModel();
    QModelIndex current_index=select_model->currentIndex();
    int row=current_index.row();
    for(int i=0;i<model->columnCount();i++){
        QStandardItem* item=model->item(row, i);
        item->setEnabled(false);
    }
        delete_rows_list->push_back(row);
}
void App_page::remove_from_delete_list(int row){
    QStandardItemModel* model=static_cast<QStandardItemModel*>(table->model());
    for(int i=0;i<model->columnCount();i++){
        QStandardItem* item=model->item(row, i);
        item->setEnabled(true);
    }
    delete_rows_list->removeOne(row);
}
void App_page::add_to_update_list(){
    QStandardItemModel* model=static_cast<QStandardItemModel*>(table->model());
    //QItemSelectionModel* select_model=table->selectionModel();
    //QModelIndex current_index=select_model->currentIndex();
    int row=update_model_index.row();
    for(int i=0;i<model->columnCount();i++){
        QStandardItem* item=model->item(row, i);
        item->setSelectable(false);
        //item->setBackground();
    }
    update_rows_list->push_back(row);
}
void App_page::remove_from_update_list(int row){
    QStandardItemModel* model=static_cast<QStandardItemModel*>(table->model());
    for(int i=0;i<model->columnCount();i++){
        QStandardItem* item=model->item(row, i);
        item->setSelectable(true);
    }
    update_rows_list->removeOne(row);
}
void App_page::on_delete_button_clicked(){
    //selected_row->clear();
    QStringList delete_list;
    QStandardItemModel* model=static_cast<QStandardItemModel*>(table->model());
    QItemSelectionModel* select_model=table->selectionModel();
    QModelIndex index=select_model->currentIndex();
    int row=index.row();
    for(int i=0; i<model->columnCount();i++){
        QModelIndex column_index=model->index(row, i);
        delete_list.push_back(column_index.data().toString());
    }

    this->add_to_delete_list();
    //delete_list=*selected_row;
    delete_list.push_front(this->email);
    emit delete_request(&delete_list);
}
void App_page::on_redact_button_clicked(){
    row_to_update->clear();
    QStandardItemModel* model=static_cast<QStandardItemModel*>(table->model());
    QItemSelectionModel* select_model=table->selectionModel();
    QModelIndex index=select_model->currentIndex();
    int row=index.row();
    update_model_index=index;
    for(int i=0; i<model->columnCount();i++){
        QModelIndex column_index=model->index(row, i);
        this->row_to_update->push_back(column_index.data().toString());
    }
    //this->add_to_update_list();   
    this->set_all_combo_box_enabled(genre_combo_box, genre_billet_widgets);
    this->set_all_combo_box_enabled(director_combo_box, director_billet_widgets);
    genre_billet_widgets->clear();
    director_billet_widgets->clear();
    QString directors=row_to_update->at(1);
    //directors.push_back(' ');
    set_scroll(director_combo_box, director_scroll_group, directors, director_billet_widgets);
    emit director_scroll_was_changed();
    QString genres=row_to_update->at(2);    
    //genres.push_back(' ');
    set_scroll(genre_combo_box, genre_scroll_group, genres, genre_billet_widgets);
    emit genre_scroll_was_changed();
    //QString genre;
    //QStandardItemModel* genre_model=static_cast<QStandardItemModel*>(genre_combo_box->model());
    redact_transfer_state=true;
    name_invalid_symbol_label->setVisible(false);
    name_edit->setText(row_to_update->at(0));
    director_invalid_symbol_label->setVisible(false);
    //director_edit->setText(row_to_update->at(1));
    date_slider->setSliderPosition(row_to_update->at(3).toInt());
    date_invalid_symbol_label->setVisible(false);
    rating_spin_box->setValue(row_to_update->at(4).toInt());
    status_combo_box->setPlaceholderText(row_to_update->at(5));
    accept_button->setText("Обновить");
}
void App_page::on_show_all_button_clicked(){
    QStringList data=QStringList();
    data<<this->email;
    emit select_all_request(&data);
}
void App_page::on_search_button_clicked(){
    QStringList data=QStringList();
    data<<this->email;
    data<<this->search_edit->text();
    emit search_request(&data);
}
void App_page::on_director_add_button_clicked(){
    qDebug()<<"in director add button clicked";
    QRegularExpression directors_r_expr("([^a-zа-яё\\d\\.\\-\\s]+)", QRegularExpression::CaseInsensitiveOption);
    bool status=finding_invalid_symbols(director_combo_box, directors_r_expr);
    if (status){
        qDebug()<<"in finding invalid symbol branch in add button clicked";
        director_invalid_symbol_label->setVisible(true);
    }
    else {
        qDebug()<<"in doesnt finding invalid symbol branch in add button clicked";
        QString text=removing_extra_symbols(director_combo_box->currentText());
        set_uppercase(text, QRegularExpression("^([a-zа-яё]{1})|(\b[a-zа-яё]{1})", QRegularExpression::DotMatchesEverythingOption));
        //QString text=director_combo_box->currentText();
        if(!directors_list->contains(text)){
            qDebug()<<"in doesnt contains text branch in add button clicked text is"<<text;
            *directors_list<<text;
            director_combo_box->addItem(text);
        }
        set_scroll(director_combo_box, director_scroll_group, text, director_billet_widgets);
    }
}
void App_page::on_director_combo_box_text_changed(){
    if(director_combo_box->currentText().isEmpty()){
        director_add_button->setEnabled(false);
    }
    else {
    director_add_button->setEnabled(true);
    }
}
void App_page::on_accept_button_clicked(){
    //removing_extra_symbols(date_edit);
    if(has_invalid_symbols()){
        qDebug()<<"in invalid symbol founded branch";
    }

    else{
        removing_extra_symbols(name_edit);       
        set_uppercase(name_edit, QRegularExpression("^([a-zа-яё]{1})|(?<=[!\\.\\:\'\"«]{1}\\s*)[a-zа-яё]{1}", QRegularExpression::NoPatternOption));//проверка двойных слэш и  "
        QString genres=widgets_list_to_string(genre_billet_widgets);
        QString directors=widgets_list_to_string(director_billet_widgets);
        QStringList insert_list= QStringList()<<this->email
                                             <<name_edit->placeholderText()
                                             <<directors
                                             <<genres
                                             <<date_edit->text()
                                             <<rating_spin_box->text()
                                             <<status_combo_box->currentText();
        if(redact_transfer_state){
            this->add_to_update_list();
            insert_list<<*row_to_update;
            emit  update_request(&insert_list);
        }
        else{
            emit insert_request(&insert_list);
        }
        this->set_all_combo_box_enabled(genre_combo_box, genre_billet_widgets);
        this->set_all_combo_box_enabled(director_combo_box, director_billet_widgets);
        name_invalid_symbol_label->setVisible(false);
        name_edit->clear();
        director_invalid_symbol_label->setVisible(false);
        director_billet_widgets->clear();
        genre_billet_widgets->clear();
        date_invalid_symbol_label->setVisible(false);
        redact_transfer_state=false;
        accept_button->setText("Добавить");
        emit genre_scroll_was_changed();
        emit director_scroll_was_changed();
    }
}
QString App_page::widgets_list_to_string(QList<QSharedPointer<Billet_widget>>* list){
    QString widgets_string;
    for(int i=0;i<list->size();i++){
        widgets_string+=genre_billet_widgets->at(i)->text();
        widgets_string+=" ";
    }
    widgets_string.removeLast();
    return widgets_string;
}
bool App_page::has_invalid_symbols(){
    bool state=false;
    QRegularExpression name_r_expr("(_+)|([^\\wа-яё\\!\\:\\.\\,\\-\\s]+)|([\\!\\:\\.\\,\\-]{2,})", QRegularExpression::CaseInsensitiveOption);//подумать над переносом строки и табуляцией
    //QRegularExpression directors_r_expr("([^a-zа-яё.-\\s]+)", QRegularExpression::CaseInsensitiveOption);
    QRegularExpression date_r_expr("([^\\d]+)", QRegularExpression::CaseInsensitiveOption);
    if(finding_invalid_symbols(name_edit, name_r_expr)){
        state=true;
        name_invalid_symbol_label->setVisible(true);
    }

    if(finding_invalid_symbols(date_edit, date_r_expr)||date_edit->text().size()!=4){
        state=true;
        date_invalid_symbol_label->setVisible(true);
    }
    return state;
}
bool App_page::finding_invalid_symbols(QTextEdit* text_edit, const QRegularExpression& expression){
    bool state=false;
    QString text=text_edit->placeholderText();
    QRegularExpressionMatchIterator match_iter=expression.globalMatch(text, 0, QRegularExpression::NormalMatch, QRegularExpression::NoMatchOption);
    if(match_iter.hasNext()){
        QRegularExpressionMatch match=match_iter.next();
        state=true;
        int pos=match.capturedStart();
        text_edit->textCursor().setPosition(pos, QTextCursor::MoveAnchor);
    }
    return state;
}
bool App_page::finding_invalid_symbols(QLineEdit* line_edit, const QRegularExpression& expression){
    bool state=false;
    QString text=line_edit->placeholderText();
    QRegularExpressionMatchIterator match_iter=expression.globalMatch(text, 0, QRegularExpression::NormalMatch, QRegularExpression::NoMatchOption);
    if(match_iter.hasNext()){
        QRegularExpressionMatch match=match_iter.next();
        state=true;
    }
    return state;
}
bool App_page::finding_invalid_symbols(QComboBox* combo_box, const QRegularExpression& expression){
    bool state=false;
    QString text=combo_box->placeholderText();
    QRegularExpressionMatchIterator match_iter=expression.globalMatch(text, 0, QRegularExpression::NormalMatch, QRegularExpression::NoMatchOption);
    if(match_iter.hasNext()){
        QRegularExpressionMatch match=match_iter.next();
        state=true;
    }
    return state;
}
void App_page::removing_extra_symbols(QTextEdit* text_edit){
    QString text=text_edit->placeholderText();
    text.remove(QRegularExpression ("^([\\s.,]+)|([\\s]{2,})|([\\s.,]+)$", QRegularExpression::CaseInsensitiveOption));
    text.squeeze();
    text_edit->setText(text);
}
void App_page::removing_extra_symbols(QLineEdit* text_edit){
    QString text=text_edit->placeholderText();
    text.remove(QRegularExpression ("^([\\s.,]+)|([\\s]{2,})|([\\s.,]+)$", QRegularExpression::CaseInsensitiveOption));
    text.squeeze();
    text_edit->setText(text);
}
QString App_page::removing_extra_symbols(QString string){
    string.remove(QRegularExpression ("^([\\s.,]+)|([\\s]{2,})|([\\s.,]+)$", QRegularExpression::CaseInsensitiveOption));
    string.squeeze();
    return string;
}
void App_page::set_uppercase(QTextEdit* text_edit, const QRegularExpression& expression){
    QString text=text_edit->placeholderText();
    QRegularExpressionMatchIterator match_iter=expression.globalMatch(text, 0, QRegularExpression::NormalMatch, QRegularExpression::NoMatchOption);
    qsizetype position=-1;
    QString symbol;
    while(match_iter.hasNext()){
        QRegularExpressionMatch match=match_iter.next();
        position=match.capturedStart();
        symbol=match.captured().toUpper();
        text.replace(position, 1, symbol);
    }

    text_edit->setText(text);
}
QString App_page::set_uppercase(QString string, const QRegularExpression& expression){
    QRegularExpressionMatchIterator match_iter=expression.globalMatch(string, 0, QRegularExpression::NormalMatch, QRegularExpression::NoMatchOption);
    qsizetype position=-1;
    QString symbol;
    while(match_iter.hasNext()){
        QRegularExpressionMatch match=match_iter.next();
        position=match.capturedStart();
        symbol=match.captured().toUpper();
        string.replace(position, 1, symbol);
    }
    return string;
}
void App_page::on_clear_button_clicked(){
    this->set_all_combo_box_enabled(genre_combo_box, genre_billet_widgets);
    this->set_all_combo_box_enabled(director_combo_box, director_billet_widgets);
    update_model_index=QModelIndex();//имеется ввиду сброс индекса  установкой недопустимного индекса
    name_invalid_symbol_label->setVisible(false);
    name_edit->clear();
    director_invalid_symbol_label->setVisible(false);
    director_billet_widgets->clear();
    genre_billet_widgets->clear();//нужно ли?
    date_invalid_symbol_label->setVisible(false);
    redact_transfer_state=false;
    accept_button->setText("Добавить");
    emit genre_scroll_was_changed();
    emit director_scroll_was_changed();
}
void App_page::on_table_row_selected(QModelIndex index){
    qDebug()<<"in table row selected";   
    delete_button->setEnabled(true);
    redact_button->setEnabled(true);

    /*selected_row->clear();
    QStandardItemModel* model=static_cast<QStandardItemModel*>(table->model());
    int row=index.row();
    for(int i=0; i<model->columnCount();i++){
        QModelIndex column_index=model->index(row, i);
        this->selected_row->push_back(column_index.data().toString());
    }*/
}
void App_page::on_search_edit_edited(){
    if(search_edit->text().isEmpty())
        search_button->setEnabled(false);
    else search_button->setEnabled(true);
}
void App_page::on_name_director_genre_data_edit_changed(){
    QTextEdit* sender_;
    if(sender_==qobject_cast<QTextEdit*>(sender())){//разобрать
        qDebug()<<"sender is text_edit";
        name_invalid_symbol_label->setVisible(false);
        director_invalid_symbol_label->setVisible(false);
    }
    if(name_edit->toPlainText().isEmpty()||
        director_billet_widgets->size()==0||
        genre_billet_widgets->size()==0||
        date_edit->text().isEmpty()){

        accept_button->setEnabled(false);
        clear_button->setEnabled(false);
    }
    else{
        accept_button->setEnabled(true);
        clear_button->setEnabled(true);
    }

}
void App_page::on_name_edit_changed(){
    QSize text_size=name_edit->fontMetrics().size(Qt::TextWordWrap, name_edit->placeholderText());
    if(text_size.width()>name_edit->width())
        name_edit->setMinimumHeight(text_size.height()*text_size.width()/name_edit->width());
}


void App_page::base_settings(){

    layout_page->setAlignment(layout_page->parentWidget(), Qt::AlignHCenter|Qt::AlignVCenter);
    layout_page->setContentsMargins(l_margin, t_margin, r_margin, b_margin);
    layout_page->setHorizontalSpacing(h_spacing);
    layout_page->setVerticalSpacing(v_spacing);
    layout_page->setColumnMinimumWidth(0, (width_window-l_margin-r_margin-v_spacing)*0.7);
    layout_page->setColumnMinimumWidth(1, (width_window-l_margin-r_margin-v_spacing)*0.3);
    layout_page->setRowMinimumHeight(0, (height_window-t_margin-b_margin-h_spacing)-navigation_group_hight);
    layout_page->setRowMinimumHeight(1, navigation_group_hight);
    layout_page->setColumnStretch(0, 2);
    layout_page->setColumnStretch(1, 2);
    layout_page->setRowStretch(0, 2);
    layout_page->setRowStretch(1, 2);

    table_group->setMinimumSize((width_window-l_margin-r_margin-v_spacing)*0.7, (height_window-t_margin-b_margin-h_spacing)-navigation_group_hight);
    //delete_sort_group->setMinimumSize( (width_window-l_margin-r_margin-v_spacing)*0.7-l_margin-r_margin, navigation_group_hight);
    delete_sort_group->setFixedHeight(navigation_group_hight);
    sort_group->setFixedWidth((width_window-l_margin-r_margin-v_spacing)*0.7*0.5);
    settings_group->setMinimumSize((width_window-l_margin-r_margin-v_spacing)*0.3, (height_window-t_margin-b_margin-h_spacing)-navigation_group_hight);
    search_group->setMinimumSize((width_window-l_margin-r_margin-v_spacing)*0.7, navigation_group_hight);
    navigation_group->setMinimumSize((width_window-l_margin-r_margin-v_spacing)*0.3, navigation_group_hight);
    //edit_group->setMinimumSize((width_window-l_margin-r_margin-v_spacing)*0.3, (hight_window-t_margin-b_margin-h_spacing)-navigation_group_hight-main_buttons_hight-h_spacing);
    name_invalid_symbol_label->setMinimumSize((width_window-l_margin-r_margin-v_spacing)*0.15, 20);
    director_invalid_symbol_label->setMinimumSize((width_window-l_margin-r_margin-v_spacing)*0.15, 20);
    director_group->setMinimumWidth((width_window-l_margin-r_margin-v_spacing)*0.15);
    genre_group->setMinimumWidth((width_window-l_margin-r_margin-v_spacing)*0.15);
    date_group->setMinimumWidth((width_window-l_margin-r_margin-v_spacing)*0.15);
    //clear_group->setMinimumSize((width_window-l_margin-r_margin-v_spacing)*0.15, navigation_group_hight);
    clear_group->setMinimumHeight(delete_sort_group->height());
    name_edit->setMinimumWidth((width_window-l_margin-r_margin-v_spacing)*0.15);
    name_edit->setMaximumHeight(100);
    date_edit->setFixedWidth((date_group->width())*0.25);
    date_edit->setAlignment(Qt::AlignCenter);
    rating_spin_box->setMinimumWidth((width_window-l_margin-r_margin-v_spacing)*0.06);
    status_combo_box->setMinimumWidth((width_window-l_margin-r_margin-v_spacing)*0.16);

    //QPalette data_slider_palette=date_slider->palette();
    //QColor data_slider_color=date_slider->palette().color(QPalette::ColorRole());
    //QString data_slider_color=date_slider->palette().color(QPalette::ColorRole()).name();
    name_invalid_symbol_label->setVisible(false);
    name_invalid_symbol_label->setStyleSheet("color: darkCyan; font-size: 12px");
    director_invalid_symbol_label->setVisible(false);
    director_invalid_symbol_label->setStyleSheet("color: darkCyan; font-size: 12px");
    date_invalid_symbol_label->setVisible(false);
    date_invalid_symbol_label->setStyleSheet("color: darkCyan; font-size: 12px");


    main_buttons_settings(main_buttons_width,main_buttons_height);
    this->main_table_settings();
    sort_combo_box->addItems(sort_list);
    QStandardItemModel* genre_model=new QStandardItemModel(genre_combo_box);
    genre_combo_box->setModel(genre_model);
    genre_combo_box->addItems(genre_list);
    QStandardItemModel* director_model=new QStandardItemModel(director_combo_box);
    director_combo_box->setModel(director_model);
    director_combo_box->setEditable(true);
    date_slider->setOrientation(Qt::Horizontal);
    //genre_scroll->setReadOnly(true);

    date_slider->setMaximum(QDate().currentDate().year());
    date_slider->setMinimum(1895);
    date_slider->setTickInterval(10);
    date_slider->setTickPosition(QSlider::TicksAbove);
    date_slider->setPageStep(1);
    date_slider->setSingleStep(1);
    date_slider->setValue((date_slider->maximum()-1895)/2);
    date_slider->setEnabled(true);
    date_slider->setTracking(true);
    date_slider->setSliderDown(true);
    rating_spin_box->setRange(0, 5);
    status_combo_box->addItems(status_list);
}
void App_page::main_buttons_settings(int w, int h){
    delete_button->setFixedSize(w, h);
    redact_button->setFixedSize(w+25, h);
    show_all_button->setFixedSize(w+15, h);
    sort_combo_box->setFixedSize(w, h);
    sort_button->setFixedSize(w+15, h);
    search_edit->setFixedSize((width_window-l_margin-r_margin-v_spacing)*0.6-2*w-50, h);
    search_button->setFixedSize(w, h);
    director_add_button->setFixedSize(w/2, h);
    QCommonStyle style;
    director_add_button->setIcon(style.standardIcon(QStyle::SP_DialogApplyButton, /*QStyleOptionButton::*/));
    accept_button->setFixedSize(w, h);
    clear_button->setFixedSize(w, h);
    back_button->setFixedSize(w, h);
    delete_button->setEnabled(false);
    redact_button->setEnabled(false);
    search_button->setEnabled(false);
    director_add_button->setEnabled(false);
    accept_button->setEnabled(false);
    clear_button->setEnabled(false);
}
void App_page::main_table_settings(){
    qDebug()<<"in main table settings";
    //table->setHorizontalHeader();
    QStandardItemModel* model=new QStandardItemModel(0, 6, this);
    this->table->setModel(model);
    table->setShowGrid(true);
    table->setSelectionMode(QAbstractItemView::SingleSelection);//мб несколько shift
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    model->setColumnCount(6);
    model->setHorizontalHeaderLabels(headers);

    table->setColumnWidth(0, table_group->width()*0.20);
    table->setColumnWidth(1, table_group->width()*0.20);
    table->setColumnWidth(2, table_group->width()*0.20);
    table->setColumnWidth(3, table_group->width()*0.10);
    table->setColumnWidth(4, table_group->width()*0.10);
    table->setColumnWidth(5, table_group->width()*0.15);
    table->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}
void App_page::main_scroll_group_settings(QScrollArea* scroll, QWidget* group, QLayout* layout){
    scroll->setWidgetResizable(false);
    scroll->setAlignment(Qt::AlignLeft);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    group->setFixedSize(scroll->width(), scroll->height());
    group->setLayout(layout);
    group->setStyleSheet("QGroupBox{border: 0px;}");
    scroll->setWidget(group);
}
QStandardItemModel* App_page::get_table_model(){
    QStandardItemModel* model=static_cast<QStandardItemModel*>(table->model());
    return model;
}
void App_page::filling_in_table(QJsonArray* array_data, int row_position){
    QStandardItemModel* model=static_cast<QStandardItemModel*>(table->model());
    int counter=row_position;
    QJsonArray::iterator array_iter=array_data->begin();
    for(;array_iter!=array_data->end();array_iter++){
        QJsonObject row_object= array_iter->toObject();
        QVariantMap row_data=row_object.toVariantMap();

        for(int column=0; column<model->columnCount();column++){
            QString string_of_item= QString();
            //QVariantMap::const_iterator iter;
            QJsonArray array_object;
            switch (column) {
            case 0:
                string_of_item=row_data.take("Title").toString();
                break;
            case 1:
                array_object=row_data.take("Directors").toJsonArray();
                string_of_item=jsonarray_to_str(array_object);
                break;
            case 2:
                array_object=row_data.take("Genres").toJsonArray();
                string_of_item=jsonarray_to_str(array_object);
                break;
            case 3:
                string_of_item=row_data.take("Year").toString();
                break;
            case 4:
                string_of_item=row_data.take("Rating").toString();
                break;
            case 5:
                string_of_item=row_data.take("Status").toString();
                break;
            default:
                break;
            }
            qDebug()<<string_of_item;
            QStandardItem* item=new QStandardItem(string_of_item);
            model->setItem(row_position, column, item);
            //row_of_item->push_back(item);
        }
        //model->appendRow(*row_of_item);
        //row_of_item->clear();
        counter++;
        row_position++;
    }
    //delete row_of_item;
}
QString App_page::jsonarray_to_str(const QJsonArray& array_object){
    QString element;
    for(int i=0; i<array_object.size();i++){
        element+=array_object.at(i).toString();        
        element+=", ";
    }
    element.removeLast();
    element.removeLast();
    return element;
}
void App_page::remove_row_in_table(QJsonArray* data){
    qDebug()<<"in remove row in table";
    QStandardItemModel* model=static_cast<QStandardItemModel*>(table->model());
    QJsonObject row_object= data->at(0).toObject();
    QVariantMap row_data=row_object.toVariantMap();
    int row=-1;
    QList<int>::iterator end=delete_rows_list->end();
    QString deleted_title=row_data.take("Title").toString();
    QString deleted_directors=jsonarray_to_str(row_data.take("Directors").toJsonArray());
    QString deleted_year=row_data.take("Year").toString();
    for(QList<int>::iterator i=delete_rows_list->begin(); i<end;i++){//считается, что пул режиссеров мог снять один title за один год
        if(model->item(*i, 0)->text()==deleted_title&&
           model->item(*i, 1)->text()==deleted_directors&&
           model->item(*i, 3)->text()==deleted_year){
            row=*i;
            break;
        }
    }
    qDebug()<<row;
    this->remove_from_delete_list(row);
    qDebug()<<"after remove from delete_list";
    model->removeRow(row);
}
void App_page::filling_page_with_data(QJsonArray* data){
    qDebug()<<"in filing page with data";
    QStandardItemModel* model=static_cast<QStandardItemModel*>(table->model());
    QJsonArray::iterator array_iter=data->begin();
    //QStringList directors_list;

    model->clear();
    main_table_settings();
    //model->setColumnCount(6);
    //model->setHorizontalHeaderLabels(headers);

    for(;array_iter!=data->end();array_iter++){
        QJsonObject row_object= array_iter->toObject();
        QVariantMap row_data=row_object.toVariantMap();
        QString director= QString();
        QJsonArray array_directors_object;
        array_directors_object=row_data.take("Directors").toJsonArray();
        //director=jsonarray_to_str(array_object);
        for(int i=0;i<array_directors_object.size();i++){
            director=array_directors_object.at(i).toString();
            if(!directors_list->contains(director)){
                directors_list->push_back(director);
            }
        }
    }
    director_combo_box->addItems(*directors_list);
    filling_in_table(data, 0);
}
void App_page::insert_row_in_table(QJsonArray* data){
    //тут или в заполнении таблицв проверка кратности размра листа 6
    qDebug()<<"in insert_row_in_table";
    QStandardItemModel* model=static_cast<QStandardItemModel*>(table->model());
    int current_number_of_rows=model->rowCount();
    filling_in_table(data, current_number_of_rows);//точно +1?
}
void App_page::update_row_in_table(QJsonObject* data_new_object, QJsonObject* data_old_object){
    QStandardItemModel* model=static_cast<QStandardItemModel*>(table->model());    
    int row=-1;
    //QJsonObject row_old_object= array_data->take("").toObject();
    QVariantMap row_old_data=data_old_object->toVariantMap();
    QList<int>::iterator end=update_rows_list->end();
    QString deleted_title=row_old_data.take("Title").toString();
    QString deleted_directors=jsonarray_to_str(row_old_data.take("Directors").toJsonArray());
    QString deleted_year=row_old_data.take("Year").toString();
    for(QList<int>::iterator i=update_rows_list->begin(); i<end;i++){//считается, что пул режиссеров мог снять один title за один год
        if(model->item(*i, 0)->text()==deleted_title&&
            model->item(*i, 1)->text()==deleted_directors&&
            model->item(*i, 3)->text()==deleted_year){
            row=*i;
            break;
        }
    }
    qDebug()<<row;
    this->remove_from_update_list(row);
    //QJsonObject row_new_object= array_data->at(1).toObject();
    QVariantMap row_new_data=data_new_object->toVariantMap();
    for(int column=0; column<model->columnCount();column++){
        QString string_of_item= QString();
        //QJsonArray::const_iterator iter;
        QJsonArray array_object;
        switch (column){
        case 0:
            string_of_item=row_new_data.take("Title").toString();
            break;
        case 1:
            array_object=row_new_data.take("Directors").toJsonArray();
            string_of_item=jsonarray_to_str(array_object);
            break;
        case 2:
            array_object=row_new_data.take("Genres").toJsonArray();
            string_of_item=jsonarray_to_str(array_object);
            break;
        case 3:
            string_of_item=row_new_data.take("Year").toString();
            break;
        case 4:
            string_of_item=row_new_data.take("Rating").toString();
            break;
        case 5:
            string_of_item=row_new_data.take("Status").toString();
            break;
        default:
            break;
            }
        QStandardItem* item=new QStandardItem(string_of_item);
        model->setItem(row, column, item);
        model->emit itemChanged(item);//проверить нужно ли
    }
}
