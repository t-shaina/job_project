#ifndef APP_PAGE_PAINTER_H
#define APP_PAGE_PAINTER_H

#include"billet_widget.h"
#include <QObject>
#include <QWidget>
#include<QGridLayout>
#include<QLineEdit>
#include<QTextEdit>
#include<QLabel>
#include<QPushButton>
#include<QRadioButton>
#include<QCheckBox>
#include<QTableWidget>
#include<QGroupBox>
#include<QComboBox>
#include<QScrollArea>
#include<QScrollBar>
#include <QSlider>
#include<QSpinBox>
#include<QStringList>
#include<QStandardItemModel>
#include<QStandardItem>
class App_page_painter:public QWidget
{
    Q_OBJECT
public:
    App_page_painter(QWidget* parent=nullptr);
    ~App_page_painter();
    QStringList* directors_list;
    QStringList* row_to_update;
    QModelIndex update_model_index;
    QPushButton* delete_button;
    QPushButton* show_all_button;
    QLineEdit* search_edit;
    QPushButton* search_button;
    QTextEdit* name_edit;
    QLabel* name_invalid_symbol_label;
    QComboBox* director_combo_box;
    QList<QSharedPointer<Billet_widget>>* genre_billet_widgets;
    QLabel* director_invalid_symbol_label;
    QList<QSharedPointer<Billet_widget>>* director_billet_widgets;
    QLineEdit* date_edit;
    QLabel* date_invalid_symbol_label;
    QSpinBox* rating_spin_box;
    QComboBox* status_combo_box;
    QPushButton* accept_button;
    QPushButton* back_button;
    QTableView* table;
    bool redact_transfer_state;


    void main_table_settings();
    QString widgets_list_to_string(QList<QSharedPointer<Billet_widget>>* list);
    void set_all_combo_box_enabled(bool enabled);

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
    QPushButton* redact_button;
    QLabel* sort_label;
    QComboBox* sort_combo_box;
    QPushButton* sort_button;
    QLabel* name_label;

    QLabel* director_label;
    QPushButton* director_add_button;
    QScrollArea* director_scroll;
    QGroupBox* director_scroll_group;
    QLabel* genre_label;
    QComboBox* genre_combo_box;
    QScrollArea* genre_scroll;
    QGroupBox* genre_scroll_group;

    QLabel* date_label;
    QSlider* date_slider;
    QLabel* rating_label;
    QLabel* status_label;
    QPushButton* clear_button;

private:
    void base_settings();
    void main_buttons_settings(int w, int h);

    void main_scroll_group_settings(QScrollArea* scroll, QWidget* group, QLayout* layout);
    void set_field_of_combo_box_enabled(QComboBox* combo_box, QString text, bool enabled);
    void set_combo_box_enabled(QComboBox* combo_box, QList<QSharedPointer<Billet_widget>>* list, bool enabled);
    bool is_field_of_combo_box_enabled(QComboBox* combo_box, QString text);



private slots:
    void set_search_edit(int search_id);//переименовать
    void set_date_edit(int data_value);
    void set_date_slider_position();
    void set_director_scroll(int director_id);
    void set_genre_scroll(int genre_id);
    void set_scroll(QComboBox* combo_box, QGroupBox* group, const QString& text, QList<QSharedPointer<Billet_widget>>* list);
    void on_search_edit_edited();
    void on_name_director_genre_data_edit_changed();
    void on_name_edit_changed();
    void on_director_combo_box_text_changed();
    void on_widget_was_deleted(QString text);

    void on_redact_button_clicked();
    void on_sort_button_clicked();
    void on_director_add_button_clicked();
    void on_clear_button_clicked();

    void on_table_row_selected(QModelIndex index);
signals:
    void genre_scroll_was_changed();
    void director_scroll_was_changed();
};

#endif // APP_PAGE_PAINTER_H
