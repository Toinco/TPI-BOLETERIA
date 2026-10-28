#ifndef GENERO_H_INCLUDED
#define GENERO_H_INCLUDED

/// Se guarda en Generos.dat
class Genero{
    private:
        int idGenero;
        char nombre[30];
        bool eliminado;

    public:
        Genero();

        int getIdGenero();
        const char *getNombre();
        bool getEliminado();

        void setIdGenero(int id);
        void setNombre(const char *n);
        void setEliminado(bool e);

        void cargar();
        void mostrar();
};

#endif // GENERO_H_INCLUDED
