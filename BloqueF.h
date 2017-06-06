#ifndef BLOQUEF_H
#define BLOQUEF_H
#include <list>
#include <iostream>
#include "fileentry.h"
#include <stdio.h>
#include "Archivo.h"
using namespace std;


class BloqueF
{
    public:
        BloqueF(char *nombre, int capacidad,int numero, int siguientebloque, Archivo *a);
        virtual ~BloqueF();
        int numerobloque;
        int tambloque;
        int capacidadbloque;
        int tamnombre;
        char * nombre;
        int sigbloque;
        list <fileentry*> FE;
        Archivo *arch;
        void InitFromChar(char * datos);
        char * BloqueFtoChar();
        void Guardar();
        void agregarfe(fileentry * fe);

    protected:

    private:
};

#endif // BLOQUEF_H
