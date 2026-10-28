#ifndef ARCHIVOGENEROS_H_INCLUDED
#define ARCHIVOGENEROS_H_INCLUDED

#include <string>
#include "Genero.h"

/// Como las bajas son logicas (nunca se borra un registro),
/// el genero con id N esta siempre en la posicion N-1 del archivo.
class ArchivoGeneros{
    private:
        std::string _nombreArchivo;

    public:
        ArchivoGeneros(std::string nombreArchivo="Generos.dat");
        bool Guardar(Genero reg);
        bool Guardar(Genero reg, int posicion);
        int Buscar(int idGenero);
        Genero Leer(int posicion);
        int CantidadRegistros();
};

#endif // ARCHIVOGENEROS_H_INCLUDED
