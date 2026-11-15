#include <iostream>
#include <cstdio>
using namespace std;
#include "ArchivoVentas.h"
#include "Venta.h"

archivoVentas::archivoVentas(std::string nombreArchivo){
    _nombreArchivo = nombreArchivo;
}

bool archivoVentas::guardar(venta reg){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "ab");
    if(pArchivo == NULL){
        return false;
    }
    bool ok = fwrite(&reg, sizeof(venta), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

bool archivoVentas::guardar(venta reg, int posicion){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb+");
    if(pArchivo == NULL){
        return false;
    }
    fseek(pArchivo, sizeof(venta) * posicion, SEEK_SET);
    bool ok = fwrite(&reg, sizeof(venta), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

int archivoVentas::buscar(int idVenta){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return -1;
    }
    venta reg;
    int i = 0;
    while(fread(&reg, sizeof(venta), 1, pArchivo)){
        if(reg.getIdVenta() == idVenta){
            fclose(pArchivo);
            return i;
        }
        i++;
    }
    fclose(pArchivo);
    return -1;
}

venta archivoVentas::leer(int posicion){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return venta();
    }
    venta reg;
    fseek(pArchivo, sizeof(venta) * posicion, SEEK_SET);
    fread(&reg, sizeof(venta), 1, pArchivo);
    fclose(pArchivo);
    return reg;
}

int archivoVentas::cantidadRegistros(){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return 0;
    }
    fseek(pArchivo, 0, SEEK_END);
    int cantidadRegistros = ftell(pArchivo) / sizeof(venta);
    fclose(pArchivo);
    return cantidadRegistros;
}
