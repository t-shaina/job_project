#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QObject>
#include <QWidget>
#include <QTextEdit>

class TextEdit : public QTextEdit{
    Q_OBJECT

public:

    TextEdit(QWidget* parent = nullptr);

public slots:

    void keyPressEvent(QKeyEvent* e);

signals:

    void enter_pressed();
    void down_pressed();
    void up_pressed();
};

#endif // TEXTEDIT_H
