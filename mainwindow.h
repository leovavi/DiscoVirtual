#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include "discovirtual.h"
#include "files.h"
#include "input.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnFolder_clicked();
    void on_btnArchivo_clicked();
    void mouseDoubleClickEvent(QMouseEvent * event);

private:
    Ui::MainWindow *ui;
    QGraphicsScene * scene;
    QTreeWidgetItem * treeItem;
    QIcon * icon;
    QString path;
    Files * selectedItem;
    FileEntry * selected;

    int actual = 0;
    DiscoVirtual * dv;
    MasterBlock * mb;
    Archivo * archivo;

    void pintarFiles();
    void refresh();
};

#endif // MAINWINDOW_H
