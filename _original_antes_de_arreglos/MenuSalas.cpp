#include <iostream>
 using namespace std;
#include <iostream>
#include "MenuSalas.h"
#include "FuncionesGlobales.h"
#include "Validaciones.h"
#include "ArchivoSalas.h"
#include <cstdlib>
void menuSalas(){
    int opcion=-1;
    while(opcion!=0){
        titulo("SALAS");
        cout<<"  1 - ALTA DE SALA"<<endl;
        cout<<"  2 - BAJA DE SALA"<<endl;
        cout<<"  3 - MODIFICAR SALA"<<endl;
        lineaSimple();
        cout<<"  0 - VOLVER"<<endl;
        lineaDoble();
        opcion=leerEntero("OPCION: ");

        switch(opcion){
            case 1: altaSala(); break;
            case 2: bajaSala(); break;
            case 3: modificarSala(); break;
            case 0: break;
            default:
                cout<<"Opcion incorrecta."<<endl;
                system("pause");
                break;
        }
    }
}

void altaSala(){
    titulo("ALTA DE SALA");
    ArchivoSalas archivo;
    Sala reg;
    reg.cargar();
    reg.setIdSala(archivo.CantidadRegistros()+1);

    lineaSimple();
    reg.mostrar();
    lineaSimple();
    if(!confirmar("Guardar la sala?")){
        cout<<"Operacion cancelada. No se guardo nada."<<endl;
        system("pause");
        return;
    }
    if(archivo.Guardar(reg)){
        cout<<"SALA GUARDADA CON ID "<<reg.getIdSala()<<endl;
    }
    else{
        cout<<"ERROR: no se pudo guardar en Salas.dat"<<endl;
    }
    system("pause");
}

void bajaSala(){
    titulo("BAJA DE SALA");
    if(contarSalasActivas()==0){
        cout<<"No hay salas cargadas."<<endl;
        system("pause");
        return;
    }

    listarSalasParaElegir();
    int id=leerEntero("ID DE LA SALA A DAR DE BAJA: ");
    ArchivoSalas archivo;
    int posicion=archivo.Buscar(id);
    if(posicion==-1){
        cout<<"No existe una sala con ese ID."<<endl;
        system("pause");
        return;
    }
    Sala reg=archivo.Leer(posicion);
    if(reg.getEliminado()){
        cout<<"Esa sala ya esta dada de baja."<<endl;
        system("pause");
        return;
    }

    lineaSimple();
    reg.mostrar();
    lineaSimple();

    if(salaTieneFuncionesFuturas(id)){
        cout<<"No se puede dar de baja: tiene funciones futuras activas."<<endl;
        cout<<"Primero hay que dar de baja esas funciones."<<endl;
        system("pause");
        return;
    }
    if(!confirmar("Confirma la baja?")){
        cout<<"Operacion cancelada."<<endl;
        system("pause");
        return;
    }

    reg.setEliminado(true);
    if(archivo.Guardar(reg, posicion)){
        cout<<"SALA DADA DE BAJA"<<endl;
    }
    else{
        cout<<"ERROR: no se pudo guardar en Salas.dat"<<endl;
    }
    system("pause");
}

void modificarSala(){
    titulo("MODIFICAR SALA");
    if(contarSalasActivas()==0){
        cout<<"No hay salas cargadas."<<endl;
        system("pause");
        return;
    }

    listarSalasParaElegir();
    int id=leerEntero("ID DE LA SALA A MODIFICAR: ");
    ArchivoSalas archivo;
    int posicion=archivo.Buscar(id);
    if(posicion==-1){
        cout<<"No existe una sala con ese ID."<<endl;
        system("pause");
        return;
    }
    Sala reg=archivo.Leer(posicion);
    if(reg.getEliminado()){
        cout<<"Esa sala esta dada de baja."<<endl;
        system("pause");
        return;
    }

    lineaSimple();
    reg.mostrar();
    lineaSimple();
    cout<<"  1 - NOMBRE"<<endl;
    cout<<"  2 - CAPACIDAD"<<endl;
    cout<<"  3 - TIPO"<<endl;
    cout<<"  0 - VOLVER"<<endl;
    int opcion=leerEntero("QUE DATO QUIERE MODIFICAR?: ");
    while(opcion<0 || opcion>3){
        cout<<"  Opcion incorrecta."<<endl;
        opcion=leerEntero("QUE DATO QUIERE MODIFICAR?: ");
    }
    if(opcion==0){
        return;
    }

    char texto[20];
    int numero;
    switch(opcion){
        case 1:
            cargarTextoObligatorio("NUEVO NOMBRE: ", texto, 19);
            reg.setNombre(texto);
            break;
        case 2:
            /// Si se achica la sala con funciones futuras podria haber mas
            /// entradas vendidas que butacas, por eso se bloquea.
            if(salaTieneFuncionesFuturas(id)){
                cout<<"No se puede cambiar la capacidad: la sala tiene funciones futuras."<<endl;
                system("pause");
                return;
            }
            numero=leerEntero("NUEVA CAPACIDAD: ");
            while(numero<=0){
                cout<<"  La capacidad debe ser mayor a cero."<<endl;
                numero=leerEntero("NUEVA CAPACIDAD: ");
            }
            reg.setCapacidad(numero);
            break;
        case 3:
            cout<<"TIPO DE SALA: 1-IMAX, 2-3D, 3-2D, 4-4D"<<endl;
            numero=leerEntero("NUEVO TIPO: ");
            while(numero<1 || numero>4){
                cout<<"  Tipo invalido. Ingrese un valor entre 1 y 4."<<endl;
                numero=leerEntero("NUEVO TIPO: ");
            }
            reg.setTipo(numero);
            break;
    }

    if(archivo.Guardar(reg, posicion)){
        cout<<"CAMBIO GUARDADO"<<endl;
    }
    else{
        cout<<"ERROR: no se pudo guardar en Salas.dat"<<endl;
    }
    system("pause");
}
