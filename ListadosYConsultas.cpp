#include <iostream>
#include <cstdlib>

using namespace std;

#include "ListadosYConsultas.h"
#include "FuncionesGlobales.h"
#include "Validaciones.h"
#include "ArchivoPeliculas.h"
#include "ArchivoDirectores.h"
#include "ArchivoPeliculasxGenero.h"

/// ---------------------------------------------------------------
/// Funciones auxiliares
/// ---------------------------------------------------------------

/// Copia en el vector las peliculas que estan en alta.
/// El vector tiene que tener lugar para contarPeliculasActivas() peliculas.
void copiarPeliculasActivas(Pelicula *v){
    ArchivoPeliculas archivo;
    int cantidadRegistros=archivo.CantidadRegistros();
    int cantidad=0;
    for(int i=0;i<cantidadRegistros;i++){
        Pelicula reg=archivo.Leer(i);
        if(!reg.getEliminado()){
            v[cantidad]=reg;
            cantidad++;
        }
    }
}

/// Copia en el vector los directores que estan en alta.
void copiarDirectoresActivos(Director *v){
    ArchivoDirectores archivo;
    int cantidadRegistros=archivo.CantidadRegistros();
    int cantidad=0;
    for(int i=0;i<cantidadRegistros;i++){
        Director reg=archivo.Leer(i);
        if(!reg.getEliminado()){
            v[cantidad]=reg;
            cantidad++;
        }
    }
}

/// Copia todos los directores (tambien los dados de baja), en el mismo
/// orden del archivo: el director con id N queda en la posicion N-1.
void copiarTodosLosDirectores(Director *v){
    ArchivoDirectores archivo;
    int cantidadRegistros=archivo.CantidadRegistros();
    for(int i=0;i<cantidadRegistros;i++){
        v[i]=archivo.Leer(i);
    }
}

/// Ordenamiento por seleccion, de la A a la Z
void ordenarPeliculasPorTitulo(Pelicula *v, int tam){
    int i, j, posmin;
    Pelicula aux;
    for(i=0;i<tam-1;i++){
        posmin=i;
        for(j=i+1;j<tam;j++){
            if(compararSinMayusculas(v[j].getTitulo(), v[posmin].getTitulo())<0){
                posmin=j;
            }
        }
        aux=v[i];
        v[i]=v[posmin];
        v[posmin]=aux;
    }
}

/// Ordenamiento por seleccion, de mayor a menor calificacion
void ordenarPeliculasPorCalificacion(Pelicula *v, int tam){
    int i, j, posmax;
    Pelicula aux;
    for(i=0;i<tam-1;i++){
        posmax=i;
        for(j=i+1;j<tam;j++){
            if(v[j].getCalificacion()>v[posmax].getCalificacion()){
                posmax=j;
            }
        }
        aux=v[i];
        v[i]=v[posmax];
        v[posmax]=aux;
    }
}

/// Ordenamiento por seleccion, por apellido de la A a la Z
void ordenarDirectoresPorApellido(Director *v, int tam){
    int i, j, posmin;
    Director aux;
    for(i=0;i<tam-1;i++){
        posmin=i;
        for(j=i+1;j<tam;j++){
            if(compararSinMayusculas(v[j].getApellido(), v[posmin].getApellido())<0){
                posmin=j;
            }
        }
        aux=v[i];
        v[i]=v[posmin];
        v[posmin]=aux;
    }
}

/// Muestra una pelicula en dos lineas. El nombre del director se toma
/// del vector de directores, en la posicion idDirector-1.
void mostrarFilaPelicula(Pelicula reg, Director *vDirectores){
    int posDirector=reg.getIdDirector()-1;
    cout<<reg.getIdPelicula()<<" - "<<reg.getTitulo()<<endl;
    cout<<"    DIRECTOR: "<<vDirectores[posDirector].getApellido()<<", "<<vDirectores[posDirector].getNombre();
    cout<<" - "<<reg.getDuracionMinutos()<<" MIN - CALIFICACION: "<<reg.getCalificacion()<<endl;
}

/// Muestra un vector de peliculas con el nombre de su director.
void mostrarPeliculasConDirector(Pelicula *v, int tam){
    ArchivoDirectores archivo;
    int cantidadDirectores=archivo.CantidadRegistros();
    Director *vDirectores=new Director[cantidadDirectores];
    if(vDirectores==NULL){
        cout<<"ERROR DE ASIGNACION DE MEMORIA"<<endl;
        return;
    }
    copiarTodosLosDirectores(vDirectores);

    for(int i=0;i<tam;i++){
        mostrarFilaPelicula(v[i], vDirectores);
    }
    lineaSimple();
    cout<<"TOTAL: "<<tam<<" PELICULA/S"<<endl;

    delete []vDirectores;
}

/// ---------------------------------------------------------------
/// Listados
/// ---------------------------------------------------------------

