#ifndef DIALOG_H
#define DIALOG_H

#include "push_button.h"

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QGridLayout>
#include <QLabel>

class Dialog: public QDialog{
    Q_OBJECT

public:

    Dialog(QWidget *parent = nullptr);
    ~Dialog();
    PushButton* close_button;
    PushButton* cancel_button;
    QLabel* label;
    Dialog(Dialog const& other)            = delete;
    Dialog& operator=(Dialog const& other) = delete;
    Dialog(Dialog && other)                = delete;
    Dialog& operator=(Dialog && other)     = delete;

private:
    //QVBoxLayout*
    //QGridLayout* layout_page;
};

#endif // DIALOG_H
