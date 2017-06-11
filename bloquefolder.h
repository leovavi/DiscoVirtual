#ifndef BLOQUEFOLDER_H
#define BLOQUEFOLDER_H
#include <list>
#include <string.h>
#include "fileentry.h"
#include "archivo.h"

class BloqueFolder
{
    public:
        BloqueFolder(char * nom, int numBlo, int capacidadBloque, Archivo * ar);

        char * getNombre();
        int getNumeroBloque();
        int getTamBloque();
        int getCapacidadBloque();
        int getEspacioLibre();
        int getSig();
        list<FileEntry*> getArchivoEntries();
        Archivo * getArchivo();

        void agregarEntry(FileEntry * fe);
        void guardar();
        void initFromChar(char * data);
        void setSig(int sig);

    private:
        int numeroBloque, tamBloque, capacidadBloque, sigBloque;
        char * nombre;
        list <FileEntry*> archivoEntries;
        Archivo * archivo;

        char * bloqueFolderToChar();
};

#endif // BLOQUEFOLDER_H
