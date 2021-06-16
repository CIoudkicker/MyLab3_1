#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QMainWindow>
#include <QFileSystemModel>
#include "CalculateSizeModel.h"
#include "CalculateSize_TableModel.h"
#include <QDir>
#include <QString>
#include <QList>
#include <QTreeView>
#include <QListView>
#include <QItemSelectionModel>
#include <QStandardItem>
#include <QGroupBox>
#include <QModelIndex>
#include <QDebug>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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

    void on_treeView_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QModelIndex Currentindex;
    QFileSystemModel *leftDirFileSys;
    CalculateSizeModel *CalcSizeModel;
    CalculateSize_TableModel *CalcTableModel;
    QGroupBox *groupbox();

};
#endif // MAINWINDOW_H
