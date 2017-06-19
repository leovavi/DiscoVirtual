#include "DiscoVirtual.h"

DiscoVirtual::DiscoVirtual(char * nombre, int tamDV, bool nuevo)
{
    nombreDV = nombre;
    archivo = new Archivo(nombreDV, nuevo);
    archivo->abrir();
    this->tamanoDiscoVirtual = tamDV;
    this->masterBlock = new MasterBlock(this->archivo, tamDV);
    int numBloques = masterBlock->getCantBloques()-2;
    cantBloquesIdx = ((numBloques*(TAMNOMBRE+8))/masterBlock->getTamBloque())+1;
    cantIndXBloque = masterBlock->getTamBloque()/(TAMNOMBRE+8);

    if(nuevo){
        masterBlock->setSigBloque(cantBloquesIdx+2);
        masterBlock->guardar();
    }
    else
        masterBlock->cargar();
}

DiscoVirtual * DiscoVirtual::crearDiscoVirtual(char* nombreArchivo)
{
    DiscoVirtual * disc = new DiscoVirtual(nombreArchivo,this->getTamanoDiscoVirtual(), true);
    disc->formatear();
    return disc;
}

void DiscoVirtual::formatear()
{
    archivo = new Archivo(nombreDV, true);
    archivo->setTamano(tamanoDiscoVirtual);
    MasterBlock * mb = new MasterBlock(this->archivo, tamanoDiscoVirtual);
    int numBloques = mb->getCantBloques()-2;
    cantBloquesIdx = ((numBloques*(TAMNOMBRE+8))/mb->getTamBloque())+1;
    cantIndXBloque = masterBlock->getTamBloque()/(TAMNOMBRE+8);
    mb->setSigBloque(cantBloquesIdx+2);

    setMasterBlock(mb);
    masterBlock->guardar();

    BloqueFolder * raiz = new BloqueFolder("Raiz", 1, mb->getTamBloque(), archivo);
    raiz->guardar();
}

int DiscoVirtual::asignarSigBloque(char * nombre, char * cont, int actual, bool esFolder)
{
    int pb = masterBlock->getSigBloque();
    int tam = 20 + strlen(nombre) +strlen(cont);
    int ub = pb + (tam/masterBlock->getTamBloque());

    char * data = archivo->leer((actual * masterBlock->getTamBloque()), masterBlock->getTamBloque());
    BloqueFolder * foldActual = new BloqueFolder("", -1, -1, archivo);
    BloqueFolder * bf;
    foldActual->initFromChar(data);

    FileEntry * fe = new FileEntry("", 0, 0, false);

    int numEntry = foldActual->getArchivoEntries().size();
    idxHashEntry * idxHE = asignHashEntry(nombre, actual, numEntry);
    if(idxHE == NULL)
        return -1;

    if(esFolder){
        bf = new BloqueFolder(nombre, pb, masterBlock->getTamBloque(), archivo);
        bf->guardar();
        masterBlock->setSigBloque(pb+1);

        fe = new FileEntry(bf->getNombre(), bf->getNumeroBloque(), bf->getNumeroBloque(), true);
    }
    else{
        BloqueArchivo * ba = new BloqueArchivo(nombre, cont, pb, ub, masterBlock->getTamBloque(), archivo);
        ba->guardar();
        masterBlock->setSigBloque(ub+1);

        fe = new FileEntry(ba->getNombre(), ba->getPrimerBloque(), ba->getUltimoBloque(), false);
    }

    while(foldActual->getSig() != -1){
        data = archivo->leer((foldActual->getSig()*masterBlock->getTamBloque()), masterBlock->getTamBloque());
        foldActual->initFromChar(data);
    }

    if(fe->getTamArchivo()<foldActual->getEspacioLibre()){
        foldActual->agregarEntry(fe);
        foldActual->guardar();
    }
    else{
        foldActual->setSig(masterBlock->getSigBloque());
        foldActual->guardar();

        BloqueFolder * sigBF = new BloqueFolder(bf->getNombre(), foldActual->getSig(), masterBlock->getTamBloque(), archivo);
        sigBF->agregarEntry(fe);
        sigBF->guardar();
        masterBlock->setSigBloque(masterBlock->getSigBloque()+1);
    }

    masterBlock->guardar();
    return 0;
}

int DiscoVirtual::getCantEntries(int actual){
    char * data = archivo->leer((actual * masterBlock->getTamBloque()), masterBlock->getTamBloque());
    BloqueFolder * bf = new BloqueFolder("", 0, 0, archivo);
    bf->initFromChar(data);
    list<FileEntry*> lista = bf->getArchivoEntries();
    int cant = lista.size();

    while(bf->getSig() != -1){
        char * data = archivo->leer((bf->getSig()*masterBlock->getTamBloque()), masterBlock->getTamBloque());
        bf->initFromChar(data);
        lista = bf->getArchivoEntries();
        cant += lista.size();
    }

    return cant;
}

void DiscoVirtual::copyEntries(list<FileEntry*> * origen, list<FileEntry*> * destino){
    for(list<FileEntry*>::iterator it = origen->begin(); it!=origen->end(); it++){
        FileEntry * fe = *it;
        destino->push_back(fe);
    }
}

