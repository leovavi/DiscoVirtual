#include "fileentry.h"

FileEntry::FileEntry(char * nombre, int pb, int ub, bool esFolder){
    this->nombre = nombre;
    primerBloque = pb;
    ultimoBloque = ub;
    tamArchivo = strlen(nombre)+17;
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
    this->nombre = nombre;
}
