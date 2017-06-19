#include "BloqueFolder.h"

BloqueFolder::BloqueFolder(char* nom, int numBlo, int capacidadBloque, Archivo* ar)
{
    this->nombre = new char[TAMNOMBRE];
    memcpy(this->nombre, nom, TAMNOMBRE);
    nombre[TAMNOMBRE-1] = '\0';

    this->numeroBloque = numBlo;
    this->tamBloque = TAMNOMBRE+12;
    this->capacidadBloque = capacidadBloque;
    this->sigBloque = -1;
    this->archivo = ar;
}

char* BloqueFolder::getNombre()
{
    return this->nombre;
}

int BloqueFolder::getNumeroBloque()
{
    return this->numeroBloque;
}

int BloqueFolder::getTamBloque(){
    return tamBloque;
}

int BloqueFolder::getCapacidadBloque(){
    return capacidadBloque;
}

int BloqueFolder::getEspacioLibre(){
    return capacidadBloque-tamBloque;
}

int BloqueFolder::getSig(){
    return sigBloque;
}

list<FileEntry*> BloqueFolder::getArchivoEntries()
{
    return archivoEntries;
}

Archivo* BloqueFolder::getArchivo()
{
    return this->archivo;
}

void BloqueFolder::agregarEntry(FileEntry * fe){
    archivoEntries.push_back(fe);
    tamBloque += fe->getTamArchivo();
}

void BloqueFolder::guardar(){
    char * data = bloqueFolderToChar();
    archivo->escribir(numeroBloque*capacidadBloque, data, tamBloque+4);
}

char * BloqueFolder::bloqueFolderToChar(){
    char * data = new char[tamBloque+4];
    int pos = 0;

    memcpy(&(data[pos]), &tamBloque, 4);
    pos += 4;
    memcpy(&(data[pos]), nombre, TAMNOMBRE);
    pos += TAMNOMBRE;
    memcpy(&(data[pos]), &numeroBloque, 4);
    pos += 4;
    memcpy(&(data[pos]), &capacidadBloque, 4);
    pos += 4;
    memcpy(&(data[pos]), &sigBloque, 4);
    pos += 4;

    for(list<FileEntry*>::iterator it = archivoEntries.begin(); it!=archivoEntries.end(); it++){
        FileEntry * fe = *it;
        int pb = fe->getPrimerBloque();
        int ub = fe->getUltimoBloque();
        int tamBloque = fe->getTamArchivo();
        bool esFolder = fe->esFold();

        memcpy(&(data[pos]), fe->getNombre(), TAMNOMBRE);
        pos += TAMNOMBRE;
        memcpy(&(data[pos]), &pb, 4);
        pos += 4;
        memcpy(&(data[pos]), &ub, 4);
        pos += 4;
        memcpy(&(data[pos]), &tamBloque, 4);
        pos += 4;
        memcpy(&(data[pos]), &esFolder, sizeof(bool));
        pos += sizeof(bool);
    }

    return data;
}

void BloqueFolder::initFromChar(char * data){
    int pos = 0;
    archivoEntries.clear();
    memcpy(&tamBloque, &(data[pos]), 4);
    pos += 4;
    nombre = new char[TAMNOMBRE];
    memcpy(nombre, &(data[pos]), TAMNOMBRE);
    pos += TAMNOMBRE;
    memcpy(&numeroBloque, &(data[pos]), 4);
    pos += 4;
    memcpy(&capacidadBloque, &(data[pos]), 4);
    pos += 4;
    memcpy(&sigBloque, &(data[pos]), 4);
    pos += 4;

    for(int i = pos; i<tamBloque; ){
        int pb = 0, ub = 0, tam = 0;
        bool esFolder = false;

        char * nom = new char[TAMNOMBRE];
        memcpy(nom, &(data[i]), TAMNOMBRE);
        i += TAMNOMBRE;
        memcpy(&pb, &(data[i]), 4);
        i += 4;
        memcpy(&ub, &(data[i]), 4);
        i += 4;
        memcpy(&tam, &(data[i]), 4);
        i += 4;
        memcpy(&esFolder, &(data[i]), sizeof(bool));
        i += sizeof(bool);

        FileEntry * fe = new FileEntry(nom, pb, ub, esFolder);
        archivoEntries.push_back(fe);
    }
}

void BloqueFolder::setSig(int sig){
    sigBloque = sig;
}
