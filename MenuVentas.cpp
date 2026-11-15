#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#include "MenuVentas.h"
#include "Venta.h"
#include "ArchivoVentas.h"
#include "ArchivoFunciones.h"
#include "ArchivoSalas.h"
#include "Fecha.h"
#include "FuncionesGlobales.h"
#include "Validaciones.h"
#include "ArchivoDirectores.h"
#include "ArchivoPeliculas.h"
#include "Pelicula.h"
#include "Director.h"


const char *nombreFormaPago(int fp){
    switch(fp){
        case 1: return "EFECTIVO";
        case 2: return "DEBITO";
        case 3: return "CREDITO";
        case 4: return "TRANSFERENCIA";
    }
    return "?";
}

const char *nombreFormato(int tipo){
    switch(tipo){
        case 1: return "IMAX";
        case 2: return "3D";
        case 3: return "2D";
        case 4: return "4D";
    }
    return "?";
}


void menuVentas(){
    int opcion = -1;
    while(opcion!=0){
        titulo("VENTAS");
        cout<<"  1 - NUEVA VENTA"<<endl;
        cout<<"  2 - ANULAR VENTA"<<endl;
        lineaSimple();
        cout<<"  0 - VOLVER"<<endl;
        lineaDoble();
        opcion=leerEntero("OPCION: ");

        switch(opcion){
            case 1: altaVenta(); break;
            case 2: anularVenta(); break;
            case 0: break;
            default:
                cout<<"Opcion incorrecta."<<endl;
                system("pause");
                break;
        }
    }
}
void mostrarComprobante(venta reg){
    ArchivoFunciones archF;
    int posF = archF.Buscar(reg.getIdFuncion());

    lineaDoble();
    cout<<"  COMPROBANTE DE VENTA N "<<reg.getIdVenta()<<endl;
    lineaDoble();
    if(posF!=-1){
        Funcion f = archF.Leer(posF);
        cout<<"  Pelicula: ";
        mostrarTituloPelicula(f.getIdPelicula());
        cout<<endl;

        ArchivoSalas archS;
        int posS = archS.Buscar(f.getIdSala());
        if(posS!=-1){
            Sala s = archS.Leer(posS);
            cout<<"  Sala:     "<<s.getNombre()<<" ("<<nombreFormato(s.getTipo())<<")"<<endl;
        }
        cout<<"  Funcion:  ";
        f.getFecha().mostrar();
        cout<<" ";
        f.getHorario().mostrar();
        cout<<endl;
    }
    cout<<"  ENTRADAS: "<<reg.getCantidad()<<endl;
    cout<<"  PRECIO:   $"<<(int)(reg.getPrecioUnitario() + 0.5f)<<endl;
    cout<<"  TOTAL:    $"<<(int)(reg.getImporte() + 0.5f)<<endl;
    cout<<"  FORMA DE PAGO :     "<<nombreFormaPago(reg.getFormaPago())<<endl;
    cout<<"  Fecha de venta: ";
    reg.getFecha().mostrar();
    cout<<endl;
    cout<<"  Estado:   "<<(reg.getEliminado() ? "ANULADA" : "VIGENTE")<<endl;
    lineaDoble();
}


