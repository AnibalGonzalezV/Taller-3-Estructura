#pragma once

#include "Transaccion.h"

class NodoAVL {
public:
    Transaccion* transaccion;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
    int altura;

    NodoAVL(Transaccion* trans);
};

class ArbolAVL {
private:
    NodoAVL* raiz;

    NodoAVL* insertar(NodoAVL* nodo, Transaccion* trans);
    NodoAVL* rotacionDerecha(NodoAVL* nodo);
    NodoAVL* rotacionIzquierda(NodoAVL* nodo);
    int altura(NodoAVL* nodo);
    int balance(NodoAVL* nodo);

public:
    ArbolAVL();
    void insertar(Transaccion* trans);
    Transaccion* buscar(int id);
};
