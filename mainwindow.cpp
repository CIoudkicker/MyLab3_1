#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFileSystemModel>
#include <QDir>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QString path = "E:\\Документы\\";
    leftDirFileSys = new QFileSystemModel(this);
    leftDirFileSys->setFilter(QDir::NoDotAndDotDot | QDir::QDir::AllEntries);
    leftDirFileSys->setRootPath(path);
    ui->listView->setModel(leftDirFileSys);
    ui->listView_2->setModel(leftDirFileSys);

    connect(ui->listView, SIGNAL(doubleClicked(QModeIndex)), this, SLOT(on_listView_doubleClicked(const QModelIndex &index)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_listView_doubleClicked(const QModelIndex &index){
    QListView *qlistView = (QListView*)sender();
    QFileInfo fileInfo = leftDirFileSys->fileInfo(index);

    if(fileInfo.fileName() == ".."){
        QDir qDir = fileInfo.dir();
        qDir.cdUp();
        qlistView->setRootIndex(leftDirFileSys->index(qDir.absolutePath()));
        qDebug() << QString(qDir.absolutePath()) ;
    }else if(fileInfo.fileName() == "."){
        qlistView->setRootIndex(leftDirFileSys->index(""));
    }else if(fileInfo.isDir()){
        qlistView->setRootIndex(index);
        qDebug() << "OPPA "<< fileInfo.absoluteFilePath();
    }

}
