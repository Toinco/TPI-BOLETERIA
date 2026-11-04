#ifndef ARCHIVOFUNCIONES_H_INCLUDED
#define ARCHIVOFUNCIONES_H_INCLUDED


class ArchivoFunciones {
private:
    char nombreArchivo[30];

public:
    ArchivoFunciones(const char* nombre = "Funciones.dat");


    bool grabar(Funcion reg);
    bool listarRegistros();


    bool haySuperposicion(Funcion regNueva, int duracionPelicula);
};

#endif // ARCHIVOFUNCIONES_H_INCLUDED
