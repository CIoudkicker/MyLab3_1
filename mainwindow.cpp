#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString path = "E:\\Документы\\";

    leftDirFileSys = new QFileSystemModel(this);
    CalcTableModel = new CalculateSize_TableModel(this);

    leftDirFileSys->setFilter(QDir::NoDotAndDotDot | QDir::QDir::AllEntries);
    leftDirFileSys->setRootPath(path);

    ui->treeView->setModel(leftDirFileSys);

    ui->treeView_2->setModel(CalcTableModel);

    ui->radioButton->setChecked(true);

    diagram = new diagramwidgets();

    QChart *chartBar =  diagram->createBarChart(10);

    ui->chartView->setChart(chartBar);


    setCentralWidget(centralWidget());

}

MainWindow::~MainWindow()
{
    delete ui;
    delete leftDirFileSys;
    delete CalcTableModel;
}


void MainWindow::on_treeView_activated(const QModelIndex &index){

    Currentindex = index;
    QFileInfo fileInfo = leftDirFileSys->fileInfo(Currentindex);

    if(index.isValid()){
        CalcTableModel->append(fileInfo.absoluteFilePath());
    }

    qDebug() << "OPPA on_treeView_activated"<< fileInfo.absoluteFilePath();
}


void MainWindow::on_radioButton_toggled(bool checked)
{
    QFileInfo fileInfo = leftDirFileSys->fileInfo(Currentindex);
    CalcTableModel->changeStrat(Context::Strategies::Folder_CalculateSize, fileInfo.absoluteFilePath());
    qDebug() << "radio 1.1";
}


void MainWindow::on_radioButton_2_toggled(bool checked)
{
    QFileInfo fileInfo = leftDirFileSys->fileInfo(Currentindex);
    CalcTableModel->changeStrat(Context::Strategies::Type_CalculateSize, fileInfo.absoluteFilePath());
    qDebug() << "radio 1.2";
}

