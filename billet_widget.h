#ifndef BILLET_WIDGET_H
#define BILLET_WIDGET_H

#include <QObject>
#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QHBoxLayout>

class Billet_widget : public QGroupBox{
    Q_OBJECT

    QLabel* text_label;
    QPushButton* delete_button;
    QHBoxLayout* layout;
public:

    explicit Billet_widget(QWidget* parent = nullptr, const QString& data = "");
    Billet_widget(const Billet_widget& b_w);
    Billet_widget& operator=(const Billet_widget& b_w);

    //Определить после

    Billet_widget(Billet_widget&& b_w)            = delete;
    Billet_widget& operator=(Billet_widget&& b_w) = delete;
    bool operator==(const Billet_widget& b_w)const;
    ~Billet_widget();
    QString text()const;

private slots:

    void on_delete_button_clicked();

signals:

    void widget_was_deleted(QString text);
    void widget_was_constructed();
};

#endif // BILLET_WIDGET_H
