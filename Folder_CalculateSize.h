#ifndef FOLDER_CALCULATESIZE_H
#define FOLDER_CALCULATESIZE_H
#include "ICalculateSize.h"

class Folder_CalculateSize : public ICalculateSize
{
public:
    Folder_CalculateSize(QString path1) : ICalculateSize(path1) { }
    ~Folder_CalculateSize() { }

    virtual DataForTable dirSize() override;

private:
    int dirSize(const QString &path, int level);
    DataForTable dirSize(const QString &path);
};

#endif // FOLDER_CALCULATESIZE_H
