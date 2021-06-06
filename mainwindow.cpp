#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    setCentralWidget(tree);

    QList<QStandardItem *> preparedRow = QList<QString>("first", "second", "third");
    QStandardItem *item = leftDirFileSys->invisibleRootItem();
    // adding a row to the invisible root item produces a root element
    item->appendRow(preparedRow);

    QList<QStandardItem *> secondRow = prepareRow("111", "222", "333");
    // adding a row to an item starts a subtree
    preparedRow.first()->appendRow(secondRow);

    treeView->setModel(standardModel);
    treeView->expandAll();

    QString path = "E:\\Документы\\";
    leftDirFileSys = new QFileSystemModel(this);
    leftDirFileSys->setFilter(QDir::NoDotAndDotDot | QDir::QDir::AllEntries);
    leftDirFileSys->setRootPath(path);
    ui->treeView->setModel(leftDirFileSys);
    ui->listView_2->setModel(leftDirFileSys);

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
    QFileInfo fileInfo = leftDirFileSys->fileInfo(index);

    qDebug() << "OPPA "<< fileInfo.absoluteFilePath();
}

void MainWindow::on_treeView_expanded(const QModelIndex &index){
    QFileInfo fileInfo = leftDirFileSys->fileInfo(index);

    qDebug() << "OPPA "<< fileInfo.absoluteFilePath();
}
