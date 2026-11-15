#include <iostream>
#include <cstdlib>

using namespace std;

#include "MenuPeliculas.h"
#include "FuncionesGlobales.h"
#include "Validaciones.h"
#include "ArchivoPeliculas.h"
#include "ArchivoPeliculasxGenero.h"

void menuPeliculas(){
    int opcion=-1;
    while(opcion!=0){
        titulo("PELICULAS");
        cout<<"  1 - ALTA DE PELICULA"<<endl;
        cout<<"  2 - BAJA DE PELICULA"<<endl;
        cout<<"  3 - MODIFICAR PELICULA"<<endl;
        lineaSimple();
        cout<<"  GENEROS DE CADA PELICULA"<<endl;
        cout<<"  4 - AGREGAR UN GENERO A UNA PELICULA"<<endl;
        cout<<"  5 - QUITAR UN GENERO DE UNA PELICULA"<<endl;
        cout<<"  6 - CAMBIAR UN GENERO DE UNA PELICULA"<<endl;
        cout<<"  7 - VER LOS GENEROS DE UNA PELICULA"<<endl;
        lineaSimple();
        cout<<"  0 - VOLVER"<<endl;
        lineaDoble();
        opcion=leerEntero("OPCION: ");

        switch(opcion){
            case 1: altaPelicula(); break;
            case 2: bajaPelicula(); break;
            case 3: modificarPelicula(); break;
            case 4: agregarGeneroAPelicula(); break;
            case 5: quitarGeneroDePelicula(); break;
            case 6: cambiarGeneroDePelicula(); break;
            case 7: verGenerosDePelicula(); break;
            case 0: break;
            default:
                cout<<"Opcion incorrecta."<<endl;
                system("pause");
                break;
        }
    }
}

/// ---------------------------------------------------------------
/// ABM de peliculas
/// ---------------------------------------------------------------

void altaPelicula(){
    titulo("ALTA DE PELICULA");
    if(contarDirectoresActivos()==0){
        cout<<"Primero hay que cargar al menos un director (menu DIRECTORES)."<<endl;
        system("pause");
        return;
    }

    ArchivoPeliculas archivo;
    Pelicula reg;
    reg.cargar();
    reg.setIdPelicula(archivo.CantidadRegistros()+1);

    lineaSimple();
    reg.mostrar();
    lineaSimple();
    if(!confirmar("Guardar la pelicula?")){
        cout<<"Operacion cancelada. No se guardo nada."<<endl;
        system("pause");
        return;
    }
    if(!archivo.Guardar(reg)){
        cout<<"ERROR: no se pudo guardar en Peliculas.dat"<<endl;
        system("pause");
        return;
    }
    cout<<"PELICULA GUARDADA CON ID "<<reg.getIdPelicula()<<endl;

    if(contarGenerosActivos()>0){
        while(confirmar("Agregar un genero a esta pelicula?")){
            int idGenero=pedirIdGeneroActivo();
            guardarGeneroDePelicula(reg.getIdPelicula(), idGenero);
        }
    }
    else{
        cout<<"(Todavia no hay generos cargados: se pueden agregar despues)"<<endl;
    }
    system("pause");
}

void bajaPelicula(){
    titulo("BAJA DE PELICULA");
    if(contarPeliculasActivas()==0){
        cout<<"No hay peliculas cargadas."<<endl;
        system("pause");
        return;
    }

    listarPeliculasParaElegir();
    int id=leerEntero("ID DE LA PELICULA A DAR DE BAJA: ");
    ArchivoPeliculas archivo;
    int posicion=archivo.Buscar(id);
    if(posicion==-1){
        cout<<"No existe una pelicula con ese ID."<<endl;
        system("pause");
        return;
    }
    Pelicula reg=archivo.Leer(posicion);
    if(reg.getEliminado()){
        cout<<"Esa pelicula ya esta dada de baja."<<endl;
        system("pause");
        return;
    }

    lineaSimple();
    reg.mostrar();
    lineaSimple();

    if(peliculaTieneFuncionesFuturas(id)){
        cout<<"No se puede dar de baja: tiene funciones futuras activas."<<endl;
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
        cout<<"PELICULA DADA DE BAJA"<<endl;
    }
    else{
        cout<<"ERROR: no se pudo guardar en Peliculas.dat"<<endl;
    }
    system("pause");
}

