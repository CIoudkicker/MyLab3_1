#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString path = "E:\\Документы\\";

    leftDirFileSys = new QFileSystemModel(this);
    CalcSizeModel = new CalculateSizeModel(this);
    CalcTableModel = new CalculateSize_TableModel(this);

    leftDirFileSys->setFilter(QDir::NoDotAndDotDot | QDir::QDir::AllEntries);
    leftDirFileSys->setRootPath(path);

    ui->treeView->setModel(leftDirFileSys);
    ui->listView->setModel(CalcSizeModel);
    ui->treeView_2->setModel(CalcTableModel);



    connect(ui->treeView, SIGNAL(doubleClicked(QModeIndex)), this, SLOT(on_listView_doubleClicked(const QModelIndex &index)));

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

void MainWindow::on_treeView_activated(const QModelIndex &index){

    Currentindex = index;
    QFileInfo fileInfo = leftDirFileSys->fileInfo(Currentindex);

    if(index.isValid()){
        CalcSizeModel->append(fileInfo.absoluteFilePath());
        CalcTableModel->append(fileInfo.absoluteFilePath());
    }

    qDebug() << "OPPA on_treeView_activated"<< fileInfo.absoluteFilePath();
}

void MainWindow::on_treeView_expanded(const QModelIndex &index){
    /*
    Currentindex = index;
    QFileInfo fileInfo = leftDirFileSys->fileInfo(Currentindex);
    qDebug() << "OPPA on_treeView_expanded"<< fileInfo.absoluteFilePath();
    */
}


void MainWindow::on_radioButton_toggled(bool checked)
{
    QFileInfo fileInfo = leftDirFileSys->fileInfo(Currentindex);
    CalcTableModel->changeStrat(CalculateSize_TableModel::Strategies::Folder_CalculateSize, fileInfo.absoluteFilePath());
    qDebug() << "radio 1.1";
}


void MainWindow::on_radioButton_2_toggled(bool checked)
{
    QFileInfo fileInfo = leftDirFileSys->fileInfo(Currentindex);
    CalcTableModel->changeStrat(CalculateSize_TableModel::Strategies::Type_CalculateSize, fileInfo.absoluteFilePath());
    qDebug() << "radio 1.2";
}

void MainWindow::on_radioButton_3_toggled(bool checked)
{

}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    Currentindex = index;
    QFileInfo fileInfo = leftDirFileSys->fileInfo(Currentindex);

    if(index.isValid()){
        CalcSizeModel->append(fileInfo.absoluteFilePath());
        CalcTableModel->append(fileInfo.absoluteFilePath());
    }
}
