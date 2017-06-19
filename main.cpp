#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    DiscoVirtual * dv = new DiscoVirtual("disco", 1024*1024, true);
    dv->formatear();
    dv->asignarSigBloque("Fold1", "", 1, true);
    dv->asignarSigBloque("Test2", "", 1, true);
    dv->asignarSigBloque("Test3", "", 1, true);
    dv->asignarSigBloque("Test4", "", 1, true);
    dv->asignarSigBloque("asd", "", 1, true);
    dv->asignarSigBloque("Test5", "", 1, true);
    dv->asignarSigBloque("Test6", "", 1, true);
    dv->asignarSigBloque("Archivo num 1", "Contenido del archivo num 1", 1, false);
    dv->asignarSigBloque("Test7", "", 1, true);
    dv->asignarSigBloque("Test8", "", 1, true);
    dv->asignarSigBloque("Test9", "", 1, true);
    Archivo * ar = dv->getArchivo();
    int actual = 1;

    char * data = ar->leer((actual * dv->getMasterBlock()->getTamBloque()), dv->getMasterBlock()->getTamBloque());

    BloqueFolder * bf = new BloqueFolder("", 0, 0, ar);
    bf->initFromChar(data);

    cout << "--------------\n" << bf->getNombre() << endl;
    cout << bf->getNumeroBloque() << endl;
    cout << bf->getTamBloque() << endl;
    cout << bf->getCapacidadBloque() << endl;

    list<FileEntry*> lista = dv->listarArchivos(actual);

    for(list<FileEntry*>::iterator it = lista.begin(); it!=lista.end(); it++){
        FileEntry * fe = *it;

        cout << "File Entry: " << fe->getNombre() << endl;
        cout << fe->getPrimerBloque() << endl;
        cout << fe->getUltimoBloque() << endl;
        cout << fe->getTamArchivo() << endl;
        cout << (fe->esFold() ? "True" : "False") << endl;
    }

//    Archivo * ar = new Archivo("prueba", true);
//    BloqueFolder * bf = new BloqueFolder("Folder", 1, 4096, ar);
//    bf->guardar();

//    char * data = ar->leer(4096,4096);

//    BloqueFolder * bf2 = new BloqueFolder("", -1, -1, ar);

//    bf2->initFromChar(data);

//    qDebug() << bf2->getNombre();
//    qDebug() << bf2->getNumeroBloque();
//    qDebug() << bf2->getTamBloque();
//    qDebug() << bf2->getSig();
//    qDebug() << bf2->getCapacidadBloque();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
