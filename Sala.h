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
    int getTipo(); /// 1 - IMAX, 2 - 3D, 3 - 2D, 4 - 4D
    bool getEliminado(); /// false = activa, true = dada de baja


void setIdSala(int id);
    void setNombre(const char* n);
    void setCapacidad(int c);
    void setTipo(int t);
    void setEliminado(bool e);

void cargar();
    void mostrar();


};

#endif // SALA_H_INCLUDED
