//#include "Banco.h"
#include "../include/Banco.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

Banco::Banco() {
    cargarReglasFraude();
    cargarTransacciones();
}

void Banco::cargarReglasFraude() {
    //Reglas para detectar el Fraude
    Transaccion* regla1 = new Transaccion(1000000, "regla", "monto", 100000, "", "", "");
    Transaccion* regla2 = new Transaccion(1000001, "regla", "ubicacion", 0, "Desconocida", "", "");
    arbolDecisionFraude.insertar(regla1);
    arbolDecisionFraude.insertar(regla2);
}

void Banco::evaluarReglasFraude(Transaccion* transaccion) {
    bool esSospechosa = false;
    string razon;

    if (transaccion->getMonto() > 100000) {
        razon += "Monto mayor a 100.000; ";
        esSospechosa = true;
    }

    if (transaccion->getUbicacion() == "Desconocida") {
        razon += "Ubicación desconocida; ";
        esSospechosa = true;
    }

    string cuenta = transaccion->getCuentaOrigen();
    string fecha = transaccion->getFecha();

    vector<Transaccion*> transaccionesRecientes = arbolTransacciones.encontrarTodos(cuenta, fecha);

    if (transaccionesRecientes.size() > 3) {
        razon += "Frecuencia alta de Transaccion (maximo 3 por dia); ";
        esSospechosa = true;
    }

    for (Transaccion* trans : transaccionesRecientes) {
        if (trans->getCuentaOrigen() == cuenta && trans->getUbicacion() != transaccion->getUbicacion()) {
            razon += "Ubicaciones geográficas diferentes en corto tiempo; ";
            esSospechosa = true;
            break;
        }
    }

    if (esSospechosa) {
        transaccionesSospechosas.push_back({transaccion, razon});
    }
}

void Banco::cargarTransacciones() {
    ifstream archivo("Data/transacciones.txt");
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string id, origen, destino, monto, ubicacion, fecha, hora;
        getline(ss, id, ',');
        getline(ss, origen, ',');
        getline(ss, destino, ',');
        getline(ss, monto, ',');
        getline(ss, ubicacion, ',');
        getline(ss, fecha, ',');
        getline(ss, hora, ',');

        Transaccion* trans = new Transaccion(stoi(id), origen, destino, stod(monto), ubicacion, fecha, hora);
        arbolTransacciones.insertar(trans);
        evaluarReglasFraude(trans);
    }
    archivo.close();
}

void Banco::guardarTransaccion(Transaccion* transaccion) {
    ofstream archivo("Data/transacciones.txt", ios::app);
    archivo << transaccion->getId() << "," << transaccion->getCuentaOrigen() << ","
            << transaccion->getCuentaDestino() << "," << transaccion->getMonto() << ","
            << transaccion->getUbicacion() << "," << transaccion->getFecha() << ","
            << transaccion->getHora() << endl;
    archivo.close();
}

void Banco::reportarTransaccionesSospechosas() {
    ofstream archivo("Data/transacciones_sospechosas.txt");

    cout << "Las Reglas para Transacciones sospechosas son: (Montos sobre 100.000, nombre de ubicacion 'Desconocida', "
         << "frecuencia alta de transacciones en el mismo día (Max. 3 transacciones al dia), y ubicaciones geográficas diferentes en corto tiempo).\n";

    for (const auto& par : transaccionesSospechosas) {
        Transaccion* trans = par.first;
        const string& razon = par.second;

        archivo << "ID: " << trans->getId() << ", Origen: " << trans->getCuentaOrigen()
                << ", Destino: " << trans->getCuentaDestino() << ", Monto: " << trans->getMonto()
                << ", Ubicacion: " << trans->getUbicacion() << ", Fecha: " << trans->getFecha()
                << ", Hora: " << trans->getHora() << ", Razón: " << razon << endl;

        cout << "ID: " << trans->getId() << ", Origen: " << trans->getCuentaOrigen()
             << ", Destino: " << trans->getCuentaDestino() << ", Monto: " << trans->getMonto()
             << ", Ubicacion: " << trans->getUbicacion() << ", Fecha: " << trans->getFecha()
             << ", Hora: " << trans->getHora() << ", Razón: " << razon << endl;
    }
    archivo.close();
}

void Banco::registrarTransaccion(int id, string origen, string destino, double monto, string ubicacion, string fecha, string hora) {
    Transaccion* trans = new Transaccion(id, origen, destino, monto, ubicacion, fecha, hora);
    arbolTransacciones.insertar(trans);
    guardarTransaccion(trans);
    evaluarReglasFraude(trans);
}

Transaccion* Banco::buscarTransaccion(int id) {
    return arbolTransacciones.buscar(id);
}

void Banco::generarReporte() {
    reportarTransaccionesSospechosas();
}
