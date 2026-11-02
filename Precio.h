#ifndef PRECIO_H_INCLUDED
#define PRECIO_H_INCLUDED

class Precio{

private:
    int idTipo;
    char nombre[10];
    float precio;

public:
      Precio();

    int getIdTipo();
    const char *getNombre();
    float getPrecio();

    void setIdTipo(int id);
    void setNombre(const char *n);
    void setPrecio(float p);

 void mostrar();
};

#endif // PRECIO_H_INCLUDED
