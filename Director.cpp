#include <iostream>
#include <cstring>

using namespace std;

#include "Director.h"
#include "FuncionesGlobales.h"

Director::Director(){
    idDirector=0;
    strcpy(nombre, "");
    strcpy(apellido, "");
    strcpy(nacionalidad, "");
    eliminado=false;
}

int Director::getIdDirector(){ return idDirector; }
const char *Director::getNombre(){ return nombre; }
const char *Director::getApellido(){ return apellido; }
const char *Director::getNacionalidad(){ return nacionalidad; }
bool Director::getEliminado(){ return eliminado; }

void Director::setIdDirector(int id){ idDirector=id; }
void Director::setNombre(const char *n){ strcpy(nombre, n); }
void Director::setApellido(const char *a){ strcpy(apellido, a); }
void Director::setNacionalidad(const char *n){ strcpy(nacionalidad, n); }
void Director::setEliminado(bool e){ eliminado=e; }

/// Pide todos los datos menos el id, que lo pone el programa.
void Director::cargar(){
    cargarTextoObligatorio("NOMBRE: ", nombre, 29);
    cargarTextoObligatorio("APELLIDO: ", apellido, 29);
    cargarTextoObligatorio("NACIONALIDAD: ", nacionalidad, 29);
    eliminado=false;
}

void Director::mostrar(){
    cout<<"ID: "<<idDirector<<" - "<<apellido<<", "<<nombre<<" ("<<nacionalidad<<")"<<endl;
    if(eliminado){
        cout<<"(DADO DE BAJA)"<<endl;
    }
}
