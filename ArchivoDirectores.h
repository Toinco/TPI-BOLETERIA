#ifndef ARCHIVODIRECTORES_H_INCLUDED
#define ARCHIVODIRECTORES_H_INCLUDED

#include <string>
#include "Director.h"

/// Como las bajas son logicas (nunca se borra un registro),
/// el director con id N esta siempre en la posicion N-1 del archivo.
class ArchivoDirectores{
    private:
        std::string _nombreArchivo;

    public:
        ArchivoDirectores(std::string nombreArchivo="Directores.dat");
        bool Guardar(Director reg);
        bool Guardar(Director reg, int posicion);
        int Buscar(int idDirector);
        Director Leer(int posicion);
        int CantidadRegistros();
};

#endif // ARCHIVODIRECTORES_H_INCLUDED
