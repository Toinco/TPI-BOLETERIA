#ifndef PELICULA_H_INCLUDED
#define PELICULA_H_INCLUDED

/// Se guarda en Peliculas.dat
class Pelicula{
    private:
        int idPelicula;
        char titulo[50];
        int idDirector;
        int duracionMinutos;
        float calificacion;
        char descripcion[200];
        bool eliminado;

    public:
        Pelicula();

        int getIdPelicula();
        const char *getTitulo();
        int getIdDirector();
        int getDuracionMinutos();
        float getCalificacion();
        const char *getDescripcion();
        bool getEliminado();

        void setIdPelicula(int id);
        void setTitulo(const char *t);
        void setIdDirector(int id);
        void setDuracionMinutos(int minutos);
        void setCalificacion(float c);
        void setDescripcion(const char *d);
        void setEliminado(bool e);

        void cargar();
        void mostrar();
};

#endif // PELICULA_H_INCLUDED
