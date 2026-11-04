#include <iostream>
#include <cstdlib>
#include "MenuFunciones.h"
#include "FuncionesGlobales.h"
#include "ArchivoFunciones.h"
#include "ArchivoPeliculas.h"
#include "Validaciones.h"

using namespace std;

static int duracionDePelicula(int idPelicula) {
    ArchivoPeliculas archivo;
    int posicion = archivo.Buscar(idPelicula);
    if (posicion == -1) return 0;
    Pelicula pelicula = archivo.Leer(posicion);
    return pelicula.getDuracionMinutos();
}

static bool validarFuncion(Funcion reg, int idIgnorar) {
    if (funcionVencida(reg)) {
        cout << "No se puede guardar una funcion cuya fecha y horario ya pasaron." << endl;
        return false;
    }

    int duracion = duracionDePelicula(reg.getIdPelicula());
    if (duracion <= 0) {
        cout << "No se pudo obtener la duracion de la pelicula." << endl;
        return false;
    }

    ArchivoFunciones archivo;
    if (archivo.haySuperposicion(reg, duracion, idIgnorar)) {
        cout << "El horario se superpone con otra funcion de la misma sala y fecha." << endl;
        return false;
    }
    return true;
}

void menuFunciones() {
    int opcion = -1;
    while (opcion != 0) {
        titulo("FUNCIONES");
        cout << "  1 - ALTA DE FUNCION" << endl;
        cout << "  2 - BAJA DE FUNCION" << endl;
        cout << "  3 - MODIFICAR FUNCION" << endl;
        cout << "  4 - LISTAR FUNCIONES" << endl;
        lineaSimple();
        cout << "  0 - VOLVER" << endl;
        lineaDoble();
        opcion = leerEntero("OPCION: ");

        switch (opcion) {
            case 1: altaFuncion(); break;
            case 2: bajaFuncion(); break;
            case 3: modificarFuncion(); break;
            case 4: listarFunciones(); break;
            case 0: break;
            default:
                cout << "Opcion incorrecta." << endl;
                system("pause");
                break;
        }
    }
}

void altaFuncion() {
    titulo("ALTA DE FUNCION");
    if (contarPeliculasActivas() == 0) {
        cout << "No hay peliculas activas para programar." << endl;
        system("pause");
        return;
    }
    if (contarSalasActivas() == 0) {
        cout << "No hay salas activas para programar." << endl;
        system("pause");
        return;
    }

    Funcion reg;
    reg.cargar();
    ArchivoFunciones archivo;
    reg.setIdFuncion(archivo.CantidadRegistros() + 1);

    if (!validarFuncion(reg, 0)) {
        system("pause");
        return;
    }

    lineaSimple();
    reg.mostrar();
    lineaSimple();
    if (!confirmar("Guardar la funcion?")) {
        cout << "Operacion cancelada." << endl;
        system("pause");
        return;
    }

    if (archivo.Guardar(reg)) cout << "FUNCION GUARDADA CON ID " << reg.getIdFuncion() << endl;
    else cout << "ERROR: no se pudo guardar la funcion." << endl;
    system("pause");
}

void bajaFuncion() {
    titulo("BAJA DE FUNCION");
    ArchivoFunciones archivo;
    if (archivo.CantidadRegistros() == 0) {
        cout << "No hay funciones cargadas." << endl;
        system("pause");
        return;
    }

    listarFunciones();
    int id = leerEntero("ID DE LA FUNCION A DAR DE BAJA: ");
    int posicion = archivo.Buscar(id);
    if (posicion == -1) {
        cout << "No existe una funcion con ese ID." << endl;
        system("pause");
        return;
    }

    Funcion reg = archivo.Leer(posicion);
    if (reg.getEliminado()) {
        cout << "Esa funcion ya esta dada de baja." << endl;
        system("pause");
        return;
    }

    reg.mostrar();
    if (!confirmar("Confirma la baja?")) {
        cout << "Operacion cancelada." << endl;
        system("pause");
        return;
    }

    reg.setEliminado(true);
    if (archivo.Guardar(reg, posicion)) cout << "FUNCION DADA DE BAJA." << endl;
    else cout << "ERROR: no se pudo guardar la baja." << endl;
    system("pause");
}

void modificarFuncion() {
    titulo("MODIFICAR FUNCION");
    ArchivoFunciones archivo;
    if (archivo.CantidadRegistros() == 0) {
        cout << "No hay funciones cargadas." << endl;
        system("pause");
        return;
    }

    listarFunciones();
    int id = leerEntero("ID DE LA FUNCION A MODIFICAR: ");
    int posicion = archivo.Buscar(id);
    if (posicion == -1) {
        cout << "No existe una funcion con ese ID." << endl;
        system("pause");
        return;
    }

    Funcion anterior = archivo.Leer(posicion);
    if (anterior.getEliminado()) {
        cout << "Esa funcion esta dada de baja." << endl;
        system("pause");
        return;
    }

    cout << "Ingrese los nuevos datos de la funcion." << endl;
    if (contarPeliculasActivas() == 0 || contarSalasActivas() == 0) {
        cout << "Se necesita al menos una pelicula y una sala activa." << endl;
        system("pause");
        return;
    }

    Funcion nueva;
    nueva.cargar();
    nueva.setIdFuncion(id);

    if (!validarFuncion(nueva, id)) {
        system("pause");
        return;
    }

    lineaSimple();
    nueva.mostrar();
    if (!confirmar("Guardar los cambios?")) {
        cout << "Operacion cancelada." << endl;
        system("pause");
        return;
    }

    if (archivo.Guardar(nueva, posicion)) cout << "FUNCION MODIFICADA." << endl;
    else cout << "ERROR: no se pudo modificar la funcion." << endl;
    system("pause");
}

void listarFunciones() {
    titulo("LISTADO DE FUNCIONES");
    ArchivoFunciones archivo;
    int total = archivo.CantidadRegistros();
    bool hay = false;

    for (int i = 0; i < total; i++) {
        Funcion reg = archivo.Leer(i);
        if (!reg.getEliminado()) {
            reg.mostrar();
            cout << "----------------------------------------" << endl;
            hay = true;
        }
    }

    if (!hay) cout << "No hay funciones activas." << endl;
    system("pause");
}
