#include <iostream>

using namespace std;

#include "PeliculaxGenero.h"
#include "Validaciones.h"

PeliculaxGenero::PeliculaxGenero(){
    idGenero=0;
    idPelicula=0;
    estado=true;
}

int PeliculaxGenero::getIdGenero(){ return idGenero; }
int PeliculaxGenero::getIdPelicula(){ return idPelicula; }
bool PeliculaxGenero::getEstado(){ return estado; }

void PeliculaxGenero::setIdGenero(int id){ idGenero=id; }
void PeliculaxGenero::setIdPelicula(int id){ idPelicula=id; }
void PeliculaxGenero::setEstado(bool e){ estado=e; }

/// Pide la pelicula y el genero (los dos tienen que existir y estar activos).
/// Que el par no se repita lo controla el menu antes de guardarlo.
void PeliculaxGenero::cargar(){
    idPelicula=pedirIdPeliculaActiva();
    idGenero=pedirIdGeneroActivo();
    estado=true;
}

void PeliculaxGenero::mostrar(){
    cout<<"PELICULA: ";
    mostrarTituloPelicula(idPelicula);
    cout<<" - GENERO: ";
    mostrarNombreGenero(idGenero);
    cout<<endl;
    if(!estado){
        cout<<"(DADA DE BAJA)"<<endl;
    }
}
