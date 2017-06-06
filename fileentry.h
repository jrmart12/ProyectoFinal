#ifndef FILEENTRY_H
#define FILEENTRY_H
#include <stdio.h>
#include <string.h>
using namespace std;

class fileentry
{
    public:
        fileentry(char *nombre, int empieza, int termina, bool folder, int tamano);
        int tamnom;
        char* nombre;
        int empieza;
        int termina;
        bool EsFolder;
        int TamanoArchivo;
        virtual ~fileentry();

    protected:

    private:
};

#endif // FILEENTRY_H
