#ifndef SALA_H_INCLUDED
#define SALA_H_INCLUDED

class Sala{

private:
    int idSala;
    char nombre [20];
    int capacidad;
    int tipo;
    bool eliminado;


public:
    Sala();

int getIdSala();
    const char* getNombre();
    int getCapacidad();
    int getTipo();
    bool getEliminado();


void setIdSala(int id);
    void setNombre(const char* n);
    void setCapacidad(int c);
    void setTipo(int t);
    void setEliminado(bool e);

void cargar();
    void mostrar();


};

#endif // SALA_H_INCLUDED
