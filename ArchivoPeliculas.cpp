#include <iostream>
#include <cstdio>

using namespace std;

#include "ArchivoPeliculas.h"

ArchivoPeliculas::ArchivoPeliculas(std::string nombreArchivo){
    _nombreArchivo = nombreArchivo;
}

bool ArchivoPeliculas::Guardar(Pelicula reg){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "ab");
    if(pArchivo == NULL){
        return false;
    }
    bool ok = fwrite(&reg, sizeof(Pelicula), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

bool ArchivoPeliculas::Guardar(Pelicula reg, int posicion){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb+");
    if(pArchivo == NULL){
        return false;
    }
    fseek(pArchivo, sizeof(Pelicula) * posicion, SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Pelicula), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

int ArchivoPeliculas::Buscar(int idPelicula){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return -1;
    }
    Pelicula reg;
    int i = 0;
    while(fread(&reg, sizeof(Pelicula), 1, pArchivo)){
        if(reg.getIdPelicula() == idPelicula){
            fclose(pArchivo);
            return i;
        }
        i++;
    }
    fclose(pArchivo);
    return -1;
}

Pelicula ArchivoPeliculas::Leer(int posicion){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return Pelicula();
    }
    Pelicula reg;
    fseek(pArchivo, sizeof(Pelicula) * posicion, SEEK_SET);
    fread(&reg, sizeof(Pelicula), 1, pArchivo);
    fclose(pArchivo);
    return reg;
}

int ArchivoPeliculas::CantidadRegistros(){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return 0;
    }
    fseek(pArchivo, 0, SEEK_END);
    int cantidadRegistros = ftell(pArchivo) / sizeof(Pelicula);
    fclose(pArchivo);
    return cantidadRegistros;
}
