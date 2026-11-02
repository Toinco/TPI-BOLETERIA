#ifndef ARCHIVOPRECIOS_H_INCLUDED
#define ARCHIVOPRECIOS_H_INCLUDED
#include "Precio.h"

class ArchivoPrecios{
    private:
        char AnombreArchivo[30];

    public:
        ArchivoPrecios(const char *nombre="Precios.dat");
        bool Guardar(Precio reg);

        bool Guardar(Precio reg, int posicion);

        int Buscar(int idTipo);

        Precio Leer(int posicion);

        int CantidadRegistros();

        void cargarPreciosIniciales();
};







#endif // ARCHIVOPRECIOS_H_INCLUDED
