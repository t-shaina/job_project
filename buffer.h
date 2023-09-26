#ifndef BUFFER_H
#define BUFFER_H

#include <QObject>
#include<QQueue>
#include<QPair>
#include<QByteArray>

class Buffer
{

public:
    explicit Buffer();
    ~Buffer();
    QQueue<QPair<int, QByteArray>>* buffer;
    void push(const QByteArray& data);
    QByteArray pop();
    bool is_empty();
private:
    bool contains_key(int key);
};

#endif // BUFFER_H
