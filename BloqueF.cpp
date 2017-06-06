#include "BloqueF.h"

BloqueF::BloqueF(char *nombre, int capacidad,int numero, int siguientebloque, Archivo *a)
{
    this->numerobloque=numero;
    this->sigbloque=-1;
    this->capacidadbloque=capacidad;
    this->tamnombre=strlen(nombre);
    this->nombre=nombre;
    this->arch=a;
    this->tambloque=16+tamnombre;
    //sigbloque aqui siempre -1?
}
void BloqueF::InitFromChar(char * datos)
{

    int pos=0;
    memcpy(&numerobloque,&datos[pos],4);
    pos+=4;
    memcpy(&sigbloque,&datos[pos],4);
    pos+=4;
    memcpy(&capacidadbloque,&datos[pos],4);
    pos+=4;
    memcpy(&tambloque, &datos[pos], 4);
    pos += 4;
    memcpy(&tamnombre,&datos[pos],4);
    pos+=4;
    memcpy(&nombre,&datos[pos],tamnombre);
    pos+=tamnombre;


    for(int i = pos; i<tambloque; ){
        fileentry * f = new fileentry("",0,0,true,0);
        memcpy(&f->tamnom,&datos[pos], 4);
        pos += 4;
        memcpy(&f->nombre,&datos[pos], f->tamnom);
        pos += f->tamnom;
        memcpy(&f->empieza,&datos[pos], 4);
        pos += 4;
        memcpy(&f->termina,&datos[pos], 4);
        pos += 4;
        memcpy(&f->TamanoArchivo,&datos[pos], 4);
        pos += 4;
        memcpy(&f->EsFolder,&datos[pos], 1);
        pos += 1;
    }
}
char * BloqueF::BloqueFtoChar()
{
    int pos=0;
    char *datos=new char[tambloque+4];
    memcpy(&datos[pos],&numerobloque,4);
    pos+=4;
    memcpy(&datos[pos],&sigbloque,4);
    pos+=4;
    memcpy(&datos[pos], &capacidadbloque,4);
    pos+=4;
    memcpy(&(datos[pos]), &tambloque, 4);
    pos += 4;
    memcpy(&datos[pos],&tamnombre,4);
    pos+=4;
    memcpy(&datos[pos],&nombre, tamnombre);
    pos+=tamnombre;


      for(list<fileentry*>::iterator it = FE.begin(); it!=FE.end(); it++){
        fileentry * f = *it;
        memcpy(&datos[pos],&(f->tamnom), 4);
        pos += 4;
        memcpy(&datos[pos],&f->nombre, f->tamnom);
        pos += f->tamnom;
        memcpy(&datos[pos],&f->empieza, 4);
        pos += 4;
        memcpy(&datos[pos],&f->termina, 4);
        pos += 4;
        memcpy(&datos[pos],&f->TamanoArchivo, 4);
        pos += 4;
        memcpy(&datos[pos],&f->EsFolder, 1);
        pos += 1;
    }
        return datos;

}
void BloqueF::Guardar()
{


    this->arch->Open();
    this->arch->Write(numerobloque*4096,BloqueFtoChar(),tambloque);

}
void BloqueF::agregarfe(fileentry * fe)
{
    FE.push_back(fe);
    this->tambloque+=17+fe->tamnom;

}
BloqueF::~BloqueF()
{
    //dtor
}
