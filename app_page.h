#ifndef APP_PAGE_H
#define APP_PAGE_H

//#include"billet_widget.h"
#include"app_page_painter.h"
#include <QObject>
#include <QWidget>
/*#include<QGridLayout>
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
#include<QStringList>*/

#include<QSharedPointer>
#include<QVector>
class App_page:public QWidget
{
    Q_OBJECT
public:
    App_page(QWidget* parent=nullptr);
    ~App_page();
    QString email;
    App_page_painter* app_page_painter;   
    QList<int>* delete_rows_list;
    QList<int>* update_rows_list;
private:

    void add_to_delete_list();
    void remove_from_delete_list(int row);
    void add_to_update_list();
    void remove_from_update_list(int row);
    int find_row_in_list(QList<int>* list, const QJsonObject& object_row);

    //bool has_invalid_symbols();


    /*void removing_extra_symbols(QTextEdit* text_edit);
    void removing_extra_symbols(QLineEdit* line_edit);
    QString removing_extra_symbols(QString string);
    void set_uppercase(QTextEdit* text_edit, const QRegularExpression& expression);
    QString set_uppercase(QString string, const QRegularExpression& expression);*/
    QString jsonarray_to_str(const QJsonArray& array_object);
    void filling_in_table(QJsonArray* data, int row_position);
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
