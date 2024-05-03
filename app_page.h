#ifndef APP_PAGE_H
#define APP_PAGE_H

#include "app_page_painter.h"
#include <QObject>
#include <QWidget>
#include <QSharedPointer>
#include <QVector>

class App_page : public QWidget{
    Q_OBJECT

public:

    App_page(QWidget* parent = nullptr);
    ~App_page();
    QString email;
    App_page_painter* app_page_painter;   
    QList<int>* delete_rows_list;
    QList<int>* update_rows_list;

private:

    App_page(App_page const& other)             = delete;
    App_page& operator=(App_page const& other)  = delete;
    App_page(App_page&& other)                  = delete;
    App_page& operator=(App_page&& other)       = delete;
    void add_to_delete_list();
    void remove_from_delete_list(int row);
    void add_to_update_list();
    void remove_from_update_list(int row);
    int find_row_in_list(QList<int>* list, const QJsonObject& object_row);
    QString jsonarray_to_str(const QJsonArray& array_object);
    void filling_in_table(QJsonArray* data, int row_position);
    void filling_in_director_combo_box(QJsonArray* data);
    bool has_invalid_symbols();

public slots:

    QStandardItemModel* get_table_model();
    void remove_row_in_table(QJsonArray* data);
    void filling_page_with_data(QJsonArray* data);
    void insert_row_in_table(QJsonArray* data);
    void update_row_in_table(QJsonObject* data_new_object, QJsonObject* data_old_object);

private slots:

    void on_back_button_clicked();
    void on_delete_button_clicked();   
    void on_show_all_button_clicked();    
    void on_search_button_clicked();   
    void on_accept_button_clicked();   

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
