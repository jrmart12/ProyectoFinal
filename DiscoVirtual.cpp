#include "DiscoVirtual.h"

DiscoVirtual::DiscoVirtual(char*nombre,int tam)
{
    this->nombre= nombre;
    this->tamano=tam;
    this->ar= new Archivo(nombre,tam);
    foldActual=new BloqueF("",0,0,0,ar);
    formatear();
}
void DiscoVirtual::Regresar()
{

}
void DiscoVirtual::formatear()
{
    mb= new MB(tamano,4096,this->ar);
    BloqueF * raiz= new BloqueF("raiz",this->tambloque,1,-1,ar);
    this->foldActual=raiz;
    raiz->Guardar();
    mb->SiguienteBloqueDisponible=2;;
    mb->Guardar();
}
 list<fileentry*> DiscoVirtual::ListarArchivos(int actual)
 {
    char *data= ar->Read(actual * mb->TamanoBloque,mb->TamanoBloque);
    BloqueF *bf= new BloqueF("",0,0,0,ar);
    bf->InitFromChar(data);

    list<fileentry*> lista=bf->FE;
    while(foldActual->sigbloque!=-1){
        char*data=ar->Read(bf->sigbloque*tambloque,tambloque);
        bf->InitFromChar(data);
        list<fileentry*>::iterator it =lista.end();
        lista.splice(it, bf->FE);
    }

    return lista;
 }
void DiscoVirtual::Open(char * nom )
{
    list<fileentry*> temp=foldActual->FE;

    for(list<fileentry*>::iterator l=temp.begin();l!=temp.end();l++)
    {
        fileentry *imp=*l;
        if(strcmp(imp->nombre, nom) == 0)
        {
            if(imp->EsFolder)
            {
                cout << "lo encontro" << endl;
                char * datos= new char[imp->TamanoArchivo];
                datos=ar->Read(imp->empieza*4096,imp->TamanoArchivo);
                BloqueF * newFolder = new BloqueF("", 0, -1, -1, ar);
                newFolder->InitFromChar(datos);
                foldActual = newFolder;
                cout << "Nombre: " << foldActual->nombre << endl;
                cout << "Primer Bloque: " << foldActual->numerobloque << endl;
                cout << foldActual->capacidadbloque << endl;
                cout << foldActual->sigbloque << endl;
                cout << foldActual->tambloque << endl;
            }
            else
            {
                char * datos= new char[imp->TamanoArchivo];
                cout << imp->empieza << endl;
                datos=ar->Read(imp->empieza*4096,mb->TamanoBloque);
                BloqueA * tempo= new BloqueA("","",2,3,ar);
                tempo->InitFromChar(datos);
                cout<< "Nombre: " << tempo->nombre<<endl;
                cout<< "Contenido: " << tempo->contenido<<endl;
            }
        }
    }
}
void DiscoVirtual::OpenFolder()
{
    cout << foldActual->nombre << endl;
    list<fileentry*> temp=foldActual->FE;

    for(list<fileentry*>::iterator l=temp.begin();l!=temp.end();l++)
    {
        fileentry *imp=*l;
        cout<<imp->nombre<<endl;
    }
}

void DiscoVirtual::AgregarFolder(char * nom)
{
    agregarNuevoBloque(nom,"",this->foldActual->numerobloque,true);
    cout <<"Se Agrego Folder"<<endl;
}

void DiscoVirtual::AgregaArchivo(char * nom, char * cont)
{
    agregarNuevoBloque(nom,cont,this->foldActual->numerobloque,false);
    cout<<"Se Agrego Archivo"<<endl;
}

void DiscoVirtual::agregarNuevoBloque(char*nombre,char*cont,int actual,bool esFolder)
{
    int pb=mb->SiguienteBloqueDisponible;
    int tam=20+strlen(nombre)+strlen(cont);
    int ub= pb+tam/mb->TamanoBloque;
    fileentry *fe= new fileentry("",0,0,false,0);

    if(esFolder){
        BloqueF *bf= new BloqueF(nombre, mb->TamanoBloque, mb->SiguienteBloqueDisponible, -1, ar);
        bf->Guardar();
        mb->SiguienteBloqueDisponible = pb+1;
        fe=new fileentry(nombre,pb,pb,true, 17+strlen(nombre));
    }
    else{
        BloqueA * ba= new BloqueA(nombre,cont,pb,ub,ar);
        ba->Guardar();
        mb->SiguienteBloqueDisponible = pb+1;
        fe= new fileentry(nombre,pb, ub, false, 17+strlen(nombre)+strlen(cont));
    }
    while(foldActual->sigbloque!=-1){
        char * data = ar->Read(foldActual->sigbloque * tambloque, tambloque);
        foldActual->InitFromChar(data);
    }

    if(fe->TamanoArchivo<(foldActual->capacidadbloque-foldActual->tambloque)){
        foldActual->agregarfe(fe);
        foldActual->Guardar();
    }
    else{
        BloqueF *folder= new BloqueF(fe->nombre,tambloque,mb->SiguienteBloqueDisponible, -1, ar);
        foldActual->sigbloque = (folder->numerobloque);
        folder->agregarfe(fe);
        folder->Guardar();
        mb->SiguienteBloqueDisponible = (mb->SiguienteBloqueDisponible+1);
        foldActual->Guardar();
    }
 }
