#include "buffer.h"

#include <QJsonParseError>
#include <QJsonObject>

Buffer::Buffer(){
    buffer = new QQueue<QPair<int, QByteArray>>;
}

void Buffer::push(const QByteArray& data){
    QJsonParseError parse_error;
    QJsonObject object;
    QJsonDocument json_doc = QJsonDocument::fromJson(data, &parse_error);
    if (parse_error.error != QJsonParseError::NoError) {
        qWarning() << "Parse error at" << parse_error.offset << ":" << parse_error.errorString();
    }
    else {
        object = json_doc.object();
    }
    int request_code = object.take("RequestCode").toString().toInt();
    if (!contains_key(request_code)){
        QPair<int, QByteArray> element = qMakePair(request_code, data);
        buffer->enqueue(element);
    }
}

QByteArray Buffer::pop(){
    QPair<int, QByteArray> element = buffer->dequeue();
    return element.second;
}

QByteArray Buffer::head(){
    QPair<int, QByteArray> element = buffer->head();
    return element.second;
}

bool Buffer::contains_key(int key){
    for (QQueue<QPair<int, QByteArray>>::iterator i = buffer->begin(); i < buffer->end(); i++) {
        if (i->first == key)
            return true;
    }
    return false;
}

bool Buffer::is_empty(){
    return buffer->isEmpty();
}
Buffer::~Buffer(){
    delete buffer;
}
