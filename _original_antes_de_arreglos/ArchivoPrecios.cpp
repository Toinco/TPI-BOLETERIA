#include <iostream>
 using namespace std;
#include <cstdio>
#include "ArchivoPrecios.h"
#include <cstring>

ArchivoPrecios::ArchivoPrecios(const char *nombre){
    strcpy(AnombreArchivo, nombre);
}

bool ArchivoPrecios::Guardar(Precio reg){ ///Agrega un precio al final del archivo
    FILE *pArchivo = fopen(AnombreArchivo, "ab");
    if(pArchivo == NULL){
        return false;
    }
    bool ok = fwrite(&reg, sizeof(Precio), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

bool ArchivoPrecios::Guardar(Precio reg, int posicion){
    FILE *pArchivo = fopen(AnombreArchivo, "rb+");
    if(pArchivo == NULL){
        return false;
    }
    fseek(pArchivo, sizeof(Precio) *posicion, SEEK_SET);
bool ok = fwrite(&reg, sizeof(Precio), 1, pArchivo);

    fclose(pArchivo);

    return ok;
}


int ArchivoPrecios::CantidadRegistros(){
    FILE *pArchivo = fopen(AnombreArchivo, "rb");
    if(pArchivo == NULL){
        return 0;
    }
    Precio reg;
    int cantidad = 0;
    while(fread(&reg, sizeof(Precio), 1, pArchivo) == 1){
        cantidad++;
    }
    fclose(pArchivo);
    return cantidad;
}

int ArchivoPrecios::Buscar(int idTipo){
    FILE *pArchivo = fopen(AnombreArchivo, "rb");
    if(pArchivo == NULL){
        return -1;
    }
    Precio reg;
    int posicion = 0;
    while(fread(&reg, sizeof(Precio), 1, pArchivo) == 1){
      if(reg.getIdTipo() == idTipo){
            fclose(pArchivo);
            return posicion;
        }
        posicion++;
    }
    fclose(pArchivo);
    return -1;
}

Precio ArchivoPrecios::Leer(int posicion){
    Precio reg;
    FILE *pArchivo = fopen(AnombreArchivo, "rb");
    if(pArchivo == NULL){
        return reg;
    }
   fseek(pArchivo, sizeof(Precio) * posicion, SEEK_SET);
    fread(&reg, sizeof(Precio), 1, pArchivo);
    fclose(pArchivo);
    return reg;
}


    void ArchivoPrecios::cargarPreciosIniciales(){

    if(CantidadRegistros() > 0){
        return;
    }

    const char *nombres[4] = {"IMAX", "3D", "2D", "4D"};
    float precios[4] = {20000, 18000, 15000, 22000};

    for(int i = 0; i < 4; i++){
        Precio reg;

        reg.setIdTipo(i + 1);
        reg.setNombre(nombres[i]);
        reg.setPrecio(precios[i]);

        Guardar(reg);
    }
}


