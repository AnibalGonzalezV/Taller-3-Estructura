#pragma once

#include "ArbolAVL.h"
#include "ArbolABB.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Banco {
private:
    ArbolAVL arbolTransacciones;
    ArbolABB arbolDecisionFraude;
    vector<pair<Transaccion*, string>> transaccionesSospechosas;

    void cargarReglasFraude();
    void evaluarReglasFraude(Transaccion* transaccion);
    void cargarTransacciones();
    void guardarTransaccion(Transaccion* transaccion);
    void reportarTransaccionesSospechosas();

public:
    Banco();
    void registrarTransaccion(int id, string origen, string destino, double monto, string ubicacion, string fecha, string hora);
    Transaccion* buscarTransaccion(int id);
    void generarReporte();
};
