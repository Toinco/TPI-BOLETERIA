#ifndef VALIDACIONES_H_INCLUDED
#define VALIDACIONES_H_INCLUDED

/// Existe en el archivo y no esta dado de baja
bool existeDirectorActivo(int idDirector);
bool existePeliculaActiva(int idPelicula);
bool existeGeneroActivo(int idGenero);

int contarDirectoresActivos();
int contarPeliculasActivas();
int contarGenerosActivos();

/// Listas cortas (id y nombre) para que el usuario elija
void listarDirectoresParaElegir();
void listarPeliculasParaElegir();
void listarGenerosParaElegir();

/// Piden un id hasta que se ingrese uno que exista y este activo.
/// Antes de llamarlas hay que controlar que haya al menos uno activo.
int pedirIdDirectorActivo();
int pedirIdPeliculaActiva();
int pedirIdGeneroActivo();

/// Muestran el nombre a partir del id
void mostrarNombreDirector(int idDirector);
void mostrarTituloPelicula(int idPelicula);
void mostrarNombreGenero(int idGenero);

/// Integridad para las bajas
bool directorTienePeliculasActivas(int idDirector);
bool generoTienePeliculasActivas(int idGenero);
bool peliculaTieneFuncionesFuturas(int idPelicula);   /// la completa el bloque 2

#endif // VALIDACIONES_H_INCLUDED
