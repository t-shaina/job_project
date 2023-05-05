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
const int hight_window=800;
const int l_margin=10;
const int t_margin=30;
const int r_margin=10;
const int b_margin=30;
const int v_spacing=30;
const int h_spacing=30;
const int navigation_group_hight=50;
const int table_magrin=5;
const int main_buttons_width=100;
const int main_buttons_hight=30;
const QStringList genre_list=QStringList()<<"Комедия"<<"Мелодрама"<<"Мультфильм"<<"Ужасы"<<"Фантастика"<<"Триллер"
                                              <<"Боевик"<<"Детектив"<<"Фентези"<<"Исторический"<<"Драма"<<"Документальный"
                                              <<"Криминал"<<"Биография"<<"Вестерн"<<"Мюзиклы"<<"Короткометражка";
const QStringList headers= QStringList()<<"№"<<"Название"<<"Режиссер"<<"Жанр"<<"Год"<<"Рейтинг"<<"Статус";
const QStringList search_list=QStringList()<<"Название"<<"Режиссер"<<"Жанр"<<"Статус";
const QStringList status_list=QStringList()<<"Просмотрено"<<"Собираюсь смотреть"<<"Не рекомендую";
static int required_fields_flag =0;

App_page::App_page(QWidget *parent)
    :QWidget(parent),
    //page_group(new QGroupBox(this)),
    layout_page(new QGridLayout(this)),
    table_group(new QGroupBox(this)),
    scroll_table_group(new QGroupBox(table_group)),
    search_group(new QGroupBox(this)),
    settings_group(new QGroupBox(this)),
    edit_group(new QGroupBox(this)),
    navigation_group(new QGroupBox(this)),
    table_scroll(new QScrollArea()),
    edit_scroll(new QScrollArea()),
    director_group(new QGroupBox(edit_group)),
    genre_group(new QGroupBox(edit_group)),
    data_group(new QGroupBox(edit_group)),
    table(new QTableWidget(scroll_table_group)),
    delete_button(new QPushButton("Удалить", this)),
    search_combo_box(new QComboBox(this)),
    search_edit(new QLineEdit(this)),
    search_button(new QPushButton("Поиск", this)),
    name_label (new QLabel("Название", this)),
    name_edit (new QLineEdit(this)),
    director_label (new QLabel("Режиссер", this)),
    director_combo_box(new QComboBox(this)),
    director_edit(new QLineEdit(this)),
    genre_label (new QLabel("Жанр", this)),
    genre_edit(new QLineEdit(this)),
    genre_combo_box(new QComboBox(this)),
    data_edit(new QLineEdit(this)),
    data_label (new QLabel("Год создания", this)),
    data_slider(new QSlider(this)),
    rating_label (new QLabel("Рейтинг", this)),
    rating_spin_box(new QSpinBox(this)),
    status_label (new QLabel("Статус", this)),
    status_combo_box(new QComboBox(this)),
    accept_button (new QPushButton("Принять", this)),
    back_button (new QPushButton("Назад", this))
{

    QVBoxLayout* table_group_layout=new QVBoxLayout;
    QVBoxLayout* scroll_table_group_layout=new QVBoxLayout;
    QHBoxLayout* search_group_layout=new QHBoxLayout;
    QHBoxLayout* navigation_group_layout=new QHBoxLayout;
    QVBoxLayout* settings_group_layout=new QVBoxLayout;
    QGridLayout* edit_group_layout=new QGridLayout;
    QVBoxLayout* director_group_layout=new QVBoxLayout;
    QVBoxLayout* genre_group_layout=new QVBoxLayout;
    QVBoxLayout* data_group_layout=new QVBoxLayout;

    table_group_layout->addWidget(table_scroll);
    table_group_layout->addWidget(delete_button);
    search_group_layout->addWidget(search_combo_box);
    search_group_layout->addWidget(search_edit);
    search_group_layout->addWidget(search_button, Qt::AlignCenter);
    settings_group_layout->addWidget(edit_scroll);
    settings_group_layout->addWidget(accept_button, Qt::AlignCenter);
    edit_group_layout->addWidget(name_label, 0,0, Qt::AlignLeft|Qt::AlignTop);
    edit_group_layout->addWidget(name_edit, 0,1, Qt::AlignCenter|Qt::AlignTop);
    edit_group_layout->addWidget(director_label, 1,0, Qt::AlignLeft|Qt::AlignTop);
    edit_group_layout->addWidget(director_group, 1,1, Qt::AlignCenter|Qt::AlignTop);
    edit_group_layout->addWidget(genre_label, 2,0, Qt::AlignLeft|Qt::AlignTop);
    edit_group_layout->addWidget(genre_group, 2,1, Qt::AlignCenter|Qt::AlignTop);
    edit_group_layout->addWidget(data_label, 3,0, Qt::AlignLeft|Qt::AlignTop);
    edit_group_layout->addWidget(data_group, 3,1, Qt::AlignCenter|Qt::AlignTop);
    edit_group_layout->addWidget(rating_label, 4,0, Qt::AlignLeft|Qt::AlignTop);
    edit_group_layout->addWidget(rating_spin_box, 4,1, Qt::AlignCenter|Qt::AlignTop);
    edit_group_layout->addWidget(status_label, 5,0, Qt::AlignLeft|Qt::AlignTop);
    edit_group_layout->addWidget(status_combo_box, 5,1, Qt::AlignCenter|Qt::AlignTop);
    director_group_layout->addWidget(director_combo_box, Qt::AlignCenter);
    director_group_layout->addWidget(director_edit, Qt::AlignCenter);
    genre_group_layout->addWidget(genre_combo_box, Qt::AlignCenter);
    genre_group_layout->addWidget(genre_edit, Qt::AlignCenter);
    data_group_layout->addWidget(data_slider, Qt::AlignCenter);
    data_group_layout->addWidget(data_edit, Qt::AlignRight);
    navigation_group_layout->addWidget(back_button, Qt::AlignRight);

    table_group->setLayout(table_group_layout);
    scroll_table_group->setLayout(scroll_table_group_layout);
    search_group->setLayout(search_group_layout);
    settings_group->setLayout(settings_group_layout);
    edit_group->setLayout(edit_group_layout);
    director_group->setLayout(director_group_layout);
    genre_group->setLayout(genre_group_layout);
    data_group->setLayout(data_group_layout);
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
    this->resize(width_window,hight_window);
    this->setMaximumHeight(hight_window);
    this->setMaximumWidth(width_window);
    //edit_group_layout->setRowMinimumHeight(6, 30);
    edit_group_layout->setVerticalSpacing(25);
    edit_group_layout->setColumnMinimumWidth(1, (width_window-l_margin-r_margin-v_spacing)*0.15);
    base_settings();
    connect(search_combo_box, SIGNAL(activated(int)), this, SLOT(set_search_edit(int)));
    connect(genre_combo_box, SIGNAL(activated(int)), this, SLOT(set_genre_edit(int)));
    connect(data_slider, SIGNAL(valueChanged(int)), this, SLOT(set_data_edit(int)));

    connect(back_button, SIGNAL(clicked()), this, SLOT(on_back_button_clicked()));
    connect(delete_button, SIGNAL(clicked()), this, SLOT(on_delete_button_clicked()));
    connect(search_button, SIGNAL(clicked()), this, SLOT(on_search_button_clicked()));
    connect(accept_button, SIGNAL(clicked()), this, SLOT(on_accept_button_clicked()));

    connect(table, SIGNAL(pressed()), this, SLOT(on_table_row_selected()));
    connect(search_edit, SIGNAL(textEdited()), this, SLOT(on_search_edit_edited()));
    connect(name_edit, SIGNAL(textChanged()), this, SLOT(on_name_edit_changed()));
    connect(director_edit, SIGNAL(textChanged()), this, SLOT(on_director_edit_changed()));
    connect(genre_edit, SIGNAL(textChanged()), this, SLOT(on_genre_edit_changed()));
    connect(data_edit, SIGNAL(textChanged()), this, SLOT(on_data_edit_changed()));

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
void App_page::set_search_edit(int search_id){
    //
}
void App_page::set_data_edit(int data_value){
    QString text=QString::number(data_value);
    data_edit->setText(text);
}
void App_page::set_genre_edit(int genre_id){

    QString text=genre_list.at(genre_id);
    genre_edit->setText(text);
}
void App_page::on_delete_button_clicked(){
    QStringList delete_list=QStringList();
    emit delete_request(&delete_list);

}
void App_page::on_search_button_clicked(){

    QString* search_string=new QString(search_edit->text());
    emit search_request(search_string);


}
void App_page::on_accept_button_clicked(){

    QStringList update_list= QStringList()   <<name_edit->text()
                                             <<director_edit->text()
                                             <<genre_edit->text()
                                             <<data_edit->text()
                                             <<rating_spin_box->text()
                                             <<status_combo_box->currentText();
    emit update_request(&update_list);

}
void App_page::on_table_row_selected(){
    delete_button->setEnabled(true);
}
void App_page::on_search_edit_edited(){
    if(search_edit->text()!="")
    search_button->setEnabled(true);
}
void App_page::on_name_edit_changed(){
    if(name_edit->text()!="")
        required_fields_flag++;
    else if(required_fields_flag!=0)
        required_fields_flag--;
    if (required_fields_flag==4)
        accept_button->setEnabled(true);

}
void App_page::on_director_edit_changed(){
    if(director_edit->text()!="")
        required_fields_flag++;
    else if(required_fields_flag!=0)
        required_fields_flag--;
    if (required_fields_flag==4)
        accept_button->setEnabled(true);
}
void App_page::on_genre_edit_changed(){
    if(genre_edit->text()!="")
        required_fields_flag++;
    else if(required_fields_flag!=0)
        required_fields_flag--;
    if (required_fields_flag==4)
        accept_button->setEnabled(true);
}
void App_page::on_data_edit_changed(){
    if(data_edit->text()!="")
        required_fields_flag++;
    else if(required_fields_flag!=0)
        required_fields_flag--;
    if (required_fields_flag==4)
        accept_button->setEnabled(true);
}
void App_page::base_settings(){

    layout_page->setAlignment(layout_page->parentWidget(), Qt::AlignHCenter|Qt::AlignVCenter);
    layout_page->setContentsMargins(l_margin, t_margin, r_margin, b_margin);
    layout_page->setHorizontalSpacing(h_spacing);
    layout_page->setVerticalSpacing(v_spacing);
    layout_page->setColumnMinimumWidth(0, (width_window-l_margin-r_margin-v_spacing)*0.7);
    layout_page->setColumnMinimumWidth(1, (width_window-l_margin-r_margin-v_spacing)*0.3);
    layout_page->setRowMinimumHeight(0, (hight_window-t_margin-b_margin-h_spacing)-navigation_group_hight);
    layout_page->setRowMinimumHeight(1, navigation_group_hight);
    layout_page->setColumnStretch(0, 2);
    layout_page->setColumnStretch(1, 2);
    layout_page->setRowStretch(0, 2);
    layout_page->setRowStretch(1, 2);

    table_group->setMinimumSize((width_window-l_margin-r_margin-v_spacing)*0.7, (hight_window-t_margin-b_margin-h_spacing)-navigation_group_hight);
    settings_group->setMinimumSize((width_window-l_margin-r_margin-v_spacing)*0.3, (hight_window-t_margin-b_margin-h_spacing)-navigation_group_hight);
    search_group->setMinimumSize((width_window-l_margin-r_margin-v_spacing)*0.7, navigation_group_hight);
    navigation_group->setMinimumSize((width_window-l_margin-r_margin-v_spacing)*0.3, navigation_group_hight);
    //edit_group->setMinimumSize((width_window-l_margin-r_margin-v_spacing)*0.3, (hight_window-t_margin-b_margin-h_spacing)-navigation_group_hight-main_buttons_hight-h_spacing);
    director_group->setMinimumWidth((width_window-l_margin-r_margin-v_spacing)*0.15);
    genre_group->setMinimumWidth((width_window-l_margin-r_margin-v_spacing)*0.15);
    data_group->setMinimumWidth((width_window-l_margin-r_margin-v_spacing)*0.15);
    name_edit->setMinimumWidth((width_window-l_margin-r_margin-v_spacing)*0.15);
    data_edit->setFixedWidth((data_group->width())*0.25);
    data_edit->setAlignment(Qt::AlignCenter);
    //name_edit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    //director_edit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    //genre_edit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    rating_spin_box->setMinimumWidth((width_window-l_margin-r_margin-v_spacing)*0.06);
    status_combo_box->setMinimumWidth((width_window-l_margin-r_margin-v_spacing)*0.16);

    table->setMinimumSize((width_window-l_margin-r_margin-v_spacing)*0.7, (hight_window-t_margin-b_margin-h_spacing)-navigation_group_hight-main_buttons_hight);
    table->setColumnCount(7);
    table->setShowGrid(true);
    table->setSelectionMode(QAbstractItemView::SingleSelection);//мб несколько shift
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setHorizontalHeaderLabels(headers);
    table->setColumnWidth(0, (width_window-l_margin-r_margin-v_spacing)*0.7*0.06);
    table->setColumnWidth(1, (width_window-l_margin-r_margin-v_spacing)*0.7*0.19);
    table->setColumnWidth(2, (width_window-l_margin-r_margin-v_spacing)*0.7*0.19);
    table->setColumnWidth(3, (width_window-l_margin-r_margin-v_spacing)*0.7*0.17);
    table->setColumnWidth(4, (width_window-l_margin-r_margin-v_spacing)*0.7*0.08);
    table->setColumnWidth(5, (width_window-l_margin-r_margin-v_spacing)*0.7*0.11);
    table->setColumnWidth(6, (width_window-l_margin-r_margin-v_spacing)*0.7*0.2);

    main_buttons_settings(main_buttons_width,main_buttons_hight);

    search_combo_box->addItems(search_list);
    genre_combo_box->addItems(genre_list);
    data_slider->setOrientation(Qt::Horizontal);
    QDate* current_date=new QDate();
    data_slider->setMaximum(current_date->currentDate().year());
    data_slider->setMinimum(1895);
    data_slider->setTickInterval(10);
    data_slider->setTickPosition(QSlider::TicksAbove);
    data_slider->setPageStep(1);
    data_slider->setSingleStep(1);
    data_slider->setValue((data_slider->maximum()-1895)/2);
    data_slider->setEnabled(true);
    data_slider->setTracking(true);
    data_slider->setSliderDown(true);
    rating_spin_box->setRange(0, 5);
    status_combo_box->addItems(status_list);
}
void App_page::main_buttons_settings(int w, int h){
    delete_button->setFixedSize(w, h);
    search_combo_box->setFixedSize(w, h);
    search_edit->setFixedSize((width_window-l_margin-r_margin-v_spacing)*0.6-2*w-50, h);
    search_button->setFixedSize(w, h);
    accept_button->setFixedSize(w, h);
    back_button->setFixedSize(w, h);
    delete_button->setEnabled(false);
    search_button->setEnabled(false);
    accept_button->setEnabled(false);
}
