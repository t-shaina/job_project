#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QObject>
#include <QWidget>
#include <QPushButton>

class PushButton:public QPushButton{
    Q_OBJECT

public:

    PushButton(const QString& text, QWidget* parent = nullptr);
    PushButton(QWidget* parent = nullptr);

public slots:

    void keyPressEvent(QKeyEvent* e);

signals:

    void enter_pressed();
    void down_pressed();
    void up_pressed();
    void right_pressed();
    void left_pressed();
};

#endif // PUSHBUTTON_H
