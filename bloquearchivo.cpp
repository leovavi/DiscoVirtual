#include "BloqueArchivo.h"

BloqueArchivo::BloqueArchivo(char * nom, char * cont, int pb, int ub, int cap, Archivo * ar){
    nombre = new char[TAMNOMBRE];
    memcpy(nombre, nom, TAMNOMBRE);
    nombre[TAMNOMBRE-1] = '\0';
    contenido = new char[strlen(cont)];
    memcpy(contenido, cont, strlen(cont));
    primerBloque = pb;
    ultimoBloque = ub;
    tamanoBloque = 20 + TAMNOMBRE + strlen(contenido);
    capacidadBloque = cap;
    this->ar = ar;
}

char * BloqueArchivo::getNombre(){
    return nombre;
}

char * BloqueArchivo::getContenido(){
    return contenido;
}

int BloqueArchivo::getPrimerBloque(){
    return primerBloque;
}

int BloqueArchivo::getUltimoBloque(){
    return ultimoBloque;
}

int BloqueArchivo::getTamanoBloque(){
    return tamanoBloque;
}

int BloqueArchivo::getCapacidadBloque(){
    return capacidadBloque;
}

void BloqueArchivo::setNombre(char * nombre){
    this->nombre = new char[TAMNOMBRE];
    memcpy(this->nombre, nombre, TAMNOMBRE);
    this->nombre[TAMNOMBRE-1] = '\0';
}

void BloqueArchivo::setContenido(char * contenido){
    this->contenido = new char[strlen(contenido)+1];
    memcpy(this->contenido, contenido, strlen(contenido));
    this->contenido[strlen(contenido)] = '\0';
}

char * BloqueArchivo::bloqueArchivoToChar(){
    int tam = 20, pos = 0;
    tam += (TAMNOMBRE + strlen(contenido));

    char * data = new char[tam];

    int tamContenido = strlen(contenido);

    memcpy(&(data[pos]), nombre, TAMNOMBRE);
    pos += TAMNOMBRE;
    memcpy(&(data[pos]), &primerBloque, 4);
    pos += 4;
    memcpy(&(data[pos]), &ultimoBloque, 4);
    pos += 4;
    memcpy(&(data[pos]), &tamanoBloque, 4);
    pos += 4;
    memcpy(&(data[pos]), &capacidadBloque, 4);
    pos += 4;
    memcpy(&(data[pos]), &tamContenido, 4);
    pos += 4;
    memcpy(&(data[pos]), contenido, tamContenido);

    return data;
}

void BloqueArchivo::guardar(){
    char * data = bloqueArchivoToChar();
    ar->escribir(primerBloque*capacidadBloque, data, tamanoBloque);
}

void BloqueArchivo::initFromChar(char * data){
    int pos = 0, tamContenido = 0;

    nombre = new char[TAMNOMBRE];
    memcpy(nombre, &(data[pos]), TAMNOMBRE);
    pos += TAMNOMBRE;
    memcpy(&primerBloque, &(data[pos]), 4);
    pos += 4;
    memcpy(&ultimoBloque, &(data[pos]), 4);
    pos += 4;
    memcpy(&tamanoBloque, &(data[pos]), 4);
    pos += 4;
    memcpy(&capacidadBloque, &(data[pos]), 4);
    pos += 4;
    memcpy(&tamContenido, &(data[pos]), 4);
    pos += 4;
    contenido = new char[tamContenido];
    memcpy(contenido, &(data[pos]), tamContenido);
}
