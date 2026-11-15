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
        return -1;
    }

    Sala reg;
    int posicion = 0;

    while (fread(&reg, sizeof(Sala), 1, p) == 1) {
        if (reg.getIdSala() == idBuscado) {
            fclose(p);
            return posicion;
        }
        posicion++;
    }

    fclose(p);
    return -1;
}

// Cuenta los registros guardados
int ArchivoSalas::CantidadRegistros() {
    FILE *p = fopen(nombreArchivo, "rb");

    if (p == NULL) {
        return 0;
    }

    Sala reg;
    int cantidad = 0;

    while (fread(&reg, sizeof(Sala), 1, p) == 1) {
        cantidad++;
    }

    fclose(p);
    return cantidad;
}

// Guarda una sala nueva
bool ArchivoSalas::Guardar(Sala reg) {
    return grabar(reg);
}

// Reemplaza una sala en una posicion existente
bool ArchivoSalas::Guardar(Sala reg, int posicion) {
    FILE *p = fopen(nombreArchivo, "rb+");

    if (p == NULL) {
        return false;
    }

    fseek(p, sizeof(Sala) * posicion, SEEK_SET);

    bool guardo = fwrite(&reg, sizeof(Sala), 1, p);

    fclose(p);
    return guardo;
}

// Busca una sala por su ID
int ArchivoSalas::Buscar(int idSala) {
    return buscarID(idSala);
}

// Lee una sala por su posicion
Sala ArchivoSalas::Leer(int posicion) {
    Sala reg;

    FILE *p = fopen(nombreArchivo, "rb");

    if (p == NULL) {
        return reg;
    }

    fseek(p, sizeof(Sala) * posicion, SEEK_SET);
    fread(&reg, sizeof(Sala), 1, p);

    fclose(p);
    return reg;
}


















