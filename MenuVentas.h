#ifndef MENUVENTAS_H_INCLUDED
#define MENUVENTAS_H_INCLUDED

#include "Fecha.h"

/// Opcion 7 del menu principal y salidas del bloque 3
Fecha fechaActual();
void altaVenta();
void anularVenta();
void menuVentas();

/// Listados y consultas de ventas
void ventasOrdenadasPorFecha();
void ventasPorNumero();
void ventasPorRangoDeFechas();
void ventasPorFormaPago();

/// Informes
void recaudacionAnual();
void recaudacionPorPelicula();
void recaudacionPorFormaPago();
void entradasPorTipoDeSala();
void ocupacionPorSala();

void pedirPeriodo(Fecha &desde, Fecha &hasta);

#endif // MENUVENTAS_H_INCLUDED
