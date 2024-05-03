#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>

class LineEdit : public QLineEdit{
    Q_OBJECT

public:

    LineEdit(QWidget* parent = nullptr);

public slots:

    void keyPressEvent(QKeyEvent* e);

signals:

    void enter_pressed();
    void down_pressed();
    void up_pressed();
    void right_pressed();
    void left_pressed();
};

#endif // LINEEDIT_H
