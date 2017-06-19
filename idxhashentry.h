#ifndef IDXHASHENTRY_H
#define IDXHASHENTRY_H
#define TAMNOMBRE 25
#include <string.h>
#include "archivo.h"

class idxHashEntry
{
public:
    idxHashEntry(char * nombre, int numBloque, int numEntry, int tamBloque, Archivo * ar);
    idxHashEntry(int tamBloque, Archivo * ar);

    char * getNombre();
    int getNumeroBloque();
    int getNumeroEntry();
    void guardar(int bloqueHash, int entryHash);
    void initFromChar(char * data);

private:
    char * nombre;
    int numeroBloque, numeroEntry, tamBloque;
    Archivo * archivo;

    char * idxHashEntryToChar();
};

#endif // IDXHASHENTRY_H
