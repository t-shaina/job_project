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

const int width_window=1280;
const int height_window=800;
const int l_margin=10;
const int t_margin=30;
const int r_margin=10;
const int b_margin=30;
const int v_spacing=30;
const int h_spacing=30;
const int navigation_group_hight=50;
const int table_magrin=5;
const int main_buttons_width=100;
const int main_buttons_height=30;
const QStringList genre_list=QStringList()<<"Комедия"<<"Мелодрама"<<"Мультфильм"<<"Ужасы"<<"Фантастика"<<"Триллер"
                                              <<"Боевик"<<"Детектив"<<"Фентези"<<"Исторический"<<"Драма"<<"Документальный"
                                              <<"Криминал"<<"Биография"<<"Вестерн"<<"Мюзиклы"<<"Короткометражка";
const QStringList headers= QStringList()<<"№"<<"Название"<<"Режиссер"<<"Жанр"<<"Год"<<"Рейтинг"<<"Статус";
const QStringList sort_list=QStringList()<<"Год"<<"Рейтинг"<<"Статус";
const QStringList status_list=QStringList()<<"Просмотрено"<<"Собираюсь смотреть"<<"Не рекомендую";
static int required_fields_flag =0;

App_page::App_page(QWidget *parent)
    :QWidget(parent),
    //page_group(new QGroupBox(this)),
    row_data(new QStringList()),
    redact_transfer_state(false),
    layout_page(new QGridLayout(this)),
    table_group(new QGroupBox(this)),
    scroll_table_group(new QGroupBox(table_group)),
    delete_sort_group(new QGroupBox(table_group)),
    sort_group(new QGroupBox(delete_sort_group)),
    search_group(new QGroupBox(this)),
    settings_group(new QGroupBox(this)),
    edit_group(new QGroupBox(this)),
    navigation_group(new QGroupBox(this)),
    table_scroll(new QScrollArea()),
    edit_scroll(new QScrollArea()),
    director_group(new QGroupBox(edit_group)),
    genre_group(new QGroupBox(edit_group)),
    date_group(new QGroupBox(edit_group)),
    table(new QTableView(scroll_table_group)),
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
    genre_edit(new QTextEdit(this)),
    genre_combo_box(new QComboBox(this)),
    date_edit(new QLineEdit(this)),
    date_label (new QLabel("Год создания", this)),
    date_slider(new QSlider(this)),
    rating_label (new QLabel("Рейтинг", this)),
    rating_spin_box(new QSpinBox(this)),
    status_label (new QLabel("Статус", this)),
    status_combo_box(new QComboBox(this)),
    accept_button (new QPushButton("Добавить", this)),
    back_button (new QPushButton("Выйти", this))
{

    QVBoxLayout* table_group_layout=new QVBoxLayout;
    QVBoxLayout* scroll_table_group_layout=new QVBoxLayout;
    QHBoxLayout* delete_sort_group_layout=new QHBoxLayout;
    QHBoxLayout* sort_group_layout=new QHBoxLayout;
    QHBoxLayout* search_group_layout=new QHBoxLayout;
    QHBoxLayout* navigation_group_layout=new QHBoxLayout;
    QVBoxLayout* settings_group_layout=new QVBoxLayout;
    QGridLayout* edit_group_layout=new QGridLayout;
    QVBoxLayout* director_group_layout=new QVBoxLayout;
    QVBoxLayout* genre_group_layout=new QVBoxLayout;
    QVBoxLayout* date_group_layout=new QVBoxLayout;

    table_group_layout->addWidget(table_scroll);
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
    settings_group_layout->addWidget(edit_scroll);
    settings_group_layout->addWidget(accept_button, Qt::AlignCenter);
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
    navigation_group_layout->addWidget(back_button, Qt::AlignRight);

    table_group->setLayout(table_group_layout);
    scroll_table_group->setLayout(scroll_table_group_layout);
    delete_sort_group->setLayout(delete_sort_group_layout);
    sort_group->setLayout(sort_group_layout);
    search_group->setLayout(search_group_layout);
    settings_group->setLayout(settings_group_layout);
    edit_group->setLayout(edit_group_layout);
    director_group->setLayout(director_group_layout);
    genre_group->setLayout(genre_group_layout);
    date_group->setLayout(date_group_layout);
    navigation_group->setLayout(navigation_group_layout);

    table_scroll->setWidget(scroll_table_group);
    table_scroll->setWidgetResizable(true);
    edit_scroll->setWidget(edit_group);
    edit_scroll->setWidgetResizable(true);

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
    delete_sort_group_layout->setContentsMargins(0,0,0,0);
    director_group_layout->setContentsMargins(0,0,0,0);
    genre_group_layout->setContentsMargins(0,0,0,0);
    date_group_layout->setContentsMargins(0,0,0,0);
    sort_group->setStyleSheet("QGroupBox{border: 0px;}");
    navigation_group->setStyleSheet("QGroupBox{border: 0px;}");
    search_group->setStyleSheet("QGroupBox{border: 0px;}");
    edit_group_layout->setVerticalSpacing(25);
    edit_group_layout->setColumnMinimumWidth(1, (width_window-l_margin-r_margin-v_spacing)*0.15);
    base_settings();
    main_table_settings();
    //connect(sort_combo_box, SIGNAL(activated(int)), this, SLOT(set_search_edit(int)));
    connect(genre_combo_box, SIGNAL(activated(int)), this, SLOT(set_genre_edit(int)));
    connect(date_slider, SIGNAL(valueChanged(int)), this, SLOT(set_date_edit(int)));

    connect(back_button, SIGNAL(clicked()), this, SLOT(on_back_button_clicked()));
    connect(delete_button, SIGNAL(clicked()), this, SLOT(on_delete_button_clicked()));
    connect(delete_button, SIGNAL(clicked()), this, SLOT(on_redact_button_clicked()));
    connect(delete_button, SIGNAL(clicked()), this, SLOT(on_show_all_button_clicked()));
    connect(sort_button, SIGNAL(clicked()), this, SLOT(on_sort_button_clicked()));
    connect(search_button, SIGNAL(clicked()), this, SLOT(on_search_button_clicked()));
    connect(accept_button, SIGNAL(clicked()), this, SLOT(on_accept_button_clicked()));


    connect(table, SIGNAL(itemClicked(int)), this, SLOT(on_table_row_selected(int)));
    connect(search_edit, SIGNAL(textEdited(QString)), this, SLOT(on_search_edit_edited()));
    connect(name_edit, SIGNAL(textChanged()), this, SLOT(on_name_director_genre_data_edit_changed()));
    connect(director_edit, SIGNAL(textChanged()), this, SLOT(on_name_director_genre_data_edit_changed()));
    connect(genre_edit, SIGNAL(textChanged()), this, SLOT(on_name_director_genre_data_edit_changed()));
    connect(date_edit, SIGNAL(textChanged(QString)), this, SLOT(on_name_director_genre_data_edit_changed()));
    connect(date_edit, SIGNAL(textEdited(QString)), this, SLOT(set_date_slider_position()));

}
/*void App_page::set_app_page_visible(bool flag){
    table_group->setVisible(flag);
    search_group->setVisible(flag);
    settings_group->setVisible(flag);
    navigation_group->setVisible(flag);
}*/
void App_page::on_back_button_clicked(){
    emit step_back();
}
void App_page::on_sort_button_clicked(){
    int sort_id=sort_combo_box->currentIndex();
    QStandardItemModel* model=static_cast<QStandardItemModel*>(table->model());
    model->sort(sort_id+4, Qt::AscendingOrder);

}
void App_page::set_search_edit(int search_id){
    //
}
void App_page::set_date_edit(int data_value){
    QString text=QString::number(data_value);
    date_edit->setText(text);
}
void App_page::set_genre_edit(int genre_id){

    QString text=genre_list.at(genre_id);
    genre_edit->setText(genre_edit->toPlainText()+" "+text);
}
void App_page::set_date_slider_position(){
    int year=date_edit->text().toInt();
    int current_year=QDate().currentDate().year();
    if(year<=current_year)
        date_slider->setSliderPosition(year);
    else date_slider->setSliderPosition(current_year);
}
void App_page::on_delete_button_clicked(){
    /*int row=table->currentRow();
    QStringList delete_list=QStringList();
    for(int i=1; i<table->columnCount();i++)
        delete_list<<table->item(row, i)->text();*/
    QItemSelectionModel* select_model=table->selectionModel();
    *model_index=select_model->currentIndex();
    emit delete_request(row_data);
}
void App_page::on_redact_button_clicked(){//тут добавить перенос из таблицы в область редактирования
    QItemSelectionModel* select_model=table->selectionModel();
    QStandardItemModel* model=static_cast<QStandardItemModel*>(table->model());
    QModelIndex index=select_model->currentIndex();
    int row=index.row();
    redact_transfer_state=true;
    QStringList redact_list=QStringList();//или row_data
    for(int i=1; i<model->columnCount();i++)
        redact_list<<model->item(row, i)->data().toStringList();
    name_edit->setText(redact_list.at(1));
    director_edit->setText(redact_list.at(2));
    genre_edit->setText(redact_list.at(3));
    date_slider->setSliderPosition(redact_list.at(4).toInt());
    rating_spin_box->setValue(redact_list.at(5).toInt());
    status_combo_box->setPlaceholderText(redact_list.at(6));
    accept_button->setText("Обновить");

}
void App_page::on_show_all_button_clicked(){
    QStringList data=QStringList();
    data<<this->email;
    emit select_all_request(&data);
}
void App_page::on_search_button_clicked(){
    QStringList data=QStringList();
    data<<this->search_edit->text();
    emit search_request(&data);
}
void App_page::on_accept_button_clicked(){

    QStringList insert_list= QStringList()   <<this->email
                                             <<name_edit->placeholderText()
                                             <<encoding_data(director_edit->placeholderText())
                                             <<encoding_data(genre_edit->placeholderText())
                                             <<date_edit->text()
                                             <<rating_spin_box->text()
                                             <<status_combo_box->currentText();
    if(redact_transfer_state){
        insert_list<<*row_data;
        emit  update_request(&insert_list);
    }
    else
        emit insert_request(&insert_list);
    redact_transfer_state=false;
    accept_button->setText("Добавить");

}
void App_page::on_table_row_selected(int){
    row_data->clear();
    delete_button->setEnabled(true);
    redact_button->setEnabled(true);
    QString cell_data;
    QItemSelectionModel* select_model=table->selectionModel();
    QStandardItemModel* model=static_cast<QStandardItemModel*>(table->model());
    QModelIndex index=select_model->currentIndex();
    int row=index.row();
    for(int i=1; i<8;i++){
        if(i==2||i==3){//для режиссеров и жанров дополнительное кодирование
            cell_data=encoding_data(model->item(row,i)->data().toString());
        }
        else
            cell_data=model->item(row,i)->data().toString();
        this->row_data->push_back(cell_data);
        cell_data.clear();
    }

}
void App_page::on_search_edit_edited(){
    if(search_edit->text().isEmpty())
        search_button->setEnabled(false);
    else search_button->setEnabled(true);
}
void App_page::on_name_director_genre_data_edit_changed(){
    if(name_edit->toPlainText().isEmpty()||
        director_edit->toPlainText().isEmpty()||
        genre_edit->toPlainText().isEmpty()||
        date_edit->text().isEmpty())
        accept_button->setEnabled(false);
    else accept_button->setEnabled(true);

}
void App_page::on_name_edit_changed(){
    QSize text_size=name_edit->fontMetrics().size(Qt::TextWordWrap, name_edit->placeholderText());
    if(text_size.width()>name_edit->width())
        name_edit->setMinimumHeight(text_size.height()*text_size.width()/name_edit->width());
}
QString App_page::encoding_data(const QString& data){
    QString encoded_data;
    QString word;
    int size=0;
    for (int i=0;i<data.size();i++){
        if(data.at(i)!=' '){
            word+=data.at(i);
            size++;
        }
        else{
            encoded_data.push_back(static_cast<char>(size));
            encoded_data.push_back(word);
            size=0;
            word.clear();
        }
    }
    return encoded_data;
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
    sort_group->setFixedWidth((width_window-l_margin-r_margin-v_spacing)*0.7*0.5);
    settings_group->setMinimumSize((width_window-l_margin-r_margin-v_spacing)*0.3, (height_window-t_margin-b_margin-h_spacing)-navigation_group_hight);
    search_group->setMinimumSize((width_window-l_margin-r_margin-v_spacing)*0.7, navigation_group_hight);
    navigation_group->setMinimumSize((width_window-l_margin-r_margin-v_spacing)*0.3, navigation_group_hight);
    //edit_group->setMinimumSize((width_window-l_margin-r_margin-v_spacing)*0.3, (hight_window-t_margin-b_margin-h_spacing)-navigation_group_hight-main_buttons_hight-h_spacing);
    director_group->setMinimumWidth((width_window-l_margin-r_margin-v_spacing)*0.15);
    genre_group->setMinimumWidth((width_window-l_margin-r_margin-v_spacing)*0.15);
    date_group->setMinimumWidth((width_window-l_margin-r_margin-v_spacing)*0.15);
    name_edit->setMinimumWidth((width_window-l_margin-r_margin-v_spacing)*0.15);
    name_edit->setMaximumHeight(100);
    date_edit->setFixedWidth((date_group->width())*0.25);
    date_edit->setAlignment(Qt::AlignCenter);
    //name_edit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    //director_edit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    //genre_edit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    rating_spin_box->setMinimumWidth((width_window-l_margin-r_margin-v_spacing)*0.06);
    status_combo_box->setMinimumWidth((width_window-l_margin-r_margin-v_spacing)*0.16);

    table->setMinimumSize((width_window-l_margin-r_margin-v_spacing)*0.7, (height_window-t_margin-b_margin-h_spacing)-navigation_group_hight-main_buttons_height);

    table->setShowGrid(true);
    table->setSelectionMode(QAbstractItemView::SingleSelection);//мб несколько shift
    table->setSelectionBehavior(QAbstractItemView::SelectRows);

    table->setColumnWidth(0, (width_window-l_margin-r_margin-v_spacing)*0.7*0.06);
    table->setColumnWidth(1, (width_window-l_margin-r_margin-v_spacing)*0.7*0.19);
    table->setColumnWidth(2, (width_window-l_margin-r_margin-v_spacing)*0.7*0.19);
    table->setColumnWidth(3, (width_window-l_margin-r_margin-v_spacing)*0.7*0.17);
    table->setColumnWidth(4, (width_window-l_margin-r_margin-v_spacing)*0.7*0.08);
    table->setColumnWidth(5, (width_window-l_margin-r_margin-v_spacing)*0.7*0.11);
    table->setColumnWidth(6, (width_window-l_margin-r_margin-v_spacing)*0.7*0.2);

    main_buttons_settings(main_buttons_width,main_buttons_height);

    sort_combo_box->addItems(sort_list);
    genre_combo_box->addItems(genre_list);
    date_slider->setOrientation(Qt::Horizontal);
    genre_edit->setReadOnly(true);

    //QDate* current_date=new QDate();
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
    back_button->setFixedSize(w, h);
    delete_button->setEnabled(false);
    redact_button->setEnabled(false);
    search_button->setEnabled(false);
    accept_button->setEnabled(false);
}
void App_page::main_table_settings(){
    QStandardItemModel* model=new QStandardItemModel(1, 7, this);
    this->table->setModel(model);
    model->setColumnCount(7);
    model->setHorizontalHeaderLabels(headers);
}
QStandardItemModel* App_page::get_table_model(){
    QStandardItemModel* model=static_cast<QStandardItemModel*>(table->model());
    return model;
}
void App_page::filling_in_table(QStringList* data, int row_position){
    QStandardItemModel* model=static_cast<QStandardItemModel*>(table->model());
    //int number_of_rows=(data->size()-2)/6;
    QStringList::iterator i=data->begin();
     //i+=2;
    int counter=row_position;
    QList<QStandardItem*>* row_of_item= new QList<QStandardItem*>(7);
    while (i<data->end()){
        for(int j=0; j<7;j++){
            QString string_of_item= QString();
            if(j==0){
                string_of_item=QString::number(counter);
            }
            else if(j==2||j==3){
                string_of_item=decoding_element(i);
                i++;
            }
            else {
                string_of_item=*i;
                i++;
            }
            QStandardItem* item=new QStandardItem(string_of_item);
            row_of_item->push_back(item);
        }
        model->appendRow(*row_of_item);
        row_of_item->clear();
        counter++;
    }
    delete row_of_item;
}
QString App_page::decoding_element(const QStringList::iterator iter_to_element){
    QString element;
    int length=0;
    for(int i=0; i<iter_to_element->size()-length-1; i+=length){
        length=iter_to_element->at(i).digitValue();
        element.push_back(iter_to_element->sliced(i+1, length));
        element.push_back(' ');
    }
    return element;
}
void App_page::remove_row_in_table(){
    QStandardItemModel* model=static_cast<QStandardItemModel*>(table->model());
    model->removeRow(model_index->row());
}
void App_page::insert_rows_in_table(QStringList* data){
    filling_in_table(data, 1);
}
void App_page::insert_row_in_table(QStringList* data){//переделать два метода, код повторяется
    QStandardItemModel* model=static_cast<QStandardItemModel*>(table->model());
    int current_number_of_rows=model->rowCount();
    filling_in_table(data, current_number_of_rows);
}
