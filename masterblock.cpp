#include "masterblock.h"

MasterBlock::MasterBlock(Archivo * archivo, int tamDisco){
    this->archivo = archivo;
    tamBloque = TAMBLOQUE;
    cantBloques = tamDisco/tamBloque;
    primerBloque = 1;
    sigBloque = -1;
}

void MasterBlock::initFromChar(char * data){
    int pos = 0;
    memcpy(&tamBloque, &(data[pos]), 4);
    pos += 4;
    memcpy(&cantBloques, &(data[pos]), 4);
    pos += 4;
    memcpy(&primerBloque, &(data[pos]), 4);
    pos += 4;
    memcpy(&sigBloque, &(data[pos]), 4);
}

char* MasterBlock::masterBlockToChar(){
    char * data = new char[tamBloque];
    int pos = 0;

    memcpy(&(data[pos]), &tamBloque, 4);
    pos += 4;
    memcpy(&(data[pos]), &cantBloques, 4);
    pos += 4;
    memcpy(&(data[pos]), &primerBloque, 4);
    pos += 4;
    memcpy(&(data[pos]), &sigBloque, 4);

    return data;
}

void MasterBlock::guardar(){
    char * data = masterBlockToChar();
    archivo->escribir(0, data, tamBloque);
}

void MasterBlock::cargar()
{
    char * data = archivo->leer(0,TAMBLOQUE);
    initFromChar(data);
}

int MasterBlock::getTamBloque()
{
    return this->tamBloque;
}

int MasterBlock::getCantBloques()
{
    return this->cantBloques;
}

int MasterBlock::getPrimerBloque()
{
    return this->primerBloque;
}

int MasterBlock::getSigBloque()
{
    return this->sigBloque;
}

void MasterBlock::setTamBloque(int tamBlo)
{
    this->tamBloque = tamBlo;
}

void MasterBlock::setCantBloques(int cantBlo)
{
    this->cantBloques = cantBlo;
}

void MasterBlock::setPrimerBloque(int primerBlo)
{
    this->primerBloque = primerBlo;
}

void MasterBlock::setSigBloque(int sigBlo)
{
    this->sigBloque = sigBlo;
}

