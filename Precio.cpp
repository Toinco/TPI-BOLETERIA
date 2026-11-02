#include <iostream>
 using namespace std;
#include <cstring>
#include "Precio.h"

Precio::Precio(){
    idTipo=0;
    strcpy(nombre, "");
    precio=0;
}



int Precio::getIdTipo(){
    return idTipo;
}

const char *Precio::getNombre(){
    return nombre;
}

float Precio::getPrecio(){
    return precio;
}



void Precio::setIdTipo(int id){
    idTipo=id;
}
void Precio::setNombre(const char *n){
    strcpy(nombre, n);
}
void Precio::setPrecio(float p){
    if(p>0){
        precio=p;
    }
}


void Precio::mostrar(){
    cout<<idTipo<<" - "<<nombre<<": $"<<precio<<endl;
}

























