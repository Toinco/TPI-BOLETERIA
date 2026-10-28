#ifndef MENUCONFIGURACION_H_INCLUDED
#define MENUCONFIGURACION_H_INCLUDED

#include <cstdio>

/// Opcion 11 del menu principal: copias de seguridad (carpeta backups),
/// restaurar con codigo de confirmacion y exportar a CSV.
void menuConfiguracion();

void realizarCopiaDeSeguridad();
void restaurarCopiaDeSeguridad();
void exportarDatosCsv();

bool existeArchivo(const char *nombre);
bool copiarArchivo(const char *origen, const char *destino);
void armarRutaBackup(char *ruta, int indice);
void mostrarListaArchivos();
int elegirArchivo(const char *mensaje);

/// Escritura de texto en el CSV
void escribirTexto(FILE *p, const char *texto);
void escribirCampoTexto(FILE *p, const char *texto);
void escribirEntero(FILE *p, int numero);
void escribirDecimal(FILE *p, float numero);

bool exportarPeliculas();
bool exportarDirectores();
bool exportarGeneros();
bool exportarPeliculasxGenero();

#endif // MENUCONFIGURACION_H_INCLUDED
