#include <iostream>
#include <cstdio>

using namespace std;

#include "ArchivoDirectores.h"

ArchivoDirectores::ArchivoDirectores(std::string nombreArchivo){
    _nombreArchivo = nombreArchivo;
}

bool ArchivoDirectores::Guardar(Director reg){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "ab");
    if(pArchivo == NULL){
        return false;
    }
    bool ok = fwrite(&reg, sizeof(Director), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

bool ArchivoDirectores::Guardar(Director reg, int posicion){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb+");
    if(pArchivo == NULL){
        return false;
    }
    fseek(pArchivo, sizeof(Director) * posicion, SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Director), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

int ArchivoDirectores::Buscar(int idDirector){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return -1;
    }
    Director reg;
    int i = 0;
    while(fread(&reg, sizeof(Director), 1, pArchivo)){
        if(reg.getIdDirector() == idDirector){
            fclose(pArchivo);
            return i;
        }
        i++;
    }
    fclose(pArchivo);
    return -1;
}

Director ArchivoDirectores::Leer(int posicion){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return Director();
    }
    Director reg;
    fseek(pArchivo, sizeof(Director) * posicion, SEEK_SET);
    fread(&reg, sizeof(Director), 1, pArchivo);
    fclose(pArchivo);
    return reg;
}

int ArchivoDirectores::CantidadRegistros(){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return 0;
    }
    fseek(pArchivo, 0, SEEK_END);
    int cantidadRegistros = ftell(pArchivo) / sizeof(Director);
    fclose(pArchivo);
    return cantidadRegistros;
}