void recaudacionAnual(){
    titulo("RECAUDACION ANUAL");
    int anio = leerEntero("INGRESE ANIO: ");
    while(anio<1900 || anio>2100){
        cout<<"  Anio invalido."<<endl;
        anio = leerEntero("ANIO: ");
    }

    archivoVentas archV;
    int cant = archV.cantidadRegistros();
    float total = 0;
    float meses[12] = {0};
    const char *mesesTexto[12] = {"ENERO", "FEBRERO", "MARZO", "ABRIL", "MAYO", "JUNIO", "JULIO", "AGOSTO", "SEPTIEMBRE", "OCTUBRE", "NOVIEMBRE", "DICIEMBRE"};

    for(int i=0;i<cant;i++){
        venta v = archV.leer(i);
        if(!v.getEliminado() && v.getFecha().getAnio()==anio){
            total += v.getImporte();
            meses[v.getFecha().getMes() - 1] += v.getImporte();
        }
    }

    cout<<"MES                    RECAUDACION"<<endl;
    for(int i=0;i<12;i++){
        cout<<mesesTexto[i];
        int largo = 0;
        while(mesesTexto[i][largo] != '\0') {
            largo++; //cuenta el largo de la letra
        }
        for(int j=largo;j<23;j++){ //hasta que llegue a 23 que es el largo de la columna imprime " "
            cout<<" ";
        }
        cout<<"$"<<(long long)(meses[i] + 0.5f)<<endl;
    }
    lineaDoble();
    cout<<"TOTAL DEL ANIO "<<anio<<":   $"<<(long long)(total + 0.5f)<<endl;
    system("pause");
}



void ventasOrdenadasPorFecha() {
    titulo("VENTAS ORDENADAS POR FECHA");
    archivoVentas archV;
    int cant = archV.cantidadRegistros();
    if (cant == 0) {
        cout << "  No hay ventas registradas." << endl;
        system("pause");
        return;
    }

  //vector que almacena las ventas sin ordenar
    venta* ventas = new venta[cant];
    for (int i = 0; i < cant; i++) {
        ventas[i] = archV.leer(i);
    }

    //Ordenamiento burbuja: de la venta mas reciente a la mas antigua
    for (int i = 0; i < cant - 1; i++) {
    for (int j = 0; j < cant - i - 1; j++) {
        Fecha fecha1 = ventas[j].getFecha();
        Fecha fecha2 = ventas[j + 1].getFecha();

        bool intercambiar = false;
        if (fecha1.getAnio() != fecha2.getAnio()) {
            intercambiar = fecha1.getAnio() < fecha2.getAnio();
        }
        else if (fecha1.getMes() != fecha2.getMes()) {
            intercambiar = fecha1.getMes() < fecha2.getMes();
        }
        else if (fecha1.getDia() != fecha2.getDia()) {
            intercambiar = fecha1.getDia() < fecha2.getDia();
        }
        else {
            // misma fecha: primero la venta con número más alto (la más nueva)
            intercambiar = ventas[j].getIdVenta() < ventas[j + 1].getIdVenta();
        }

        if (intercambiar) {
            venta temp = ventas[j];
            ventas[j] = ventas[j + 1];
            ventas[j + 1] = temp;
        }
    }
}

    // Muestro las ventas ya ordenadas
    for (int i = 0; i < cant; i++) {
        mostrarComprobante(ventas[i]);
    }

    delete[] ventas;
    system("pause");
}


void recaudacionPorFormaPago() {
    titulo("RECAUDACION POR FORMA DE PAGO");
    Fecha desde, hasta;
    pedirPeriodo(desde, hasta);
    lineaSimple();

    archivoVentas archV;
    int cant = archV.cantidadRegistros();
    float totalPorForma[4] = {0};   // 0 - Efectivo, 1 - Debito, 2 - Credito, 3 - Transferencia
    int ventasPorForma[4] = {0};
    float total = 0;
    int totalVentas = 0;
    for (int i = 0; i < cant; i++) {
        venta v = archV.leer(i);
        int n = v.getFecha().aNumero();
        int formaPago = v.getFormaPago();
        if (!v.getEliminado() && n >= desde.aNumero() && n <= hasta.aNumero() &&
            formaPago >= 1 && formaPago <= 4) {
            totalPorForma[formaPago - 1] += v.getImporte();
            ventasPorForma[formaPago - 1]++;
            total += v.getImporte();
            totalVentas++;
        }
    }

    cout << "FORMA DE PAGO     VENTAS     RECAUDACION     %" << endl;
    for (int i = 0; i < 4; i++) {
        float porcentaje = 0;
        if (total > 0) {
            porcentaje = totalPorForma[i] * 100 / total;
        }
        cout << nombreFormaPago(i + 1) << "     " << ventasPorForma[i]
             << "     $" << totalPorForma[i] << "     " << (int)(porcentaje + 0.5) << " %" << endl;
    }
    lineaDoble();
    cout << "TOTAL     VENTAS: " << totalVentas << "     $" << total << endl;
    system("pause");
}

