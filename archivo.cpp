#include "archivo.h"

Archivo::Archivo(char * nombre, bool nuevo)
{
    this->nombre = nombre;
    if(nuevo){
        file = fopen(nombre, "w");
        fclose(file);
    }
}

void Archivo::abrir(){
    file = fopen(nombre, "r+");
}

char * Archivo::leer(int pos, int longitud){
    abrir();
    fseek(file, pos, SEEK_SET);
    char * data = new char[longitud];
    fread(data, sizeof(char), longitud, file);

    return data;
}

void Archivo::escribir(int pos, char * data, int longitud){
    abrir();
    fseek(file, pos, SEEK_SET);
    fwrite(data, sizeof(char), longitud, file);
    cerrar();
}

void Archivo::setTamano(int pos){
    abrir();
    fseek(file, pos, SEEK_SET);
    fputc('\0', file);
    cerrar();
}

void Archivo::cerrar(){
    fclose(file);
}
