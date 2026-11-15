#include <iostream>
#include <cstring>

using namespace std;

#include "Pelicula.h"
#include "FuncionesGlobales.h"
#include "Validaciones.h"

Pelicula::Pelicula(){
    idPelicula=0;
    strcpy(titulo, "");
    idDirector=0;
    duracionMinutos=0;
    calificacion=0;
    strcpy(descripcion, "");
    eliminado=false;
}

int Pelicula::getIdPelicula(){ return idPelicula; }
const char *Pelicula::getTitulo(){ return titulo; }
int Pelicula::getIdDirector(){ return idDirector; }
int Pelicula::getDuracionMinutos(){ return duracionMinutos; }
float Pelicula::getCalificacion(){ return calificacion; }
const char *Pelicula::getDescripcion(){ return descripcion; }
bool Pelicula::getEliminado(){ return eliminado; }

void Pelicula::setIdPelicula(int id){ idPelicula=id; }
void Pelicula::setTitulo(const char *t){ strcpy(titulo, t); }
void Pelicula::setIdDirector(int id){ idDirector=id; }
void Pelicula::setDuracionMinutos(int minutos){
    if(minutos>0){
        duracionMinutos=minutos;
    }
}
void Pelicula::setCalificacion(float c){
    if(c>=1 && c<=10){
        calificacion=c;
    }
}
void Pelicula::setDescripcion(const char *d){ strcpy(descripcion, d); }
void Pelicula::setEliminado(bool e){ eliminado=e; }

/// Pide todos los datos menos el id, que lo pone el programa.
/// Antes de llamarlo tiene que haber al menos un director activo.
void Pelicula::cargar(){
    cargarTextoObligatorio("TITULO: ", titulo, 49);

    idDirector=pedirIdDirectorActivo();

    duracionMinutos=leerEntero("DURACION (MINUTOS): ");
    while(duracionMinutos<=0){
        cout<<"  La duracion tiene que ser mayor a cero."<<endl;
        duracionMinutos=leerEntero("DURACION (MINUTOS): ");
    }

    calificacion=leerFloat("CALIFICACION (1 A 10): ");
    while(calificacion<1 || calificacion>10){
        cout<<"  La calificacion tiene que ir de 1 a 10."<<endl;
        calificacion=leerFloat("CALIFICACION (1 A 10): ");
    }

    cout<<"DESCRIPCION: ";
    cargarCadena(descripcion, 199);

    eliminado=false;
}

void Pelicula::mostrar(){
    cout<<"ID: "<<idPelicula<<" - "<<titulo<<endl;
    cout<<"DIRECTOR: ";
    mostrarNombreDirector(idDirector);
    cout<<endl;
    cout<<"DURACION: "<<duracionMinutos<<" MIN - CALIFICACION: "<<calificacion<<endl;
    cout<<"DESCRIPCION: "<<descripcion<<endl;
    if(eliminado){
        cout<<"(DADA DE BAJA)"<<endl;
    }
}
