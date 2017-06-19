#ifndef DISCOVIRTUAL_H
#define DISCOVIRTUAL_H
#include <list>
#include <QtCore>
#include "archivo.h"
#include "masterblock.h"
#include "BloqueArchivo.h"
#include "fileentry.h"
#include "BloqueFolder.h"
#include "idxhashentry.h"
#include "input.h"

class DiscoVirtual
{
    public:
        DiscoVirtual(char * nombre, int tamDV, bool nuevo);

        DiscoVirtual * crearDiscoVirtual(char * nombreArchivo);
        int asignarSigBloque(char * nombre, char * cont, int actual, bool esFolder);
        int getCantEntries(int actual);

        Archivo * getArchivo();
        int getTamanoDiscoVirtual();
        MasterBlock * getMasterBlock();

        void setArchivo(Archivo * ar);
        void setTamanoDiscoVirtual(int tamDV);
        void setMasterBlock(MasterBlock * mb);

        void formatear();
        int cargarFolder(char * key);
        void cargarArchivo(char * key);
        list<FileEntry *> listarArchivos(int actual);

    private:
        Archivo * archivo;
        MasterBlock * masterBlock;
        int tamanoDiscoVirtual, cantBloquesIdx, cantIndXBloque;
        char * nombreDV;

        int hash(char *key);
        idxHashEntry * asignHashEntry(char * key, int numBloque, int numEntry);
        void copyEntries(list<FileEntry*> * origen, list<FileEntry*> * destino);
};

#endif // DISCOVIRTUAL_H
