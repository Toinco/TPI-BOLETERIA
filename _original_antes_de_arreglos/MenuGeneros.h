#ifndef MENUGENEROS_H_INCLUDED
#define MENUGENEROS_H_INCLUDED

/// Opcion 3 del menu principal: ABM de generos.
void menuGeneros();

void altaGenero();
void bajaGenero();
void modificarGenero();
void verGeneros();
bool nombreGeneroRepetido(const char *nombre, int idExcluir);

#endif // MENUGENEROS_H_INCLUDED
