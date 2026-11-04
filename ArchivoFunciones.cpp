#include <iostream>
using namespace std;
#include <cstdio>
#include <cstring>
#include "ArchivoFunciones.h"
#include "ArchivoPeliculas.h"

ArchivoFunciones::ArchivoFunciones(const char* nombre){
    strcpy(nombreArchivo, nombre);
}

bool ArchivoFunciones::Guardar(Funcion reg){
    FILE *p = fopen(nombreArchivo, "ab");
    if(p == NULL){
        return false;
    }
    bool ok = fwrite(&reg, sizeof(Funcion), 1, p);
    fclose(p);
    return ok;
}

bool ArchivoFunciones::Guardar(Funcion reg, int posicion){
    FILE *p = fopen(nombreArchivo, "rb+");
    if(p == NULL){
        return false;
    }
    fseek(p, sizeof(Funcion) * posicion, SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Funcion), 1, p);
    fclose(p);
    return ok;
}

int ArchivoFunciones::Buscar(int idBuscado){
    FILE *p = fopen(nombreArchivo, "rb");
    if(p == NULL){
        return -1;
    }
    Funcion reg;
    int posicion = 0;
    while(fread(&reg, sizeof(Funcion), 1, p) == 1){
        if(reg.getIdFuncion() == idBuscado){
            fclose(p);
            return posicion;
        }
        posicion++;
    }
    fclose(p);
    return -1;
}

Funcion ArchivoFunciones::Leer(int posicion){
    Funcion reg;
    FILE *p = fopen(nombreArchivo, "rb");
    if(p == NULL){
        return reg;
    }
    fseek(p, sizeof(Funcion) * posicion, SEEK_SET);
    fread(&reg, sizeof(Funcion), 1, p);
    fclose(p);
    return reg;
}

int ArchivoFunciones::CantidadRegistros(){
    FILE *p = fopen(nombreArchivo, "rb");
    if(p == NULL){
        return 0;
    }
    fseek(p, 0, SEEK_END);
    int cantidad = ftell(p) / sizeof(Funcion);
    fclose(p);
    return cantidad;
}

bool ArchivoFunciones::haySuperposicion(Funcion regNueva, int duracionNueva, int idIgnorar){
    FILE *p = fopen(nombreArchivo, "rb");
    if(p == NULL){
        return false;   /// si el archivo no existe todavia, no hay superposicion
    }

    Funcion regExistente;
    ArchivoPeliculas archPeliculas;

    while(fread(&regExistente, sizeof(Funcion), 1, p) == 1){
        if(regExistente.getEliminado()){
            continue;
        }
        if(regExistente.getIdFuncion() == idIgnorar){
            continue;
        }

        int duracionExistente = 0;
        int posPeli = archPeliculas.Buscar(regExistente.getIdPelicula());
        if(posPeli != -1){
            Pelicula peli = archPeliculas.Leer(posPeli);
            duracionExistente = peli.getDuracionMinutos();
        }

        if(regNueva.seSuperpone(regExistente, duracionNueva, duracionExistente)){
            fclose(p);
            return true;
        }
    }

    fclose(p);
    return false;
}