void modificarPelicula(){
    titulo("MODIFICAR PELICULA");
    if(contarPeliculasActivas()==0){
        cout<<"No hay peliculas cargadas."<<endl;
        system("pause");
        return;
    }

    listarPeliculasParaElegir();
    int id=leerEntero("ID DE LA PELICULA A MODIFICAR: ");
    ArchivoPeliculas archivo;
    int posicion=archivo.Buscar(id);
    if(posicion==-1){
        cout<<"No existe una pelicula con ese ID."<<endl;
        system("pause");
        return;
    }
    Pelicula reg=archivo.Leer(posicion);
    if(reg.getEliminado()){
        cout<<"Esa pelicula esta dada de baja."<<endl;
        system("pause");
        return;
    }

    lineaSimple();
    reg.mostrar();
    lineaSimple();
    cout<<"  1 - TITULO"<<endl;
    cout<<"  2 - DIRECTOR"<<endl;
    cout<<"  3 - DURACION"<<endl;
    cout<<"  4 - DESCRIPCION"<<endl;
    cout<<"  (La calificacion queda fija desde el alta)"<<endl;
    cout<<"  0 - VOLVER"<<endl;
    int opcion=leerEntero("QUE DATO QUIERE MODIFICAR?: ");
    while(opcion<0 || opcion>4){
        cout<<"  Opcion incorrecta."<<endl;
        opcion=leerEntero("QUE DATO QUIERE MODIFICAR?: ");
    }
    if(opcion==0){
        return;
    }

    char texto[200];
    int duracion;
    switch(opcion){
        case 1:
            cargarTextoObligatorio("NUEVO TITULO: ", texto, 49);
            reg.setTitulo(texto);
            break;
        case 2:
            reg.setIdDirector(pedirIdDirectorActivo());
            break;
        case 3:
            duracion=leerEntero("NUEVA DURACION (MINUTOS): ");
            while(duracion<=0){
                cout<<"  La duracion tiene que ser mayor a cero."<<endl;
                duracion=leerEntero("NUEVA DURACION (MINUTOS): ");
            }
            reg.setDuracionMinutos(duracion);
            break;
        case 4:
            cout<<"NUEVA DESCRIPCION: ";
            cargarCadena(texto, 199);
            reg.setDescripcion(texto);
            break;
    }

    if(archivo.Guardar(reg, posicion)){
        cout<<"CAMBIO GUARDADO"<<endl;
    }
    else{
        cout<<"ERROR: no se pudo guardar en Peliculas.dat"<<endl;
    }
    system("pause");
}

/// ---------------------------------------------------------------
/// Generos de cada pelicula (PeliculasxGenero.dat)
/// ---------------------------------------------------------------

/// Muestra los generos activos de la pelicula y devuelve cuantos tiene.
int mostrarGenerosDePelicula(int idPelicula){
    ArchivoPeliculasxGenero archivo;
    int cantidadRegistros=archivo.CantidadRegistros();
    int cantidad=0;
    cout<<"GENEROS DE LA PELICULA:"<<endl;
    for(int i=0;i<cantidadRegistros;i++){
        PeliculaxGenero reg=archivo.Leer(i);
        if(reg.getEstado() && reg.getIdPelicula()==idPelicula){
            cout<<"  "<<reg.getIdGenero()<<" - ";
            mostrarNombreGenero(reg.getIdGenero());
            cout<<endl;
            cantidad++;
        }
    }
    if(cantidad==0){
        cout<<"  (NINGUNO)"<<endl;
    }
    return cantidad;
}

/// Guarda el par pelicula-genero sin repetirlo: si el par ya existe
/// dado de baja, lo vuelve a activar en vez de agregar otro registro.
void guardarGeneroDePelicula(int idPelicula, int idGenero){
    ArchivoPeliculasxGenero archivo;
    int posicion=archivo.Buscar(idPelicula, idGenero);

    if(posicion!=-1){
        PeliculaxGenero reg=archivo.Leer(posicion);
        if(reg.getEstado()){
            cout<<"La pelicula ya tiene ese genero. No se agrego nada."<<endl;
            return;
        }
        reg.setEstado(true);
        if(archivo.Guardar(reg, posicion)){
            cout<<"GENERO AGREGADO A LA PELICULA"<<endl;
        }
        else{
            cout<<"ERROR: no se pudo guardar en PeliculasxGenero.dat"<<endl;
        }
        return;
    }

    PeliculaxGenero reg;
    reg.setIdPelicula(idPelicula);
    reg.setIdGenero(idGenero);
    reg.setEstado(true);
    if(archivo.Guardar(reg)){
        cout<<"GENERO AGREGADO A LA PELICULA"<<endl;
    }
    else{
        cout<<"ERROR: no se pudo guardar en PeliculasxGenero.dat"<<endl;
    }
}

