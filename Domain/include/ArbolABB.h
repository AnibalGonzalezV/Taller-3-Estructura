#pragma once

#include "Transaccion.h"


#include <vector>

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
    void encontrarTodos(NodoABB* nodo, const std::string& cuenta, const std::string& fecha, std::vector<Transaccion*>& encontradas) const;

public:
    ArbolABB();
    void insertar(Transaccion* trans);
    Transaccion* buscar(int id);
    std::vector<Transaccion*> encontrarTodos(const std::string& cuenta, const std::string& fecha) const;
};
