#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    dv = new DiscoVirtual("Disco Virtual", 1024*1024);
    dv->formatear();
    mb = dv->getMasterBlock();
    archivo = dv->getArchivo();
    selected = NULL;
    path = "Raiz";
    actual = 1;

    scene = new QGraphicsScene(parent);
    ui->graphicsView->setScene(scene);
    ui->dir->setText(path);
    ui->lblCant->setText("Cantidad: 0");
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::pintarFiles(){
    scene->clear();

    list<FileEntry*> lista = dv->listarArchivos(actual);

    int posX = -100, posY = 0;

    for(list<FileEntry*>::iterator it = lista.begin(); it!=lista.end(); it++){
        FileEntry * fe = *it;

        bool select = (fe == selected ? true : false);

        posY = (posX>=460 ? posY+140 : posY);
        posX = (posX>=460 ? 30 : posX+130);

        scene->addItem(new Files(fe, posX, posY, select));
    }

    posY = (posY<=140 ? 380 : posY+150);
    scene->setSceneRect(0, 0, 680, posY);
}

void MainWindow::refresh(){
    ui->graphicsView->viewport()->update();
    pintarFiles();
    ui->dir->setText(path);
    ui->lblCant->setText("Cantidad: "+QString::number(dv->getCantEntries(actual)));
}

void MainWindow::on_btnFolder_clicked()
{
    bool confirm = false;

    QString text = QInputDialog::getText(this, tr("Nuevo Folder"), tr("Nombre:"), QLineEdit::Normal, "", &confirm);
    char * nombre = new char[text.size()];
    strcpy(nombre, text.toStdString().c_str());

    if(confirm && !(text.isEmpty())){
        dv->asignarSigBloque(nombre, "", actual, true);
        char * data = archivo->leer((actual*mb->getTamBloque()), mb->getTamBloque());
        BloqueFolder * bf = new BloqueFolder("", 0, 0, archivo);
        bf->initFromChar(data);
        refresh();
    }
}


void MainWindow::on_btnArchivo_clicked()
{
    BloqueArchivo * ba = new BloqueArchivo("", "", 0, 0, 0, archivo);
    Input * inp = new Input(this, ba);
    inp->exec();
    if(strlen(ba->getNombre()) != 0){
        dv->asignarSigBloque(ba->getNombre(), ba->getContenido(), actual , false);
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
    }
}
