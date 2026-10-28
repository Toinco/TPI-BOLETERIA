#include <iostream>
#include <cstdlib>

using namespace std;

#include "MenuDirectores.h"
#include "FuncionesGlobales.h"
#include "Validaciones.h"
#include "ArchivoDirectores.h"

void menuDirectores(){
    int opcion=-1;
    while(opcion!=0){
        titulo("DIRECTORES");
        cout<<"  1 - ALTA DE DIRECTOR"<<endl;
        cout<<"  2 - BAJA DE DIRECTOR"<<endl;
        cout<<"  3 - MODIFICAR DIRECTOR"<<endl;
        lineaSimple();
        cout<<"  0 - VOLVER"<<endl;
        lineaDoble();
        opcion=leerEntero("OPCION: ");

        switch(opcion){
            case 1: altaDirector(); break;
            case 2: bajaDirector(); break;
            case 3: modificarDirector(); break;
            case 0: break;
            default:
                cout<<"Opcion incorrecta."<<endl;
                system("pause");
                break;
        }
    }
}

void altaDirector(){
    titulo("ALTA DE DIRECTOR");
    ArchivoDirectores archivo;
    Director reg;
    reg.cargar();
    reg.setIdDirector(archivo.CantidadRegistros()+1);

    lineaSimple();
    reg.mostrar();
    lineaSimple();
    if(!confirmar("Guardar el director?")){
        cout<<"Operacion cancelada. No se guardo nada."<<endl;
        system("pause");
        return;
    }
    if(archivo.Guardar(reg)){
        cout<<"DIRECTOR GUARDADO CON ID "<<reg.getIdDirector()<<endl;
    }
    else{
        cout<<"ERROR: no se pudo guardar en Directores.dat"<<endl;
    }
    system("pause");
}

void bajaDirector(){
    titulo("BAJA DE DIRECTOR");
    if(contarDirectoresActivos()==0){
        cout<<"No hay directores cargados."<<endl;
        system("pause");
        return;
    }

    listarDirectoresParaElegir();
    int id=leerEntero("ID DEL DIRECTOR A DAR DE BAJA: ");
    ArchivoDirectores archivo;
    int posicion=archivo.Buscar(id);
    if(posicion==-1){
        cout<<"No existe un director con ese ID."<<endl;
        system("pause");
        return;
    }
    Director reg=archivo.Leer(posicion);
    if(reg.getEliminado()){
        cout<<"Ese director ya esta dado de baja."<<endl;
        system("pause");
        return;
    }

    lineaSimple();
    reg.mostrar();
    lineaSimple();

    if(directorTienePeliculasActivas(id)){
        cout<<"No se puede dar de baja: tiene peliculas activas."<<endl;
        cout<<"Primero hay que dar de baja sus peliculas o cambiarles el director."<<endl;
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
        cout<<"DIRECTOR DADO DE BAJA"<<endl;
    }
    else{
        cout<<"ERROR: no se pudo guardar en Directores.dat"<<endl;
    }
    system("pause");
}

void modificarDirector(){
    titulo("MODIFICAR DIRECTOR");
    if(contarDirectoresActivos()==0){
        cout<<"No hay directores cargados."<<endl;
        system("pause");
        return;
    }

    listarDirectoresParaElegir();
    int id=leerEntero("ID DEL DIRECTOR A MODIFICAR: ");
    ArchivoDirectores archivo;
    int posicion=archivo.Buscar(id);
    if(posicion==-1){
        cout<<"No existe un director con ese ID."<<endl;
        system("pause");
        return;
    }
    Director reg=archivo.Leer(posicion);
    if(reg.getEliminado()){
        cout<<"Ese director esta dado de baja."<<endl;
        system("pause");
        return;
    }

    lineaSimple();
    reg.mostrar();
    lineaSimple();
    cout<<"  1 - NOMBRE"<<endl;
    cout<<"  2 - APELLIDO"<<endl;
    cout<<"  3 - NACIONALIDAD"<<endl;
    cout<<"  0 - VOLVER"<<endl;
    int opcion=leerEntero("QUE DATO QUIERE MODIFICAR?: ");
    while(opcion<0 || opcion>3){
        cout<<"  Opcion incorrecta."<<endl;
        opcion=leerEntero("QUE DATO QUIERE MODIFICAR?: ");
    }
    if(opcion==0){
        return;
    }

    char texto[30];
    switch(opcion){
        case 1:
            cargarTextoObligatorio("NUEVO NOMBRE: ", texto, 29);
            reg.setNombre(texto);
            break;
        case 2:
            cargarTextoObligatorio("NUEVO APELLIDO: ", texto, 29);
            reg.setApellido(texto);
            break;
        case 3:
            cargarTextoObligatorio("NUEVA NACIONALIDAD: ", texto, 29);
            reg.setNacionalidad(texto);
            break;
    }

    if(archivo.Guardar(reg, posicion)){
        cout<<"CAMBIO GUARDADO"<<endl;
    }
    else{
        cout<<"ERROR: no se pudo guardar en Directores.dat"<<endl;
    }
    system("pause");
}
