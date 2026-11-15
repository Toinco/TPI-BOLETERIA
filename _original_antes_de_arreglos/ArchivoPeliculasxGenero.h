#ifndef ARCHIVOPELICULASXGENERO_H_INCLUDED
#define ARCHIVOPELICULASXGENERO_H_INCLUDED

#include <string>
#include "PeliculaxGenero.h"

class ArchivoPeliculasxGenero{
    private:
        std::string _nombreArchivo;

    public:
        ArchivoPeliculasxGenero(std::string nombreArchivo="PeliculasxGenero.dat");
        bool Guardar(PeliculaxGenero reg);
        bool Guardar(PeliculaxGenero reg, int posicion);
        /// Posicion del par pelicula-genero (activo o dado de baja), o -1.
        int Buscar(int idPelicula, int idGenero);
        PeliculaxGenero Leer(int posicion);
        int CantidadRegistros();
};

#endif // ARCHIVOPELICULASXGENERO_H_INCLUDED
