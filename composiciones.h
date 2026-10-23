#ifndef COMPOSICIONES_H
#define COMPOSICIONES_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Criterios de ordenamiento
#define NIVEL 1
#define NOTAS 2

// Una composicion creada por un alumno de la escuela
struct Composicion {
    int id;
    string titulo;
    string alumno;
    string instrumento;
    int nivel;          // 1 = principiante, 2 = intermedio, 3 = avanzado
    string melodia;     // notas separadas por espacio, ej. "Do Re Mi"
    int numNotas;
};

// Cuenta cuantas notas tiene una melodia (cada palabra es una nota)
int contarNotas(string melodia) {
    int cont = 0;
    int n = melodia.size();
    for (int i = 0; i < n; i++) {
        if (melodia[i] != ' ' && (i == 0 || melodia[i - 1] == ' ')) {
            cont++;
        }
    }
    return cont;
}

// Regresa true si la palabra es una de las 7 notas
bool esNota(string palabra) {
    return palabra == "Do" || palabra == "Re" || palabra == "Mi" ||
           palabra == "Fa" || palabra == "Sol" || palabra == "La" ||
           palabra == "Si";
}

// Regresa true si la melodia tiene al menos una nota y todas son validas
bool melodiaValida(string melodia) {
    string palabra = "";
    int notas = 0;
    melodia = melodia + " ";
    int n = melodia.size();
    for (int i = 0; i < n; i++) {
        if (melodia[i] == ' ') {
            if (palabra != "") {
                if (!esNota(palabra)) {
                    return false;
                }
                notas++;
                palabra = "";
            }
        } else {
            palabra = palabra + melodia[i];
        }
    }
    return notas > 0;
}

// Crea una composicion y calcula su numero de notas
Composicion nuevaComposicion(int id, string titulo, string alumno,
                             string instrumento, int nivel, string melodia) {
    Composicion c;
    c.id = id;
    c.titulo = titulo;
    c.alumno = alumno;
    c.instrumento = instrumento;
    c.nivel = nivel;
    c.melodia = melodia;
    c.numNotas = contarNotas(melodia);
    return c;
}

string nombreNivel(int nivel) {
    if (nivel == 1) return "Principiante";
    if (nivel == 2) return "Intermedio";
    return "Avanzado";
}

// Regresa true si "a" debe ir antes que "b"
bool vaAntes(const Composicion &a, const Composicion &b, int criterio) {
    if (criterio == NIVEL) {
        return a.nivel <= b.nivel;
    }
    return a.numNotas <= b.numNotas;
}

// Junta dos mitades ya ordenadas: [inicio..medio] y [medio+1..fin]
void mezclar(vector<Composicion> &lista, int inicio, int medio, int fin, int criterio) {
    vector<Composicion> izq;
    vector<Composicion> der;

    for (int i = inicio; i <= medio; i++) {
        izq.push_back(lista[i]);
    }
    for (int j = medio + 1; j <= fin; j++) {
        der.push_back(lista[j]);
    }

    int i = 0, j = 0, k = inicio;
    int nIzq = izq.size();
    int nDer = der.size();

    while (i < nIzq && j < nDer) {
        if (vaAntes(izq[i], der[j], criterio)) {
            lista[k] = izq[i];
            i++;
        } else {
            lista[k] = der[j];
            j++;
        }
        k++;
    }

    // Copiar lo que haya sobrado de alguna mitad
    while (i < nIzq) {
        lista[k] = izq[i];
        i++;
        k++;
    }
    while (j < nDer) {
        lista[k] = der[j];
        j++;
        k++;
    }
}

// Merge Sort recursivo
void mergeSort(vector<Composicion> &lista, int inicio, int fin, int criterio) {
    if (inicio < fin) {
        int medio = (inicio + fin) / 2;
        mergeSort(lista, inicio, medio, criterio);
        mergeSort(lista, medio + 1, fin, criterio);
        mezclar(lista, inicio, medio, fin, criterio);
    }
}

void mostrarComposicion(const Composicion &c) {
    cout << "ID: " << c.id
         << " | " << c.titulo
         << " | Alumno: " << c.alumno
         << " | " << c.instrumento
         << " | Nivel: " << nombreNivel(c.nivel)
         << " | Notas: " << c.numNotas << endl;
    cout << "   Melodia: " << c.melodia << endl;
}

void mostrarComposiciones(const vector<Composicion> &lista) {
    cout << "\n----- Composiciones de la escuela -----\n";
    int n = lista.size();
    for (int i = 0; i < n; i++) {
        mostrarComposicion(lista[i]);
    }
    cout << "---------------------------------------\n";
}

#endif
