#include "app_page_painter.h"
#include "billet_widget.h"
#include "symbols_inspector.h"

#include <QCommonStyle>
#include <QDate>
#include <QHeaderView>
#include <QJsonArray>

const int width_window           = 1280;
const int height_window          = 800;
const int l_margin               = 10;
const int t_margin               = 30;
const int r_margin               = 10;
const int b_margin               = 30;
const int inside_margin          = 10;
const int inside_spacing         = 10;
const int v_spacing              = 30;
const int h_spacing              = 30;
const int edit_group_v_spacing   = 20;
const int navigation_group_hight = 50;
const int table_magrin           = 5;
const int main_buttons_width     = 100;
const int main_buttons_height    = 30;

const QStringList genre_list = QStringList() << "Комедия"
                                             << "Мелодрама"
                                             << "Мультфильм"
                                             << "Ужасы"
                                             << "Фантастика"
                                             << "Триллер"
                                             << "Боевик"
                                             << "Детектив"
                                             << "Фентези"
                                             << "Исторический"
                                             << "Драма"
                                             << "Документальный"
                                             << "Криминал"
                                             << "Биография"
                                             << "Вестерн"
                                             << "Мюзиклы"
                                             << "Короткометражка";

const QStringList headers = QStringList() << "Название"
                                          << "Режиссер"
                                          << "Жанр"
                                          << "Год"
                                          << "Рейтинг"
                                          << "Статус";
const QStringList sort_list = QStringList() << "Год"
                                            << "Рейтинг"
                                            << "Статус";
const QStringList status_list = QStringList() << "Просмотрено"
                                              << "Буду смотреть"
                                              << "Не рекомендую";


