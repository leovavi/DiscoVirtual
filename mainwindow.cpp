#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    dv = new DiscoVirtual("Disco Virtual", 1024*1024, false);
//    dv->formatear();
    mb = dv->getMasterBlock();
    archivo = dv->getArchivo();
    selectedFE = new char[TAMNOMBRE];
    path = "Raiz";
    actual = 1;
    posInHistory = 0;
    history.push_back(path);

    scene = new QGraphicsScene(parent);
    ui->graphicsView->setScene(scene);
    ui->dir->setText(path);
    ui->lblCant->setText("Cantidad: 0");
    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderLabel("");
    ui->treeWidget->header()->setFixedHeight(0);
    treeItem = new QTreeWidgetItem(QStringList() << "Raiz");
    icon = new QIcon("C:\\Users\\Leovavi\\Documents\\UNITEC\\Recursos\\File Explorer\\folder.png");
    treeItem->setIcon(0, *icon);
    treeItem->setSelected(true);
    ui->treeWidget->addTopLevelItem(treeItem);
    refresh();
    initTree(treeItem, actual);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::initTree(QTreeWidgetItem * treeItem, int actual){
    list<FileEntry*> lista = dv->listarArchivos(actual);

    for(list<FileEntry*>::iterator it = lista.begin(); it!=lista.end(); it++){
        FileEntry * fe = *it;

        if(fe->esFold()){
            QTreeWidgetItem * newItem = new QTreeWidgetItem(QStringList() << fe->getNombre());
            newItem->setIcon(0, *icon);
            treeItem->addChild(newItem);
            treeItem->setExpanded(true);
            initTree(newItem, fe->getPrimerBloque());
        }
    }

    ui->treeWidget->resizeColumnToContents(0);
}

void MainWindow::refreshTree(QString path){
    QStringList lista = path.split("/");
    treeItem->setSelected(false);
    treeItem = ui->treeWidget->topLevelItem(0);

    for(int i = 1; i<lista.size(); i++){
        QTreeWidgetItem * temp = getHijo(lista.at(i));
        if(temp)
            treeItem = temp;
    }

    treeItem->setSelected(true);
    if(treeItem != ui->treeWidget->topLevelItem(0))
        treeItem->parent()->setExpanded(true);
    ui->treeWidget->resizeColumnToContents(0);
}

QTreeWidgetItem * MainWindow::getHijo(QString nombre){
    for(int i = 0; i<treeItem->childCount(); i++){
        QTreeWidgetItem * temp = treeItem->child(i);
        if(temp->text(0) == nombre)
            return temp;
    }
    return NULL;
}

void MainWindow::addToHistory(){
    if(posInHistory < history.size()-1 && history.at(posInHistory+1) != path){
        for(int i = posInHistory; i<history.size(); i++)
            history.pop_back();
    }

    history.push_back(path);
    posInHistory++;
}

void MainWindow::pintarFiles(){
    scene->clear();

    list<FileEntry*> lista = dv->listarArchivos(actual);

    int posX = -100, posY = 0;

    for(list<FileEntry*>::iterator it = lista.begin(); it!=lista.end(); it++){
        FileEntry * fe = *it;

        bool select = (strcmp(fe->getNombre(), selectedFE) == 0 ? true : false);

        posY = (posX>=460 ? posY+140 : posY);
        posX = (posX>=460 ? 30 : posX+130);

        scene->addItem(new Files(fe->getNombre(), fe->esFold(), posX, posY, select));
    }

    posY = (posY<=140 ? 380 : posY+150);
    scene->setSceneRect(0, 0, 680, posY);
    ui->lblCant->setText("Cantidad: "+QString::number(lista.size()));
}

void MainWindow::refresh(){
    ui->graphicsView->viewport()->update();
    pintarFiles();
    ui->dir->setText(path);
}

void MainWindow::on_btnFolder_clicked()
{
    bool confirm = false;

    QString text = QInputDialog::getText(this, tr("Nuevo Folder"), tr("Nombre:"), QLineEdit::Normal, "", &confirm);
    char * nombre = new char[TAMNOMBRE];
    memcpy(nombre, text.toStdString().c_str(), TAMNOMBRE);

    if(confirm && !(text.isEmpty())){
        int asignado = dv->asignarSigBloque(nombre, "", actual, true);
        if(asignado != -1){
            QTreeWidgetItem * newItem = new QTreeWidgetItem(QStringList() << nombre);
            newItem->setIcon(0, *icon);
            treeItem->addChild(newItem);
            treeItem->setExpanded(true);
            ui->treeWidget->resizeColumnToContents(0);
            refresh();
        }
        else
            QMessageBox::warning(this, tr("Error"), tr("Nombre inválido"));
    }
}


