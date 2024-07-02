#include "ArbolAVL.h"

#include <algorithm>

NodoAVL::NodoAVL(Transaccion* trans) : transaccion(trans), izquierdo(nullptr), derecho(nullptr), altura(1) {}

ArbolAVL::ArbolAVL() : raiz(nullptr) {}

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

    nodo->altura = 1 + std::max(altura(nodo->izquierdo), altura(nodo->derecho));

    int balanceFactor = balance(nodo);

    // Casos de desequilibrio
    if (balanceFactor > 1 && trans->getId() < nodo->izquierdo->transaccion->getId()) {
        return rotacionDerecha(nodo);
    }

    if (balanceFactor < -1 && trans->getId() > nodo->derecho->transaccion->getId()) {
        return rotacionIzquierda(nodo);
    }

    if (balanceFactor > 1 && trans->getId() > nodo->izquierdo->transaccion->getId()) {
        nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
        return rotacionDerecha(nodo);
    }

    if (balanceFactor < -1 && trans->getId() < nodo->derecho->transaccion->getId()) {
        nodo->derecho = rotacionDerecha(nodo->derecho);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

void ArbolAVL::insertar(Transaccion* trans) {
    raiz = insertar(raiz, trans);
}

Transaccion* ArbolAVL::buscar(int id) {
    NodoAVL* actual = raiz;

    while (actual != nullptr) {
        if (id < actual->transaccion->getId()) {
            actual = actual->izquierdo;
        } else if (id > actual->transaccion->getId()) {
            actual = actual->derecho;
        } else {
            return actual->transaccion;
        }
    }

    return nullptr;
}

NodoAVL* ArbolAVL::rotacionDerecha(NodoAVL* nodo) {
    NodoAVL* izquierdo = nodo->izquierdo;
    NodoAVL* subArbol = izquierdo->derecho;

    izquierdo->derecho = nodo;
    nodo->izquierdo = subArbol;

    nodo->altura = std::max(altura(nodo->izquierdo), altura(nodo->derecho)) + 1;
    izquierdo->altura = std::max(altura(izquierdo->izquierdo), altura(izquierdo->derecho)) + 1;

    return izquierdo;
}

NodoAVL* ArbolAVL::rotacionIzquierda(NodoAVL* nodo) {
    NodoAVL* derecho = nodo->derecho;
    NodoAVL* subArbol = derecho->izquierdo;

    derecho->izquierdo = nodo;
    nodo->derecho = subArbol;

    nodo->altura = std::max(altura(nodo->izquierdo), altura(nodo->derecho)) + 1;
    derecho->altura = std::max(altura(derecho->izquierdo), altura(derecho->derecho)) + 1;

    return derecho;
}

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
