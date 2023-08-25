#ifndef APP_PAGE_H
#define APP_PAGE_H

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
#include<QSharedPointer>
#include<QVector>
class App_page:public QWidget
{
    Q_OBJECT
public:
    App_page(QWidget* parent=nullptr);
    QString email;
    QList<QSharedPointer<Billet_widget>>* genre_billet_widgets;
    QList<QSharedPointer<Billet_widget>>* director_billet_widgets;
    QStringList* directors_list;
    QStringList* row_to_update;
    QModelIndex update_model_index;
    QList<int>* delete_rows_list;
    QList<int>* update_rows_list;
private:
    bool redact_transfer_state;
    QGridLayout* layout_page;
    QGroupBox* table_group;
    //QGroupBox* scroll_table_group;
    QGroupBox* delete_sort_group;
    QGroupBox* sort_group;
    QGroupBox* search_group;
    QGroupBox* settings_group;
    QGroupBox* edit_group;
    QGroupBox* navigation_group;
    //QScrollArea* table_scroll;
    //QScrollArea* edit_scroll;
    QGroupBox* name_group;
    QGroupBox* director_group;
    QGroupBox* genre_group;
    QGroupBox* date_group;
    QGroupBox* clear_group;

    QTableView* table;
    QPushButton* delete_button;
    QPushButton* redact_button;
    QPushButton* show_all_button;
    QLabel* sort_label;
    QComboBox* sort_combo_box;
    QPushButton* sort_button;
    QLineEdit* search_edit;
    QPushButton* search_button;
    QLabel* name_label;
    QLabel* name_invalid_symbol_label;
    QTextEdit* name_edit;
    QLabel* director_label;
    QLabel* director_invalid_symbol_label;
    QComboBox* director_combo_box;
    QPushButton* director_add_button;
    QScrollArea* director_scroll;
    QGroupBox* director_scroll_group;
    //QTextEdit* director_edit;
    QLabel* genre_label;
    QComboBox* genre_combo_box;
    QScrollArea* genre_scroll;
    QGroupBox* genre_scroll_group;
    QLineEdit* date_edit;
    QLabel* date_invalid_symbol_label;
    QLabel* date_label;
    QSlider* date_slider;
    QLabel* rating_label;
    QSpinBox* rating_spin_box;
    QLabel* status_label;
    QComboBox* status_combo_box;
    QPushButton* accept_button;
    QPushButton* clear_button;
    QPushButton* back_button;

    void base_settings();
    void main_buttons_settings(int w, int h);
    void main_table_settings();
    void main_scroll_group_settings(QScrollArea* scroll, QWidget* group, QLayout* layout);
    void add_to_delete_list();
    void remove_from_delete_list(int row);
    void add_to_update_list();
    void remove_from_update_list(int row);
    void set_combo_box_enabled(QComboBox* combo_box, QString text, bool enabled);
    void set_all_combo_box_enabled(QComboBox* combo_box, QList<QSharedPointer<Billet_widget>>* list);
    bool has_invalid_symbols();
    bool finding_invalid_symbols(QTextEdit* text_edit, const QRegularExpression& expression);
    bool finding_invalid_symbols(QLineEdit* line_edit, const QRegularExpression& expression);
    bool finding_invalid_symbols(QComboBox* combo_box, const QRegularExpression& expression);
    void removing_extra_symbols(QTextEdit* text_edit);
    void removing_extra_symbols(QLineEdit* line_edit);
    QString removing_extra_symbols(QString string);
    void set_uppercase(QTextEdit* text_edit, const QRegularExpression& expression);
    QString set_uppercase(QString string, const QRegularExpression& expression);
    QString widgets_list_to_string(QList<QSharedPointer<Billet_widget>>* list);

    //int finding_row_in_list();
    //QString encoding_data(const QString& data);
    QString jsonarray_to_str(const QJsonArray& array_object);
    void filling_in_table(QJsonArray* data, int row_position);
public slots:
    QStandardItemModel* get_table_model();
    void remove_row_in_table(QJsonArray* data);
    void filling_page_with_data(QJsonArray* data);
    void insert_row_in_table(QJsonArray* data);
    void update_row_in_table(QJsonObject* data_new_object, QJsonObject* data_old_object);

private slots:
    //void set_app_page_visible(bool flag);
    void on_back_button_clicked();
    void on_delete_button_clicked();
    void on_redact_button_clicked();
    void on_show_all_button_clicked();
    void on_sort_button_clicked();
    void on_search_button_clicked();
    void on_director_add_button_clicked();
    void on_director_combo_box_text_changed();
    void on_accept_button_clicked();
    void on_clear_button_clicked();
    void on_widget_was_deleted(QString text);

    void set_search_edit(int search_id);//переименовать
    void set_date_edit(int data_value);
    void set_date_slider_position();
    void set_director_scroll(int director_id);
    void set_genre_scroll(int genre_id);
    void set_scroll(QComboBox* combo_box, QGroupBox* group, const QString& text, QList<QSharedPointer<Billet_widget>>* list);
    void on_search_edit_edited();
    void on_name_director_genre_data_edit_changed();
    void on_name_edit_changed();
    void on_table_row_selected(QModelIndex index);
signals:
    void step_out();
    void search_request(QStringList*);
    void select_all_request(QStringList*);
    void update_request(QStringList*);
    void insert_request(QStringList*);
    void delete_request(QStringList*);
    void genre_scroll_was_changed();
    void director_scroll_was_changed();

};

#endif // APP_PAGE_H
