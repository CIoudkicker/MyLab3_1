#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QMainWindow>
#include <QFileSystemModel>
#include "CalculateSizeModel.h"
#include <QDir>
#include <QString>
#include <QtGui>
#include <QList>
#include <QTreeView>
#include <QListView>
#include <QItemSelectionModel>
#include <QStandardItem>
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
    void on_listView_doubleClicked(const QModelIndex &index);

    void on_treeView_activated(const QModelIndex &index);

    void on_treeView_expanded(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QFileSystemModel *leftDirFileSys;
    CalculateSizeModel *CalcSizeModel;

};
#endif // MAINWINDOW_H
