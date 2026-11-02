#ifndef FUNCION_H_INCLUDED
#define FUNCION_H_INCLUDED

#include "Fecha.h"
#include "Horario.h"

class Funcion {
private:
    int idFuncion;
    int idPelicula;
    int idSala;
    Fecha fecha;
    Horario horario;
    bool eliminado;

public:
    Funcion();

    int getIdFuncion();
    int getIdPelicula();
    int getIdSala();
    Fecha getFecha();
    Horario getHorario();
    bool getEliminado();
    void setIdFuncion(int id);
    void setIdPelicula(int id);
    void setIdSala(int id);
    void setFecha(Fecha f);
    void setHorario(Horario h);
    void setEliminado(bool e);
///---
    void cargar();
    void mostrar();
///--- Esto es para que no se repitan lo horarios de las funciones
    bool mismaFecha(Funcion otra);
    int horaFin(int duracionMinutos);
    bool seSuperpone(Funcion otra,
                     int duracionEsta,
                     int duracionOtra);
};







#endif // FUNCION_H_INCLUDED
