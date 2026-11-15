#include <iostream>
#include <cstdio>

using namespace std;

#include "ArchivoPeliculasxGenero.h"

ArchivoPeliculasxGenero::ArchivoPeliculasxGenero(std::string nombreArchivo){
    _nombreArchivo = nombreArchivo;
}

bool ArchivoPeliculasxGenero::Guardar(PeliculaxGenero reg){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "ab");
    if(pArchivo == NULL){
        return false;
    }
    bool ok = fwrite(&reg, sizeof(PeliculaxGenero), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

bool ArchivoPeliculasxGenero::Guardar(PeliculaxGenero reg, int posicion){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb+");
    if(pArchivo == NULL){
        return false;
    }
    fseek(pArchivo, sizeof(PeliculaxGenero) * posicion, SEEK_SET);
    bool ok = fwrite(&reg, sizeof(PeliculaxGenero), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

int ArchivoPeliculasxGenero::Buscar(int idPelicula, int idGenero){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return -1;
    }
    PeliculaxGenero reg;
    int i = 0;
    while(fread(&reg, sizeof(PeliculaxGenero), 1, pArchivo)){
        if(reg.getIdPelicula() == idPelicula && reg.getIdGenero() == idGenero){
            fclose(pArchivo);
            return i;
        }
        i++;
    }
    fclose(pArchivo);
    return -1;
}

PeliculaxGenero ArchivoPeliculasxGenero::Leer(int posicion){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return PeliculaxGenero();
    }
    PeliculaxGenero reg;
    fseek(pArchivo, sizeof(PeliculaxGenero) * posicion, SEEK_SET);
    fread(&reg, sizeof(PeliculaxGenero), 1, pArchivo);
    fclose(pArchivo);
    return reg;
}

int ArchivoPeliculasxGenero::CantidadRegistros(){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return 0;
    }
    fseek(pArchivo, 0, SEEK_END);
    int cantidadRegistros = ftell(pArchivo) / sizeof(PeliculaxGenero);
    fclose(pArchivo);
    return cantidadRegistros;
}
