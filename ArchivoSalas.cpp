#include <iostream>
 using namespace std;
#include <cstdio>
#include <cstring>
#include "ArchivoSalas.h"
#include "Sala.h"

ArchivoSalas::ArchivoSalas(const char* nombre) {
    strcpy(nombreArchivo, nombre);
}




bool ArchivoSalas::grabar(Sala reg) {
    FILE *p = fopen(nombreArchivo, "ab");

if (p == NULL) {
        cout << "ERROR: No se pudo abrir el archivo Salas.dat para escritura." << endl;
        return false;
    }


    bool guardo = fwrite(&reg, sizeof(Sala), 1, p);

    fclose(p);


return guardo;
}




bool ArchivoSalas::listarRegistros() {
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == NULL) {
        cout << "No hay salas registradas todavia." << endl;
        return false;
    }

    Sala reg;

    while (fread(&reg, sizeof(Sala), 1, p) == 1) {
        reg.mostrar();
        cout << "-----------------------------------" << endl;
    }

    fclose(p);
    return true;
}



int ArchivoSalas::buscarID(int idBuscado) {
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == NULL) {
        return -1; // Si el archivo no existe, la sala tampoco
    }


    Sala reg;
    int posicion = 0; // Para llevar la cuenta del casillero en el que esta

    while (fread(&reg, sizeof(Sala), 1, p) == 1) {
        if (reg.getIdSala() == idBuscado) {
            fclose(p);
            return posicion; // Si la sala existe devuelve la posición
        }
        posicion++;
    }

    fclose(p);
    return -1; // Esto ya es si no
}


