App_page_painter::App_page_painter(QWidget* parent)
    :QWidget(parent),
    directors_list               (new QStringList()),
    row_to_update                (new QStringList()),
    delete_button                (new PushButton("Удалить", this)),
    show_all_button              (new PushButton("Показать все", this)),
    search_edit                  (new LineEdit(this)),
    search_button                (new PushButton("Поиск", this)),
    name_edit                    (new TextEdit(this)),
    name_invalid_symbol_label    (new QLabel("Введен недопустимый символ",this)),
    director_combo_box           (new EditComboBox(this)),
    genre_billet_widgets         (new QList<QSharedPointer<Billet_widget>>),
    director_invalid_symbol_label(new QLabel("Введен недопустимый символ",this)),
    director_billet_widgets      (new QList<QSharedPointer<Billet_widget>>),
    date_edit                    (new LineEdit(this)),
    date_invalid_symbol_label    (new QLabel("Введен недопустимый символ",this)),
    rating_spin_box              (new SpinBox(this)),
    status_combo_box             (new ComboBox(this)),
    accept_button                (new PushButton("Добавить", this)),
    back_button                  (new PushButton("Выйти", this)),
    table                        (new FilmsTableView(this)),
    redact_transfer_state        (false),

    layout_page                  (new QGridLayout(this)),
    table_group                  (new QGroupBox(this)),
    delete_sort_group            (new QGroupBox(table_group)),
    sort_group                   (new QGroupBox(delete_sort_group)),
    search_group                 (new QGroupBox(this)),
    settings_group               (new QGroupBox(this)),
    edit_group                   (new QGroupBox(this)),
    navigation_group             (new QGroupBox(this)),
    name_group                   (new QGroupBox(edit_group)),
    director_group               (new QGroupBox(edit_group)),
    genre_group                  (new QGroupBox(edit_group)),
    date_group                   (new QGroupBox(edit_group)),
    clear_group                  (new QGroupBox(this)),
    redact_button                (new PushButton("Редактировать", this)),
    sort_label                   (new QLabel("Сортировать по", this)),
    sort_combo_box               (new ComboBox(this)),
    sort_button                  (new PushButton("Сортировать",this)),
    name_label                   (new QLabel("Название", this)),
    director_label               (new QLabel("Режиссер", this)),

    director_add_button          (new PushButton(this)),
    director_scroll              (new QScrollArea(this)),
    director_scroll_group        (new QGroupBox(director_scroll)),
    genre_label                  (new QLabel("Жанр", this)),
    genre_scroll                 (new QScrollArea(this)),
    genre_scroll_group           (new QGroupBox(genre_scroll)),
    genre_combo_box              (new ComboBox(this)),
    date_label                   (new QLabel("Год создания", this)),
    date_slider                  (new QSlider(this)),
    rating_label                 (new QLabel("Рейтинг", this)),
    status_label                 (new QLabel("Статус", this)),
    clear_button                 (new PushButton("Очистить", this)){

    // тело конструктора начинается здесь

    /*QVBoxLayout* */ table_group_layout       = new QVBoxLayout();
    /*QHBoxLayout* */ delete_sort_group_layout = new QHBoxLayout();
    /*QHBoxLayout* */ sort_group_layout        = new QHBoxLayout();
    /*QHBoxLayout* */ search_group_layout      = new QHBoxLayout();
    /*QHBoxLayout* */ navigation_group_layout  = new QHBoxLayout();
    /*QVBoxLayout* */ settings_group_layout    = new QVBoxLayout();
    /*QGridLayout* */ edit_group_layout        = new QGridLayout();
    /*QVBoxLayout* */ name_group_layout        = new QVBoxLayout();
    /*QVBoxLayout* */ director_group_layout    = new QVBoxLayout();
    /*QVBoxLayout* */ director_scroll_layout   = new QVBoxLayout();
    /*QVBoxLayout* */ genre_group_layout       = new QVBoxLayout();
    /*QVBoxLayout* */ genre_scroll_layout      = new QVBoxLayout();
    /*QVBoxLayout* */ date_group_layout        = new QVBoxLayout();
    /*QHBoxLayout* */ clear_group_layout       = new QHBoxLayout();

    table_group_layout->addWidget(table);
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
    edit_group_layout->addWidget(name_label, 0,0, Qt::AlignLeft | Qt::AlignTop);
    edit_group_layout->addWidget(name_group, 0,1, Qt::AlignCenter | Qt::AlignTop);
    edit_group_layout->addWidget(director_label, 1,0, Qt::AlignLeft | Qt::AlignTop);
    edit_group_layout->addWidget(director_group, 1,1, Qt::AlignCenter | Qt::AlignTop);
    edit_group_layout->addWidget(genre_label, 2,0, Qt::AlignLeft | Qt::AlignTop);
    edit_group_layout->addWidget(genre_group, 2,1, Qt::AlignCenter | Qt::AlignTop);
    edit_group_layout->addWidget(date_label, 3,0, Qt::AlignLeft | Qt::AlignTop);
    edit_group_layout->addWidget(date_group, 3,1, Qt::AlignCenter | Qt::AlignTop);
    edit_group_layout->addWidget(rating_label, 4,0, Qt::AlignLeft | Qt::AlignTop);
    edit_group_layout->addWidget(rating_spin_box, 4,1, Qt::AlignCenter | Qt::AlignTop);
    edit_group_layout->addWidget(status_label, 5,0, Qt::AlignLeft | Qt::AlignTop);
    edit_group_layout->addWidget(status_combo_box, 5,1, Qt::AlignCenter | Qt::AlignTop);

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

    layout_page->addWidget(table_group, 0,0, Qt::AlignLeft | Qt::AlignTop);
    layout_page->addWidget(search_group, 1,0, Qt::AlignLeft | Qt::AlignBottom);
    layout_page->addWidget(settings_group, 0,1, Qt::AlignRight | Qt::AlignTop);
    layout_page->addWidget(navigation_group, 1,1, Qt::AlignRight | Qt::AlignBottom);

    setLayout(layout_page);
    this->show();
    this->resize(width_window,height_window);
    this->setMaximumHeight(height_window);
    this->setMaximumWidth(width_window);
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
    edit_group_layout->setColumnMinimumWidth(1, (width_window-l_margin - r_margin - v_spacing) * 0.15);

    main_scroll_group_settings(director_scroll, director_scroll_group, director_scroll_layout);
    main_scroll_group_settings(genre_scroll, genre_scroll_group, genre_scroll_layout);

    base_settings();
    set_focus_to_show_all_button();
    connect(redact_button, SIGNAL(clicked()), this, SLOT(on_redact_button_clicked()));
    connect(sort_button, SIGNAL(clicked()), this, SLOT(on_sort_button_clicked()));
    connect(director_add_button, SIGNAL(clicked()), this, SLOT(on_director_add_button_clicked()));
    connect(clear_button, SIGNAL(clicked()), this, SLOT(on_clear_button_clicked()));

    connect(table, SIGNAL(clicked(QModelIndex)), this, SLOT(on_table_row_selected(QModelIndex)));

    connect(genre_combo_box, SIGNAL(activated(int)), this, SLOT(set_genre_scroll(int)));
    connect(director_combo_box, SIGNAL(activated(int)), this, SLOT(set_director_scroll(int)));
    connect(date_slider, SIGNAL(valueChanged(int)), this, SLOT(set_date_edit(int)));

    connect(search_edit, SIGNAL(textEdited(QString)), this, SLOT(on_search_edit_edited()));
    connect(name_edit, SIGNAL(textChanged()), this, SLOT(on_name_director_genre_data_edit_changed()));
    QObject::connect(this, SIGNAL( director_scroll_was_changed()), this, SLOT(on_name_director_genre_data_edit_changed()));
    QObject::connect(this, SIGNAL(genre_scroll_was_changed()), this, SLOT(on_name_director_genre_data_edit_changed()));
    connect(director_combo_box, SIGNAL(editTextChanged(QString)), this, SLOT(on_director_combo_box_text_changed()));
    connect(date_edit, SIGNAL(textChanged(QString)), this, SLOT(on_name_director_genre_data_edit_changed()));
    connect(date_edit, SIGNAL(textEdited(QString)), this, SLOT(set_date_slider_position()));

    //switches for redact widgets

    connect(search_edit, SIGNAL(right_pressed()), this, SLOT(set_focus_to_search_button()));
    connect(search_edit, SIGNAL(up_pressed()), this, SLOT(set_focus_to_show_all_button()));
    connect(name_edit, SIGNAL(down_pressed()), this, SLOT(set_focus_to_director_combo_box()));
    connect(director_combo_box, SIGNAL(return_pressed()), this, SLOT(on_director_add_button_clicked()));
    connect(director_combo_box, SIGNAL(down_pressed()), this, SLOT(set_focus_to_genre_combo_box()));
    connect(director_combo_box, SIGNAL(up_pressed()), this, SLOT(set_focus_to_name_edit()));
    //connect(director_combo_box, SIGNAL(right_pressed()), this, SLOT(set_focus_to_genre_combo_box_item()));
    connect(genre_combo_box, SIGNAL(down_pressed()), this, SLOT(set_focus_to_date_edit()));
    connect(genre_combo_box, SIGNAL(up_pressed()), this, SLOT(set_focus_to_director_combo_box()));
    connect(rating_spin_box, SIGNAL(down_pressed()), this, SLOT(set_focus_to_status_combo_box()));
    connect(rating_spin_box, SIGNAL(up_pressed()), this, SLOT(set_focus_to_date_edit()));
    connect(date_edit, SIGNAL(down_pressed()), this, SLOT(set_focus_to_rating_spin_box()));
    connect(date_edit, SIGNAL(up_pressed()), this, SLOT(set_focus_to_genre_combo_box()));
    connect(status_combo_box, SIGNAL(down_pressed()), this, SLOT(set_focus_to_accept_button()));
    connect(status_combo_box, SIGNAL(up_pressed()), this, SLOT(set_focus_to_rating_spin_box()));
    //switches for buttons
    connect(delete_button, SIGNAL(down_pressed()), this, SLOT(set_focus_to_search_edit()));
    connect(delete_button, SIGNAL(right_pressed()), this, SLOT(set_focus_to_redact_button()));
    connect(delete_button, SIGNAL(up_pressed()), this, SLOT(set_focus_to_table()));
    connect(redact_button, SIGNAL(down_pressed()), this, SLOT(set_focus_to_search_edit()));
    connect(redact_button, SIGNAL(right_pressed()), this, SLOT(set_focus_to_show_all_button()));
    connect(redact_button, SIGNAL(left_pressed()), this, SLOT(set_focus_to_delete_button()));
    connect(redact_button, SIGNAL(enter_pressed()), this, SLOT(on_redact_button_clicked()));
    connect(redact_button, SIGNAL(up_pressed()), this, SLOT(set_focus_to_table()));
    connect(show_all_button, SIGNAL(down_pressed()), this, SLOT(set_focus_to_search_edit()));
    connect(show_all_button, SIGNAL(right_pressed()), this, SLOT(set_focus_to_sort_combo_box()));
    connect(show_all_button, SIGNAL(left_pressed()), this, SLOT(set_focus_to_redact_button()));
    connect(show_all_button, SIGNAL(up_pressed()), this, SLOT(set_focus_to_table()));
    connect(sort_button, SIGNAL(down_pressed()), this, SLOT(set_focus_to_search_edit()));
    connect(sort_button, SIGNAL(right_pressed()), this, SLOT(set_focus_to_accept_button()));
    connect(sort_button, SIGNAL(left_pressed()), this, SLOT(set_focus_to_sort_combo_box()));
    connect(sort_button, SIGNAL(enter_pressed()), this, SLOT(on_sort_button_clicked()));
    connect(sort_button, SIGNAL(up_pressed()), this, SLOT(set_focus_to_table()));
    connect(search_button, SIGNAL(right_pressed()), this, SLOT(set_focus_to_back_button()));
    connect(director_add_button, SIGNAL(enter_pressed()), this, SLOT(on_director_add_button_clicked()));
    connect(accept_button, SIGNAL(down_pressed()), this, SLOT(set_focus_to_back_button()));
    connect(accept_button, SIGNAL(right_pressed()), this, SLOT(set_focus_to_clear_button()));
    connect(accept_button, SIGNAL(left_pressed()), this, SLOT(set_focus_to_sort_button()));
    connect(clear_button, SIGNAL(down_pressed()), this, SLOT(set_focus_to_back_button()));
    connect(clear_button, SIGNAL(left_pressed()), this, SLOT(set_focus_to_accept_button()));
    connect(clear_button, SIGNAL(enter_pressed()), this, SLOT(on_clear_button_clicked()));
    connect(back_button, SIGNAL(left_pressed()), this, SLOT(set_focus_to_search_edit()));
    connect(back_button, SIGNAL(up_pressed()), this, SLOT(set_focus_to_accept_button()));

    //switches for table

    connect(table, SIGNAL(down_pressed()), this, SLOT(on_table_down_pressed()));
    connect(table, SIGNAL(update_action()),this, SLOT(on_redact_button_clicked()));

    //switches for sort_combo_box

    connect(sort_combo_box, SIGNAL(right_pressed()), this, SLOT(set_focus_to_sort_button()));
    connect(sort_combo_box, SIGNAL(left_pressed()), this, SLOT(set_focus_to_show_all_button()));
    connect(sort_combo_box, SIGNAL(down_pressed()), this, SLOT(set_focus_to_search_edit()));
    connect(sort_combo_box, SIGNAL(up_pressed()), this, SLOT(set_focus_to_table()));


}
App_page_painter::~App_page_painter(){
    delete directors_list;
    delete row_to_update;
    delete genre_billet_widgets;
    delete director_billet_widgets;
    delete delete_button;
    delete show_all_button;
    delete search_button;
    delete name_edit;
    delete director_combo_box;;
    delete date_edit;
    delete  rating_spin_box;
    delete status_combo_box;
    delete accept_button;
    delete back_button;
    delete table;

}

