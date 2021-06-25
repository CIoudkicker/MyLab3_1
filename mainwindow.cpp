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

void MainWindow::Attach(IObserver *observer) {
  list_observer_.push_back(observer);
}
void MainWindow::Detach(IObserver *observer)  {
  list_observer_.remove(observer);
}
void MainWindow::Notify()  {
  std::list<IObserver *>::iterator iterator = list_observer_.begin();
  while (iterator != list_observer_.end()) {
    (*iterator)->Update(CalcTableModel->getMap());
    ++iterator;
  }
}

void MainWindow::on_treeView_activated(const QModelIndex &index){

    Currentindex = index;
    QFileInfo fileInfo = leftDirFileSys->fileInfo(Currentindex);

    if(index.isValid()){
        CalcTableModel->append(fileInfo.absoluteFilePath());
        diagram->generateData(CalcTableModel->getMap());
        ui->chartView->setChart(diagram->createPieChart());
        //ui->chartView->setChart(diagram->createBarChart(10));
    }

    qDebug() << "OPPA on_treeView_activated"<< fileInfo.absoluteFilePath();
}


void MainWindow::on_radioButton_toggled(bool checked)
{
    QFileInfo fileInfo = leftDirFileSys->fileInfo(Currentindex);
    CalcTableModel->changeStrat(Context::Strategies::Folder_CalculateSize, fileInfo.absoluteFilePath());
    diagram->generateData(CalcTableModel->getMap());
    qDebug() << "radio 1.1";
}


void MainWindow::on_radioButton_2_toggled(bool checked)
{
    QFileInfo fileInfo = leftDirFileSys->fileInfo(Currentindex);
    CalcTableModel->changeStrat(Context::Strategies::Type_CalculateSize, fileInfo.absoluteFilePath());
    diagram->generateData(CalcTableModel->getMap());
    qDebug() << "radio 1.2";
}


void MainWindow::on_radioButton_3_toggled(bool checked){

    QFileInfo fileInfo = leftDirFileSys->fileInfo(Currentindex);
    diagram->generateData(CalcTableModel->getMap());
    ui->chartView->setChart(diagram->createBarChart());
}

void MainWindow::on_radioButton_4_toggled(bool checked){

    QFileInfo fileInfo = leftDirFileSys->fileInfo(Currentindex);
    diagram->generateData(CalcTableModel->getMap());
    ui->chartView->setChart(diagram->createPieChart());
}
