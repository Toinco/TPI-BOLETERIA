#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

class Fecha{
    private:
        int dia;
        int mes;
        int anio;
        int diasDelMes(int m, int a);

    public:
        Fecha();

        int getDia();
        int getMes();
        int getAnio();
///---
        void setDia(int d);
        void setMes(int m);
        void setAnio(int a);
///---
        void cargar();
        void mostrar();
/// Esto es para comparar los años, lo explico en fecha cpp
        int aNumero();
};









#endif // FECHA_H_INCLUDED
