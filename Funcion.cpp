#include <iostream>
 #include "Funcion.h"
#include "FuncionesGlobales.h"
#include "Validaciones.h"
#include "ArchivoSalas.h"
using namespace std;

Funcion::Funcion(){
    idFuncion = 0;
    idPelicula = 0;
    idSala = 0;
    eliminado = false;
}

int Funcion::getIdFuncion(){
    return idFuncion;
}

int Funcion::getIdPelicula(){
    return idPelicula;
}

int Funcion::getIdSala() {
    return idSala;
}

Horario Funcion::getHorario() {
    return horario;
}

Fecha Funcion::getFecha(){
    return fecha;
}

bool Funcion::getEliminado() {
    return eliminado;
}

void Funcion::setIdFuncion(int id){
    idFuncion = id;
}

void Funcion::setIdPelicula(int id) {
    idPelicula = id;
}

void Funcion::setIdSala(int id){
    idSala = id;
}

void Funcion::setHorario(Horario h){
    horario = h;
}

void Funcion::setFecha(Fecha f) {
    fecha = f;
}

void Funcion::setEliminado(bool e){
    eliminado = e;
}

///---

void Funcion::cargar() {
    idPelicula = pedirIdPeliculaActiva();

    idSala = pedirIdSalaActiva();
/// ------------------

    cout<<"FECHA DE LA FUNCION" <<endl;
    fecha.cargar();

    cout<<"HORARIO DE LA FUNCION" <<endl;
    horario.cargar();

    eliminado = false;
}

void Funcion::mostrar() {
    cout<<"ID de funcion: "<<idFuncion<< endl;
    cout<<"ID de pelicula: "<<idPelicula<< endl;
    cout<<"ID de sala: "<<idSala<<endl;

    cout<<"Fecha: ";
    fecha.mostrar();
    cout<<endl;

    cout<<"Horario: ";
    horario.mostrar();
    cout<<endl;

    cout<<"Eliminado: ";
    if (eliminado) {
        cout<< "Si";
    } else {
        cout<< "No";
    }

    cout<<endl;
}


///---



bool Funcion::mismaFecha(Funcion otra) {
    Fecha fechaOtra = otra.getFecha();

    return fecha.getDia() == fechaOtra.getDia() && fecha.getMes() == fechaOtra.getMes() && fecha.getAnio() == fechaOtra.getAnio();
}

int Funcion::horaFin(int duracionMinutos) {
    return horario.aMinutos() + duracionMinutos;
}

bool Funcion::seSuperpone(Funcion otra, int duracionEsta, int duracionOtra) {
    if (eliminado || otra.getEliminado()) {
        return false;
    }

    if (idSala != otra.getIdSala()) {
        return false;
    }

    if (!mismaFecha(otra)) {
        return false;
    }

    if (duracionEsta <= 0 || duracionOtra <= 0) {
        return false;
    }

    int inicioEsta = horario.aMinutos();
    int finEsta = horaFin(duracionEsta);

    Horario horarioOtra = otra.getHorario();

    int inicioOtra = horarioOtra.aMinutos();
    int finOtra = inicioOtra + duracionOtra;

    return inicioEsta < finOtra && inicioOtra < finEsta;
}
