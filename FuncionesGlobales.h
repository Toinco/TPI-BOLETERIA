#ifndef FUNCIONESGLOBALES_H_INCLUDED
#define FUNCIONESGLOBALES_H_INCLUDED

/// Carga una cadena con espacios (la funcion de los apuntes de la catedra).
/// tam es la cantidad maxima de letras: el vector tiene que medir tam+1.
void cargarCadena(char *pal, int tam);

/// Pide un texto que no puede quedar vacio.
void cargarTextoObligatorio(const char *mensaje, char *texto, int tam);

/// Piden un numero hasta que se ingrese uno valido
/// (si se escriben letras no se cuelga: se vuelve a pedir).
int leerEntero(const char *mensaje);
float leerFloat(const char *mensaje);

/// Pregunta S/N y devuelve true si se respondio S.
bool confirmar(const char *mensaje);

/// Texto
void pasarAMayusculas(char *cad);
int compararSinMayusculas(const char *cad1, const char *cad2);

/// Vectores
void ponerCeroVector(int *v, int tam);

/// Pantalla
void lineaDoble();
void lineaSimple();
void titulo(const char *texto);

#endif // FUNCIONESGLOBALES_H_INCLUDED