void ventasPorNumero() {
    titulo("CONSULTA DE VENTA POR NUMERO");
    archivoVentas archV;
    if (archV.cantidadRegistros() == 0) {
        cout << "  No hay ventas registradas." << endl;
        system("pause");
        return;
    }
    int id = leerEntero("NUMERO DE VENTA: ");
    int pos = archV.buscar(id);
    if (pos == -1) {
        cout << "  No existe una venta con ese numero." << endl;
    }
    else {
        mostrarComprobante(archV.leer(pos));
    }
    system("pause");
}


void ventasPorRangoDeFechas() {
    titulo("CONSULTA DE VENTAS POR RANGO DE FECHAS");
    archivoVentas archV;
    int cant = archV.cantidadRegistros();
    if (cant == 0) {
        cout << "  No hay ventas registradas." << endl;
        system("pause");
        return;
    }

    Fecha desde, hasta;
    pedirPeriodo(desde, hasta);
    int inicioNum = desde.aNumero();
    int finalNum  = hasta.aNumero();

    int vEncontradas = 0;
    for (int i = 0; i < cant; i++) {
        venta reg = archV.leer(i);
        int n = reg.getFecha().aNumero();
        if (n >= inicioNum && n <= finalNum) {
            mostrarComprobante(reg);
            vEncontradas++;
            system("pause");
        }
    }

    if (vEncontradas == 0) {
        cout << "  No hay ventas en el rango de fechas especificado." << endl;
    }
    else {
        cout << "  VENTAS ENCONTRADAS: " << vEncontradas << endl;
    }
    system("pause");
}

void recaudacionPorPelicula() {
    titulo("RECAUDACION POR PELICULA");

    Fecha desde, hasta;
    pedirPeriodo(desde, hasta);
    int inicioNum = desde.aNumero();
    int finalNum  = hasta.aNumero();
    lineaSimple();

    ArchivoPeliculas archPel;
    int cantPeliculas = archPel.CantidadRegistros();
    if (cantPeliculas == 0) {
        cout << "  No hay peliculas cargadas." << endl;
        system("pause");
        return;
    }

    //  i es la pelicula de id i+1
    float *vecImporte = new float[cantPeliculas]{};
    int   *vecCant    = new int[cantPeliculas]{};
    int   *vecAux     = new int[cantPeliculas];

    archivoVentas archV;
    ArchivoFunciones archFunc;
    int cantVentas = archV.cantidadRegistros();
    for (int i = 0; i < cantVentas; i++) {
        venta reg = archV.leer(i);
        if (reg.getEliminado()) continue;

        int n = reg.getFecha().aNumero();
        if (n < inicioNum || n > finalNum) continue;

        int posFunc = archFunc.Buscar(reg.getIdFuncion());
        if (posFunc == -1) continue;
        Funcion func = archFunc.Leer(posFunc);

        int posPel = func.getIdPelicula() - 1;
        if (posPel < 0 || posPel >= cantPeliculas) continue;

        vecImporte[posPel] += reg.getCantidad() * reg.getPrecioUnitario();
        vecCant[posPel]    += reg.getCantidad();
    }

    // vecAux guarda las posiciones de las peliculas en alta
    int cantAlta = 0;
    for (int i = 0; i < cantPeliculas; i++) {
        Pelicula p = archPel.Leer(i);
        if (!p.getEliminado()) {
            vecAux[cantAlta] = i;
            cantAlta++;
        }
    }

    // ordeno vecAux por importe de mayor a menor
    for (int i = 0; i < cantAlta - 1; i++) {
        int mayor = i;
        for (int j = i + 1; j < cantAlta; j++) {
            if (vecImporte[vecAux[j]] > vecImporte[vecAux[mayor]]) mayor = j;
        }
        int aux = vecAux[i];
        vecAux[i] = vecAux[mayor];
        vecAux[mayor] = aux;
    }

    // 4) mostrar recorriendo vecAux
    ArchivoDirectores archDir;
    for (int k = 0; k < cantAlta; k++) {
        int pos = vecAux[k];
        // Para ocultar las peliculas sin ventas descomenten la linea de abajo:
        // if (vecCant[pos] == 0) continue;

        Pelicula p = archPel.Leer(pos);
        cout << " PUESTO " << (k + 1) << endl;
        cout << "   PELICULA: " << p.getTitulo() << endl;

        int posDir = archDir.Buscar(p.getIdDirector());
        if (posDir != -1) {
            Director d = archDir.Leer(posDir);
            cout << "   DIRECTOR: " << d.getApellido() << ", " << d.getNombre() << endl;
        }
        cout << "   ENTRADAS: " << vecCant[pos]
             << "     TOTAL: $ " << (long long)(vecImporte[pos] + 0.5f) << endl;
        lineaSimple();
    }

    delete[] vecImporte;
    delete[] vecCant;
    delete[] vecAux;
    system("pause");
}





