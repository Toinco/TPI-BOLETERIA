#include <iostream>

using namespace std;

#include "Validaciones.h"
#include "FuncionesGlobales.h"
#include "ArchivoPeliculas.h"
#include "ArchivoDirectores.h"
#include "ArchivoGeneros.h"
#include "ArchivoPeliculasxGenero.h"

/// ---------------------------------------------------------------
/// Existe y esta activo
/// ---------------------------------------------------------------

bool existeDirectorActivo(int idDirector){
    ArchivoDirectores archivo;
    int posicion=archivo.Buscar(idDirector);
    if(posicion==-1){
        return false;
    }
    Director reg=archivo.Leer(posicion);
    return !reg.getEliminado();
}

bool existePeliculaActiva(int idPelicula){
    ArchivoPeliculas archivo;
    int posicion=archivo.Buscar(idPelicula);
    if(posicion==-1){
        return false;
    }
    Pelicula reg=archivo.Leer(posicion);
    return !reg.getEliminado();
}

bool existeGeneroActivo(int idGenero){
    ArchivoGeneros archivo;
    int posicion=archivo.Buscar(idGenero);
    if(posicion==-1){
        return false;
    }
    Genero reg=archivo.Leer(posicion);
    return !reg.getEliminado();
}

int contarDirectoresActivos(){
    ArchivoDirectores archivo;
    int cantidadRegistros=archivo.CantidadRegistros();
    int activos=0;
    for(int i=0;i<cantidadRegistros;i++){
        Director reg=archivo.Leer(i);
        if(!reg.getEliminado()){
            activos++;
        }
    }
    return activos;
}

int contarPeliculasActivas(){
    ArchivoPeliculas archivo;
    int cantidadRegistros=archivo.CantidadRegistros();
    int activas=0;
    for(int i=0;i<cantidadRegistros;i++){
        Pelicula reg=archivo.Leer(i);
        if(!reg.getEliminado()){
            activas++;
        }
    }
    return activas;
}

int contarGenerosActivos(){
    ArchivoGeneros archivo;
    int cantidadRegistros=archivo.CantidadRegistros();
    int activos=0;
    for(int i=0;i<cantidadRegistros;i++){
        Genero reg=archivo.Leer(i);
        if(!reg.getEliminado()){
            activos++;
        }
    }
    return activos;
}

/// ---------------------------------------------------------------
/// Listas para elegir
/// ---------------------------------------------------------------

void listarDirectoresParaElegir(){
    ArchivoDirectores archivo;
    int cantidadRegistros=archivo.CantidadRegistros();
    cout<<"DIRECTORES:"<<endl;
    for(int i=0;i<cantidadRegistros;i++){
        Director reg=archivo.Leer(i);
        if(!reg.getEliminado()){
            cout<<"  "<<reg.getIdDirector()<<" - "<<reg.getApellido()<<", "<<reg.getNombre()<<endl;
        }
    }
}

void listarPeliculasParaElegir(){
    ArchivoPeliculas archivo;
    int cantidadRegistros=archivo.CantidadRegistros();
    cout<<"PELICULAS:"<<endl;
    for(int i=0;i<cantidadRegistros;i++){
        Pelicula reg=archivo.Leer(i);
        if(!reg.getEliminado()){
            cout<<"  "<<reg.getIdPelicula()<<" - "<<reg.getTitulo()<<endl;
        }
    }
}

void listarGenerosParaElegir(){
    ArchivoGeneros archivo;
    int cantidadRegistros=archivo.CantidadRegistros();
    cout<<"GENEROS:"<<endl;
    for(int i=0;i<cantidadRegistros;i++){
        Genero reg=archivo.Leer(i);
        if(!reg.getEliminado()){
            cout<<"  "<<reg.getIdGenero()<<" - "<<reg.getNombre()<<endl;
        }
    }
}

/// ---------------------------------------------------------------
/// Pedir un id valido
/// ---------------------------------------------------------------

int pedirIdDirectorActivo(){
    listarDirectoresParaElegir();
    int id=leerEntero("ID DEL DIRECTOR: ");
    while(!existeDirectorActivo(id)){
        cout<<"  Ese director no existe o esta dado de baja."<<endl;
        id=leerEntero("ID DEL DIRECTOR: ");
    }
    return id;
}

int pedirIdPeliculaActiva(){
    listarPeliculasParaElegir();
    int id=leerEntero("ID DE LA PELICULA: ");
    while(!existePeliculaActiva(id)){
        cout<<"  Esa pelicula no existe o esta dada de baja."<<endl;
        id=leerEntero("ID DE LA PELICULA: ");
    }
    return id;
}

int pedirIdGeneroActivo(){
    listarGenerosParaElegir();
    int id=leerEntero("ID DEL GENERO: ");
    while(!existeGeneroActivo(id)){
        cout<<"  Ese genero no existe o esta dado de baja."<<endl;
        id=leerEntero("ID DEL GENERO: ");
    }
    return id;
}

/// ---------------------------------------------------------------
/// Nombres a partir del id
/// ---------------------------------------------------------------

void mostrarNombreDirector(int idDirector){
    ArchivoDirectores archivo;
    int posicion=archivo.Buscar(idDirector);
    if(posicion==-1){
        cout<<"(INEXISTENTE)";
        return;
    }
    Director reg=archivo.Leer(posicion);
    cout<<reg.getApellido()<<", "<<reg.getNombre();
}

void mostrarTituloPelicula(int idPelicula){
    ArchivoPeliculas archivo;
    int posicion=archivo.Buscar(idPelicula);
    if(posicion==-1){
        cout<<"(INEXISTENTE)";
        return;
    }
    Pelicula reg=archivo.Leer(posicion);
    cout<<reg.getTitulo();
}

void mostrarNombreGenero(int idGenero){
    ArchivoGeneros archivo;
    int posicion=archivo.Buscar(idGenero);
    if(posicion==-1){
        cout<<"(INEXISTENTE)";
        return;
    }
    Genero reg=archivo.Leer(posicion);
    cout<<reg.getNombre();
}

/// ---------------------------------------------------------------
/// Integridad para las bajas
/// ---------------------------------------------------------------

bool directorTienePeliculasActivas(int idDirector){
    ArchivoPeliculas archivo;
    int cantidadRegistros=archivo.CantidadRegistros();
    for(int i=0;i<cantidadRegistros;i++){
        Pelicula reg=archivo.Leer(i);
        if(!reg.getEliminado() && reg.getIdDirector()==idDirector){
            return true;
        }
    }
    return false;
}

bool generoTienePeliculasActivas(int idGenero){
    ArchivoPeliculasxGenero archivo;
    int cantidadRegistros=archivo.CantidadRegistros();
    for(int i=0;i<cantidadRegistros;i++){
        PeliculaxGenero reg=archivo.Leer(i);
        if(reg.getEstado() && reg.getIdGenero()==idGenero && existePeliculaActiva(reg.getIdPelicula())){
            return true;
        }
    }
    return false;
}

/// *** LA COMPLETA EL BLOQUE 2 ***
/// El informe pide que no se pueda dar de baja una pelicula que tenga
/// funciones futuras activas. Las funciones son del bloque 2, asi que
/// ellos tienen que recorrer Funciones.dat y devolver true si hay una
/// funcion no eliminada de esta pelicula con fecha y horario que todavia
/// no pasaron. Mientras tanto devuelve false y la baja funciona igual.
bool peliculaTieneFuncionesFuturas(int idPelicula){
    return false;
}
