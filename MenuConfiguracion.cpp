#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

#include "MenuConfiguracion.h"
#include "FuncionesGlobales.h"
#include "ArchivoPeliculas.h"
#include "ArchivoDirectores.h"
#include "ArchivoGeneros.h"
#include "ArchivoPeliculasxGenero.h"

/// Los ocho archivos del sistema, en el orden del menu
const int CANTIDAD_ARCHIVOS=8;
const int OPCION_TODOS=9;

char vArchivos[CANTIDAD_ARCHIVOS][30]={
    "Peliculas.dat",
    "Directores.dat",
    "Generos.dat",
    "PeliculasxGenero.dat",
    "Precios.dat",
    "Salas.dat",
    "Funciones.dat",
    "Ventas.dat"
};

char vNombres[CANTIDAD_ARCHIVOS][30]={
    "PELICULAS",
    "DIRECTORES",
    "GENEROS",
    "PELICULAS X GENERO",
    "PRECIOS",
    "SALAS",
    "FUNCIONES",
    "VENTAS"
};

void menuConfiguracion(){
    int opcion=-1;
    while(opcion!=0){
        titulo("CONFIGURACION");
        cout<<"  1 - REALIZAR COPIA DE SEGURIDAD"<<endl;
        cout<<"  2 - RESTAURAR COPIA DE SEGURIDAD"<<endl;
        cout<<"  3 - EXPORTAR DATOS A CSV"<<endl;
        lineaSimple();
        cout<<"  0 - VOLVER"<<endl;
        lineaDoble();
        opcion=leerEntero("OPCION: ");

        switch(opcion){
            case 1: realizarCopiaDeSeguridad(); break;
            case 2: restaurarCopiaDeSeguridad(); break;
            case 3: exportarDatosCsv(); break;
            case 0: break;
            default:
                cout<<"Opcion incorrecta."<<endl;
                system("pause");
                break;
        }
    }
}

/// ---------------------------------------------------------------
/// Funciones de archivos
/// ---------------------------------------------------------------

bool existeArchivo(const char *nombre){
    FILE *p=fopen(nombre, "rb");
    if(p==NULL){
        return false;
    }
    fclose(p);
    return true;
}

/// Copia un archivo byte por byte
bool copiarArchivo(const char *origen, const char *destino){
    FILE *pOrigen=fopen(origen, "rb");
    if(pOrigen==NULL){
        return false;
    }
    FILE *pDestino=fopen(destino, "wb");
    if(pDestino==NULL){
        fclose(pOrigen);
        return false;
    }
    char letra;
    while(fread(&letra, sizeof letra, 1, pOrigen)==1){
        fwrite(&letra, sizeof letra, 1, pDestino);
    }
    fclose(pOrigen);
    fclose(pDestino);
    return true;
}

/// Arma "backups/NombreArchivo.dat"
void armarRutaBackup(char *ruta, int indice){
    strcpy(ruta, "backups/");
    strcat(ruta, vArchivos[indice]);
}

void mostrarListaArchivos(){
    for(int i=0;i<CANTIDAD_ARCHIVOS;i++){
        cout<<"  "<<i+1<<" - "<<vNombres[i]<<endl;
    }
    cout<<"  "<<OPCION_TODOS<<" - TODOS"<<endl;
    lineaSimple();
    cout<<"  0 - VOLVER"<<endl;
    lineaDoble();
}

int elegirArchivo(const char *mensaje){
    int opcion=leerEntero(mensaje);
    while(opcion<0 || opcion>OPCION_TODOS){
        cout<<"  Opcion incorrecta."<<endl;
        opcion=leerEntero(mensaje);
    }
    return opcion;
}

/// ---------------------------------------------------------------
/// Copia de seguridad
/// ---------------------------------------------------------------

void realizarCopiaDeSeguridad(){
    titulo("REALIZAR COPIA DE SEGURIDAD");
    mostrarListaArchivos();
    int opcion=elegirArchivo("ARCHIVO A COPIAR: ");
    if(opcion==0){
        return;
    }

    system("if not exist backups mkdir backups");
    lineaSimple();

    int desde=opcion-1, hasta=opcion-1;
    if(opcion==OPCION_TODOS){
        desde=0;
        hasta=CANTIDAD_ARCHIVOS-1;
    }

    char ruta[50];
    for(int i=desde;i<=hasta;i++){
        armarRutaBackup(ruta, i);
        if(!existeArchivo(vArchivos[i])){
            cout<<vNombres[i]<<": todavia no tiene datos, no se copio."<<endl;
        }
        else if(copiarArchivo(vArchivos[i], ruta)){
            cout<<vNombres[i]<<": copia realizada."<<endl;
        }
        else{
            cout<<vNombres[i]<<": ERROR al copiar (falta la carpeta backups?)."<<endl;
        }
    }
    system("pause");
}

