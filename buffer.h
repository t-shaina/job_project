#ifndef BUFFER_H
#define BUFFER_H

#include <QObject>
#include <QQueue>
#include <QPair>
#include <QByteArray>

class Buffer{

public:

    explicit Buffer();
    ~Buffer();
    QQueue<QPair<int, QByteArray>>* buffer;
    void push(const QByteArray& data);
    QByteArray pop();
    QByteArray head();
    bool is_empty();

private:

    Buffer(Buffer const & other)            = delete;
    Buffer& operator=(Buffer const & other) = delete;
    Buffer(Buffer&& other)                  = delete;
    Buffer& operator=(Buffer&& other)       = delete;
    bool contains_key(int key);
};

#endif // BUFFER_H
