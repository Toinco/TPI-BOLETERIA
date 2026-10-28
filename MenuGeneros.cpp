#include <iostream>
#include <cstdlib>

using namespace std;

#include "MenuGeneros.h"
#include "FuncionesGlobales.h"
#include "Validaciones.h"
#include "ArchivoGeneros.h"

void menuGeneros(){
    int opcion=-1;
    while(opcion!=0){
        titulo("GENEROS");
        cout<<"  1 - ALTA DE GENERO"<<endl;
        cout<<"  2 - BAJA DE GENERO"<<endl;
        cout<<"  3 - MODIFICAR GENERO"<<endl;
        cout<<"  4 - VER GENEROS"<<endl;
        lineaSimple();
        cout<<"  0 - VOLVER"<<endl;
        lineaDoble();
        opcion=leerEntero("OPCION: ");

        switch(opcion){
            case 1: altaGenero(); break;
            case 2: bajaGenero(); break;
            case 3: modificarGenero(); break;
            case 4: verGeneros(); break;
            case 0: break;
            default:
                cout<<"Opcion incorrecta."<<endl;
                system("pause");
                break;
        }
    }
}

/// Devuelve true si ya hay otro genero activo con ese nombre
/// (sin importar mayusculas). idExcluir es para no compararlo consigo mismo.
bool nombreGeneroRepetido(const char *nombre, int idExcluir){
    ArchivoGeneros archivo;
    int cantidadRegistros=archivo.CantidadRegistros();
    for(int i=0;i<cantidadRegistros;i++){
        Genero reg=archivo.Leer(i);
        if(!reg.getEliminado() && reg.getIdGenero()!=idExcluir &&
           compararSinMayusculas(reg.getNombre(), nombre)==0){
            return true;
        }
    }
    return false;
}

void altaGenero(){
    titulo("ALTA DE GENERO");
    ArchivoGeneros archivo;
    Genero reg;
    reg.cargar();
    while(nombreGeneroRepetido(reg.getNombre(), 0)){
        cout<<"  Ya existe un genero con ese nombre."<<endl;
        reg.cargar();
    }
    reg.setIdGenero(archivo.CantidadRegistros()+1);

    if(archivo.Guardar(reg)){
        cout<<"GENERO GUARDADO CON ID "<<reg.getIdGenero()<<endl;
    }
    else{
        cout<<"ERROR: no se pudo guardar en Generos.dat"<<endl;
    }
    system("pause");
}

void bajaGenero(){
    titulo("BAJA DE GENERO");
    if(contarGenerosActivos()==0){
        cout<<"No hay generos cargados."<<endl;
        system("pause");
        return;
    }

    listarGenerosParaElegir();
    int id=leerEntero("ID DEL GENERO A DAR DE BAJA: ");
    ArchivoGeneros archivo;
    int posicion=archivo.Buscar(id);
    if(posicion==-1){
        cout<<"No existe un genero con ese ID."<<endl;
        system("pause");
        return;
    }
    Genero reg=archivo.Leer(posicion);
    if(reg.getEliminado()){
        cout<<"Ese genero ya esta dado de baja."<<endl;
        system("pause");
        return;
    }

    if(generoTienePeliculasActivas(id)){
        cout<<"No se puede dar de baja: hay peliculas activas con este genero."<<endl;
        cout<<"Primero hay que quitarselo a esas peliculas (menu PELICULAS)."<<endl;
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
        cout<<"GENERO DADO DE BAJA"<<endl;
    }
    else{
        cout<<"ERROR: no se pudo guardar en Generos.dat"<<endl;
    }
    system("pause");
}

void modificarGenero(){
    titulo("MODIFICAR GENERO");
    if(contarGenerosActivos()==0){
        cout<<"No hay generos cargados."<<endl;
        system("pause");
        return;
    }

    listarGenerosParaElegir();
    int id=leerEntero("ID DEL GENERO A MODIFICAR: ");
    ArchivoGeneros archivo;
    int posicion=archivo.Buscar(id);
    if(posicion==-1){
        cout<<"No existe un genero con ese ID."<<endl;
        system("pause");
        return;
    }
    Genero reg=archivo.Leer(posicion);
    if(reg.getEliminado()){
        cout<<"Ese genero esta dado de baja."<<endl;
        system("pause");
        return;
    }

    char nombre[30];
    cargarTextoObligatorio("NUEVO NOMBRE: ", nombre, 29);
    while(nombreGeneroRepetido(nombre, id)){
        cout<<"  Ya existe un genero con ese nombre."<<endl;
        cargarTextoObligatorio("NUEVO NOMBRE: ", nombre, 29);
    }
    reg.setNombre(nombre);

    if(archivo.Guardar(reg, posicion)){
        cout<<"CAMBIO GUARDADO"<<endl;
    }
    else{
        cout<<"ERROR: no se pudo guardar en Generos.dat"<<endl;
    }
    system("pause");
}

void verGeneros(){
    titulo("GENEROS");
    if(contarGenerosActivos()==0){
        cout<<"No hay generos cargados."<<endl;
    }
    else{
        listarGenerosParaElegir();
    }
    system("pause");
}
