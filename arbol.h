#ifndef ARBOL_H
#define ARBOL_H

#include <string>
#include <vector>
#include <cctype>
#include "composiciones.h"

using namespace std;

// Regresa el texto en minusculas para comparar titulos sin importar mayusculas
string aMinusculas(string texto) {
    int n = texto.size();
    for (int i = 0; i < n; i++) {
        texto[i] = tolower(texto[i]);
    }
    return texto;
}

// Nodo del arbol: guarda una composicion y sus dos hijos
struct Nodo {
    Composicion dato;
    Nodo *left;
    Nodo *right;

    Nodo(Composicion c) {
        dato = c;
        left = 0;
        right = 0;
    }
};

// Arbol binario de busqueda ordenado por titulo (orden alfabetico)
class ArbolComposiciones {
private:
    Nodo *root;
    int cantidad;

    Nodo* insertar(Nodo *nodo, Composicion c) {
        if (nodo == 0) {
            return new Nodo(c);
        }
        if (aMinusculas(c.titulo) < aMinusculas(nodo->dato.titulo)) {
            nodo->left = insertar(nodo->left, c);
        } else {
            nodo->right = insertar(nodo->right, c);
        }
        return nodo;
    }

    // Recorrido inorder: izquierda, nodo, derecha (queda en orden alfabetico)
    void inorder(Nodo *nodo, vector<Composicion> &lista) {
        if (nodo != 0) {
            inorder(nodo->left, lista);
            lista.push_back(nodo->dato);
            inorder(nodo->right, lista);
        }
    }

    void borrar(Nodo *nodo) {
        if (nodo != 0) {
            borrar(nodo->left);
            borrar(nodo->right);
            delete nodo;
        }
    }

public:
    ArbolComposiciones() {
        root = 0;
        cantidad = 0;
    }

    ~ArbolComposiciones() {
        borrar(root);
    }

    void agregar(Composicion c) {
        root = insertar(root, c);
        cantidad++;
    }

    // Regresa un apuntador a la composicion con ese titulo, o 0 si no existe
    Composicion* buscar(string titulo) {
        string clave = aMinusculas(titulo);
        Nodo *actual = root;
        while (actual != 0) {
            string tituloActual = aMinusculas(actual->dato.titulo);
            if (clave == tituloActual) {
                return &actual->dato;
            }
            if (clave < tituloActual) {
                actual = actual->left;
            } else {
                actual = actual->right;
            }
        }
        return 0;
    }

    // Regresa todas las composiciones en orden alfabetico por titulo
    vector<Composicion> enOrden() {
        vector<Composicion> lista;
        inorder(root, lista);
        return lista;
    }

    int size() {
        return cantidad;
    }
};

#endif
