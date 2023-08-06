#ifndef BILLET_WIDGET_H
#define BILLET_WIDGET_H

#include <QObject>
#include <QWidget>
#include<QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QString>
class Billet_widget:public QGroupBox
{
    Q_OBJECT
    //QGroupBox* group;
    QLabel* text_label;
    QPushButton* delete_button;
public:
    explicit Billet_widget(QWidget* parent=nullptr, const QString& data="");
    ~Billet_widget();
    QString text();
private slots:
    void on_delete_button_clicked();
signals:
    void widget_was_deleted(QString text);

};

#endif // BILLET_WIDGET_H
