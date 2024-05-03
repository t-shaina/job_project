#include "symbols_inspector.h"

#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>

Symbols_inspector::Symbols_inspector(){

}

void Symbols_inspector::removing_extra_symbols(QTextEdit* text_edit){
    QString text = text_edit->placeholderText();
    text.remove(QRegularExpression ("^([\\s.,]+)|([\\s]{2,})|([\\s.,]+)$", QRegularExpression::CaseInsensitiveOption));
    text.squeeze();
    text_edit->setText(text);
}

void Symbols_inspector::removing_extra_symbols(QLineEdit* text_edit){
    QString text = text_edit->placeholderText();
    text.remove(QRegularExpression ("^([\\s.,]+)|([\\s]{2,})|([\\s.,]+)$", QRegularExpression::CaseInsensitiveOption));
    text.squeeze();
    text_edit->setText(text);
}

QString Symbols_inspector::removing_extra_symbols(QString string){
    string.remove(QRegularExpression ("^([\\s.,]+)|([\\s]{2,})|([\\s.,]+)$", QRegularExpression::CaseInsensitiveOption));
    string.squeeze();
    return string;
}

QString Symbols_inspector::removing_last_spaces(QString string){
    string.remove(QRegularExpression ("([\\s.,]+)$", QRegularExpression::CaseInsensitiveOption));
    string.squeeze();
    return string;
}

QString Symbols_inspector::removing_last_comma(QString string){
    string.remove(QRegularExpression ("([,]+)", QRegularExpression::CaseInsensitiveOption));
    string.squeeze();
    return string;
}

void Symbols_inspector::set_uppercase(QTextEdit* text_edit, const QRegularExpression& expression){
    QString text = text_edit->placeholderText();
    QRegularExpressionMatchIterator match_iter = expression.globalMatch(text, 0, QRegularExpression::NormalMatch, QRegularExpression::NoMatchOption);
    qsizetype position = -1;
    QString symbol;
    while (match_iter.hasNext()){
        QRegularExpressionMatch match = match_iter.next();
        position = match.capturedStart();
        symbol = match.captured().toUpper();
        text.replace(position, 1, symbol);
    }
    text_edit->setText(text);
}

QString Symbols_inspector::set_uppercase(QString string, const QRegularExpression& expression){
    QRegularExpressionMatchIterator match_iter = expression.globalMatch(string, 0, QRegularExpression::NormalMatch, QRegularExpression::NoMatchOption);
    qsizetype position = -1;
    QString symbol;
    while (match_iter.hasNext()){
        QRegularExpressionMatch match = match_iter.next();
        position = match.capturedStart();
        symbol = match.captured().toUpper();
        string.replace(position, 1, symbol);
    }
    return string;
}

bool Symbols_inspector::finding_invalid_symbols(QComboBox* combo_box, const QRegularExpression& expression){
    bool state = false;
    QString text = combo_box->placeholderText();
    QRegularExpressionMatchIterator match_iter = expression.globalMatch(text, 0, QRegularExpression::NormalMatch, QRegularExpression::NoMatchOption);
    if (match_iter.hasNext()){
        QRegularExpressionMatch match = match_iter.next();
        state = true;
    }
    return state;
}

bool Symbols_inspector::finding_invalid_symbols(QTextEdit* text_edit, const QRegularExpression& expression){
    bool state = false;
    QString text = text_edit->placeholderText();
    QRegularExpressionMatchIterator match_iter=expression.globalMatch(text, 0, QRegularExpression::NormalMatch, QRegularExpression::NoMatchOption);
    if (match_iter.hasNext()){
        QRegularExpressionMatch match = match_iter.next();
        state = true;
        int pos = match.capturedStart();
        text_edit->textCursor().setPosition(pos, QTextCursor::MoveAnchor);
    }
    return state;
}
bool Symbols_inspector::finding_invalid_symbols(QLineEdit* line_edit, const QRegularExpression& expression){
    bool state = false;
    QString text = line_edit->placeholderText();
    QRegularExpressionMatchIterator match_iter = expression.globalMatch(text, 0, QRegularExpression::NormalMatch, QRegularExpression::NoMatchOption);
    if (match_iter.hasNext()){
        QRegularExpressionMatch match = match_iter.next();
        state = true;
    }
    return state;
}
