#include <iostream>
#include "Horario.h"
 using namespace std;

#include "Horario.h"
#include "FuncionesGlobales.h"

Horario::Horario(){
    hora=0;
    minuto=0;
}

int Horario::getHora(){ return hora; }
int Horario::getMinuto(){ return minuto; }

void Horario::setHora(int h){
    if(h>=0 && h<=23){
        hora=h;
    }
}

void Horario::setMinuto(int m){
    if(m>=0 && m<=59){
        minuto=m;
    }
}

void Horario::cargar(){
    hora=leerEntero("HORA (0 A 23): ");
    while(hora<0 || hora>23){
        cout<<"  La hora tiene que ir de 0 a 23."<<endl;
        hora=leerEntero("HORA (0 A 23): ");
    }

    minuto=leerEntero("MINUTO (0 A 59): ");
    while(minuto<0 || minuto>59){
        cout<<"  El minuto tiene que ir de 0 a 59."<<endl;
        minuto=leerEntero("MINUTO (0 A 59): ");
    }
}

void Horario::mostrar(){
    if(hora<10){
        cout<<"0";
    }
    cout<<hora<<":";
    if(minuto<10){
        cout<<"0";
    }
    cout<<minuto;
}

int Horario::aMinutos(){
    return hora*60+minuto;
}
