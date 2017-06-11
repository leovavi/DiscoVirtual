#ifndef MASTERBLOCK_H
#define MASTERBLOCK_H
#define TAMBLOQUE 4096
#include <string.h>
#include "archivo.h"

class MasterBlock
{
    public:
        MasterBlock(Archivo * archivo, int tamDisco);
        void guardar();
        void cargar();

        int getTamBloque();
        int getCantBloques();
        int getPrimerBloque();
        int getSigBloque();

        void setTamBloque(int tamBlo);
        void setCantBloques(int cantBlo);
        void setPrimerBloque(int primerBlo);
        void setSigBloque(int sigBlo);

    private:
        int tamBloque, cantBloques, primerBloque, sigBloque;
        Archivo * archivo;

        void initFromChar(char * data);
        char * masterBlockToChar();
};

#endif // MASTERBLOCK_H
