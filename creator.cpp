#include "creator.h"
#include "template_behavour.h"
#include<QChar>
#include<QString>
Creator::Creator()
{
    main_window=new MainWindow ();
    main_window->setWindowTitle("FilmsInfo");
    main_window->show();
    socket= new Socket();
    QObject::connect(this->main_window, SIGNAL(have_request(QStringList*)), this, SLOT(create_query(QStringList*)));//
    //QObject::connect(this->socket, SIGNAL(readyRead()), this, SLOT(on_readyRead()));//
    QObject::connect(this->socket, SIGNAL(new_data_received(QStringList*)), this, SLOT(on_data_received(QStringList*)));

}
Creator::~Creator()
{
    delete main_window;
    socket->disconnect();
    delete socket;
    delete behavour;
}
void Creator::create_query(QStringList* data){
    socket->sendData(data);
}
void Creator::on_data_received(QStringList* data){
    Behavour_id behavour_id=static_cast<Behavour_id>(data->at(0).data()->digitValue());
    Template_behavour* behavour;
    Template_behavour::creating_specific_behavour(behavour, behavour_id);
    behavour->processing_of_behavour(data);
}
