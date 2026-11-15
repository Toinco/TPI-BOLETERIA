#include <iostream>
using namespace std;
#include "Fecha.h"
#include "FuncionesGlobales.h"

Fecha::Fecha(){
    dia = 0;
    mes = 0;
    anio = 0;
}

int Fecha::getDia(){ return dia; }
int Fecha::getMes(){ return mes; }
int Fecha::getAnio(){ return anio; }

void Fecha::setDia(int d){
    if(d>=1 && d<=31){
        dia=d;
    }
}

void Fecha::setMes(int m){
    if(m>=1 && m<=12){
        mes=m;
    }
}

void Fecha::setAnio(int a){
    if(a>=1){
        anio=a;
    }
}

/// Cantidad de dias que tiene cada mes (febrero depende del año)
int Fecha::diasDelMes(int m, int a){
    if(m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12){
        return 31;
    }
    else if(m==4 || m==6 || m==9 || m==11){
        return 30;
    }
    else if(m==2){
        if(a%400==0 || (a%4==0 && a%100!=0)){
            return 29;
        }
        else{
            return 28;
        }
    }
    return 0;
}
///---
void Fecha::cargar(){
    int d, m, a;

    a=leerEntero("ANIO: ");
    while(a<1){
        cout<<"  El anio tiene que ser mayor que 0."<<endl;
        a=leerEntero("ANIO: ");
    }

    m=leerEntero("MES (1 A 12): ");
    while(m<1 || m>12){
        cout<<"  El mes tiene que ir de 1 a 12."<<endl;
        m=leerEntero("MES (1 A 12): ");
    }

    d=leerEntero("DIA: ");
    while(d<1 || d>diasDelMes(m, a)){
        cout<<"  Ese dia no es valido para ese mes y anio."<<endl;
        d=leerEntero("DIA: ");
    }

    dia=d;
    mes=m;
    anio=a;
}
///---
void Fecha::mostrar(){
    if(dia<10){
        cout<<"0";
    }
    cout<<dia<<"/";

    if(mes<10){
        cout<<"0";
    }
    cout<<mes<<"/";

    cout<<anio;
}

/// Convierte la fecha en un numero para poder compararlas:
/// 29/02/2024 -> 20240229. La fecha mas nueva da el numero mas grande.
int Fecha::aNumero(){
    return anio*10000 + mes*100 + dia;
}
