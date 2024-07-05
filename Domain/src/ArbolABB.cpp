//#include "ArbolABB.h"
#include "../include/ArbolABB.h"

NodoABB::NodoABB(Transaccion* trans) : transaccion(trans), izquierdo(nullptr), derecho(nullptr) {}

ArbolABB::ArbolABB() : raiz(nullptr) {}

NodoABB* ArbolABB::insertar(NodoABB* nodo, Transaccion* trans) {
    if (nodo == nullptr) {
        return new NodoABB(trans);
    }

    if (trans->getId() < nodo->transaccion->getId()) {
        nodo->izquierdo = insertar(nodo->izquierdo, trans);
    } else if (trans->getId() > nodo->transaccion->getId()) {
        nodo->derecho = insertar(nodo->derecho, trans);
    } else {
        // No se permiten IDs duplicados en este árbol
        return nodo;
    }

    return nodo;
}

void ArbolABB::insertar(Transaccion* trans) {
    raiz = insertar(raiz, trans);
}

NodoABB* ArbolABB::buscar(NodoABB* nodo, int id) {
    if (nodo == nullptr || nodo->transaccion->getId() == id) {
        return nodo;
    }

    if (id < nodo->transaccion->getId()) {
        return buscar(nodo->izquierdo, id);
    }

    return buscar(nodo->derecho, id);
}

Transaccion* ArbolABB::buscar(int id) {
    NodoABB* resultado = buscar(raiz, id);
    if (resultado != nullptr) {
        return resultado->transaccion;
    }
    return nullptr;
}

void ArbolABB::encontrarTodos(NodoABB* nodo, const std::string& cuenta, const std::string& fecha, std::vector<Transaccion*>& encontradas) const {
    if (nodo == nullptr) {
        return;
    }

    encontrarTodos(nodo->izquierdo, cuenta, fecha, encontradas);

    if (nodo->transaccion->getCuentaOrigen() == cuenta && nodo->transaccion->getFecha() == fecha) {
        encontradas.push_back(nodo->transaccion);
    }

    encontrarTodos(nodo->derecho, cuenta, fecha, encontradas);
}

std::vector<Transaccion*> ArbolABB::encontrarTodos(const std::string& cuenta, const std::string& fecha) const {
    std::vector<Transaccion*> encontradas;
    encontrarTodos(raiz, cuenta, fecha, encontradas);
    return encontradas;
}
