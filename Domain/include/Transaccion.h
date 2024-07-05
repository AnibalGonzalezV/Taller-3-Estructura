#pragma once

#include <string>
using namespace std;

class Transaccion {
private:
    int id;
    string cuentaOrigen;
    string cuentaDestino;
    double monto;
    string ubicacion;
    string fecha;
    string hora;

public:
    Transaccion(int id, string origen, string destino, double monto, string ubicacion, string fecha, string hora);
    int getId();
    string getCuentaOrigen();
    string getCuentaDestino();
    double getMonto();
    string getUbicacion();
    string getFecha();
    string getHora();
};
