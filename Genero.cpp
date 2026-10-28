#include <iostream>
#include <cstring>

using namespace std;

#include "Genero.h"
#include "FuncionesGlobales.h"

Genero::Genero(){
    idGenero=0;
    strcpy(nombre, "");
    eliminado=false;
}

int Genero::getIdGenero(){ return idGenero; }
const char *Genero::getNombre(){ return nombre; }
bool Genero::getEliminado(){ return eliminado; }

void Genero::setIdGenero(int id){ idGenero=id; }
void Genero::setNombre(const char *n){ strcpy(nombre, n); }
void Genero::setEliminado(bool e){ eliminado=e; }

/// Pide el nombre; el id lo pone el programa.
void Genero::cargar(){
    cargarTextoObligatorio("NOMBRE DEL GENERO: ", nombre, 29);
    eliminado=false;
}

void Genero::mostrar(){
    cout<<"ID: "<<idGenero<<" - "<<nombre<<endl;
    if(eliminado){
        cout<<"(DADO DE BAJA)"<<endl;
    }
}
