#ifndef ARCHIVO_VENTAS_H_INCLUDED
#define ARCHIVO_VENTAS_H_INCLUDED
#include <string>
#include "venta.h"

/// Como las bajas son logicas (nunca se borra un registro),
/// la pelicula con id N esta siempre en la posicion N-1 del archivo.
class archivoVentas{
    private:
        std::string _nombreArchivo;

    public:
        archivoVentas(std::string nombreArchivo="ventas.dat");
        bool guardar(venta reg);
        bool guardar(venta reg, int posicion);
        int buscar(int idVenta);
        venta leer(int posicion);
        int cantidadRegistros();
};

#endif // ARCHIVO_VENTAS_H_INCLUDED