list<FileEntry *> DiscoVirtual::listarArchivos(int actual)
{
    char * data = archivo->leer((actual * masterBlock->getTamBloque()), masterBlock->getTamBloque());
    BloqueFolder * bf = new BloqueFolder("", 0, 0, archivo);
    bf->initFromChar(data);

    list<FileEntry*> entries = bf->getArchivoEntries();

    while(bf->getSig() != -1){
        data = archivo->leer(bf->getSig()*masterBlock->getTamBloque(), masterBlock->getTamBloque());
        bf->initFromChar(data);
        list<FileEntry*> origen = bf->getArchivoEntries();
        copyEntries(&origen, &entries);
    }

    return entries;
}

int DiscoVirtual::cargarFolder(char * key)
{
    cout << key << endl;
    if(strcmp("Raiz", key) == 0)
        return 1;

    int pos = hash(key);
    cout << pos << endl;
    int numBloqueHash = (pos/masterBlock->getTamBloque())+2;
    int numEntryHash = pos%cantIndXBloque;
    int posArchivo = (numBloqueHash*masterBlock->getTamBloque())+(numEntryHash*(TAMNOMBRE+8));
    char * data = archivo->leer(posArchivo, (TAMNOMBRE+8));

    idxHashEntry * idxHE = new idxHashEntry(masterBlock->getTamBloque(), archivo);
    idxHE->initFromChar(data);

    cout << idxHE->getNombre() << endl;

    if(strcmp(idxHE->getNombre(), key) == 0){
        list<FileEntry*> lista = listarArchivos(idxHE->getNumeroBloque());
        list<FileEntry*>::iterator it = lista.begin();
        advance(it, idxHE->getNumeroEntry());
        FileEntry * fe = *it;
        return fe->getPrimerBloque();
    }

    return -1;
}

void DiscoVirtual::cargarArchivo(char * key){
    if(key == "Raiz")
        return;

    int pos = hash(key);
    cout << pos << endl;
    int numBloqueHash = (pos/masterBlock->getTamBloque())+2;
    int numEntryHash = pos%cantIndXBloque;
    int posArchivo = (numBloqueHash*masterBlock->getTamBloque())+(numEntryHash*(TAMNOMBRE+8));
    char * data = archivo->leer(posArchivo, (TAMNOMBRE+8));

    idxHashEntry * idxHE = new idxHashEntry(masterBlock->getTamBloque(), archivo);
    idxHE->initFromChar(data);

    if(strcmp(idxHE->getNombre(), key) == 0){
        cout << "ENTRA A IDXHE" << endl;
        cout << "Numero de bloque " << idxHE->getNumeroBloque() << endl;
        list<FileEntry*> lista = listarArchivos(idxHE->getNumeroBloque());
        list<FileEntry*>::iterator it = lista.begin();
        advance(it, idxHE->getNumeroEntry());
        FileEntry * fe = *it;

        if(!fe->esFold()){
            BloqueArchivo * ba = new BloqueArchivo("", "", -1, -1, masterBlock->getTamBloque(), archivo);
            data = archivo->leer(fe->getPrimerBloque()*masterBlock->getTamBloque(),
                                 ((fe->getUltimoBloque()-fe->getPrimerBloque())+1)*masterBlock->getTamBloque());
            ba->initFromChar(data);

            Input * inp = new Input(NULL, ba, true);
            inp->exec();
            delete inp;
        }
    }
}

int DiscoVirtual::hash(char * key){
    int sum = 0;

    for (int k = 0; k < strlen(key); k++)
        sum = sum + int(key[k]);

    return  sum;
}

idxHashEntry * DiscoVirtual::asignHashEntry(char * key, int numBloque, int numEntry){
    char * newKey = new char[TAMNOMBRE];
    memcpy(newKey, key, TAMNOMBRE);
    newKey[TAMNOMBRE-1] = '\0';
    int pos = hash(newKey);
    cout << pos << " Para key " << newKey << endl;
    int numBloqueHash = (pos/masterBlock->getTamBloque())+2;
    int numEntryHash = pos%cantIndXBloque;
    int posArchivo = (numBloqueHash*masterBlock->getTamBloque())+(numEntryHash*(TAMNOMBRE+8));
    char * data = archivo->leer(posArchivo, (TAMNOMBRE+8));

    idxHashEntry * idxHE = new idxHashEntry(masterBlock->getTamBloque(), archivo);
    idxHE->initFromChar(data);

    if(strcmp(key, idxHE->getNombre()) == 0){
        return NULL;
    }
    else{
        idxHE = new idxHashEntry(key, numBloque, numEntry, masterBlock->getTamBloque(), archivo);
        idxHE->guardar(numBloqueHash, numEntryHash);
        return idxHE;
    }
}

Archivo * DiscoVirtual::getArchivo()
{
    return this->archivo;
}

MasterBlock* DiscoVirtual::getMasterBlock()
{
    return this->masterBlock;
}

void DiscoVirtual::setMasterBlock(MasterBlock* mb)
{
    this->masterBlock = mb;
}

void DiscoVirtual::setArchivo(Archivo* ar)
{
    this->archivo = ar;
}
int DiscoVirtual::getTamanoDiscoVirtual()
{
    return this->tamanoDiscoVirtual;
}

void DiscoVirtual::setTamanoDiscoVirtual(int tamDV)
{
    this->tamanoDiscoVirtual = tamDV;
    archivo->setTamano(tamanoDiscoVirtual);
}
