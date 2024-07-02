#include "Banco.h"

void Banco::cargarReglasFraude() {
    // Reglas de fraude actualizadas:
    Transaccion* regla1 = new Transaccion(1000000, "regla", "monto", 150000, "", "", "");
    Transaccion* regla2 = new Transaccion(1000001, "regla", "ubicacion", 0, "Desconocida", "", "");
    arbolDecisionFraude.insertar(regla1);
    arbolDecisionFraude.insertar(regla2);
}


void Banco::evaluarReglasFraude(Transaccion* transaccion) {
    if (transaccion->getMonto() > 150000) {
        transaccionesSospechosas.push_back(transaccion);
    }
    if (transaccion->getUbicacion() == "Desconocida") {
        transaccionesSospechosas.push_back(transaccion);
    }
}


void Banco::cargarTransacciones() {
    ifstream archivo("transacciones.txt");
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
    ofstream archivo("transacciones.txt", ios::app);
    archivo << transaccion->getId() << "," << transaccion->getCuentaOrigen() << ","
            << transaccion->getCuentaDestino() << "," << transaccion->getMonto() << ","
            << transaccion->getUbicacion() << "," << transaccion->getFecha() << ","
            << transaccion->getHora() << endl;
    archivo.close();
}

void Banco::reportarTransaccionesSospechosas() {
    ofstream archivo("transacciones_sospechosas.txt");

    for (auto trans : transaccionesSospechosas) {
        archivo << "ID: " << trans->getId() << ", Origen: " << trans->getCuentaOrigen()
                << ", Destino: " << trans->getCuentaDestino() << ", Monto: " << trans->getMonto()
                << ", Ubicacion: " << trans->getUbicacion() << ", Fecha: " << trans->getFecha()
                << ", Hora: " << trans->getHora() << endl;
    }
    archivo.close();
}

Banco::Banco() {
    cargarReglasFraude();
    cargarTransacciones();
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
    cout << "Transacciones Sospechosas por ubicacion ('Desconocida') o monto sobre el minimo (Sobre 150000):\n";
    for (auto trans : transaccionesSospechosas) {
        cout << "ID: " << trans->getId() << ", Origen: " << trans->getCuentaOrigen()
             << ", Destino: " << trans->getCuentaDestino() << ", Monto: " << trans->getMonto()
             << ", Ubicacion: " << trans->getUbicacion() << ", Fecha: " << trans->getFecha()
             << ", Hora: " << trans->getHora() << endl;
    }
    reportarTransaccionesSospechosas();
}
