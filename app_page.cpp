#include "app_page.h"
#include<QGridLayout>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QGroupBox>
#include <QLabel>
#include<QScrollArea>
App_page::App_page(QWidget *parent)
    :QGroupBox(parent),
    layout_page(new QGridLayout(this)),
    tabel(new QTableView(this)),
    delete_button(new QPushButton(this)),
    search_combo_box(new QComboBox(this)),
    search_edit(new QLineEdit(this)),
    search_button(new QPushButton(this)),
    name_label (new QLabel("Название", this)),
    name_edit (new QLineEdit(this)),
    director_label (new QLabel("Режиссер", this)),
    director_combo_box(new QComboBox(this)),
    director_edit(new QLineEdit(this)),
    genre_label (new QLabel("Жанр", this)),
    genre_edit(new QLineEdit(this)),
    //
    data_label (new QLabel("Год создания", this)),
    data_slider(new QSlider(this)),
    rating_label (new QLabel("Рейтинг", this)),
    rating_spin_box(new QSpinBox(this)),
    status_label (new QLabel("Статус", this)),
    status_combo_box(new QComboBox(this)),
    back_button(new QPushButton(this))

{
    QGroupBox* tabel_group=new QGroupBox(this);
    QGroupBox* search_group= new QGroupBox(this);
    QGroupBox* edit_group= new QGroupBox(this);
    QGroupBox* navigation_group= new QGroupBox(this);
    QScrollArea* tabel_scroll=new QScrollArea(tabel_group);
    QScrollArea* edit_scroll=new QScrollArea(edit_group);
    QGroupBox* director_group=new QGroupBox(edit_scroll);
    QGroupBox* genre_group=new QGroupBox(edit_scroll);

    QVBoxLayout* tabel_group_layout=new QVBoxLayout;
    QHBoxLayout* search_group_layout=new QHBoxLayout;
    QHBoxLayout* navigation_group_layout=new QHBoxLayout;
    QGridLayout* edit_group_layout=new QGridLayout;
    //тут для групп директор и генри

    tabel_group_layout->addWidget(tabel_scroll);
    tabel_group_layout->addWidget(delete_button);
    search_group_layout->addWidget(search_combo_box);
    search_group_layout->addWidget(search_edit);
    search_group_layout->addWidget(search_button);
    edit_group_layout->addWidget(name_label, 0,0, Qt::AlignCenter);
    edit_group_layout->addWidget(name_edit, 0,1, Qt::AlignCenter);
    edit_group_layout->addWidget(director_label, 1,0, Qt::AlignCenter);
    edit_group_layout->addWidget(director_group, 1,1, Qt::AlignCenter);
    edit_group_layout->addWidget(genre_label, 2,0, Qt::AlignCenter);
    edit_group_layout->addWidget(genre_group, 2,1, Qt::AlignCenter);
    edit_group_layout->addWidget(data_label, 3,0, Qt::AlignCenter);
    edit_group_layout->addWidget(data_slider, 3,1, Qt::AlignCenter);
    edit_group_layout->addWidget(rating_label, 4,0, Qt::AlignCenter);
    edit_group_layout->addWidget(rating_spin_box, 4,1, Qt::AlignCenter);
    edit_group_layout->addWidget(status_label, 5,0, Qt::AlignCenter);
    edit_group_layout->addWidget(status_combo_box, 5,1, Qt::AlignCenter);
    navigation_group_layout->addWidget(back_button);

    tabel_group->setLayout(tabel_group_layout);
    search_group->setLayout(search_group_layout);
    edit_group->setLayout(edit_group_layout);
    navigation_group->setLayout(navigation_group_layout);

    layout_page->addWidget(tabel_group, 1,1, Qt::AlignCenter);
    layout_page->addWidget(search_group, 3,1, Qt::AlignCenter);
    layout_page->addWidget(edit_group, 1,3, Qt::AlignCenter);
    layout_page->addWidget(navigation_group, 3,3, Qt::AlignCenter);

    setLayout(layout_page);

    //изменить размер окна
}
void App_page::set_app_page_visible(bool flag){
    tabel->setVisible(flag);
    delete_button->setVisible(flag);
    search_combo_box->setVisible(flag);
    search_edit->setVisible(flag);
    search_button->setVisible(flag);
    name_label->setVisible(flag);
    name_edit->setVisible(flag);
    director_label->setVisible(flag);
    director_combo_box->setVisible(flag);
    director_edit->setVisible(flag);
    genre_label->setVisible(flag);
    genre_edit->setVisible(flag);
    data_label->setVisible(flag);
    data_slider->setVisible(flag);
    rating_label->setVisible(flag);
    rating_spin_box->setVisible(flag);
    status_label->setVisible(flag);
    status_combo_box->setVisible(flag);
    back_button->setVisible(flag);
}
