#ifndef ARCHIVOSALAS_H_INCLUDED
#define ARCHIVOSALAS_H_INCLUDED
#include "Sala.h"




class ArchivoSalas {
private:
    char nombreArchivo[30];

public:
    ArchivoSalas(const char* nombre = "Salas.dat");

    bool grabar(Sala reg);
    bool listarRegistros();
    int buscarID(int idSala);


    int CantidadRegistros();
    bool Guardar(Sala reg);
    bool Guardar(Sala reg, int posicion);
    int Buscar(int idSala);
    Sala Leer(int posicion);
};





#endif // ARCHIVOSALAS_H_INCLUDED
