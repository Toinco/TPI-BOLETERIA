#ifndef ARCHIVO_VENTAS_H_INCLUDED
#define ARCHIVO_VENTAS_H_INCLUDED
#include <string>
#include "Venta.h"

/// Como las bajas son logicas (nunca se borra un registro),
/// la venta con id N esta siempre en la posicion N-1 del archivo.
class archivoVentas{
    private:
        std::string _nombreArchivo;

    public:
        archivoVentas(std::string nombreArchivo="Ventas.dat");
        bool guardar(venta reg);
        bool guardar(venta reg, int posicion);
        int buscar(int idVenta);
        venta leer(int posicion);
        int cantidadRegistros();
};

#endif // ARCHIVO_VENTAS_H_INCLUDED