/// ---------------------------------------------------------------
/// Restaurar
/// ---------------------------------------------------------------

void restaurarCopiaDeSeguridad(){
    titulo("RESTAURAR COPIA DE SEGURIDAD");
    mostrarListaArchivos();
    int opcion=elegirArchivo("ARCHIVO A RESTAURAR: ");
    if(opcion==0){
        return;
    }

    int desde=opcion-1, hasta=opcion-1;
    if(opcion==OPCION_TODOS){
        desde=0;
        hasta=CANTIDAD_ARCHIVOS-1;
    }

    /// Antes de pedir el codigo se controla que haya algo para restaurar
    char ruta[50];
    int conCopia=0;
    for(int i=desde;i<=hasta;i++){
        armarRutaBackup(ruta, i);
        if(existeArchivo(ruta)){
            conCopia++;
        }
    }
    if(conCopia==0){
        cout<<"No hay ninguna copia de seguridad para restaurar."<<endl;
        system("pause");
        return;
    }

    cout<<"ATENCION: se van a reemplazar los datos actuales."<<endl;
    int codigo=rand()%90000+10000;
    cout<<"PARA CONTINUAR INGRESE EL CODIGO: "<<codigo<<endl;
    int ingresado=leerEntero("CODIGO DE CONFIRMACION: ");
    if(ingresado!=codigo){
        cout<<"Codigo incorrecto. No se restauro nada."<<endl;
        system("pause");
        return;
    }

    lineaSimple();
    for(int i=desde;i<=hasta;i++){
        armarRutaBackup(ruta, i);
        if(!existeArchivo(ruta)){
            cout<<vNombres[i]<<": no tiene copia, se dejo como estaba."<<endl;
        }
        else if(copiarArchivo(ruta, vArchivos[i])){
            cout<<vNombres[i]<<": restaurado."<<endl;
        }
        else{
            cout<<vNombres[i]<<": ERROR al restaurar."<<endl;
        }
    }
    system("pause");
}

/// ---------------------------------------------------------------
/// Exportar a CSV (separado por ; para que Excel lo abra en columnas)
/// ---------------------------------------------------------------

void escribirTexto(FILE *p, const char *texto){
    fwrite(texto, strlen(texto), 1, p);
}

/// Escribe el texto entre comillas (por si tiene un ;). Si el texto
/// tiene comillas, se escriben dobles, como pide el formato CSV.
void escribirCampoTexto(FILE *p, const char *texto){
    char comilla='"';
    fwrite(&comilla, sizeof comilla, 1, p);
    for(int i=0;texto[i]!='\0';i++){
        fwrite(&texto[i], sizeof(char), 1, p);
        if(texto[i]=='"'){
            fwrite(&comilla, sizeof comilla, 1, p);
        }
    }
    fwrite(&comilla, sizeof comilla, 1, p);
}

/// Escribe un entero como texto, digito por digito
void escribirEntero(FILE *p, int numero){
    char digitos[12];
    int cantidad=0;
    if(numero<0){
        escribirTexto(p, "-");
        numero=-numero;
    }
    do{
        digitos[cantidad]='0'+numero%10;
        numero=numero/10;
        cantidad++;
    }while(numero>0);
    for(int i=cantidad-1;i>=0;i--){
        fwrite(&digitos[i], sizeof(char), 1, p);
    }
}

/// Escribe un numero positivo con un decimal y coma (8,5) como usa Excel
void escribirDecimal(FILE *p, float numero){
    int decimas=(int)(numero*10+0.5);
    escribirEntero(p, decimas/10);
    escribirTexto(p, ",");
    escribirEntero(p, decimas%10);
}

bool exportarPeliculas(){
    FILE *p=fopen("Peliculas.csv", "w");
    if(p==NULL){
        return false;
    }

    ArchivoDirectores archivoDirectores;
    int cantidadDirectores=archivoDirectores.CantidadRegistros();
    Director *vDirectores=new Director[cantidadDirectores];
    if(vDirectores==NULL){
        fclose(p);
        return false;
    }
    for(int i=0;i<cantidadDirectores;i++){
        vDirectores[i]=archivoDirectores.Leer(i);
    }

    escribirTexto(p, "idPelicula;titulo;idDirector;director;duracionMinutos;calificacion;descripcion;eliminado\n");
    ArchivoPeliculas archivo;
    int cantidadRegistros=archivo.CantidadRegistros();
    for(int i=0;i<cantidadRegistros;i++){
        Pelicula reg=archivo.Leer(i);
        int posDirector=reg.getIdDirector()-1;
        char director[62];
        strcpy(director, vDirectores[posDirector].getApellido());
        strcat(director, ", ");
        strcat(director, vDirectores[posDirector].getNombre());
        escribirEntero(p, reg.getIdPelicula());
        escribirTexto(p, ";");
        escribirCampoTexto(p, reg.getTitulo());
        escribirTexto(p, ";");
        escribirEntero(p, reg.getIdDirector());
        escribirTexto(p, ";");
        escribirCampoTexto(p, director);
        escribirTexto(p, ";");
        escribirEntero(p, reg.getDuracionMinutos());
        escribirTexto(p, ";");
        escribirDecimal(p, reg.getCalificacion());
        escribirTexto(p, ";");
        escribirCampoTexto(p, reg.getDescripcion());
        escribirTexto(p, ";");
        if(reg.getEliminado()){
            escribirTexto(p, "SI\n");
        }
        else{
            escribirTexto(p, "NO\n");
        }
    }

    delete []vDirectores;
    fclose(p);
    return true;
}

