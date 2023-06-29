#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QMainWindow>
#include <QFileSystemModel>
#include "CalculateSize_TableModel.h"
#include <QDir>
#include <QString>
#include <QList>
#include <QTreeView>
#include <QListView>
#include <QtCharts/QChartView>
#include <QItemSelectionModel>
#include <QStandardItem>
#include <QGroupBox>
#include <QModelIndex>
#include <QDebug>
#include "diagramwidgets.h"
#include "Folder_CalculateSize.h"
#include "Type_CalculateSize.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

using namespace QtCharts;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_treeView_activated(const QModelIndex &index);

    void on_radioButton_toggled(bool checked);

    void on_radioButton_2_toggled(bool checked);

    void on_radioButton_3_toggled(bool checked);

    void on_radioButton_4_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QModelIndex Currentindex;
    QFileSystemModel *leftDirFileSys;
    diagramwidgets *diagram;
    CalculateSize_TableModel *CalcTableModel;
    QGroupBox *groupbox();
};
#endif // MAINWINDOW_H
