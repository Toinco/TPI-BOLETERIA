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
};







#endif // ARCHIVOSALAS_H_INCLUDED
