#ifndef SPINBOX_H
#define SPINBOX_H

#include <QObject>
#include <QWidget>
#include <QSpinBox>

class SpinBox : public QSpinBox{
    Q_OBJECT

public:

    SpinBox(QWidget* parent = nullptr);

public slots:

    void keyPressEvent(QKeyEvent* e);

signals:

    void enter_pressed();
    void down_pressed();
    void up_pressed();
};

#endif // SPINBOX_H