void App_page_painter::set_search_edit(int search_id){

}
QStringList App_page_painter::string_to_list(const QString& field){
    QString string = field;
    QStringList list;
    string.push_back(',');
    QString word;
    for (int i = 0; i < string.size(); ++i){
        if (string.at(i) == ','){
            i++;
            list.push_back(word);
            word.clear();
        }
        else word += string.at(i);
    }
    return list;
}

void App_page_painter::set_date_edit(int data_value){
    QString text = QString::number(data_value);
    date_edit->setText(text);
}

void App_page_painter::set_director_scroll(int director_id){
    QString text = directors_list->at(director_id);
    set_scroll(director_combo_box, director_scroll_group, text, director_billet_widgets);
    emit director_scroll_was_changed();    
}

void App_page_painter::set_genre_scroll(int genre_id){
    QString text = genre_list.at(genre_id);
    set_scroll(genre_combo_box, genre_scroll_group, text, genre_billet_widgets);
    emit genre_scroll_was_changed();
}

void App_page_painter::set_scroll(QComboBox* combo_box, QGroupBox* group, const QString& text, QList<QSharedPointer<Billet_widget>>* list){
    Symbols_inspector symbols_inspector;
    QString text_without_extra_symbols = symbols_inspector.removing_extra_symbols(text);
    if (is_field_of_combo_box_enabled(combo_box, text_without_extra_symbols)){
        this->set_field_of_combo_box_enabled(combo_box, text_without_extra_symbols, false);
        Billet_widget* widget = new Billet_widget(group, text_without_extra_symbols);
        QSharedPointer<Billet_widget> widget_ptr(widget, &QObject::deleteLater);
        group->layout()->addWidget(widget_ptr.get());
        list->push_back(widget_ptr);
        QObject::connect(widget, SIGNAL(widget_was_deleted(QString)), this, SLOT(on_widget_was_deleted(QString)));
    }
}