/// Lista las funciones vigentes y pide una. Devuelve 0 si cancela o no hay.
int pedirIdFuncionVendible(){
    ArchivoFunciones archivo;
    int total = archivo.CantidadRegistros();
    bool hay = false;

    cout<<"FUNCIONES DISPONIBLES"<<endl;
    for(int i=0;i<total;i++){
        Funcion f = archivo.Leer(i);
        if(!f.getEliminado() && !funcionVencida(f)){
            cout<<"  "<<f.getIdFuncion()<<" - ";
            mostrarTituloPelicula(f.getIdPelicula());
            cout<<" | SALA "<<f.getIdSala()<<" | ";
            f.getFecha().mostrar();
            cout<<" ";
            f.getHorario().mostrar();
            cout<<" | LIBRES: "<<butacasDisponibles(f.getIdFuncion())<<endl;
            hay = true;
        }
    }
    if(!hay){
        cout<<"  No hay funciones disponibles."<<endl;
        return 0;
    }
    lineaSimple();

    while(true){
        int id = leerEntero("ID DE FUNCION (0 = CANCELAR): ");
        if(id==0) {
            return 0;
        }
        int pos = archivo.Buscar(id);
        if(pos==-1){
            cout<<"  Esa funcion no existe."<<endl;
            continue;
        }

        Funcion f = archivo.Leer(pos);
        if(f.getEliminado() || funcionVencida(f)){
            cout<<"  Esa funcion no esta disponible."<<endl;
            continue;
        }
        return id;
    }
}


void altaVenta(){
    titulo("VENTA DE ENTRADAS");
    archivoVentas archivo;
    venta reg;

    int idFuncion = pedirIdFuncionVendible();
    if(idFuncion==0){
        system("pause");
        return;
    }

    int libres = butacasDisponibles(idFuncion);
    if(libres<=0){
        cout<<"  No quedan butacas."<<endl;
        system("pause");
        return;
    }
    float precio = precioDeFuncion(idFuncion);
    if(precio<=0){
        cout<<"  No se pudo obtener el precio de la funcion."<<endl;
        system("pause");
        return;
    }

    int cantidad = leerEntero("CANTIDAD DE ENTRADAS: ");
    while(cantidad<=0 || cantidad>libres){
        cout<<"  Tiene que ser entre 1 y "<<libres<<"."<<endl;
        cantidad = leerEntero("CANTIDAD DE ENTRADAS: ");
    }

    int pago = leerEntero("FORMA DE PAGO (1-EFECTIVO 2-DEBITO 3-CREDITO 4-TRANSFERENCIA): ");
    while(pago<1 || pago>4){
        cout<<"  Forma de pago invalida."<<endl;
        pago = leerEntero("FORMA DE PAGO (1-4): ");
    }

    reg.setIdVenta(archivo.cantidadRegistros()+1);
    reg.setIdFuncion(idFuncion);
    reg.setCantidad(cantidad);
    reg.setPrecioUnitario(precio);
    reg.setFormaPago(pago);
    reg.setFecha(fechaActual());
    reg.setEliminado(false);

    mostrarComprobante(reg);
    if(confirmar("Confirmar la venta?")){
        if(archivo.guardar(reg)){
            cout<<"  VENTA REGISTRADA CON EXITO. VENTA NRO: "<<reg.getIdVenta()<<endl;
        }
        else {
            cout<<"  ERROR: no se pudo guardar la venta."<<endl;
        }
    }
    system("pause");
}

