#include <iostream>
#include "Venta.h"
using namespace std;
#include <ctime>
#include "Fecha.h"

venta::venta() {
    idVenta = 0; 
    idFuncion = 0; 
    cantidad = 0;
    precioUnitario = 0; 
    formaPago = 0; 
    eliminado = false;
}


void venta::setFecha(Fecha f) {
    fecha = f;
}

void venta::setIdVenta(int id){
    idVenta = id;
}

void venta::setIdFuncion(int id){
    idFuncion = id;
}

void venta::setCantidad(int c){
    cantidad = c;
}

void venta::setPrecioUnitario(float p){
    precioUnitario = p;
}

void venta::setFormaPago(int fp){
    formaPago = fp;
}

void venta::setEliminado(bool e){
    eliminado = e;
}

int venta::getCantidad(){
    return cantidad;
}

float venta::getPrecioUnitario(){
    return precioUnitario;
}

int venta::getFormaPago(){
    return formaPago;
}

int venta::getIdVenta() {
    return idVenta;
}

Fecha venta::getFecha() {
    return fecha;
}

bool venta::getEliminado(){
    return eliminado;
}

int venta::getIdFuncion(){
    return idFuncion; 
}
float venta::getImporte(){
     return cantidad * precioUnitario; 
    
}

void venta::cargar(){
    cout << "Ingrese el ID de la venta: ";
    cin >> idVenta;
    cout << "Ingrese el ID de la funcion: ";
    cin >> idFuncion;
    cout << "Ingrese la cantidad de entradas: ";
    cin >> cantidad;
    cout << "Ingrese el precio unitario: ";
    cin >> precioUnitario;
    cout << "Ingrese la forma de pago (1: Efectivo, 2: Débito, 3: Crédito, 4: Transferencia): ";
    cin >> formaPago;
    eliminado = false; // Por defecto, la venta no está eliminada
}

void venta::mostrar(){
    cout << "ID Venta: " << idVenta << endl;
    cout << "ID Funcion: " << idFuncion << endl;
    cout << "Cantidad de entradas: " << cantidad << endl;
    cout << "Precio unitario: " << precioUnitario << endl;
    cout << "Forma de pago: " << (formaPago == 1 ? "Efectivo" : (formaPago == 2 ? "Débito" : (formaPago == 3 ? "Crédito" : "Transferencia"))) << endl;
    cout << "Eliminado: " << (eliminado ? "Si" : "No") << endl;
}

