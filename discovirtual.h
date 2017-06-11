#ifndef DISCOVIRTUAL_H
#define DISCOVIRTUAL_H
#include <list>
#include "archivo.h"
#include "masterblock.h"
#include "BloqueArchivo.h"
#include "fileentry.h"
#include "BloqueFolder.h"

class DiscoVirtual
{
    public:
        DiscoVirtual(char * nombre, int tamDV);

        DiscoVirtual * crearDiscoVirtual(char * nombreArchivo);
        void asignarSigBloque(char * nombre, char * cont, int actual, bool esFolder);
        int getCantEntries(int actual);

        Archivo * getArchivo();
        int getTamanoDiscoVirtual();
        MasterBlock * getMasterBlock();

        void setArchivo(Archivo * ar);
        void setTamanoDiscoVirtual(int tamDV);
        void setMasterBlock(MasterBlock * mb);

        void formatear();
        void cargar();
        list<FileEntry *> listarArchivos(int actual);

    private:
        Archivo * archivo;
        MasterBlock * masterBlock;
        int tamanoDiscoVirtual;
        char * nombreDV;

        void copyEntries(list<FileEntry*> * origen, list<FileEntry*> * destino);
};

#endif // DISCOVIRTUAL_H
