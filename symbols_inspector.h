#ifndef SYMBOLS_INSPECTOR_H
#define SYMBOLS_INSPECTOR_H

#include <QObject>
#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QComboBox>

class Symbols_inspector{

public:

    Symbols_inspector();
    bool has_invalid_symbols();
    bool finding_invalid_symbols(QComboBox* combo_box, const QRegularExpression& expression);
    bool finding_invalid_symbols(QTextEdit* text_edit, const QRegularExpression& expression);
    bool finding_invalid_symbols(QLineEdit* line_edit, const QRegularExpression& expression);
    void removing_extra_symbols(QTextEdit* text_edit);
    void removing_extra_symbols(QLineEdit* line_edit);
    QString removing_extra_symbols(QString string);
    QString removing_last_spaces(QString string);
    QString removing_last_comma(QString string);
    void set_uppercase(QTextEdit* text_edit, const QRegularExpression& expression);
    QString set_uppercase(QString string, const QRegularExpression& expression);
};

#endif // SYMBOLS_INSPECTOR_H
