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

    diagram = new diagramwidgets();

    diagram->generateData(CalcTableModel->getMap());
    diagram->createBarChart();

    ui->chartView->setChart(diagram->qChart);
    ui->chartView->update();
    ui->chartView->hide();


    QChartView *cv = diagram->chartView;

    ui->splitter->addWidget(cv);

    ui->radioButton->setChecked(true);
    ui->radioButton_3->setChecked(true);
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
        diagram->generateData(CalcTableModel->getMap());
        diagram->executeCurrentDiagram();
    }

    qDebug() << "OPPA on_treeView_activated"<< fileInfo.absoluteFilePath();
}


void MainWindow::on_radioButton_toggled(bool checked)
{
    QFileInfo fileInfo = leftDirFileSys->fileInfo(Currentindex);
    CalcTableModel->changeStrat(Context_CalculateSize::Strategies::Folder_CalculateSize, fileInfo.absoluteFilePath());
    diagram->generateData(CalcTableModel->getMap());
    diagram->executeCurrentDiagram();
    qDebug() << "radio 1.1";
}


void MainWindow::on_radioButton_2_toggled(bool checked)
{
    QFileInfo fileInfo = leftDirFileSys->fileInfo(Currentindex);
    CalcTableModel->changeStrat(Context_CalculateSize::Strategies::Type_CalculateSize, fileInfo.absoluteFilePath());
    diagram->generateData(CalcTableModel->getMap());
    diagram->executeCurrentDiagram();
    qDebug() << "radio 1.2";
}


void MainWindow::on_radioButton_3_toggled(bool checked){

    QFileInfo fileInfo = leftDirFileSys->fileInfo(Currentindex);
    diagram->generateData(CalcTableModel->getMap());
    diagram->createBarChart();
}

void MainWindow::on_radioButton_4_toggled(bool checked){

    QFileInfo fileInfo = leftDirFileSys->fileInfo(Currentindex);
    diagram->generateData(CalcTableModel->getMap());
    diagram->createPieChart();
}
