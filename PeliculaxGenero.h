#ifndef PELICULAXGENERO_H_INCLUDED
#define PELICULAXGENERO_H_INCLUDED

/// Se guarda en PeliculasxGenero.dat
/// Une una pelicula con un genero (relacion muchos a muchos).
/// estado true: la relacion esta activa. false: fue dada de baja.
class PeliculaxGenero{
    private:
        int idGenero;
        int idPelicula;
        bool estado;

    public:
        PeliculaxGenero();

        int getIdGenero();
        int getIdPelicula();
        bool getEstado();

        void setIdGenero(int id);
        void setIdPelicula(int id);
        void setEstado(bool e);

        void cargar();
        void mostrar();
};

#endif // PELICULAXGENERO_H_INCLUDED
