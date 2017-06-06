#include "fileentry.h"

fileentry::fileentry(char *nom, int e, int te, bool f, int ta)
{
    this->tamnom=strlen(nom);
    this->nombre=nom;
    this->empieza=e;
    this->termina=te;
    this->EsFolder=f;
    this->TamanoArchivo=ta;
}

fileentry::~fileentry()
{
    //dtor
}
