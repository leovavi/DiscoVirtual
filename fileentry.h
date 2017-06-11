#ifndef FILEENTRY_H
#define FILEENTRY_H
#include <string.h>

class FileEntry
{
    public:
        FileEntry(char * nombre, int pb, int ub, bool esFolder);

        char * getNombre();
        int getPrimerBloque();
        int getUltimoBloque();
        int getTamArchivo();
        bool esFold();

        void setNombre(char * nombre);

    private:
        char * nombre;
        int primerBloque, ultimoBloque, tamArchivo;
        bool esFolder;
};

#endif // FILEENTRY_H
