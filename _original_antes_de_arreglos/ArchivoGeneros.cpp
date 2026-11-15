#include <iostream>
#include <cstdio>

using namespace std;

#include "ArchivoGeneros.h"

ArchivoGeneros::ArchivoGeneros(std::string nombreArchivo){
    _nombreArchivo = nombreArchivo;
}

bool ArchivoGeneros::Guardar(Genero reg){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "ab");
    if(pArchivo == NULL){
        return false;
    }
    bool ok = fwrite(&reg, sizeof(Genero), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

bool ArchivoGeneros::Guardar(Genero reg, int posicion){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb+");
    if(pArchivo == NULL){
        return false;
    }
    fseek(pArchivo, sizeof(Genero) * posicion, SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Genero), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

int ArchivoGeneros::Buscar(int idGenero){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return -1;
    }
    Genero reg;
    int i = 0;
    while(fread(&reg, sizeof(Genero), 1, pArchivo)){
        if(reg.getIdGenero() == idGenero){
            fclose(pArchivo);
            return i;
        }
        i++;
    }
    fclose(pArchivo);
    return -1;
}

Genero ArchivoGeneros::Leer(int posicion){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return Genero();
    }
    Genero reg;
    fseek(pArchivo, sizeof(Genero) * posicion, SEEK_SET);
    fread(&reg, sizeof(Genero), 1, pArchivo);
    fclose(pArchivo);
    return reg;
}

int ArchivoGeneros::CantidadRegistros(){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return 0;
    }
    fseek(pArchivo, 0, SEEK_END);
    int cantidadRegistros = ftell(pArchivo) / sizeof(Genero);
    fclose(pArchivo);
    return cantidadRegistros;
}
