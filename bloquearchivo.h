#ifndef BLOQUEARCHIVO_H
#define BLOQUEARCHIVO_H
#include <string.h>
#include "archivo.h"

class BloqueArchivo
{
    public:
        BloqueArchivo(char * nom, char * cont, int pb, int ub, int cap, Archivo * ar);

        char * getNombre();
        char * getContenido();
        int getPrimerBloque();
        int getUltimoBloque();
        int getTamanoBloque();
        int getCapacidadBloque();

        void setNombre(char * nombre);
        void setContenido(char * contenido);
        void guardar();
        void initFromChar(char * data);

    private:
        char * nombre;
        char * contenido;
        int primerBloque, ultimoBloque, tamanoBloque, capacidadBloque;
        Archivo * ar;

        char * bloqueArchivoToChar();
};

#endif // BLOQUEARCHIVO_H
