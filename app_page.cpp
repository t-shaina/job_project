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
const int edit_group_v_spacing=25;
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
    name_edit (new QTextEdit(this)),
    director_label (new QLabel("Режиссер", this)),
    director_combo_box(new QComboBox(this)),
    director_edit(new QTextEdit(this)),
    genre_label (new QLabel("Жанр", this)),
    genre_edit(new QScrollArea(this)),
    genre_scroll_group(new QGroupBox(genre_edit)),
    genre_combo_box(new QComboBox(this)),
    date_edit(new QLineEdit(this)),
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
    QVBoxLayout* director_group_layout=new QVBoxLayout;
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
    edit_group_layout->addWidget(name_edit, 0,1, Qt::AlignCenter|Qt::AlignTop);
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
    director_group_layout->addWidget(director_combo_box, Qt::AlignCenter);
    director_group_layout->addWidget(director_edit, Qt::AlignCenter);
    genre_group_layout->addWidget(genre_combo_box, Qt::AlignCenter);
    genre_group_layout->addWidget(genre_edit, Qt::AlignCenter);
    date_group_layout->addWidget(date_slider, Qt::AlignCenter);
    date_group_layout->addWidget(date_edit, Qt::AlignRight);
    clear_group_layout->addWidget(accept_button, Qt::AlignCenter);
    clear_group_layout->addWidget(clear_button, Qt::AlignCenter);
    navigation_group_layout->addWidget(back_button, Qt::AlignRight);

    delete_sort_group->setLayout(delete_sort_group_layout);
    sort_group->setLayout(sort_group_layout);
    search_group->setLayout(search_group_layout);
    table_group->setLayout(table_group_layout);
    settings_group->setLayout(settings_group_layout);
    edit_group->setLayout(edit_group_layout);
    director_group->setLayout(director_group_layout);
    genre_group->setLayout(genre_group_layout);
    genre_edit->setLayout(genre_scroll_layout);// this
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
    director_group_layout->setContentsMargins(0,0,0,0);
    genre_group_layout->setContentsMargins(0,0,0,0);
    date_group_layout->setContentsMargins(0,0,0,0);
    sort_group->setStyleSheet("QGroupBox{border: 0px;}");
    navigation_group->setStyleSheet("QGroupBox{border: 0px;}");
    search_group->setStyleSheet("QGroupBox{border: 0px;}");

    edit_group_layout->setVerticalSpacing(edit_group_v_spacing);
    edit_group_layout->setColumnMinimumWidth(1, (width_window-l_margin-r_margin-v_spacing)*0.15);
    genre_edit->setWidgetResizable(false);
    genre_edit->setAlignment(Qt::AlignLeft);
    genre_edit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    genre_edit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    //genre_scroll_bar->setFixedWidth(15);
    //genre_scroll_bar->setFixedHeight(genre_edit->height());
    //genre_edit->setVerticalScrollBar(genre_scroll_bar);
    genre_scroll_group->setFixedSize(genre_edit->width(), genre_edit->height());
    genre_scroll_group->setLayout(genre_scroll_layout);
    genre_scroll_group->setStyleSheet("QGroupBox{border: 0px;}");
    genre_edit->setWidget(genre_scroll_group);
    base_settings();

    //connect(sort_combo_box, SIGNAL(activated(int)), this, SLOT(set_search_edit(int)));
    connect(genre_combo_box, SIGNAL(activated(int)), this, SLOT(set_genre_edit(int)));
    connect(director_combo_box, SIGNAL(activated(int)), this, SLOT(set_director_edit(int)));
    connect(date_slider, SIGNAL(valueChanged(int)), this, SLOT(set_date_edit(int)));

    connect(back_button, SIGNAL(clicked()), this, SLOT(on_back_button_clicked()));
    connect(delete_button, SIGNAL(clicked()), this, SLOT(on_delete_button_clicked()));
    connect(redact_button, SIGNAL(clicked()), this, SLOT(on_redact_button_clicked()));
    connect(show_all_button, SIGNAL(clicked()), this, SLOT(on_show_all_button_clicked()));
    connect(sort_button, SIGNAL(clicked()), this, SLOT(on_sort_button_clicked()));
    connect(search_button, SIGNAL(clicked()), this, SLOT(on_search_button_clicked()));
    connect(accept_button, SIGNAL(clicked()), this, SLOT(on_accept_button_clicked()));
    connect(clear_button, SIGNAL(clicked()), this, SLOT(on_clear_button_clicked()));

    connect(table, SIGNAL(clicked(QModelIndex)), this, SLOT(on_table_row_selected(QModelIndex)));
    connect(search_edit, SIGNAL(textEdited(QString)), this, SLOT(on_search_edit_edited()));
    connect(name_edit, SIGNAL(textChanged()), this, SLOT(on_name_director_genre_data_edit_changed()));
    connect(director_edit, SIGNAL(textChanged()), this, SLOT(on_name_director_genre_data_edit_changed()));
    connect(genre_edit, SIGNAL(textChanged()), this, SLOT(on_name_director_genre_data_edit_changed()));
    connect(date_edit, SIGNAL(textChanged(QString)), this, SLOT(on_name_director_genre_data_edit_changed()));
    connect(date_edit, SIGNAL(textEdited(QString)), this, SLOT(set_date_slider_position()));



    //Billet_widget* w=new Billet_widget(genre_edit, "Это я");

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
void App_page::set_director_edit(int director_id){

    QString text=director_combo_box->itemText(director_id);
    director_edit->setText(director_edit->toPlainText()+" "+text);
}
void App_page::set_genre_edit(int genre_id){

    QString text=genre_list.at(genre_id);
    QStandardItemModel* genre_model=static_cast<QStandardItemModel*>(genre_combo_box->model());
    genre_model->item(genre_id)->setEnabled(false);
    //genre_billet_widgets->clear();
    Billet_widget* widget=new Billet_widget(genre_edit, text);
    QSharedPointer<Billet_widget> widget_ptr(widget);
    genre_scroll_group->layout()->addWidget(widget);
    genre_billet_widgets->push_back(widget_ptr);
    QObject::connect(widget, SIGNAL(widget_was_deleted(QString)), this, SLOT(on_widget_was_deleted(QString)));
    //genre_edit->setText(genre_edit->toPlainText()+" "+text);
    qDebug()<<"in set genre edit size of list is"<<genre_billet_widgets->size();
}
void App_page::set_date_slider_position(){
    int year=date_edit->text().toInt();
    int current_year=QDate().currentDate().year();
    if(year<=current_year)
        date_slider->setSliderPosition(year);
    else date_slider->setSliderPosition(current_year);
}
void App_page::on_widget_was_deleted(QString text){
    qDebug()<<"in widget was X clicked"<<text;
    QStandardItemModel* genre_model=static_cast<QStandardItemModel*>(genre_combo_box->model());
    QList<QStandardItem*> items=genre_model->findItems(text);
    QSharedPointer<Billet_widget> widget_ptr=static_cast<QSharedPointer<Billet_widget>>(static_cast<Billet_widget*>(sender()));
    //genre_billet_widgets->removeOne(widget_ptr);
    widget_ptr.reset();
    for(QStandardItem* item:items){
        item->setEnabled(true);
    }
    qDebug()<<"in widget was deleted size of list is"<<genre_billet_widgets->size();
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
    QString genres=row_to_update->at(2);
    genres.push_back(' ');
    qDebug()<<"in redact_button second row is"<< genres;
    QString genre;

    QSharedPointer<Billet_widget> widget_ptr;
    foreach(widget_ptr, *genre_billet_widgets){
        widget_ptr.reset();
    }
    //genre_billet_widgets->clear();
    QStandardItemModel* genre_model=static_cast<QStandardItemModel*>(genre_combo_box->model());
    for(int i=0; i<genres.size();i++){
        if(genres.at(i)==' '){
            QList<QStandardItem*> items=genre_model->findItems(genre);
            for(QStandardItem* item:items){
                item->setEnabled(false);
            }

            Billet_widget* widget=new Billet_widget(genre_edit, genre);
            QSharedPointer<Billet_widget> widget_ptr(widget);
            genre_scroll_group->layout()->addWidget(widget);
            qDebug()<<"add one widget to genre_edit"<<widget->text();
            genre_billet_widgets->push_back(widget_ptr);
            QObject::connect(widget, SIGNAL(widget_was_deleted(QString)), this, SLOT(on_widget_was_deleted(QString)));
            genre.clear();
        }
        else
            genre+=genres.at(i);
    }
    redact_transfer_state=true;
    name_edit->setText(row_to_update->at(0));
    director_edit->setText(row_to_update->at(1));
    date_slider->setSliderPosition(row_to_update->at(3).toInt());
    rating_spin_box->setValue(row_to_update->at(4).toInt());
    status_combo_box->setPlaceholderText(row_to_update->at(5));
    accept_button->setText("Обновить");
    qDebug()<<"in redact button size of list is"<<genre_billet_widgets->size();
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
void App_page::on_accept_button_clicked(){
    QString genres;
    for(int i=0;i<genre_billet_widgets->size();i++){
        genres+=genre_billet_widgets->at(i)->text();
        genres+=" ";
    }
    genres.removeLast();
    QStringList insert_list= QStringList()   <<this->email
                                             <<name_edit->placeholderText()
                                             <<director_edit->placeholderText()
                                             <<genres
                                             <<date_edit->text()
                                             <<rating_spin_box->text()
                                             <<status_combo_box->currentText();
    if(redact_transfer_state){
        this->add_to_update_list();
        insert_list<<*row_to_update;
        emit  update_request(&insert_list);
    }
    else
    emit insert_request(&insert_list);
    name_edit->clear();
    director_edit->clear();
    genre_billet_widgets->clear();
    redact_transfer_state=false;
    accept_button->setText("Добавить");
    qDebug()<<"in accept button size of list is"<<genre_billet_widgets->size();
}
void App_page::on_clear_button_clicked(){
    QSharedPointer<Billet_widget> widget_ptr;
    foreach(widget_ptr, *genre_billet_widgets){
        widget_ptr.clear();
    }
    update_model_index=QModelIndex();//имеется ввиду сброс индекса  установкой недопустимного индекса
    name_edit->clear();
    director_edit->clear();
    //genre_billet_widgets->clear();//нужно ли?
    redact_transfer_state=false;
    accept_button->setText("Добавить");
    qDebug()<<"in clear button size of list is"<<genre_billet_widgets->size();
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
    if(name_edit->toPlainText().isEmpty()||
        director_edit->toPlainText().isEmpty()||
        genre_edit->children().isEmpty()||
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

    main_buttons_settings(main_buttons_width,main_buttons_height);
    this->main_table_settings();
    sort_combo_box->addItems(sort_list);
    QStandardItemModel* genre_model=new QStandardItemModel(genre_combo_box);
    genre_combo_box->setModel(genre_model);
    genre_combo_box->addItems(genre_list);
    date_slider->setOrientation(Qt::Horizontal);
    //genre_edit->setReadOnly(true);

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
    accept_button->setFixedSize(w, h);
    clear_button->setFixedSize(w, h);
    back_button->setFixedSize(w, h);
    delete_button->setEnabled(false);
    redact_button->setEnabled(false);
    search_button->setEnabled(false);
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
        element+=" ";
    }
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
    QStringList directors_list;

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
            if(!directors_list.contains(director)){
                directors_list.push_back(director);
            }
        }
    }
    director_combo_box->addItems(directors_list);
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
