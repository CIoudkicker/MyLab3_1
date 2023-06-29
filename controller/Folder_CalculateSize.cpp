#include <Folder_CalculateSize.h>
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

    qDebug().noquote().nospace() << space1.repeated(level - 1) << space2;

    foreach (QFileInfo fileInfo, dir.entryInfoList(QDir::Files | QDir::Hidden)) {
        // Calculate the file size
        size += fileInfo.size();
        fileName = fileInfo.fileName();
    }

    foreach (QString subDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden)) {
        // If there is a subdirectory, recursive call dirFileSize () function
        folderName = subDir;
        qDebug() << "";

        givenSize = dirSize(path + QDir::separator() + subDir, level + 1);
        qDebug().noquote().nospace()
                << space1.repeated(level) << "size of {" << subDir << "} is " << givenSize
                << " [summary size is " << size + givenSize << "]";

        size += givenSize;
    }

    return size;
}

DataForTable Folder_CalculateSize::dirSize(const QString &path)
{
    QDir dir(path);
    QString folderName;
    QString fileName;
    int givenSize = 0;

    float size = 0;
    QList<float> list;
    DataForTable map;

    foreach (QFileInfo fileInfo, dir.entryInfoList(QDir::Files | QDir::Hidden)) {
        // Calculate the file size
        size += fileInfo.size();
        fileName = fileInfo.fileName();

        list.append(fileInfo.size());
        map.insert(fileName, list);
        list = {};
    }

    foreach (QString subDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden)) {
        // If there is a subdirectory, recursive call dirFileSize () function
        folderName = subDir;

        givenSize = dirSize(path + QDir::separator() + subDir, 1);

        list.append(givenSize);
        map.insert(subDir, list);
        list = {};
        size += givenSize;
    }
    DataForTable::Iterator i = map.begin();
    while (i != map.end()) {

        QList<float> val;
        val = i.value();
        if (val[0] == 0) {
            val.append(ICalculateSize::trim(0));
        } else {
            val.append(ICalculateSize::trim(val[0] / (size / 100)));
        }

        map[i.key()] = val;
        i++;
    }

    list = { size };
    map.insert("", list);
    return map;
}

DataForTable Folder_CalculateSize::dirSize()
{
    return dirSize(ICalculateSize::path);
}
