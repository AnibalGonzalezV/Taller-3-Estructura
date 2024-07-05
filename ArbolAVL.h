// ArbolAVL.h
#pragma once

#include "Transaccion.h"
#include <vector>
#include <string>

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

    int altura(NodoAVL* nodo);
    int balance(NodoAVL* nodo);
    NodoAVL* rotacionDerecha(NodoAVL* nodo);
    NodoAVL* rotacionIzquierda(NodoAVL* nodo);
    NodoAVL* insertar(NodoAVL* nodo, Transaccion* trans);
    NodoAVL* buscar(NodoAVL* nodo, int id);
    void encontrarTodos(NodoAVL* nodo, const std::string& cuenta, const std::string& fecha, std::vector<Transaccion*>& encontradas) const;

public:
    ArbolAVL();
    void insertar(Transaccion* trans);
    Transaccion* buscar(int id);
    std::vector<Transaccion*> encontrarTodos(const std::string& cuenta, const std::string& fecha) const;
};