void anularVenta(){
    titulo("ANULAR VENTA");
    archivoVentas archivo;
    if(archivo.cantidadRegistros()==0){
        cout<<"  No hay ventas registradas."<<endl;
        system("pause");
        return;
    }
    int id = leerEntero("NUMERO DE VENTA (0 = CANCELAR): ");
    if(id==0) return;

    int pos = archivo.buscar(id);
    if(pos==-1){
        cout<<"  Esa venta no existe."<<endl;
        system("pause");
        return;
    }
    venta reg = archivo.leer(pos);
    if(reg.getEliminado()){
        cout<<"  Esa venta ya esta anulada."<<endl;
        system("pause");
        return;
    }
    mostrarComprobante(reg);
    if(confirmar("Anular esta venta?")){
        reg.setEliminado(true);
        archivo.guardar(reg, pos);
        cout<<"  VENTA ANULADA."<<endl;
    }
    system("pause");
}

Fecha fechaActual(){
    time_t t = time(NULL);
    tm* ahora = localtime(&t);

    Fecha f;
    f.setDia(ahora->tm_mday);
    f.setMes(ahora->tm_mon + 1);
    f.setAnio(ahora->tm_year + 1900);
    return f;
}


/// Pide el periodo de un informe o consulta. Con 0 se toma el anio actual
/// completo (del 1/1 al 31/12); con 1 se ingresan las dos fechas.
void pedirPeriodo(Fecha &desde, Fecha &hasta){
    int opcion=leerEntero("PERIODO (0 = ANIO ACTUAL, 1 = INGRESAR FECHAS): ");
    while(opcion!=0 && opcion!=1){
        cout<<"  Ingrese 0 o 1."<<endl;
        opcion=leerEntero("PERIODO (0 = ANIO ACTUAL, 1 = INGRESAR FECHAS): ");
    }
    if(opcion==0){
        int anio=fechaActual().getAnio();
        desde.setAnio(anio); desde.setMes(1);  desde.setDia(1);
        hasta.setAnio(anio); hasta.setMes(12); hasta.setDia(31);
    }
    else{
        cout<<"FECHA DESDE"<<endl;
        desde.cargar();
        cout<<"FECHA HASTA"<<endl;
        hasta.cargar();
        while(hasta.aNumero()<desde.aNumero()){
            cout<<"  La fecha HASTA no puede ser menor que la fecha DESDE."<<endl;
            hasta.cargar();
        }
    }
    cout<<"PERIODO: ";
    desde.mostrar();
    cout<<" AL ";
    hasta.mostrar();
    cout<<endl;
}

/// Consulta: ventas cobradas con una forma de pago (se muestra cada comprobante)
void ventasPorFormaPago(){
    titulo("CONSULTA DE VENTAS POR FORMA DE PAGO");
    int pago = leerEntero("FORMA DE PAGO (1-EFECTIVO 2-DEBITO 3-CREDITO 4-TRANSFERENCIA): ");
    while(pago<1 || pago>4){
        cout<<"  Forma de pago invalida."<<endl;
        pago = leerEntero("FORMA DE PAGO (1-4): ");
    }
    archivoVentas archV;
    int cant = archV.cantidadRegistros();
    int encontradas = 0;
    for(int i=0;i<cant;i++){
        venta reg = archV.leer(i);
        if(!reg.getEliminado() && reg.getFormaPago()==pago){
            mostrarComprobante(reg);
            encontradas++;
        }
    }
    if(encontradas==0){
        cout<<"  No hay ventas con esa forma de pago."<<endl;
    }
    else{
        cout<<"  VENTAS ENCONTRADAS: "<<encontradas<<endl;
    }
    system("pause");
}