bool exportarDirectores(){
    FILE *p=fopen("Directores.csv", "w");
    if(p==NULL){
        return false;
    }
    escribirTexto(p, "idDirector;nombre;apellido;nacionalidad;eliminado\n");
    ArchivoDirectores archivo;
    int cantidadRegistros=archivo.CantidadRegistros();
    for(int i=0;i<cantidadRegistros;i++){
        Director reg=archivo.Leer(i);
        escribirEntero(p, reg.getIdDirector());
        escribirTexto(p, ";");
        escribirCampoTexto(p, reg.getNombre());
        escribirTexto(p, ";");
        escribirCampoTexto(p, reg.getApellido());
        escribirTexto(p, ";");
        escribirCampoTexto(p, reg.getNacionalidad());
        escribirTexto(p, ";");
        if(reg.getEliminado()){
            escribirTexto(p, "SI\n");
        }
        else{
            escribirTexto(p, "NO\n");
        }
    }
    fclose(p);
    return true;
}

bool exportarGeneros(){
    FILE *p=fopen("Generos.csv", "w");
    if(p==NULL){
        return false;
    }
    escribirTexto(p, "idGenero;nombre;eliminado\n");
    ArchivoGeneros archivo;
    int cantidadRegistros=archivo.CantidadRegistros();
    for(int i=0;i<cantidadRegistros;i++){
        Genero reg=archivo.Leer(i);
        escribirEntero(p, reg.getIdGenero());
        escribirTexto(p, ";");
        escribirCampoTexto(p, reg.getNombre());
        escribirTexto(p, ";");
        if(reg.getEliminado()){
            escribirTexto(p, "SI\n");
        }
        else{
            escribirTexto(p, "NO\n");
        }
    }
    fclose(p);
    return true;
}

bool exportarPeliculasxGenero(){
    FILE *p=fopen("PeliculasxGenero.csv", "w");
    if(p==NULL){
        return false;
    }
    escribirTexto(p, "idGenero;idPelicula;estado\n");
    ArchivoPeliculasxGenero archivo;
    int cantidadRegistros=archivo.CantidadRegistros();
    for(int i=0;i<cantidadRegistros;i++){
        PeliculaxGenero reg=archivo.Leer(i);
        escribirEntero(p, reg.getIdGenero());
        escribirTexto(p, ";");
        escribirEntero(p, reg.getIdPelicula());
        escribirTexto(p, ";");
        if(reg.getEstado()){
            escribirTexto(p, "ACTIVA\n");
        }
        else{
            escribirTexto(p, "BAJA\n");
        }
    }
    fclose(p);
    return true;
}

void exportarDatosCsv(){
    titulo("EXPORTAR DATOS A CSV");
    mostrarListaArchivos();
    int opcion=elegirArchivo("ARCHIVO A EXPORTAR: ");
    if(opcion==0){
        return;
    }
    lineaSimple();

    int desde=opcion-1, hasta=opcion-1;
    if(opcion==OPCION_TODOS){
        desde=0;
        hasta=CANTIDAD_ARCHIVOS-1;
    }

    for(int i=desde;i<=hasta;i++){
        bool ok=false;
        switch(i){
            case 0: ok=exportarPeliculas(); break;
            case 1: ok=exportarDirectores(); break;
            case 2: ok=exportarGeneros(); break;
            case 3: ok=exportarPeliculasxGenero(); break;
            /// *** BLOQUES 2 Y 3 ***
            /// Agregar aca la exportacion de Precios (4), Salas (5),
            /// Funciones (6) y Ventas (7), con el modelo de las de arriba.
        }
        if(i>=4){
            cout<<vNombres[i]<<": esta exportacion la agrega el bloque ";
            if(i==7){
                cout<<"3."<<endl;
            }
            else{
                cout<<"2."<<endl;
            }
        }
        else if(ok){
            cout<<vNombres[i]<<": exportado."<<endl;
        }
        else{
            cout<<vNombres[i]<<": ERROR al exportar."<<endl;
        }
    }
    system("pause");
}
