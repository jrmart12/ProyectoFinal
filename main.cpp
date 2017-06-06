#include <iostream>
#include "DiscoVirtual.h"


using namespace std;

int main()
{
    DiscoVirtual *dv = new DiscoVirtual("C",1024*1024);

    Archivo * ar = new Archivo("disco", 1024*1024);
    BloqueA * ba = new BloqueA("Archivo", "Contenido", 2, 2, ar);
    BloqueF * bf = new BloqueF("Folder1",4096,5,5,ar);

    ba->Guardar();
    bf->Guardar();

    BloqueA * ba2 = new BloqueA("","", 0, 0, ar);
    ba2->InitFromChar(ar->Read(2*4096, 4096));
    BloqueF * bf2 =new BloqueF("",0,0,0,ar);
    bf2->InitFromChar(ar->Read(5*4096,4096));


    dv->AgregarFolder("Folder1");
    dv->AgregarFolder("Foldeer2");
    dv->AgregarFolder("Foldeer3");
    int opcion=0;
    while(opcion!=7)
    {
    cout << "1. Formatear Disco\n2. Crear Folder\n3. Crear Archivo\n4. Listar Archivos\n5. Open Documento\n6. Regresar a Folder Anterior\n7. Salir"<<endl;
    cin >> opcion;
    char *nom=new char[1];
    char * cont=new char[1];

    switch (opcion)
    {
    case 1:
        dv->formatear();
        break;
    case 2:
        cin >> nom;
        dv->AgregarFolder(nom);
        break;
    case 3:
        cin >> nom >>cont;
        dv->AgregaArchivo(nom,cont);
        break;
    case 4:
        dv->OpenFolder();
        break;
    case 5:
        cin >> nom;
        dv->Open(nom);
        break;
    case 6:

        break;
    case 7:
        dv->ar->Close();
        cout<<"Cerrando Programa"<<endl;
        break;
    }
    }


//
//    Archivo * ar = new Archivo("disco", 1024*1024);
//
//    ar->Write(0, "Esto es una prueba2", 50);


    return 0;
}
