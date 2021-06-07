#include<Folder_CalculateSize.h>
#include "ICalculateSize.h"

int Folder_CalculateSize::dirSize(const QString &path, int level)
{
    QDir dir(path);
    QString folderName;
    QString fileName;
    QString space1 = "   ";
    QString space2 = " |__";
    int givenSize = 0;
    int size = 0;
    //dir.entryInfoList(QDir::Files) returns file information

    qDebug().noquote().nospace() << space1.repeated(level-1)<< space2;

    foreach(QFileInfo fileInfo, dir.entryInfoList(QDir::Files | QDir::Hidden))
    {
        // Calculate the file size
        size += fileInfo.size();
        fileName = fileInfo.fileName();
        /*
        qDebug().noquote().nospace() << space1.repeated(level) <<"|>"<<"fileName is "<<">"<<fileName <<"< "<<
                                        "[file size is "<<fileInfo.size()<<"] [summary size is "<< size<<"]";
        */
    }
    //dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot) returns all subdirectories and filters them
    foreach(QString subDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden))
    {
        // If there is a subdirectory, recursive call dirFileSize () function
        folderName = subDir;
        qDebug() << "";
        /*
        qDebug().noquote().nospace() << space1.repeated(level) <<"[=]"<<"folderName is {"<< folderName <<
                                        "} [summary size is "<< size <<"]";
        */
        givenSize = dirSize(path + QDir::separator() + subDir, level+1);
        qDebug().noquote().nospace() << space1.repeated(level) <<"size of {"<< subDir << "} is "<< givenSize <<" [summary size is "<< size+givenSize <<"]";

        size += givenSize;

    }
    //qDebug().noquote() << space.repeated(level) <<"fileName is "<< fileName <<"folderName is "<< folderName <<"size is "<< size;
    return size;
}

QMap<QString, QList<float>> Folder_CalculateSize::dirSize(const QString &path)
{
    QDir dir(path);
    QString folderName;
    QString fileName;
    int givenSize = 0;
    int level = 0;
    float size = 0;
    QList<float> list;
    QMap<QString, QList<float>> map;
    //dir.entryInfoList(QDir::Files) returns file information
    foreach(QFileInfo fileInfo, dir.entryInfoList(QDir::Files | QDir::Hidden))
    {
        // Calculate the file size
        size += fileInfo.size();
        fileName = fileInfo.fileName();
        //qDebug().noquote().nospace() <<"fileName is "<< fileName <<"folderName is "<< folderName <<" size is "<< size;
        list.append(fileInfo.size());
        map.insert(fileName, list);
        list = {};
    }

    //dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot) returns all subdirectories and filters them
    foreach(QString subDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden))
    {
        // If there is a subdirectory, recursive call dirFileSize () function
        folderName = subDir;
        //qDebug() << "";
        //qDebug().noquote().nospace() <<"[=]folderName is {"<< folderName <<"} [summary size is "<< size <<"]";
        givenSize = dirSize(path + QDir::separator() + subDir, 1);
        //qDebug().noquote().nospace() <<"size of {"<< subDir << "} is "<< givenSize <<" [summary size is "<< size+givenSize <<"]";
        list.append(givenSize);
        map.insert(subDir, list);
        list = {};
        size += givenSize;
    }
    QMap<QString, QList<float>>::Iterator i = map.begin();
    while (i != map.end()) {
        //qDebug().noquote().nospace() <<"value " << i.key();
        QList<float> val;
        val = i.value();
        if(val[0] == 0){
            val.append(ICalculateSize::trim(0));
        }else{
            val.append(ICalculateSize::trim(val[0]/(size/100)));
        }

        map[i.key()] = val;
        i++;
    }

    list = {size};
    map.insert("", list);
    return map;
}

QMap<QString, QList<float>> Folder_CalculateSize::dirSize(){
    return dirSize(ICalculateSize::path);
}
