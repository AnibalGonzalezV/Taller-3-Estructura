//#include "Banco.h"
#include "../Domain/include/Banco.h"


using namespace std;

void menu() {
    Banco banco;
    int opcion, id;
    string origen, destino, ubicacion, fecha, hora;
    double monto;
    Transaccion* trans = nullptr; 

    while (true) {
        cout << "1. Registrar Transaccion\n2. Buscar Transaccion\n3. Generar Reporte\n4. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese ID (2 digitos): "; cin >> id;
                cout << "Ingrese Cuenta Origen (5 digitos): "; cin >> origen;
                cout << "Ingrese Cuenta Destino (5 digitos): "; cin >> destino;
                cout << "Ingrese Monto: "; cin >> monto;
                cout << "Ingrese Ubicacion (sin espacios): "; cin >> ubicacion;
                cout << "Ingrese Fecha (YYYY-MM-DD): "; cin >> fecha;
                cout << "Ingrese Hora (HH:MM): "; cin >> hora;
                banco.registrarTransaccion(id, origen, destino, monto, ubicacion, fecha, hora);
                break;
            case 2:
                cout << "Ingrese ID de la Transaccion que busca: "; cin >> id;
                trans = banco.buscarTransaccion(id); 
                if (trans) {
                    cout << "ID: " << trans->getId() << ", Origen: " << trans->getCuentaOrigen()
                         << ", Destino: " << trans->getCuentaDestino() << ", Monto: " << trans->getMonto()
                         << ", Ubicacion: " << trans->getUbicacion() << ", Fecha: " << trans->getFecha()
                         << ", Hora: " << trans->getHora() << endl;
                } else {
                    cout << "ID de Transaccion no encontrada." << endl;
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
    cout<<"**Bienvenido al Sistema de Gestion de Transacciones Financieras**"<<endl;
    menu();
    return 0;
}