void App_page_painter::set_date_slider_position(){
    int year = date_edit->text().toInt();
    int current_year = QDate().currentDate().year();
    if (year <= current_year)
        date_slider->setSliderPosition(year);
    else date_slider->setSliderPosition(current_year);
}

void App_page_painter::on_widget_was_deleted(const QString& text){
    Symbols_inspector symbols_inspector;
    QString text_without_extra_symbols = symbols_inspector.removing_extra_symbols(text);
    Billet_widget* widget = static_cast<Billet_widget*>(sender());
    QGroupBox* parent = qobject_cast<QGroupBox*>(widget->parent());
    QSharedPointer<Billet_widget> widget_ptr = static_cast<QSharedPointer<Billet_widget>>(widget);
    if (parent == genre_scroll_group){
        genre_billet_widgets->removeOne(widget_ptr);
        set_field_of_combo_box_enabled(genre_combo_box, text_without_extra_symbols, true);
        emit genre_scroll_was_changed();
    }
    else {
        director_billet_widgets->removeOne(widget_ptr);
        set_field_of_combo_box_enabled(director_combo_box, text_without_extra_symbols, true);
        emit director_scroll_was_changed();
    }
}

void App_page_painter::set_field_of_combo_box_enabled(QComboBox* combo_box, const QString& text, bool enabled){
    QStandardItemModel* model = static_cast<QStandardItemModel*>(combo_box->model());
    QList<QStandardItem*> items = model->findItems(text);
    for (QStandardItem* item : items){
        item->setEnabled(enabled);
    }
}

