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
#include<QTableView>
#include<QGroupBox>
#include<QComboBox>

class App_page: public QGroupBox
{
    Q_OBJECT
public:
    App_page(QWidget* parent=nullptr);
private:
    QGridLayout* layout_page2;
    QTableView* tabel;


};

#endif // APP_PAGE_H