/// Informe: entradas vendidas y recaudacion por tipo de sala en un periodo.
/// Como los tipos son 4 fijos, se acumula en vectores de 4 posiciones.
void entradasPorTipoDeSala(){
    titulo("ENTRADAS VENDIDAS POR TIPO DE SALA");
    Fecha desde, hasta;
    pedirPeriodo(desde, hasta);
    lineaSimple();
    int entradas[4] = {0};
    float recaudado[4] = {0};

    archivoVentas archV;
    ArchivoFunciones archF;
    ArchivoSalas archS;
    int cant = archV.cantidadRegistros();
    for(int i=0;i<cant;i++){
        venta v = archV.leer(i);
        if(v.getEliminado()) continue;
        int n = v.getFecha().aNumero();
        if(n<desde.aNumero() || n>hasta.aNumero()) continue;

        /// venta -> funcion -> sala -> tipo
        int posF = archF.Buscar(v.getIdFuncion());
        if(posF==-1) continue;
        Funcion f = archF.Leer(posF);
        int posS = archS.Buscar(f.getIdSala());
        if(posS==-1) continue;
        Sala s = archS.Leer(posS);
        int tipo = s.getTipo();
        if(tipo<1 || tipo>4) continue;

        entradas[tipo-1] += v.getCantidad();
        recaudado[tipo-1] += v.getImporte();
    }
    for(int i=0;i<4;i++){
        cout<<"TIPO: "<<nombreFormato(i+1)<<"     ENTRADAS: "<<entradas[i]
            <<"     TOTAL: $"<<recaudado[i]<<endl;
        lineaSimple();
    }
    system("pause");
}

/// Informe: por cada sala activa, funciones del periodo, butacas ofrecidas
/// (capacidad x funciones), butacas vendidas y porcentaje de ocupacion.
void ocupacionPorSala(){
    titulo("OCUPACION POR SALA");
    Fecha desde, hasta;
    pedirPeriodo(desde, hasta);
    lineaSimple();
    ArchivoSalas archS;
    ArchivoFunciones archF;
    int cantSalas = archS.CantidadRegistros();
    int cantFunc = archF.CantidadRegistros();
    int salasMostradas = 0;

    for(int i=0;i<cantSalas;i++){
        Sala s = archS.Leer(i);
        if(s.getEliminado()) continue;
        int funciones = 0, vendidas = 0;
        for(int j=0;j<cantFunc;j++){
            Funcion f = archF.Leer(j);
            int n = f.getFecha().aNumero();
            if(!f.getEliminado() && f.getIdSala()==s.getIdSala() &&
               n>=desde.aNumero() && n<=hasta.aNumero()){
                funciones++;
                vendidas += s.getCapacidad() - butacasDisponibles(f.getIdFuncion());
            }
        }
        int ofrecidas = funciones * s.getCapacidad();
        float porcentaje = 0;
        if(ofrecidas>0){
            porcentaje = vendidas*100.0/ofrecidas;
        }
        cout<<s.getNombre()<<" ("<<nombreFormato(s.getTipo())<<")"<<endl;
        cout<<"  FUNCIONES: "<<funciones<<"   BUTACAS OFRECIDAS: "<<ofrecidas<<endl;
        cout<<"  VENDIDAS: "<<vendidas<<"   OCUPACION: "<<(int)(porcentaje+0.5)<<" %"<<endl;
        lineaSimple();
        salasMostradas++;
    }
    if(salasMostradas==0){
        cout<<"No hay salas cargadas."<<endl;
    }
    system("pause");
}
