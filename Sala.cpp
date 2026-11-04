#include <iostream>
#include <cstring>
using namespace std;
#include "Sala.h"
#include "FuncionesGlobales.h"

Sala::Sala(){
    idSala = 0;
    strcpy(nombre, "");
    capacidad = 0;
    tipo = 0;
    eliminado = false;
}

///Get
int Sala::getIdSala(){ return idSala; }
const char* Sala::getNombre(){ return nombre; }
int Sala::getCapacidad(){ return capacidad; }
int Sala::getTipo(){ return tipo; }
bool Sala::getEliminado(){ return eliminado; }

///Set
void Sala::setIdSala(int id){ idSala = id; }

void Sala::setNombre(const char* n){
    strcpy(nombre, n);
}

void Sala::setCapacidad(int c){
    if(c > 0){
        capacidad = c;
    }
}

void Sala::setTipo(int t){
    if(t >= 1 && t <= 4){
        tipo = t;
    }
}

void Sala::setEliminado(bool e){ eliminado = e; }

///Metodo cargar
void Sala::cargar(){
    cargarTextoObligatorio("NOMBRE DE LA SALA: ", nombre, 19);

    capacidad = leerEntero("CAPACIDAD (BUTACAS): ");
    while(capacidad <= 0){
        cout << "  La capacidad debe ser mayor a cero." << endl;
        capacidad = leerEntero("CAPACIDAD (BUTACAS): ");
    }

    cout << "TIPO DE SALA: 1-IMAX, 2-3D, 3-2D, 4-4D" << endl;
    tipo = leerEntero("TIPO: ");
    while(tipo < 1 || tipo > 4){
        cout << "  Tipo invalido. Ingrese un valor entre 1 y 4." << endl;
        tipo = leerEntero("TIPO: ");
    }

    eliminado = false;
}

///Metodo mostrar
void Sala::mostrar(){
    cout << "ID SALA: " << idSala << " | NOMBRE: " << nombre
         << " | CAPACIDAD: " << capacidad << " butacas | TIPO: ";
    switch(tipo){
        case 1: cout << "IMAX"; break;
        case 2: cout << "3D"; break;
        case 3: cout << "2D"; break;
        case 4: cout << "4D"; break;
    }
    cout << endl;
}
