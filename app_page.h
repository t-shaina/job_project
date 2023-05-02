#ifndef APP_PAGE_H
#define APP_PAGE_H

#include <QObject>
#include <QWidget>
#include<QGridLayout>
#include<QLineEdit>
#include <QLabel>
#include<QPushButton>
#include<QRadioButton>
#include<QCheckBox>
#include<QTableWidget>>
#include<QGroupBox>
#include<QComboBox>
#include<QScrollArea>
#include <QSlider>
#include<QSpinBox>
class App_page:public QWidget
{
    Q_OBJECT
    friend class MainWindow;
public:
    App_page(QWidget* parent=nullptr);
private:
    //QGroupBox* page_group;
    QGridLayout* layout_page;
    QGroupBox* table_group;
    QGroupBox* scroll_table_group;
    QGroupBox* search_group;
    QGroupBox* settings_group;
    QGroupBox* edit_group;
    QGroupBox* navigation_group;
    QScrollArea* table_scroll;
    QScrollArea* edit_scroll;
    QGroupBox* director_group;
    QGroupBox* genre_group;
    QGroupBox* data_group;

    QTableWidget* table;
    QPushButton* delete_button;
    QComboBox* search_combo_box;
    QLineEdit* search_edit;
    QPushButton* search_button;
    QLabel* name_label;
    QLineEdit* name_edit;
    QLabel* director_label;
    QComboBox* director_combo_box;
    QLineEdit* director_edit;
    QLabel* genre_label;
    QComboBox* genre_combo_box;
    QLineEdit* genre_edit;
    QLineEdit* data_edit;
    QLabel* data_label;
    QSlider* data_slider;
    QLabel* rating_label;
    QSpinBox* rating_spin_box;
    QLabel* status_label;
    QComboBox* status_combo_box;
    QPushButton* accept_button;
    QPushButton* back_button;

    void base_settings();
    void main_buttons_settings(int w, int h);
public slots:
    void set_app_page_visible(bool flag);
    void on_back_button_clicked();
private slots:
    void set_search_edit(int search_id);//переименовать
    void set_data_edit(int data_value);
    void set_genre_edit(int genre_id);
signals:
    void step_back();

};

#endif // APP_PAGE_H