void agregarGeneroAPelicula(){
    titulo("AGREGAR UN GENERO A UNA PELICULA");
    if(contarPeliculasActivas()==0 || contarGenerosActivos()==0){
        cout<<"Tiene que haber al menos una pelicula y un genero cargados."<<endl;
        system("pause");
        return;
    }

    PeliculaxGenero reg;
    reg.cargar();
    lineaSimple();
    guardarGeneroDePelicula(reg.getIdPelicula(), reg.getIdGenero());
    system("pause");
}

void quitarGeneroDePelicula(){
    titulo("QUITAR UN GENERO DE UNA PELICULA");
    if(contarPeliculasActivas()==0){
        cout<<"No hay peliculas cargadas."<<endl;
        system("pause");
        return;
    }

    int idPelicula=pedirIdPeliculaActiva();
    lineaSimple();
    if(mostrarGenerosDePelicula(idPelicula)==0){
        cout<<"Esta pelicula no tiene generos para quitar."<<endl;
        system("pause");
        return;
    }

    int idGenero=leerEntero("ID DEL GENERO A QUITAR: ");
    ArchivoPeliculasxGenero archivo;
    int posicion=archivo.Buscar(idPelicula, idGenero);
    if(posicion==-1){
        cout<<"Esa pelicula no tiene ese genero."<<endl;
        system("pause");
        return;
    }
    PeliculaxGenero reg=archivo.Leer(posicion);
    if(!reg.getEstado()){
        cout<<"Esa pelicula no tiene ese genero."<<endl;
        system("pause");
        return;
    }
    if(!confirmar("Confirma que quiere quitar el genero?")){
        cout<<"Operacion cancelada."<<endl;
        system("pause");
        return;
    }

    reg.setEstado(false);
    if(archivo.Guardar(reg, posicion)){
        cout<<"GENERO QUITADO DE LA PELICULA"<<endl;
    }
    else{
        cout<<"ERROR: no se pudo guardar en PeliculasxGenero.dat"<<endl;
    }
    system("pause");
}

void cambiarGeneroDePelicula(){
    titulo("CAMBIAR UN GENERO DE UNA PELICULA");
    if(contarPeliculasActivas()==0 || contarGenerosActivos()==0){
        cout<<"Tiene que haber al menos una pelicula y un genero cargados."<<endl;
        system("pause");
        return;
    }

    int idPelicula=pedirIdPeliculaActiva();
    lineaSimple();
    if(mostrarGenerosDePelicula(idPelicula)==0){
        cout<<"Esta pelicula no tiene generos para cambiar."<<endl;
        system("pause");
        return;
    }

    int idViejo=leerEntero("ID DEL GENERO A CAMBIAR: ");
    ArchivoPeliculasxGenero archivo;
    int posicionViejo=archivo.Buscar(idPelicula, idViejo);
    if(posicionViejo==-1){
        cout<<"Esa pelicula no tiene ese genero."<<endl;
        system("pause");
        return;
    }
    PeliculaxGenero viejo=archivo.Leer(posicionViejo);
    if(!viejo.getEstado()){
        cout<<"Esa pelicula no tiene ese genero."<<endl;
        system("pause");
        return;
    }

    lineaSimple();
    cout<<"NUEVO GENERO"<<endl;
    int idNuevo=pedirIdGeneroActivo();
    if(idNuevo==idViejo){
        cout<<"Es el mismo genero. No se cambio nada."<<endl;
        system("pause");
        return;
    }
    int posicionNuevo=archivo.Buscar(idPelicula, idNuevo);
    if(posicionNuevo!=-1){
        PeliculaxGenero nuevo=archivo.Leer(posicionNuevo);
        if(nuevo.getEstado()){
            cout<<"La pelicula ya tiene ese genero. No se cambio nada."<<endl;
            system("pause");
            return;
        }
    }
    if(!confirmar("Confirma el cambio?")){
        cout<<"Operacion cancelada."<<endl;
        system("pause");
        return;
    }

    /// Se da de baja el par viejo y se guarda el nuevo (sin repetir pares)
    viejo.setEstado(false);
    if(!archivo.Guardar(viejo, posicionViejo)){
        cout<<"ERROR: no se pudo guardar en PeliculasxGenero.dat"<<endl;
        system("pause");
        return;
    }
    guardarGeneroDePelicula(idPelicula, idNuevo);
    system("pause");
}

void verGenerosDePelicula(){
    titulo("GENEROS DE UNA PELICULA");
    if(contarPeliculasActivas()==0){
        cout<<"No hay peliculas cargadas."<<endl;
        system("pause");
        return;
    }
    int idPelicula=pedirIdPeliculaActiva();
    lineaSimple();
    mostrarGenerosDePelicula(idPelicula);
    system("pause");
}
