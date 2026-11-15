#ifndef MENUPELICULAS_H_INCLUDED
#define MENUPELICULAS_H_INCLUDED

/// Opcion 1 del menu principal: ABM de peliculas y de sus generos.
void menuPeliculas();

void altaPelicula();
void bajaPelicula();
void modificarPelicula();

void agregarGeneroAPelicula();
void quitarGeneroDePelicula();
void cambiarGeneroDePelicula();
void verGenerosDePelicula();

int mostrarGenerosDePelicula(int idPelicula);
void guardarGeneroDePelicula(int idPelicula, int idGenero);

#endif // MENUPELICULAS_H_INCLUDED
