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
    void mousePressEvent(QMouseEvent * event);
    void mouseDoubleClickEvent(QMouseEvent * event);

    void on_actionNuevo_Archivo_triggered();

    void on_actionNuevo_Folder_triggered();

    void on_actionSalir_triggered();

    void on_actionFormatear_Disco_triggered();

    void on_treeWidget_clicked(const QModelIndex &index);

    void on_btnBack_clicked();

    void on_btnFront_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene * scene;
    QTreeWidgetItem * treeItem;
    QIcon * icon;
    QString path;
    QVector<QString> history;
    Files * selectedItem;

    char * selectedFE;
    int actual = 0, posInHistory = 0;
    DiscoVirtual * dv;
    MasterBlock * mb;
    Archivo * archivo;

    void pintarFiles();
    void refresh();
    void initTree(QTreeWidgetItem *treeItem, int actual);
    void refreshTree(QString path);
    void addToHistory();
    QTreeWidgetItem * getHijo(QString nombre);
    QString getPath(QTreeWidgetItem * item);
};

#endif // MAINWINDOW_H
