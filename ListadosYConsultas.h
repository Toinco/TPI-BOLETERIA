#ifndef LISTADOSYCONSULTAS_H_INCLUDED
#define LISTADOSYCONSULTAS_H_INCLUDED

#include "Pelicula.h"
#include "Director.h"

/// Listados
void listadoPeliculasPorTitulo();
void listadoPeliculasPorCalificacion();
void listadoDirectoresPorApellido();

/// Consultas
void consultaPeliculasPorTitulo();
void consultaPeliculasPorGenero();
void consultaPeliculasPorDuracion();
void consultaDirectorPorId();
void consultaDirectoresPorApellido();

/// Informe (filtro): peliculas de un director ordenadas por calificacion.
/// Tambien es la consulta "peliculas por director".
void peliculasDeUnDirector();

/// Funciones auxiliares
void copiarPeliculasActivas(Pelicula *v);
void copiarDirectoresActivos(Director *v);
void copiarTodosLosDirectores(Director *v);
void ordenarPeliculasPorTitulo(Pelicula *v, int tam);
void ordenarPeliculasPorCalificacion(Pelicula *v, int tam);
void ordenarDirectoresPorApellido(Director *v, int tam);
void mostrarFilaPelicula(Pelicula reg, Director *vDirectores);
void mostrarPeliculasConDirector(Pelicula *v, int tam);

#endif // LISTADOSYCONSULTAS_H_INCLUDED
