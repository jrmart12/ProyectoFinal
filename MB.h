#ifndef MB_H
#define MB_H
#include "Archivo.h"
#include <stdio.h>
#include <string.h>
using namespace std;


class MB
{
    public:
        MB(int tamArch, int tamB, Archivo *a);
        int TamanoBloque;
        int CantidadBloques;
        //primer bloque Archivo?
        int SiguienteBloqueDisponible;
        Archivo *arch;
        char *MasterBlockToChar();
        void Guardar();
        void Initfromchar(char *data);
        void Cargar();
        virtual ~MB();

    protected:

    private:
};

#endif // MB_H
