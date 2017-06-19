#include "fileentry.h"

FileEntry::FileEntry(char * nombre, int pb, int ub, bool esFolder){
    this->nombre = new char[TAMNOMBRE];
    memcpy(this->nombre, nombre, TAMNOMBRE);
    this->nombre[TAMNOMBRE-1] = '\0';
    primerBloque = pb;
    ultimoBloque = ub;
    tamArchivo = TAMNOMBRE+13;
    this->esFolder = esFolder;
}

char * FileEntry::getNombre(){
    return nombre;
}

int FileEntry::getPrimerBloque(){
    return primerBloque;
}

int FileEntry::getUltimoBloque(){
    return ultimoBloque;
}

int FileEntry::getTamArchivo(){
    return tamArchivo;
}

bool FileEntry::esFold(){
    return esFolder;
}

void FileEntry::setNombre(char * nombre){
    this->nombre = new char[TAMNOMBRE];
    memcpy(this->nombre, nombre, TAMNOMBRE);
    this->nombre[TAMNOMBRE-1] = '\0';
}
