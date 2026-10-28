#ifndef DIRECTOR_H_INCLUDED
#define DIRECTOR_H_INCLUDED

/// Se guarda en Directores.dat
class Director{
    private:
        int idDirector;
        char nombre[30];
        char apellido[30];
        char nacionalidad[30];
        bool eliminado;

    public:
        Director();

        int getIdDirector();
        const char *getNombre();
        const char *getApellido();
        const char *getNacionalidad();
        bool getEliminado();

        void setIdDirector(int id);
        void setNombre(const char *n);
        void setApellido(const char *a);
        void setNacionalidad(const char *n);
        void setEliminado(bool e);

        void cargar();
        void mostrar();
};

#endif // DIRECTOR_H_INCLUDED
