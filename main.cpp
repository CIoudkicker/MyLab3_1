#include "mainwindow.h"
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
#include"ICalculateSize.h"
#include"Folder_CalculateSize.h"
#include"Type_CalculateSize.h"

using namespace std;

void printMap(QMap<QString, QList<float>> map){
    QMap<QString, QList<float>>::Iterator i = map.begin();
    qDebug() << ""<<i.key() << "размер всего "<< i.value();
    i++;
    while (i != map.end()) {
        qDebug() << "Элемент "<<i.key() << "размер и процент "<< i.value();
        i++;
    }
}

int main(int argc, char *argv[])
{

    //testFunc("E:\\Qt Projects");

    ICalculateSize *Folder = new Folder_CalculateSize("E:\\Qt Projects\\");
    ICalculateSize *Type = new Type_CalculateSize("E:\\Qt Projects\\");

    QMap<QString, QList<float>> folder_size = Folder->dirSize();
    QMap<QString, QList<float>> type_size = Type->dirSize();
    qDebug() << "СОРТИРОВКА ПАПОК\n";
    printMap(folder_size);
    qDebug() << "СОРТИРОВКА ПО ТИПАМ\n";
    printMap(type_size);
    qDebug()<< "";
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    */
    return 1;
}
