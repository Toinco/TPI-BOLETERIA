#include <iostream>
#ifndef VENTA_H_INCLUDED
#define VENTA_H_INCLUDED                            
#include "Fecha.h"
using namespace std;

class venta {
    private:
        int idVenta;
        int idFuncion;
        Fecha fecha;
        int cantidad;
        float precioUnitario;
        int formaPago;
        bool eliminado;

    public:
        venta();
        venta(int idVenta, int idFuncion, int cantidad, float precioUnitario, int formaPago);
        void setIdVenta(int id);
        void setIdFuncion(int id);
        void setFecha(Fecha f);
        void setCantidad(int c);
        void setPrecioUnitario(float p);
        void setFormaPago(int fp);
        void setEliminado(bool e);

        int getIdVenta();
        int getIdFuncion();
        Fecha getFecha();
        int getCantidad();
        float getPrecioUnitario();
        int getFormaPago();
        float getImporte();
        bool getEliminado();

        void cargar();
        void mostrar();
};



#endif // VENTA_H_INCLUDED