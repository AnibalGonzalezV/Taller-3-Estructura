#include "Transaccion.h"

Transaccion::Transaccion(int id, string origen, string destino, double monto, string ubicacion, string fecha, string hora)
    : id(id), cuentaOrigen(origen), cuentaDestino(destino), monto(monto), ubicacion(ubicacion), fecha(fecha), hora(hora) {}

int Transaccion::getId() {
    return id;
}

string Transaccion::getCuentaOrigen() {
    return cuentaOrigen;
}

string Transaccion::getCuentaDestino() {
    return cuentaDestino;
}

double Transaccion::getMonto() {
    return monto;
}

string Transaccion::getUbicacion() {
    return ubicacion;
}

string Transaccion::getFecha() {
    return fecha;
}

string Transaccion::getHora() {
    return hora;
}