void App_page_painter::set_combo_box_enabled(QComboBox* combo_box, QList<QSharedPointer<Billet_widget>>* list, bool enabled){
    QSharedPointer<Billet_widget> widget_ptr;
    foreach(widget_ptr, *list){
        this->set_field_of_combo_box_enabled(combo_box, widget_ptr->text(), enabled);
    }
}

void App_page_painter::set_all_combo_box_enabled(bool enabled){
    set_combo_box_enabled(director_combo_box, director_billet_widgets, enabled);
    set_combo_box_enabled(genre_combo_box, genre_billet_widgets, enabled);
}

void App_page_painter::filling_in_director_combo_box(QJsonArray directors){
    QString director = QString();
    for (int i = 0; i < directors.size(); i++){
        Symbols_inspector symbols_inspector;
        director = symbols_inspector.removing_last_spaces(directors.at(i).toString());
        if (!directors_list->contains(director)){
            directors_list->push_back(director);
            director_combo_box->addItem(director);
        }
    }
}

bool App_page_painter::is_field_of_combo_box_enabled(QComboBox* combo_box, const QString& text){
    bool status = true;
    Symbols_inspector symbols_inspector;
    QString text_without_extra_symbols = symbols_inspector.removing_extra_symbols(text);
    QStandardItemModel* model = static_cast<QStandardItemModel*>(combo_box->model());
    QList<QStandardItem*> items = model->findItems(text_without_extra_symbols);
    foreach (QStandardItem* item, items) {
        if (!item->isEnabled()){
            status = false;
        }
    }
    return status;
}

