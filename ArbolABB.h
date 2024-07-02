#pragma once

#include "Transaccion.h"

class NodoABB {
public:
    Transaccion* transaccion;
    NodoABB* izquierdo;
    NodoABB* derecho;

    NodoABB(Transaccion* trans);
};

class ArbolABB {
private:
    NodoABB* raiz;

    NodoABB* insertar(NodoABB* nodo, Transaccion* trans);
    NodoABB* buscar(NodoABB* nodo, int id);

public:
    ArbolABB();
    void insertar(Transaccion* trans);
    Transaccion* buscar(int id);
};
