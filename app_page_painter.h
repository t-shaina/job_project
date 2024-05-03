#ifndef APP_PAGE_PAINTER_H
#define APP_PAGE_PAINTER_H

#include "billet_widget.h"
#include "combo_box.h"
#include "text_edit.h"
#include "line_edit.h"
#include "spin_box.h"
#include "push_button.h"
#include "films_table_view.h"

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QTableWidget>
#include <QGroupBox>
#include <QComboBox>
#include <QScrollArea>
#include <QScrollBar>
#include <QSlider>
#include <QSpinBox>
#include <QStringList>
#include <QStandardItemModel>
#include <QStandardItem>

class App_page_painter : public QWidget{
    Q_OBJECT

public:

    App_page_painter(QWidget* parent = nullptr);
    ~App_page_painter();

    QStringList* directors_list;
    QStringList* row_to_update;
    QModelIndex update_model_index;
    PushButton* delete_button;
    PushButton* show_all_button;
    QLineEdit* search_edit;
    PushButton* search_button;
    TextEdit* name_edit;
    QLabel* name_invalid_symbol_label;
    EditComboBox* director_combo_box;
    QList<QSharedPointer<Billet_widget>>* genre_billet_widgets;
    QLabel* director_invalid_symbol_label;
    QList<QSharedPointer<Billet_widget>>* director_billet_widgets;
    LineEdit* date_edit;
    QLabel* date_invalid_symbol_label;
    SpinBox* rating_spin_box;
    ComboBox* status_combo_box;
    PushButton* accept_button;
    PushButton* back_button;
    FilmsTableView* table;
    bool redact_transfer_state;


private:

    QGridLayout* layout_page;
    QGroupBox* table_group;
    QGroupBox* delete_sort_group;
    QGroupBox* sort_group;
    QGroupBox* search_group;
    QGroupBox* settings_group;
    QGroupBox* edit_group;
    QGroupBox* navigation_group;
    QGroupBox* name_group;
    QGroupBox* director_group;
    QGroupBox* genre_group;
    QGroupBox* date_group;
    QGroupBox* clear_group;
    PushButton* redact_button;
    QLabel* sort_label;
    ComboBox* sort_combo_box;
    PushButton* sort_button;
    QLabel* name_label;
    QLabel* director_label;
    PushButton* director_add_button;
    QScrollArea* director_scroll;
    QGroupBox* director_scroll_group;
    QLabel* genre_label;
    ComboBox* genre_combo_box;
    QScrollArea* genre_scroll;
    QGroupBox* genre_scroll_group;
    QLabel* date_label;
    QSlider* date_slider;
    QLabel* rating_label;
    QLabel* status_label;
    PushButton* clear_button;

    QVBoxLayout* table_group_layout;
    QHBoxLayout* delete_sort_group_layout;
    QHBoxLayout* sort_group_layout;
    QHBoxLayout* search_group_layout;
    QHBoxLayout* navigation_group_layout;
    QVBoxLayout* settings_group_layout;
    QGridLayout* edit_group_layout;
    QVBoxLayout* name_group_layout;
    QVBoxLayout* director_group_layout;
    QVBoxLayout* director_scroll_layout;
    QVBoxLayout* genre_group_layout;
    QVBoxLayout* genre_scroll_layout;
    QVBoxLayout* date_group_layout;
    QHBoxLayout* clear_group_layout;

private:

    App_page_painter(App_page_painter const& other)             = delete;
    App_page_painter& operator=(App_page_painter const& other)  = delete;
    App_page_painter(App_page_painter&& other)                  = delete;
    App_page_painter& operator=(App_page_painter&& other)       = delete;
    void base_settings();
    void main_buttons_settings(int w, int h);
    void main_scroll_group_settings(QScrollArea* scroll, QWidget* group, QLayout* layout);
    void set_field_of_combo_box_enabled(QComboBox* combo_box, const QString& text, bool enabled);
    void set_combo_box_enabled(QComboBox* combo_box, QList<QSharedPointer<Billet_widget>>* list, bool enabled);
    bool is_field_of_combo_box_enabled(QComboBox* combo_box, const QString& text);
    QStringList string_to_list(const QString& field);

public:

    void main_table_settings();
    QString widgets_list_to_string(QList<QSharedPointer<Billet_widget>>* list);
    void set_all_combo_box_enabled(bool enabled);
    void filling_in_director_combo_box(QJsonArray directors);

private slots:

    void set_search_edit(int search_id);
    void set_date_edit(int data_value);
    void set_date_slider_position();
    void set_director_scroll(int director_id);
    void set_genre_scroll(int genre_id);
    void set_scroll(QComboBox* combo_box, QGroupBox* group, const QString& text, QList<QSharedPointer<Billet_widget>>* list);
    void on_search_edit_edited();
    void on_name_director_genre_data_edit_changed();
    bool is_data_input_complete();
    void on_name_edit_changed();
    void on_director_combo_box_text_changed();
    void on_widget_was_deleted(const QString& text);
    void on_redact_button_clicked();
    void on_sort_button_clicked();
    void on_director_add_button_clicked();
    void on_clear_button_clicked();
    void on_table_row_selected(QModelIndex index);

    //switches for redact widgets

    void set_focus_to(QWidget* widget);
    void set_focus_to(ComboBox* widget);
    inline void set_focus_to_search_edit(){ search_edit->setFocus();}
    inline void set_focus_to_name_edit(){ name_edit->setFocus();}
    inline void set_focus_to_director_combo_box(){ director_combo_box->setFocus();}
    inline void set_focus_to_genre_combo_box(){ genre_combo_box->setFocus();}
    inline void set_focus_to_sort_combo_box(){ sort_combo_box->setFocus();}
    //void set_focus_to_genre_combo_box_item();
    inline void set_focus_to_date_edit(){ date_edit->setFocus();}
    inline void set_focus_to_rating_spin_box(){ rating_spin_box->setFocus();}
    inline void set_focus_to_status_combo_box(){ status_combo_box->setFocus();}

    //switches for buttons

    inline void set_focus_to_delete_button(){delete_button->setFocus();}
    inline void set_focus_to_redact_button(){redact_button->setFocus();}
    inline void set_focus_to_show_all_button(){show_all_button->setFocus();}
    inline void set_focus_to_sort_button(){sort_button->setFocus();}
    inline void set_focus_to_search_button(){search_button->setFocus();}
    inline void set_focus_to_accept_button(){ accept_button->setFocus();}
    inline void set_focus_to_clear_button(){clear_button->setFocus();}
    inline void set_focus_to_back_button(){ back_button->setFocus();}

    //switches for table

    inline void set_focus_to_table(){ table->setFocus();}
    void on_table_down_pressed();

signals:

    void genre_scroll_was_changed();
    void director_scroll_was_changed();
};

#endif // APP_PAGE_PAINTER_H
