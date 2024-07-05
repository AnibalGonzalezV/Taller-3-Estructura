//#include "ArbolAVL.h"
#include "../include/ArbolAVL.h"

//Implementamos manualmente el max.
int max(int a, int b) {
    return (a > b) ? a : b;
}

NodoAVL::NodoAVL(Transaccion* trans) : transaccion(trans), izquierdo(nullptr), derecho(nullptr), altura(1) {}

ArbolAVL::ArbolAVL() : raiz(nullptr) {}

int ArbolAVL::altura(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    return nodo->altura;
}

int ArbolAVL::balance(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    return altura(nodo->izquierdo) - altura(nodo->derecho);
}

NodoAVL* ArbolAVL::rotacionDerecha(NodoAVL* nodo) {
    NodoAVL* izquierdo = nodo->izquierdo;
    NodoAVL* derecha_izq = izquierdo->derecho;

    izquierdo->derecho = nodo;
    nodo->izquierdo = derecha_izq;

    nodo->altura = max(altura(nodo->izquierdo), altura(nodo->derecho)) + 1;
    izquierdo->altura = max(altura(izquierdo->izquierdo), altura(izquierdo->derecho)) + 1;

    return izquierdo;
}

NodoAVL* ArbolAVL::rotacionIzquierda(NodoAVL* nodo) {
    NodoAVL* derecho = nodo->derecho;
    NodoAVL* izquierda_der = derecho->izquierdo;

    derecho->izquierdo = nodo;
    nodo->derecho = izquierda_der;

    nodo->altura = max(altura(nodo->izquierdo), altura(nodo->derecho)) + 1;
    derecho->altura = max(altura(derecho->izquierdo), altura(derecho->derecho)) + 1;

    return derecho;
}

NodoAVL* ArbolAVL::insertar(NodoAVL* nodo, Transaccion* trans) {
    if (nodo == nullptr) {
        return new NodoAVL(trans);
    }

    if (trans->getId() < nodo->transaccion->getId()) {
        nodo->izquierdo = insertar(nodo->izquierdo, trans);
    } else if (trans->getId() > nodo->transaccion->getId()) {
        nodo->derecho = insertar(nodo->derecho, trans);
    } else {
        // No se permiten IDs duplicados en este árbol
        return nodo;
    }

    nodo->altura = 1 + max(altura(nodo->izquierdo), altura(nodo->derecho));

    int balance_actual = balance(nodo);

    // Casos de Rotacion para Mantener Balance
    if (balance_actual > 1 && trans->getId() < nodo->izquierdo->transaccion->getId()) {
        return rotacionDerecha(nodo);
    }

    if (balance_actual < -1 && trans->getId() > nodo->derecho->transaccion->getId()) {
        return rotacionIzquierda(nodo);
    }

    if (balance_actual > 1 && trans->getId() > nodo->izquierdo->transaccion->getId()) {
        nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
        return rotacionDerecha(nodo);
    }

    if (balance_actual < -1 && trans->getId() < nodo->derecho->transaccion->getId()) {
        nodo->derecho = rotacionDerecha(nodo->derecho);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

void ArbolAVL::insertar(Transaccion* trans) {
    raiz = insertar(raiz, trans);
}

NodoAVL* ArbolAVL::buscar(NodoAVL* nodo, int id) {
    if (nodo == nullptr || nodo->transaccion->getId() == id) {
        return nodo;
    }

    if (id < nodo->transaccion->getId()) {
        return buscar(nodo->izquierdo, id);
    }

    return buscar(nodo->derecho, id);
}

Transaccion* ArbolAVL::buscar(int id) {
    NodoAVL* resultado = buscar(raiz, id);
    if (resultado != nullptr) {
        return resultado->transaccion;
    }
    return nullptr;
}

void ArbolAVL::encontrarTodos(NodoAVL* nodo, const std::string& cuenta, const std::string& fecha, std::vector<Transaccion*>& encontradas) const {
    if (nodo == nullptr) {
        return;
    }

    encontrarTodos(nodo->izquierdo, cuenta, fecha, encontradas);

    if (nodo->transaccion->getCuentaOrigen() == cuenta && nodo->transaccion->getFecha() == fecha) {
        encontradas.push_back(nodo->transaccion);
    }

    encontrarTodos(nodo->derecho, cuenta, fecha, encontradas);
}

std::vector<Transaccion*> ArbolAVL::encontrarTodos(const std::string& cuenta, const std::string& fecha) const {
    std::vector<Transaccion*> encontradas;
    encontrarTodos(raiz, cuenta, fecha, encontradas);
    return encontradas;
}
