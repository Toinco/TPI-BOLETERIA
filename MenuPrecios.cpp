#include <iostream>
 using namespace std;


 #include "MenuPrecios.h"
#include "ArchivoPrecios.h"
#include "FuncionesGlobales.h"

void menuPrecios(){

    ArchivoPrecios archivo;
    archivo.cargarPreciosIniciales();

    int opcion;

    do{
        system("cls");

        cout << "========== MENU PRECIOS ==========" << endl;
        cout << "1 - Listar precios" << endl;
        cout << "2 - Modificar precio" << endl;
        cout << "0 - Volver al menu principal" << endl;
        cout << "==================================" << endl;
        opcion = leerEntero("Ingrese una opcion: ");

        system("cls");

        switch(opcion){

            case 1:{
                cout << "========== LISTADO DE PRECIOS ==========" << endl;

                for(int i = 0; i < archivo.CantidadRegistros(); i++){
                    Precio reg = archivo.Leer(i);
                    reg.mostrar();
                }

                system("pause");
                break;
            }

            case 2:{
                int idTipo;
                float nuevoPrecio;

                cout << "========== MODIFICAR PRECIO ==========" << endl;
                cout << "Ingrese el tipo de sala:" << endl;
                cout << "1 - IMAX" << endl;
                cout << "2 - 3D" << endl;
                cout << "3 - 2D" << endl;
                cout << "4 - 4D" << endl;
                idTipo = leerEntero("Opcion: ");

                int posicion = archivo.Buscar(idTipo);

                if(posicion == -1){
                    cout << "Tipo de sala inexistente." << endl;
                }
                else{
                    Precio reg = archivo.Leer(posicion);

                    cout << "Precio actual: $" << reg.getPrecio() << endl;
                    nuevoPrecio = leerFloat("Ingrese el nuevo precio: $");

                    while(nuevoPrecio <= 0){
                        cout << "El precio debe ser mayor a cero." << endl;
                        nuevoPrecio = leerFloat("Ingrese nuevamente: $");
                    }

                    reg.setPrecio(nuevoPrecio);

                    if(archivo.Guardar(reg, posicion)){
                        cout << "Precio modificado correctamente." << endl;
                    }
                    else{
                        cout << "Error al modificar el precio." << endl;
                    }
                }

                system("pause");
                break;
            }

            case 0:
                break;

            default:
                cout << "Opcion incorrecta." << endl;
                system("pause");
                break;
        }

    }while(opcion != 0);
}

/// Listado de precios ordenados por tipo de sala (1 - IMAX, 2 - 3D, 3 - 2D, 4 - 4D)
void listadoPreciosPorTipo(){
    titulo("PRECIOS POR TIPO DE SALA");
    ArchivoPrecios archivo;
    archivo.cargarPreciosIniciales();
    for(int tipo=1;tipo<=4;tipo++){
        int posicion=archivo.Buscar(tipo);
        if(posicion!=-1){
            Precio reg=archivo.Leer(posicion);
            reg.mostrar();
        }
    }
    system("pause");
}