void listadoPeliculasPorTitulo(){
    titulo("PELICULAS POR TITULO");
    int cantidad=contarPeliculasActivas();
    if(cantidad==0){
        cout<<"No hay peliculas cargadas."<<endl;
        system("pause");
        return;
    }

    Pelicula *vPeliculas=new Pelicula[cantidad];
    if(vPeliculas==NULL){
        cout<<"ERROR DE ASIGNACION DE MEMORIA"<<endl;
        return;
    }
    copiarPeliculasActivas(vPeliculas);
    ordenarPeliculasPorTitulo(vPeliculas, cantidad);
    mostrarPeliculasConDirector(vPeliculas, cantidad);
    delete []vPeliculas;
    system("pause");
}

void listadoPeliculasPorCalificacion(){
    titulo("PELICULAS POR CALIFICACION");
    int cantidad=contarPeliculasActivas();
    if(cantidad==0){
        cout<<"No hay peliculas cargadas."<<endl;
        system("pause");
        return;
    }

    Pelicula *vPeliculas=new Pelicula[cantidad];
    if(vPeliculas==NULL){
        cout<<"ERROR DE ASIGNACION DE MEMORIA"<<endl;
        return;
    }
    copiarPeliculasActivas(vPeliculas);
    ordenarPeliculasPorCalificacion(vPeliculas, cantidad);
    mostrarPeliculasConDirector(vPeliculas, cantidad);
    delete []vPeliculas;
    system("pause");
}

void listadoDirectoresPorApellido(){
    titulo("DIRECTORES POR APELLIDO");
    int cantidad=contarDirectoresActivos();
    if(cantidad==0){
        cout<<"No hay directores cargados."<<endl;
        system("pause");
        return;
    }

    Director *vDirectores=new Director[cantidad];
    if(vDirectores==NULL){
        cout<<"ERROR DE ASIGNACION DE MEMORIA"<<endl;
        return;
    }
    copiarDirectoresActivos(vDirectores);
    ordenarDirectoresPorApellido(vDirectores, cantidad);
    for(int i=0;i<cantidad;i++){
        vDirectores[i].mostrar();
    }
    lineaSimple();
    cout<<"TOTAL: "<<cantidad<<" DIRECTOR/ES"<<endl;
    delete []vDirectores;
    system("pause");
}

/// ---------------------------------------------------------------
/// Consultas de peliculas
/// ---------------------------------------------------------------

void consultaPeliculasPorTitulo(){
    titulo("CONSULTA DE PELICULAS POR TITULO");
    char buscado[50];
    cargarTextoObligatorio("TITULO: ", buscado, 49);
    lineaSimple();

    ArchivoPeliculas archivo;
    int cantidadRegistros=archivo.CantidadRegistros();
    int encontradas=0;
    for(int i=0;i<cantidadRegistros;i++){
        Pelicula reg=archivo.Leer(i);
        if(!reg.getEliminado() && compararSinMayusculas(reg.getTitulo(), buscado)==0){
            reg.mostrar();
            lineaSimple();
            encontradas++;
        }
    }
    if(encontradas==0){
        cout<<"No hay ninguna pelicula con ese titulo."<<endl;
    }
    system("pause");
}

void consultaPeliculasPorGenero(){
    titulo("CONSULTA DE PELICULAS POR GENERO");
    if(contarGenerosActivos()==0){
        cout<<"No hay generos cargados."<<endl;
        system("pause");
        return;
    }
    int idGenero=pedirIdGeneroActivo();
    lineaSimple();

    ArchivoPeliculas archivoPeliculas;
    int cantidadPeliculas=archivoPeliculas.CantidadRegistros();
    if(cantidadPeliculas==0){
        cout<<"No hay peliculas cargadas."<<endl;
        system("pause");
        return;
    }

    /// Un lugar por cada pelicula del archivo: la pelicula con id N va en la
    /// posicion N-1. Se marca con 1 cada pelicula que tiene el genero.
    int *vTieneGenero=new int[cantidadPeliculas];
    if(vTieneGenero==NULL){
        cout<<"ERROR DE ASIGNACION DE MEMORIA"<<endl;
        return;
    }
    ponerCeroVector(vTieneGenero, cantidadPeliculas);

    ArchivoPeliculasxGenero archivoPxG;
    int cantidadPxG=archivoPxG.CantidadRegistros();
    for(int i=0;i<cantidadPxG;i++){
        PeliculaxGenero reg=archivoPxG.Leer(i);
        if(reg.getEstado() && reg.getIdGenero()==idGenero){
            vTieneGenero[reg.getIdPelicula()-1]=1;
        }
    }

    int encontradas=0;
    for(int i=0;i<cantidadPeliculas;i++){
        if(vTieneGenero[i]==1){
            Pelicula reg=archivoPeliculas.Leer(i);
            if(!reg.getEliminado()){
                cout<<reg.getIdPelicula()<<" - "<<reg.getTitulo()<<endl;
                encontradas++;
            }
        }
    }
    if(encontradas==0){
        cout<<"No hay peliculas activas de ese genero."<<endl;
    }
    else{
        lineaSimple();
        cout<<"TOTAL: "<<encontradas<<" PELICULA/S"<<endl;
    }

    delete []vTieneGenero;
    system("pause");
}

