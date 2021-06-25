#ifndef IOBSERVER_H
#define IOBSERVER_H

#include <QString>

class IObserver
{
    public:
        IObserver();
        virtual void Update(QMap<QString, QList<float>> map) = 0;

};


class ISubject{

    public:

        ISubject();
        virtual ~ISubject(){};
        virtual void Attach(IObserver *observer) = 0;
        virtual void Detach(IObserver *observer) = 0;
        virtual void Notify() = 0;

};
#endif // IOBSERVER_H
