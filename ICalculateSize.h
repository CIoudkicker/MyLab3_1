#ifndef ICALCULATESIZE_H
#define ICALCULATESIZE_H
#include <iostream>
#include <variant>
#include <string>
#include <cassert>
#include <QApplication>
#include <QCoreApplication>
#include <QDir>
#include<QFile>
#include<QFileInfo>
#include<QString>
#include<QList>
#include<QMap>

#include<QDebug>


class ICalculateSize{

    public:

        ICalculateSize(QString path1): path(path1){}
        virtual ~ICalculateSize(){}

        virtual QMap<QString, QList<float>> dirSize() = 0;
        static float trim(float in); // округляет число

    protected:

        QString path;
};

#endif // ICALCULATESIZE_H