void MainWindow::on_btnArchivo_clicked()
{
    BloqueArchivo * ba = new BloqueArchivo("", "", 0, 0, 0, archivo);
    Input * inp = new Input(this, ba, false);
    inp->exec();
    delete inp;
    if(strlen(ba->getNombre()) != 0){
        int pos = dv->asignarSigBloque(ba->getNombre(), ba->getContenido(), actual , false);
        if(pos != -1)
            refresh();
        else
            QMessageBox::warning(this, tr("Error"), tr("Nombre inválido"));
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    QPoint click = event->pos();
    click.setX(click.x()-140);
    click.setY(click.y()-98);

    QGraphicsItem * item = ui->graphicsView->itemAt(click);

    if(item){
        selectedItem = (Files*)item;
        memcpy(selectedFE, selectedItem->nombre, TAMNOMBRE);
        refresh();
    }
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent * event){
    QPoint click = event->pos();
    click.setX(click.x()-140);
    click.setY(click.y()-98);

    QGraphicsItem * item = ui->graphicsView->itemAt(click);

    if(item != NULL){
        selectedItem = (Files*)item;

        if(selectedItem->esFold){
            int newActual = dv->cargarFolder(selectedItem->nombre);
            qDebug() << "NUEVO ACTUAL " << newActual;
            if(newActual>0){
                qDebug() << newActual;
                actual = newActual;
                QString add(selectedItem->nombre);
                path += "/"+add;
                addToHistory();
                refreshTree(path);
                selectedFE = new char[TAMNOMBRE];
                refresh();
            }
            else
                QMessageBox::information(this, tr("Abrir Archivo"), tr("No se pudo abrir el archivo seleccionado"));
        }
        else{
            qDebug() << selectedFE;
            dv->cargarArchivo(selectedFE);
        }
    }
}

void MainWindow::on_actionNuevo_Archivo_triggered(){on_btnArchivo_clicked();}
void MainWindow::on_actionNuevo_Folder_triggered(){on_btnFolder_clicked();}
void MainWindow::on_actionSalir_triggered(){MainWindow::close();}

void MainWindow::on_actionFormatear_Disco_triggered()
{
    QMessageBox::StandardButton resp;
    resp = QMessageBox::question(this, tr("Formatear Disco"), tr("¿Desea formatear el disco?"),
                                 QMessageBox::Yes | QMessageBox::No);
    if(resp == QMessageBox::Yes){
        dv->formatear();
        actual = 1;
        path = "Raiz";
        ui->treeWidget->clear();
        treeItem = new QTreeWidgetItem(QStringList() << "Raiz");
        treeItem->setIcon(0, *icon);
        treeItem->setSelected(true);
        ui->treeWidget->addTopLevelItem(treeItem);
        posInHistory = 0;
        history.clear();
        history.push_back(path);
        refresh();
    }
}

QString MainWindow::getPath(QTreeWidgetItem * item){
    if(item->text(0) != "Raiz")
        return getPath(item->parent())+"/"+item->text(0);
    return "Raiz";
}

void MainWindow::on_treeWidget_clicked(const QModelIndex &index)
{
    if(ui->treeWidget->currentItem() != treeItem){
        treeItem = ui->treeWidget->currentItem();
        QString newPath = getPath(treeItem);
        QStringList lista = newPath.split("/");
        char * nombre = new char[TAMNOMBRE];
        memcpy(nombre, (lista.at(lista.size()-1)).toStdString().c_str(), TAMNOMBRE);
        nombre[TAMNOMBRE-1] = '\0';
        actual = dv->cargarFolder(nombre);
        if(actual>0){
            path = newPath;
            addToHistory();
            refresh();
        }
    }
}

void MainWindow::on_btnBack_clicked(){
    if(posInHistory > 0){
        posInHistory--;
        path = history.at(posInHistory);
        QStringList lista = path.split("/");
        char * nombre = new char[TAMNOMBRE];
        memcpy(nombre, (lista.at(lista.size()-1)).toStdString().c_str(), TAMNOMBRE);
        int newActual = dv->cargarFolder(nombre);
        if(newActual>0){
            actual = newActual;
            refreshTree(path);
            refresh();
        }
    }
}

void MainWindow::on_btnFront_clicked(){
    if(posInHistory < history.size()-1){
        posInHistory++;
        path = history.at(posInHistory);
        QStringList lista = path.split("/");
        char * nombre = new char[TAMNOMBRE];
        memcpy(nombre, (lista.at(lista.size()-1)).toStdString().c_str(), TAMNOMBRE);
        int newActual = dv->cargarFolder(nombre);
        if(newActual>0){
            actual = newActual;
            refreshTree(path);
            refresh();
        }
    }
}
