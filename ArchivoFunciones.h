#ifndef ARCHIVOFUNCIONES_H_INCLUDED
#define ARCHIVOFUNCIONES_H_INCLUDED
#include "Funcion.h"

class ArchivoFunciones {
private:
    char nombreArchivo[30];

public:
    ArchivoFunciones(const char* nombre = "Funciones.dat");

    bool Guardar(Funcion reg);
    bool Guardar(Funcion reg, int posicion);
    int Buscar(int idFuncion);
    Funcion Leer(int posicion);
    int CantidadRegistros();


    bool haySuperposicion(Funcion regNueva, int duracionNueva, int idIgnorar = 0);
};

#endif // ARCHIVOFUNCIONES_H_INCLUDED
