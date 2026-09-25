#ifndef COMPOSICIONES_H
#define COMPOSICIONES_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

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
    for (int i = 0; i < melodia.size(); i++) {
        if (melodia[i] != ' ' && (i == 0 || melodia[i - 1] == ' ')) {
            cont++;
        }
    }
    return cont;
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
// criterio 1 = por nivel, criterio 2 = por numero de notas
bool vaAntes(const Composicion &a, const Composicion &b, int criterio) {
    if (criterio == 1) {
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

    while (i < izq.size() && j < der.size()) {
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
    while (i < izq.size()) {
        lista[k] = izq[i];
        i++;
        k++;
    }
    while (j < der.size()) {
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

void mostrarComposiciones(const vector<Composicion> &lista) {
    cout << "\n----- Composiciones de la escuela -----\n";
    for (int i = 0; i < lista.size(); i++) {
        cout << "ID: " << lista[i].id
             << " | " << lista[i].titulo
             << " | Alumno: " << lista[i].alumno
             << " | " << lista[i].instrumento
             << " | Nivel: " << nombreNivel(lista[i].nivel)
             << " | Notas: " << lista[i].numNotas << endl;
        cout << "   Melodia: " << lista[i].melodia << endl;
    }
    cout << "---------------------------------------\n";
}

#endif
