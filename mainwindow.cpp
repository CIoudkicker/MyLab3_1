#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString path = "E:\\Документы\\";

    leftDirFileSys = new QFileSystemModel(this);
    CalcTableModel = new CalculateSize_TableModel(this);

    leftDirFileSys->setFilter(QDir::NoDotAndDotDot | QDir::QDir::AllEntries);
    leftDirFileSys->setRootPath(path);

    ui->treeView->setModel(leftDirFileSys);

    ui->treeView_2->setModel(CalcTableModel);

    diagram = new diagramwidgets(*CalcTableModel);

    diagram->generateData(CalcTableModel->getMap());

    QChartView *cv = diagram->chartView;

    ui->splitter->addWidget(cv);

    ui->radioButton->setChecked(true);
    //    ui->radioButton_2->setChecked(true);
    ui->radioButton_3->setChecked(true);
    //    ui->radioButton_4->setChecked(true);

    setCentralWidget(centralWidget());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete leftDirFileSys;
    delete CalcTableModel;
}

void MainWindow::on_treeView_activated(const QModelIndex &index)
{

    Currentindex = index;
    QFileInfo fileInfo = leftDirFileSys->fileInfo(Currentindex);

    if (index.isValid()) {

        CalcTableModel->append(fileInfo.absoluteFilePath());
    }

    qDebug() << "OPPA on_treeView_activated" << fileInfo.absoluteFilePath();
}

void MainWindow::on_radioButton_toggled(bool /*checked*/)
{
    QFileInfo fileInfo = leftDirFileSys->fileInfo(Currentindex);
    CalcTableModel->changeStrat(new Type_CalculateSize(fileInfo.absoluteFilePath()),
                                fileInfo.absoluteFilePath());

    qDebug() << fileInfo << "radio 1.1";
}

void MainWindow::on_radioButton_2_toggled(bool /*checked*/)
{
    QFileInfo fileInfo = leftDirFileSys->fileInfo(Currentindex);
    CalcTableModel->changeStrat(new Folder_CalculateSize(fileInfo.absoluteFilePath()),
                                fileInfo.absoluteFilePath());

    qDebug() << "radio 1.2";
}

void MainWindow::on_radioButton_3_toggled(bool /*checked*/)
{

    QFileInfo fileInfo = leftDirFileSys->fileInfo(Currentindex);
    diagram->generateData(CalcTableModel->getMap());
    diagram->createBarChart();
}

void MainWindow::on_radioButton_4_toggled(bool /*checked*/)
{

    QFileInfo fileInfo = leftDirFileSys->fileInfo(Currentindex);
    diagram->generateData(CalcTableModel->getMap());
    diagram->createPieChart();
}