void App_page_painter::on_sort_button_clicked(){
    int sort_id = sort_combo_box->currentIndex();
    QStandardItemModel* model = static_cast<QStandardItemModel*>(table->model());
    model->sort(sort_id + 3, Qt::AscendingOrder);
}

void App_page_painter::on_redact_button_clicked(){
    row_to_update->clear();
    QStandardItemModel* model = static_cast<QStandardItemModel*>(table->model());
    QItemSelectionModel* select_model = table->selectionModel();
    QModelIndex index = select_model->currentIndex();
    int row = index.row();
    update_model_index = index;
    Symbols_inspector symbols_inspector;
    for(int i = 0; i < model->columnCount(); i++){
        QModelIndex column_index = model->index(row, i);
        this->row_to_update->push_back(column_index.data().toString());
        qDebug() << "on redact button clicked row to update is" << column_index.data();
    }
    this->set_all_combo_box_enabled(true);
    genre_billet_widgets->clear();
    director_billet_widgets->clear();
    QString directors=row_to_update->at(1);
    QStringList directors_list = string_to_list(directors);
    for(int i = 0; i < directors_list.size(); ++i){
        set_scroll(director_combo_box, director_scroll_group, directors_list.at(i), director_billet_widgets);
    }
    emit director_scroll_was_changed();
    QString genres = row_to_update->at(2);
    QStringList genres_list = string_to_list(genres);
    for(int i = 0; i < genres_list.size(); ++i){
        set_scroll(genre_combo_box, genre_scroll_group, genres_list.at(i), genre_billet_widgets);
    }
    emit genre_scroll_was_changed();   
    redact_transfer_state = true;
    name_invalid_symbol_label->setVisible(false);
    name_edit->setText(row_to_update->at(0));
    director_invalid_symbol_label->setVisible(false);
    date_slider->setSliderPosition(row_to_update->at(3).toInt());
    date_invalid_symbol_label->setVisible(false);
    rating_spin_box->setValue(row_to_update->at(4).toInt());
    status_combo_box->setPlaceholderText(row_to_update->at(5));
    accept_button->setText("Обновить");
}
void App_page_painter::on_director_add_button_clicked(){
    QRegularExpression directors_r_expr("([^a-zа-яё\\d\\.\\-\\s]+)", QRegularExpression::CaseInsensitiveOption);
    Symbols_inspector symbols_inspector = Symbols_inspector();
    bool status = symbols_inspector.finding_invalid_symbols(director_combo_box, directors_r_expr);
    if (status){
        director_invalid_symbol_label->setVisible(true);
    }
    else {
        QString text = symbols_inspector.removing_extra_symbols(director_combo_box->currentText());
        symbols_inspector.set_uppercase(text, QRegularExpression("^([a-zа-яё]{1})|(\b[a-zа-яё]{1})", QRegularExpression::DotMatchesEverythingOption));
        if (!directors_list->contains(text)){
            *directors_list << text;
            director_combo_box->addItem(text);
        }
        set_scroll(director_combo_box, director_scroll_group, text, director_billet_widgets);
        director_combo_box->setEditText("");
    }
}

