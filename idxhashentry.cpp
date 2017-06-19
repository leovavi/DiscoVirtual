#include "idxhashentry.h"

idxHashEntry::idxHashEntry(char * nombre, int numBloque, int numEntry, int tamBloque, Archivo * ar){
    this->nombre = new char[TAMNOMBRE];
    memcpy(this->nombre, nombre, TAMNOMBRE);
    this->nombre[TAMNOMBRE-1] = '\0';

    numeroBloque = numBloque;
    numeroEntry = numEntry;
    this->tamBloque = tamBloque;
    archivo = ar;
}

idxHashEntry::idxHashEntry(int tamBloque, Archivo *ar){
    this->nombre = new char[TAMNOMBRE];
    numeroBloque = 0;
    numeroEntry = 0;
    this->tamBloque = tamBloque;
    archivo = ar;
}

char * idxHashEntry::getNombre(){
    return nombre;
}

int idxHashEntry::getNumeroBloque(){
    return numeroBloque;
}

int idxHashEntry::getNumeroEntry(){
    return numeroEntry;
}

void idxHashEntry::guardar(int bloqueHash, int entryHash){
    char * data = idxHashEntryToChar();

    int pos = (bloqueHash*tamBloque)+(entryHash*(TAMNOMBRE+8));
    archivo->escribir(pos, data, (TAMNOMBRE+8));
}

void idxHashEntry::initFromChar(char * data){
    nombre = new char[TAMNOMBRE];
    int pos = 0;

    memcpy(nombre, &(data[pos]), TAMNOMBRE);
    pos += TAMNOMBRE;
    memcpy(&numeroBloque, &(data[pos]), 4);
    pos += 4;
    memcpy(&numeroEntry, &(data[pos]), 4);
}

char * idxHashEntry::idxHashEntryToChar(){
    char * data = new char[TAMNOMBRE+8];
    int pos = 0;

    memcpy(&(data[pos]), nombre, TAMNOMBRE);
    pos += TAMNOMBRE;
    memcpy(&(data[pos]), &numeroBloque, 4);
    pos += 4;
    memcpy(&(data[pos]), &numeroEntry, 4);

    return data;
}
