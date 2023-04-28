#include "app_page.h"
#include<QGridLayout>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QGroupBox>
#include <QLabel>
#include<QScrollArea>
#include<QDate>
App_page::App_page(QWidget *parent)
    :QWidget(parent),
    layout_page(new QGridLayout(this)),
    tabel_group(new QGroupBox(this)),
    search_group(new QGroupBox(this)),
    edit_group(new QGroupBox(this)),
    navigation_group(new QGroupBox(this)),
    tabel_scroll(new QScrollArea(tabel_group)),
    edit_scroll(new QScrollArea(edit_group)),
    director_group(new QGroupBox(edit_scroll)),
    genre_group(new QGroupBox(edit_scroll)),
    data_group(new QGroupBox(edit_scroll)),
    tabel(new QTableView(this)),
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

    QVBoxLayout* tabel_group_layout=new QVBoxLayout;
    QHBoxLayout* search_group_layout=new QHBoxLayout;
    QHBoxLayout* navigation_group_layout=new QHBoxLayout;
    QGridLayout* edit_group_layout=new QGridLayout;
    QVBoxLayout* director_group_layout=new QVBoxLayout;
    QVBoxLayout* genre_group_layout=new QVBoxLayout;
    QVBoxLayout* data_group_layout=new QVBoxLayout;

    tabel_group_layout->addWidget(tabel_scroll);
    tabel_group_layout->addWidget(delete_button);
    search_group_layout->addWidget(search_combo_box);
    search_group_layout->addWidget(search_edit);
    search_group_layout->addWidget(search_button);
    edit_group_layout->addWidget(name_label, 0,0, Qt::AlignLeft|Qt::AlignTop);
    edit_group_layout->addWidget(name_edit, 0,1, Qt::AlignCenter);
    edit_group_layout->addWidget(director_label, 1,0, Qt::AlignLeft|Qt::AlignTop);
    edit_group_layout->addWidget(director_group, 1,1, Qt::AlignCenter);
    edit_group_layout->addWidget(genre_label, 2,0, Qt::AlignLeft|Qt::AlignTop);
    edit_group_layout->addWidget(genre_group, 2,1, Qt::AlignCenter);
    edit_group_layout->addWidget(data_label, 3,0, Qt::AlignLeft|Qt::AlignTop);
    edit_group_layout->addWidget(data_group, 3,1, Qt::AlignCenter);
    edit_group_layout->addWidget(rating_label, 4,0, Qt::AlignLeft|Qt::AlignTop);
    edit_group_layout->addWidget(rating_spin_box, 4,1, Qt::AlignCenter);
    edit_group_layout->addWidget(status_label, 5,0, Qt::AlignLeft|Qt::AlignTop);
    edit_group_layout->addWidget(status_combo_box, 5,1, Qt::AlignCenter);
    edit_group_layout->addWidget(accept_button, 7,1, Qt::AlignCenter);
    director_group_layout->addWidget(director_combo_box, Qt::AlignCenter);
    director_group_layout->addWidget(director_edit, Qt::AlignCenter);
    genre_group_layout->addWidget(genre_combo_box, Qt::AlignCenter);
    genre_group_layout->addWidget(genre_edit, Qt::AlignCenter);
    data_group_layout->addWidget(data_slider, Qt::AlignCenter);
    data_group_layout->addWidget(data_edit, Qt::AlignCenter);
    navigation_group_layout->addWidget(back_button);

    tabel_group->setLayout(tabel_group_layout);
    search_group->setLayout(search_group_layout);
    edit_group->setLayout(edit_group_layout);
    director_group->setLayout(director_group_layout);
    genre_group->setLayout(genre_group_layout);
    data_group->setLayout(data_group_layout);
    navigation_group->setLayout(navigation_group_layout);


    layout_page->addWidget(tabel_group, 1,1, Qt::AlignLeft|Qt::AlignTop);
    layout_page->addWidget(search_group, 3,1, Qt::AlignLeft|Qt::AlignBottom);
    layout_page->addWidget(edit_group, 1,3, Qt::AlignRight|Qt::AlignTop);
    layout_page->addWidget(navigation_group, 3,3, Qt::AlignRight|Qt::AlignBottom);

    setLayout(layout_page);
    this->show();
    //this->setFixedSize(500,350);
    this->resize(800,600);
    this->setMaximumHeight(768);
    this->setMaximumWidth(1024);
    edit_group_layout->setRowMinimumHeight(6, 30);
    edit_group_layout->setVerticalSpacing(25);
    base_settings();
    connect(back_button, SIGNAL(clicked()), this, SLOT(on_back_button_clicked()));
}
void App_page::set_app_page_visible(bool flag){
    tabel_group->setVisible(flag);
    search_group->setVisible(flag);
    edit_group->setVisible(flag);
    navigation_group->setVisible(flag);
}
void App_page::on_back_button_clicked(){
    emit step_back();
}
void App_page::base_settings(){
    layout_page->setAlignment(layout_page->parentWidget(), Qt::AlignHCenter|Qt::AlignVCenter);
    layout_page->setContentsMargins(8,10, 8, 10);
    layout_page->setHorizontalSpacing(50);
    layout_page->setVerticalSpacing(50);
    layout_page->setColumnMinimumWidth(0, 0);
    layout_page->setColumnMinimumWidth(4, 0);
    layout_page->setColumnMinimumWidth(2, 8);
    layout_page->setRowMinimumHeight(0, 0);
    layout_page->setRowMinimumHeight(2, 8);
    layout_page->setRowMinimumHeight(4, 0);
    layout_page->setColumnStretch(1, 2);
    layout_page->setColumnStretch(3, 2);
    layout_page->setRowStretch(1, 2);
    layout_page->setRowStretch(3, 2);

    data_slider->setOrientation(Qt::Horizontal);
    QDate* currenta_date=new QDate();
    data_slider->setMaximum(currenta_date->year());
    data_slider->setMinimum(1895);
    data_slider->setTickInterval(1);
}
