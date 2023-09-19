#ifndef COMBO_BOX_H
#define COMBO_BOX_H

#include <QObject>
#include <QWidget>
#include<QComboBox>

class ComboBox: public QComboBox
{
    Q_OBJECT
public:
    //QComboBox
    ComboBox(QWidget* parent=nullptr);
public slots:
    void keyPressEvent(QKeyEvent *e);
signals:
    void enter_pressed();
    void down_pressed();
    void up_pressed();
};

#endif // COMBO_BOX_H
