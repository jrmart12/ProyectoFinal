#ifndef DISCOVIRTUAL_H
#define DISCOVIRTUAL_H
#include "Archivo.h"
#include "MB.h"
#include "fileentry.h"
#include "list"
#include "BloqueA.h"
#include "BloqueF.h"
#include "iostream"
#include "string"
#include <list>
#include <stdio.h>

class DiscoVirtual
{
    public:
        DiscoVirtual(char * nombre, int tam);
        void formatear();
        list<fileentry*> ListarArchivos(int actual);
        void agregarNuevoBloque(char*nombre,char *cont,int actual,bool esFolder);
        Archivo *ar;
        char* nombre;
        int tambloque=4096;
        MB *mb;
        int tamano;
        BloqueF * foldActual;
        void AgregarFolder(char * nom);
        void AgregaArchivo(char * nom, char * cont);
        void Regresar();
        void OpenFolder();
        void Open(char * nom);
    protected:

    private:
};

#endif // DISCOVIRTUAL_H
