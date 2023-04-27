#ifndef START_PAGE_H
#define START_PAGE_H

#include <QWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include<QString>
class Start_page : public QGroupBox
{
    Q_OBJECT
public:
    explicit Start_page(QWidget *parent = nullptr);
    ~Start_page();
private:
    QLabel* label_email;
    QLabel* label_password;
    QLineEdit* edit_email;
    QLineEdit* edit_password;
    QPushButton* button_entry;
    QGridLayout* layout_page1;

    void set_start_page_visible(bool flag);
signals:
    void logged_in(QString username);
public slots:
    void on_button_entry_clicked();
};

#endif // START_PAGE_H
