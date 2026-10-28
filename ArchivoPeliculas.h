#ifndef ARCHIVOPELICULAS_H_INCLUDED
#define ARCHIVOPELICULAS_H_INCLUDED

#include <string>
#include "Pelicula.h"

/// Como las bajas son logicas (nunca se borra un registro),
/// la pelicula con id N esta siempre en la posicion N-1 del archivo.
class ArchivoPeliculas{
    private:
        std::string _nombreArchivo;

    public:
        ArchivoPeliculas(std::string nombreArchivo="Peliculas.dat");
        bool Guardar(Pelicula reg);
        bool Guardar(Pelicula reg, int posicion);
        int Buscar(int idPelicula);
        Pelicula Leer(int posicion);
        int CantidadRegistros();
};

#endif // ARCHIVOPELICULAS_H_INCLUDED