void App_page_painter::on_clear_button_clicked(){
    this->set_all_combo_box_enabled(true);
    update_model_index = QModelIndex(); //имеется ввиду сброс индекса  установкой недопустимного индекса
    name_invalid_symbol_label->setVisible(false);
    name_edit->clear();
    director_invalid_symbol_label->setVisible(false);
    director_billet_widgets->clear();
    genre_billet_widgets->clear();
    date_invalid_symbol_label->setVisible(false);
    redact_transfer_state = false;
    accept_button->setText("Добавить");
    emit genre_scroll_was_changed();
    emit director_scroll_was_changed();
}

void App_page_painter::on_table_row_selected(QModelIndex index){
    delete_button->setEnabled(true);
    redact_button->setEnabled(true);   
}

void App_page_painter::on_director_combo_box_text_changed(){
    if (director_combo_box->currentText().isEmpty()){
        director_add_button->setEnabled(false);
    }
    else {
        director_add_button->setEnabled(true);
    }
}

QString App_page_painter::widgets_list_to_string(QList<QSharedPointer<Billet_widget>>* list){
    QString widgets_string;
    int size = list->size();
    for(int i = 0; i < size - 1; i++){
        widgets_string += list->at(i)->text();
        widgets_string += " ";
    }
    widgets_string += list->at(size-1)->text();
    return widgets_string;
}

void App_page_painter::on_search_edit_edited(){
    if (search_edit->text().isEmpty())
        search_button->setEnabled(false);
    else search_button->setEnabled(true);
}

void App_page_painter::on_name_director_genre_data_edit_changed(){
    QTextEdit* sender_;
    if (sender_ == qobject_cast<QTextEdit*>(sender())){
        name_invalid_symbol_label->setVisible(false);
        director_invalid_symbol_label->setVisible(false);
    }
    if (name_edit->toPlainText().isEmpty()        ||
        director_billet_widgets->size()    == 0   ||
        genre_billet_widgets->size()       == 0   ||
        date_edit->text().isEmpty()){

        accept_button->setEnabled(false);
        clear_button->setEnabled(false);
    }
    else {
        accept_button->setEnabled(true);
        clear_button->setEnabled(true);
    }

}
bool App_page_painter::is_data_input_complete(){
    if (name_edit->toPlainText().isEmpty()        ||
        director_billet_widgets->size()    == 0   ||
        genre_billet_widgets->size()       == 0   ||
        date_edit->text().isEmpty()               ||
        rating_spin_box->cleanText()       == "0" ||
        status_combo_box->currentText()    == "Просмотрено"){
        return false;
    }
    else return true;
}
void App_page_painter::on_name_edit_changed(){
    QSize text_size = name_edit->fontMetrics().size(Qt::TextWordWrap, name_edit->placeholderText());
    if (text_size.width() > name_edit->width())
        name_edit->setMinimumHeight(text_size.height()*text_size.width() / name_edit->width());
}

void App_page_painter::set_focus_to(QWidget* widget){
    widget->setFocus();
}

void App_page_painter::set_focus_to(ComboBox* widget){
    widget->setFocus();
}

/*void App_page_painter::set_focus_to_genre_combo_box_item(){
    //QStandardItemModel* model=static_cast<QStandardItemModel*>(genre_combo_box->model());
    //genre_combo_box->rootModelIndex().setFocus();

}*/