void consultaPeliculasPorDuracion(){
    titulo("CONSULTA DE PELICULAS POR DURACION");
    int minimo=leerEntero("DURACION MINIMA (MINUTOS): ");
    while(minimo<=0){
        cout<<"  Tiene que ser mayor a cero."<<endl;
        minimo=leerEntero("DURACION MINIMA (MINUTOS): ");
    }
    int maximo=leerEntero("DURACION MAXIMA (MINUTOS): ");
    while(maximo<minimo){
        cout<<"  Tiene que ser mayor o igual a la minima."<<endl;
        maximo=leerEntero("DURACION MAXIMA (MINUTOS): ");
    }
    lineaSimple();

    ArchivoPeliculas archivo;
    int cantidadRegistros=archivo.CantidadRegistros();
    int encontradas=0;
    for(int i=0;i<cantidadRegistros;i++){
        Pelicula reg=archivo.Leer(i);
        if(!reg.getEliminado() && reg.getDuracionMinutos()>=minimo && reg.getDuracionMinutos()<=maximo){
            cout<<reg.getIdPelicula()<<" - "<<reg.getTitulo()<<" ("<<reg.getDuracionMinutos()<<" MIN)"<<endl;
            encontradas++;
        }
    }
    if(encontradas==0){
        cout<<"No hay peliculas que duren entre "<<minimo<<" y "<<maximo<<" minutos."<<endl;
    }
    else{
        lineaSimple();
        cout<<"TOTAL: "<<encontradas<<" PELICULA/S"<<endl;
    }
    system("pause");
}

/// ---------------------------------------------------------------
/// Consultas de directores
/// ---------------------------------------------------------------

void consultaDirectorPorId(){
    titulo("CONSULTA DE DIRECTOR POR ID");
    int id=leerEntero("ID DEL DIRECTOR: ");
    lineaSimple();

    ArchivoDirectores archivo;
    int posicion=archivo.Buscar(id);
    if(posicion==-1){
        cout<<"No existe un director con ese ID."<<endl;
    }
    else{
        Director reg=archivo.Leer(posicion);
        reg.mostrar();
    }
    system("pause");
}

void consultaDirectoresPorApellido(){
    titulo("CONSULTA DE DIRECTORES POR APELLIDO");
    char buscado[30];
    cargarTextoObligatorio("APELLIDO: ", buscado, 29);
    lineaSimple();

    ArchivoDirectores archivo;
    int cantidadRegistros=archivo.CantidadRegistros();
    int encontrados=0;
    for(int i=0;i<cantidadRegistros;i++){
        Director reg=archivo.Leer(i);
        if(!reg.getEliminado() && compararSinMayusculas(reg.getApellido(), buscado)==0){
            reg.mostrar();
            encontrados++;
        }
    }
    if(encontrados==0){
        cout<<"No hay ningun director con ese apellido."<<endl;
    }
    system("pause");
}

/// ---------------------------------------------------------------
/// Informe: peliculas de un director segun su calificacion
/// ---------------------------------------------------------------

void peliculasDeUnDirector(){
    titulo("PELICULAS DE UN DIRECTOR");
    int idDirector=leerEntero("INGRESE ID DE DIRECTOR: ");
    if(!existeDirectorActivo(idDirector)){
        cout<<"El director no existe."<<endl;
        system("pause");
        return;
    }
    cout<<"DIRECTOR: ";
    mostrarNombreDirector(idDirector);
    cout<<endl;
    lineaSimple();

    /// Se cuentan sus peliculas activas para pedir el vector justo
    ArchivoPeliculas archivo;
    int cantidadRegistros=archivo.CantidadRegistros();
    int cantidad=0;
    for(int i=0;i<cantidadRegistros;i++){
        Pelicula reg=archivo.Leer(i);
        if(!reg.getEliminado() && reg.getIdDirector()==idDirector){
            cantidad++;
        }
    }
    if(cantidad==0){
        cout<<"El director no tiene peliculas activas."<<endl;
        system("pause");
        return;
    }

    Pelicula *vPeliculas=new Pelicula[cantidad];
    if(vPeliculas==NULL){
        cout<<"ERROR DE ASIGNACION DE MEMORIA"<<endl;
        return;
    }
    int pos=0;
    for(int i=0;i<cantidadRegistros;i++){
        Pelicula reg=archivo.Leer(i);
        if(!reg.getEliminado() && reg.getIdDirector()==idDirector){
            vPeliculas[pos]=reg;
            pos++;
        }
    }

    ordenarPeliculasPorCalificacion(vPeliculas, cantidad);

    cout<<"POS  PELICULA  -  CALIFICACION"<<endl;
    lineaSimple();
    for(int i=0;i<cantidad;i++){
        cout<<" "<<i+1<<"   "<<vPeliculas[i].getTitulo()<<"  -  "<<vPeliculas[i].getCalificacion()<<endl;
    }
    lineaDoble();

    delete []vPeliculas;
    system("pause");
}
