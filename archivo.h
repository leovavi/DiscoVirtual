#ifndef ARCHIVO_H
#define ARCHIVO_H
#include <stdio.h>
#include <iostream>

using namespace std;

class Archivo
{
    public:
        Archivo(char * nombre, bool nuevo);
        void abrir();
        char * leer(int pos, int longitud);
        void escribir(int pos, char * data, int longitud);
        void setTamano(int pos);
        void cerrar();

    private:
        FILE * file;
        char * nombre;
};

#endif // ARCHIVO_H
