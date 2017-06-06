#include "BloqueA.h"

BloqueA::BloqueA(char * nombre, char * contenido, int primerbloque,int ultimobloque,Archivo * a)
{
    this->tamnombre=strlen(nombre);
    this->nombre=nombre;
    this->tamcont=strlen(contenido);
    this->contenido=contenido;
    this->primerbloque=primerbloque;
    this->ultimobloque=ultimobloque;
    this->tambloque=20+tamnombre+tamcont;
    this->arch=a;
    //ultimo bloque, se calcula o va en parametro?

}
char * BloqueA::BloqueArchtoChar()
{
    int pos=0;
    char *datos=new char[tambloque];
    memcpy(&datos[pos],&tambloque,4);
    pos+=4;
    memcpy(&datos[pos],&tamnombre,4);
    pos+=4;
    memcpy(&datos[pos], &nombre,tamnombre);
    pos+=tamnombre;
    memcpy(&datos[pos],&tamcont,4);
    pos+=4;
    memcpy(&datos[pos],&contenido, tamcont);
    pos+=tamcont;
    memcpy(&datos[pos],&primerbloque,4);
    pos+=4;
    memcpy(&datos[pos],&ultimobloque,4);
    pos+=4;
    return datos;


}
void BloqueA::InitFromChar(char * datos)
{

    int pos=0;
    memcpy(&tambloque,&datos[pos],4);
    pos+=4;
    memcpy(&tamnombre,&datos[pos],4);
    pos+=4;
    memcpy(&nombre,&datos[pos],tamnombre);
    pos+=tamnombre;
    memcpy(&tamcont,&datos[pos],4);
    pos+=4;
    memcpy(&contenido,&datos[pos],tamcont);
    pos+=tamcont;
    memcpy(&primerbloque,&datos[pos],4);
    pos+=4;
    memcpy(&ultimobloque,&datos[pos],4);
    pos+=4;



}
void BloqueA::Guardar()
{

    this->arch->Open();
    this->arch->Write(primerbloque*4096,BloqueArchtoChar(),tambloque);
    //empezar a escribir desde primer bloque?
}
BloqueA::~BloqueA()
{
    //dtor
}
