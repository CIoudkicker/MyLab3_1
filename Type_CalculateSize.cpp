#include<Type_CalculateSize.h>
#include "ICalculateSize.h"

QString Type_CalculateSize::getType(QString s){
    QString out;
    for(int i = 0; i < s.length(); i++){
        if(s[i] == "."){
            for(int j = i; j < s.length(); j++){
                out.append(s[j]);
            }
            break;
        }
    }
    return out;
}

QMap<QString, QList<float>> Type_CalculateSize::dirSize(const QString &path, int level, QMap<QString, QList<float>> map1)
{
    QDir dir(path);
    QString folderName;
    QString fileName;
    QString space1 = "   ";
    QString space2 = " |__";
    QList<float> val;
    QMap<QString, QList<float>> map = map1;
    int givenSize = 0;
    //dir.entryInfoList(QDir::Files) returns file information

    qDebug().noquote().nospace() << space1.repeated(level-1)<< space2;

    foreach(QFileInfo fileInfo, dir.entryInfoList(QDir::Files | QDir::Hidden))
    {
        // Calculate the file size
        Type_CalculateSize::size += fileInfo.size();
        fileName = fileInfo.fileName();

        qDebug().noquote().nospace() << space1.repeated(level) <<"|>"<<"fileName is "<<">"<<fileName <<"< "<<
                                        "[file size is "<<fileInfo.size()<<"] [summary size is "<< Type_CalculateSize::size<<"]";
        if(map.contains(fileInfo.suffix())){
            val = map.value(fileInfo.suffix());
            val[0] = val[0] + fileInfo.size();
            map[fileInfo.suffix()] = val;
        }else{
            val = {float(fileInfo.size())};
            map[fileInfo.suffix()] = val;
        }

    }
    //dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot) returns all subdirectories and filters them
    foreach(QString subDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden))
    {
        // If there is a subdirectory, recursive call dirFileSize () function
        folderName = subDir;
        qDebug() << "";

        qDebug().noquote().nospace() << space1.repeated(level) <<"[=]"<<"folderName is {"<< folderName <<
                                        "} [summary size is "<< Type_CalculateSize::size <<"]";

        map = dirSize(path + QDir::separator() + subDir, level+1, map);
        qDebug().noquote().nospace() << space1.repeated(level) <<"size of {"<< subDir << "} is "<< givenSize <<" [summary size is "<< Type_CalculateSize::size <<"]";
    }
    //qDebug().noquote() << space.repeated(level) <<"fileName is "<< fileName <<"folderName is "<< folderName <<"size is "<< size;
    return map;
}

QMap<QString, QList<float>> Type_CalculateSize::dirSize(const QString &path)
{
    QDir dir(path);
    QString folderName;
    QString fileName;
    int givenSize = 0;
    float size = 0;
    QList<float> val;
    QMap<QString, QList<float>> map;
    //dir.entryInfoList(QDir::Files) returns file information
    foreach(QFileInfo fileInfo, dir.entryInfoList(QDir::Files | QDir::Hidden))
    {
        // Calculate the file size
        Type_CalculateSize::size += fileInfo.size();
        fileName = fileInfo.fileName();
        qDebug().noquote().nospace() <<"fileName is "<< fileName <<"folderName is "<< folderName <<" size is "<< size;
        if(map.contains(fileInfo.suffix())){
            val = map.value(fileInfo.suffix());
            val[0] = val[0] + fileInfo.size();
            map[fileInfo.suffix()] = val;
        }else{
            val = {float(fileInfo.size())};
            map[fileInfo.suffix()] = val;
        }
    }

    //dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot) returns all subdirectories and filters them
    foreach(QString subDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden))
    {
        // If there is a subdirectory, recursive call dirFileSize () function
        folderName = subDir;
        qDebug() << "";
        qDebug().noquote().nospace() <<"[=]folderName is {"<< folderName <<"} [summary size is "<< size <<"]";
        map = dirSize(path + QDir::separator() + subDir, 1, map);
        qDebug().noquote().nospace() <<"size of {"<< subDir << "} is "<< givenSize <<" [summary size is "<< Type_CalculateSize::size <<"]";
    }
    QMap<QString, QList<float>>::Iterator i = map.begin();
    int size1 = Type_CalculateSize::size;
    while (i != map.end()) {
        QList<float> val;
        val = i.value();
        if(val[0] == 0){
            val.append(ICalculateSize::trim(0));
        }else{
            val.append(ICalculateSize::trim(val[0]/(size1/100)));
        }
        map[i.key()] = val;
        i++;
    }
    val = {float(Type_CalculateSize::size)};
    map.insert("", val);
    return map;
}

QMap<QString, QList<float>> Type_CalculateSize::dirSize(){

    Type_CalculateSize::size = 0;
    return dirSize(ICalculateSize::path);
}


