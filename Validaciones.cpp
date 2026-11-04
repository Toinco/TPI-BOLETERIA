#include <iostream>

using namespace std;
#include "ArchivoSalas.h"
#include "ArchivoFunciones.h"
#include "Validaciones.h"
#include "FuncionesGlobales.h"
#include "ArchivoPeliculas.h"
#include "ArchivoDirectores.h"
#include "ArchivoGeneros.h"
#include "ArchivoPeliculasxGenero.h"
#include <ctime>
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

/// ---------------------------------------------------------------
/// Bloque 2: salas y funciones
/// ---------------------------------------------------------------

bool existeSalaActiva(int idSala){
    ArchivoSalas archivo;
    int posicion=archivo.Buscar(idSala);
    if(posicion==-1){
        return false;
    }
    Sala reg=archivo.Leer(posicion);
    return !reg.getEliminado();
}

int contarSalasActivas(){
    ArchivoSalas archivo;
    int cantidad=0;
    int total=archivo.CantidadRegistros();
    for(int i=0;i<total;i++){
        Sala reg=archivo.Leer(i);
        if(!reg.getEliminado()){
            cantidad++;
        }
    }
    return cantidad;
}

void listarSalasParaElegir(){
    ArchivoSalas archivo;
    int total=archivo.CantidadRegistros();
    cout<<"SALAS:"<<endl;
    for(int i=0;i<total;i++){
        Sala reg=archivo.Leer(i);
        if(!reg.getEliminado()){
            cout<<"  "<<reg.getIdSala()<<" - "<<reg.getNombre()
                <<" ("<<reg.getCapacidad()<<" butacas)"<<endl;
        }
    }
}

int pedirIdSalaActiva(){
    listarSalasParaElegir();
    int id=leerEntero("ID DE LA SALA: ");
    while(!existeSalaActiva(id)){
        cout<<"  Esa sala no existe o esta dada de baja."<<endl;
        id=leerEntero("ID DE LA SALA: ");
    }
    return id;
}

/// Una funcion esta vencida si su fecha y horario ya pasaron
bool funcionVencida(Funcion f){
    time_t t=time(NULL);
    tm *ahora=localtime(&t);
    int hoy=(ahora->tm_year+1900)*10000+(ahora->tm_mon+1)*100+ahora->tm_mday;
    int minutosAhora=ahora->tm_hour*60+ahora->tm_min;

    Fecha fecha=f.getFecha();
    Horario horario=f.getHorario();

    if(fecha.aNumero()<hoy){
        return true;
    }
    if(fecha.aNumero()==hoy && horario.aMinutos()<minutosAhora){
        return true;
    }
    return false;
}

bool peliculaTieneFuncionesFuturas(int idPelicula){
    ArchivoFunciones archivo;
    int total=archivo.CantidadRegistros();
    for(int i=0;i<total;i++){
        Funcion reg=archivo.Leer(i);
        if(!reg.getEliminado() && reg.getIdPelicula()==idPelicula && !funcionVencida(reg)){
            return true;
        }
    }
    return false;
}

bool salaTieneFuncionesFuturas(int idSala){
    ArchivoFunciones archivo;
    int total=archivo.CantidadRegistros();
    for(int i=0;i<total;i++){
        Funcion reg=archivo.Leer(i);
        if(!reg.getEliminado() && reg.getIdSala()==idSala && !funcionVencida(reg)){
            return true;
        }
    }
    return false;
}
