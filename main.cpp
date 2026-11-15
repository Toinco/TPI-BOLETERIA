/// BOLETERA - Boleteria de cine
/// UTN FRGP - Programacion II - TP Integrador
///
/// Menu principal: une los submenus de los tres bloques y los menus de
/// listados, consultas e informes.

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "FuncionesGlobales.h"
#include "MenuPeliculas.h"
#include "MenuDirectores.h"
#include "MenuGeneros.h"
#include "ListadosYConsultas.h"
#include "MenuConfiguracion.h"
#include "MenuPrecios.h"
#include "MenuSalas.h"
#include "MenuFunciones.h"
#include "MenuVentas.h"
#include "ArchivoPrecios.h"
void menuListados();
void menuConsultas();
void menuInformes();

int main(){
    srand(time(NULL));   /// para el codigo al azar de la restauracion

    /// Si Precios.dat esta vacio, crea los 4 tipos de sala con su precio.
    /// Asi se puede vender aunque nunca se haya entrado al menu PRECIOS.
    ArchivoPrecios archivoPrecios;
    archivoPrecios.cargarPreciosIniciales();

    int opcion=-1;
    while(opcion!=0){
        titulo("MENU PRINCIPAL");
        cout<<"ARCHIVOS"<<endl;
        cout<<"  1 - PELICULAS          4 - PRECIOS"<<endl;
        cout<<"  2 - DIRECTORES         5 - SALAS"<<endl;
        cout<<"  3 - GENEROS            6 - FUNCIONES"<<endl;
        lineaSimple();
        cout<<"OPERACION"<<endl;
        cout<<"  7 - VENTA DE ENTRADAS"<<endl;
        lineaSimple();
        cout<<"SALIDAS"<<endl;
        cout<<"  8 - LISTADOS   9 - CONSULTAS   10 - INFORMES"<<endl;
        lineaSimple();
        cout<<" 11 - CONFIGURACION"<<endl;
        cout<<"  0 - SALIR"<<endl;
        lineaDoble();
        opcion=leerEntero("OPCION: ");

        switch(opcion){
            case 1: menuPeliculas(); break;
            case 2: menuDirectores(); break;
            case 3: menuGeneros(); break;
            case 4: menuPrecios(); break;
            case 5: menuSalas(); break;
            case 6: menuFunciones(); break;
            case 7: menuVentas(); break;
            case 8: menuListados(); break;
            case 9: menuConsultas(); break;
            case 10: menuInformes(); break;
            case 11: menuConfiguracion(); break;
            case 0:
                cout<<"Gracias por usar BOLETERA."<<endl;
                break;
            default:
                cout<<"Opcion incorrecta."<<endl;
                system("pause");
                break;
        }
    }
    return 0;
}

void menuListados(){
    int opcion=-1;
    while(opcion!=0){
        titulo("LISTADOS");
        cout<<"  1 - PELICULAS POR TITULO"<<endl;
        cout<<"  2 - PELICULAS POR CALIFICACION"<<endl;
        cout<<"  3 - DIRECTORES POR APELLIDO"<<endl;
        cout<<"  4 - PRECIOS POR TIPO DE SALA"<<endl;
        cout<<"  5 - SALAS POR CAPACIDAD"<<endl;
        cout<<"  6 - FUNCIONES POR FECHA Y HORARIO"<<endl;
        cout<<"  7 - VENTAS POR FECHA"<<endl;
        lineaSimple();
        cout<<"  0 - VOLVER"<<endl;
        lineaDoble();
        opcion=leerEntero("OPCION: ");

        switch(opcion){
            case 1: listadoPeliculasPorTitulo(); break;
            case 2: listadoPeliculasPorCalificacion(); break;
            case 3: listadoDirectoresPorApellido(); break;
            case 4: listadoPreciosPorTipo(); break;
            case 5: listadoSalasPorCapacidad(); break;
            case 6: listadoFuncionesPorFecha(); break;
            case 7: ventasOrdenadasPorFecha(); break;
            case 0: break;
            default:
                cout<<"Opcion incorrecta."<<endl;
                system("pause");
                break;
        }
    }
}

void menuConsultas(){
    int opcion=-1;
    while(opcion!=0){
        titulo("CONSULTAS");
        cout<<"PELICULAS"<<endl;
        cout<<"  1 - POR TITULO"<<endl;
        cout<<"  2 - POR DIRECTOR (ORDENADAS POR CALIFICACION)"<<endl;
        cout<<"  3 - POR GENERO"<<endl;
        cout<<"  4 - POR RANGO DE DURACION"<<endl;
        cout<<"DIRECTORES"<<endl;
        cout<<"  5 - POR ID"<<endl;
        cout<<"  6 - POR APELLIDO"<<endl;
        cout<<"FUNCIONES"<<endl;
        cout<<"  7 - POR FECHA          8 - POR PELICULA"<<endl;
        cout<<"  9 - POR SALA          10 - CON ENTRADAS DISPONIBLES"<<endl;
        cout<<"VENTAS"<<endl;
        cout<<" 11 - POR NUMERO        12 - POR RANGO DE FECHAS"<<endl;
        cout<<" 13 - POR FORMA DE PAGO"<<endl;
        lineaSimple();
        cout<<"  0 - VOLVER"<<endl;
        lineaDoble();
        opcion=leerEntero("OPCION: ");

        switch(opcion){
            case 1: consultaPeliculasPorTitulo(); break;
            case 2: peliculasDeUnDirector(); break;
            case 3: consultaPeliculasPorGenero(); break;
            case 4: consultaPeliculasPorDuracion(); break;
            case 5: consultaDirectorPorId(); break;
            case 6: consultaDirectoresPorApellido(); break;
            case 7: consultaFuncionesPorFecha(); break;
            case 8: consultaFuncionesPorPelicula(); break;
            case 9: consultaFuncionesPorSala(); break;
            case 10: consultaFuncionesDisponibles(); break;
            case 11: ventasPorNumero(); break;
            case 12: ventasPorRangoDeFechas(); break;
            case 13: ventasPorFormaPago(); break;
            case 0: break;
            default:
                cout<<"Opcion incorrecta."<<endl;
                system("pause");
                break;
        }
    }
}

void menuInformes(){
    int opcion=-1;
    while(opcion!=0){
        titulo("INFORMES");
        cout<<"  1 - RECAUDACION ANUAL"<<endl;
        cout<<"  2 - RECAUDACION POR PELICULA"<<endl;
        cout<<"  3 - ENTRADAS VENDIDAS POR TIPO DE SALA"<<endl;
        cout<<"  4 - OCUPACION POR SALA"<<endl;
        cout<<"  5 - PELICULAS DE UN DIRECTOR SEGUN SU CALIFICACION"<<endl;
        cout<<"  6 - RECAUDACION POR FORMA DE PAGO"<<endl;
        lineaSimple();
        cout<<"  0 - VOLVER"<<endl;
        lineaDoble();
        opcion=leerEntero("OPCION: ");

        switch(opcion){
            case 1: recaudacionAnual(); break;
            case 2: recaudacionPorPelicula(); break;
            case 3: entradasPorTipoDeSala(); break;
            case 4: ocupacionPorSala(); break;
            case 5: peliculasDeUnDirector(); break;
            case 6: recaudacionPorFormaPago(); break;
            case 0: break;
            default:
                cout<<"Opcion incorrecta."<<endl;
                system("pause");
                break;
        }
    }
}