void App_page_painter::base_settings(){
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
    delete_sort_group->setFixedHeight(navigation_group_hight);
    sort_group->setFixedWidth((width_window-l_margin-r_margin-v_spacing)*0.7*0.5);
    settings_group->setMinimumSize((width_window-l_margin-r_margin-v_spacing)*0.3, (height_window-t_margin-b_margin-h_spacing)-navigation_group_hight);
    search_group->setMinimumSize((width_window-l_margin-r_margin-v_spacing)*0.7, navigation_group_hight);
    navigation_group->setMinimumSize((width_window-l_margin-r_margin-v_spacing)*0.3, navigation_group_hight);
    name_invalid_symbol_label->setMinimumSize((width_window-l_margin-r_margin-v_spacing)*0.15, 20);
    director_invalid_symbol_label->setMinimumSize((width_window-l_margin-r_margin-v_spacing)*0.15, 20);
    director_group->setMinimumWidth((width_window-l_margin-r_margin-v_spacing)*0.15);
    genre_group->setMinimumWidth((width_window-l_margin-r_margin-v_spacing)*0.15);
    date_group->setMinimumWidth((width_window-l_margin-r_margin-v_spacing)*0.15);
    clear_group->setMinimumHeight(delete_sort_group->height());
    name_edit->setMinimumWidth((width_window-l_margin-r_margin-v_spacing)*0.15);
    name_edit->setMaximumHeight(100);
    date_edit->setFixedWidth((date_group->width())*0.25);
    date_edit->setAlignment(Qt::AlignCenter);
    rating_spin_box->setMinimumWidth((width_window-l_margin-r_margin-v_spacing)*0.06);
    status_combo_box->setMinimumWidth((width_window-l_margin-r_margin-v_spacing)*0.16);

    name_invalid_symbol_label->setVisible(false);
    name_invalid_symbol_label->setStyleSheet("color: darkCyan; font-size: 12px");
    director_invalid_symbol_label->setVisible(false);
    director_invalid_symbol_label->setStyleSheet("color: darkCyan; font-size: 12px");
    date_invalid_symbol_label->setVisible(false);
    date_invalid_symbol_label->setStyleSheet("color: darkCyan; font-size: 12px");

    main_buttons_settings(main_buttons_width,main_buttons_height);
    this->main_table_settings();
    sort_combo_box->addItems(sort_list);
    QStandardItemModel* genre_model = new QStandardItemModel(genre_combo_box);
    genre_combo_box->setModel(genre_model);
    genre_combo_box->addItems(genre_list);
    QStandardItemModel* director_model = new QStandardItemModel(director_combo_box);
    director_combo_box->setModel(director_model);
    date_slider->setOrientation(Qt::Horizontal);

    date_slider->setMaximum(QDate().currentDate().year());
    date_slider->setMinimum(1895);
    date_slider->setTickInterval(10);
    date_slider->setTickPosition(QSlider::TicksAbove);
    date_slider->setPageStep(1);
    date_slider->setSingleStep(1);
    date_slider->setValue((date_slider->maximum() - 1895) / 2);
    date_slider->setEnabled(true);
    date_slider->setTracking(true);
    date_slider->setSliderDown(true);
    rating_spin_box->setRange(0, 5);
    status_combo_box->addItems(status_list);
}
void App_page_painter::main_buttons_settings(int w, int h){
    delete_button->setFixedSize(w, h);
    redact_button->setFixedSize(w + 25, h);
    show_all_button->setFixedSize(w + 15, h);
    sort_combo_box->setFixedSize(w, h);
    sort_button->setFixedSize(w + 15, h);
    search_edit->setFixedSize((width_window - l_margin - r_margin - v_spacing) * 0.6 - 2 * w - 50, h);
    search_button->setFixedSize(w, h);
    director_add_button->setFixedSize(w / 2, h);
    QCommonStyle style;
    director_add_button->setIcon(style.standardIcon(QStyle::SP_ToolBarVerticalExtensionButton /*QStyleOptionButton::*/));
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

void App_page_painter::main_table_settings(){
    table->table_settings(table_group->width());
}

void App_page_painter::main_scroll_group_settings(QScrollArea* scroll, QWidget* group, QLayout* layout){
    scroll->setWidgetResizable(false);
    scroll->setAlignment(Qt::AlignLeft);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    group->setFixedSize(scroll->width(), scroll->height());
    group->setLayout(layout);
    group->setStyleSheet("QGroupBox{border: 0px;}");
    scroll->setWidget(group);
}
void App_page_painter::on_table_down_pressed(){
    QStandardItemModel* model = static_cast<QStandardItemModel*>(table->model());
    QItemSelectionModel* select_model = table->selectionModel();
    if (model->rowCount() == (select_model->currentIndex().row() + 1)){
        set_focus_to_show_all_button();        
    }
}
