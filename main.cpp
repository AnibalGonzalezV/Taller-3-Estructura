#include "Banco.h"

using namespace std;

void menu() {
    Banco banco;
    int opcion, id;
    string origen, destino, ubicacion, fecha, hora;
    double monto;
    Transaccion* trans = nullptr; // Declaración fuera del switch

    while (true) {
        cout << "1. Registrar Transaccion\n2. Buscar Transaccion\n3. Generar Reporte\n4. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese ID: "; cin >> id;
                cout << "Ingrese Cuenta Origen: "; cin >> origen;
                cout << "Ingrese Cuenta Destino: "; cin >> destino;
                cout << "Ingrese Monto: "; cin >> monto;
                cout << "Ingrese Ubicacion: "; cin >> ubicacion;
                cout << "Ingrese Fecha: "; cin >> fecha;
                cout << "Ingrese Hora: "; cin >> hora;
                banco.registrarTransaccion(id, origen, destino, monto, ubicacion, fecha, hora);
                break;
            case 2:
                cout << "Ingrese ID: "; cin >> id;
                trans = banco.buscarTransaccion(id); // Asignación dentro del case
                if (trans) {
                    cout << "ID: " << trans->getId() << ", Origen: " << trans->getCuentaOrigen()
                         << ", Destino: " << trans->getCuentaDestino() << ", Monto: " << trans->getMonto()
                         << ", Ubicacion: " << trans->getUbicacion() << ", Fecha: " << trans->getFecha()
                         << ", Hora: " << trans->getHora() << endl;
                } else {
                    cout << "Transaccion no encontrada." << endl;
                }
                break;
            case 3:
                banco.generarReporte();
                break;
            case 4:
                cout << "Saliendo del sistema..." << endl;
                return;
            default:
                cout << "Opcion no valida, por favor intente nuevamente." << endl;
        }
    }
}

int main() {
    menu();
    return 0;
}
