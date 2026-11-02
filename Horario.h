#ifndef HORARIO_H_INCLUDED
#define HORARIO_H_INCLUDED

class Horario{
    private:
        int hora;
    int minuto;

    public:
        Horario();

          int getHora();
        int getMinuto();

        void setHora(int h);
        void setMinuto(int m);

        void cargar();
        void mostrar();


          int aMinutos();
};





#endif // HORARIO_H_INCLUDED
