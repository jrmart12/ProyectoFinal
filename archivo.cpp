#include "Archivo.h"

Archivo::Archivo(char * nombre, bool nuevo)
{
    this->nombre = nombre;
    if(nuevo){
        file = fopen(nombre, "w");
        fclose(file);
    }
}

char * Archivo::Read(int pos, int longitud){
    Open();

    char * data = new char[longitud];
    fseek(file, pos, SEEK_SET);
    fread(data, 1, longitud, file);

    return data;
}

void Archivo::Write(int pos, char * data, int longitud){
    Open();
    fseek(file, pos, SEEK_SET);
    fwrite(data, sizeof(char), longitud, file);
    Close();
}

void Archivo::Open(){
    file = fopen(nombre, "r+");
}

void Archivo::Close(){
    fclose(file);
}

void Archivo::setTam(int pos){
    Open();
    fseek(file, pos, SEEK_SET);
    fputc('\0', file);
    Close();
}
