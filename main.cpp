#include <fstream>
#include <sstream>
#include <cstdlib>
#include "composiciones.h"
#include "arbol.h"

// Lee el archivo y guarda cada composicion en el arbol
// Formato de cada linea: titulo,alumno,instrumento,nivel,melodia
int cargarComposiciones(string nombreArchivo, ArbolComposiciones &arbol, int &siguienteId) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return 0;
    }

    string linea;
    int cargadas = 0;

    while (getline(archivo, linea)) {
        // Quita el '\r' que deja Windows al final de cada linea
        if (linea != "" && linea[linea.size() - 1] == '\r') {
            linea = linea.substr(0, linea.size() - 1);
        }

        stringstream ss(linea);
        string titulo, alumno, instrumento, nivelTexto, melodia;

        getline(ss, titulo, ',');
        getline(ss, alumno, ',');
        getline(ss, instrumento, ',');
        getline(ss, nivelTexto, ',');
        getline(ss, melodia);

        int nivel = atoi(nivelTexto.c_str());

        // Se ignoran las lineas incompletas, con datos invalidos o titulo repetido
        if (titulo == "" || nivel < 1 || nivel > 3 || !melodiaValida(melodia)) {
            continue;
        }
        if (arbol.buscar(titulo) != 0) {
            continue;
        }

        arbol.agregar(nuevaComposicion(siguienteId, titulo, alumno,
                                       instrumento, nivel, melodia));
        siguienteId++;
        cargadas++;
    }

    archivo.close();
    return cargadas;
}

// Lee un numero del teclado; si se escribe algo que no es numero regresa -1
int leerNumero() {
    int numero;
    if (!(cin >> numero)) {
        cin.clear();
        numero = -1;
    }
    cin.ignore(1000, '\n');
    return numero;
}

int main() {
    ArbolComposiciones arbol;
    int siguienteId = 1;

    int cargadas = cargarComposiciones("composiciones.csv", arbol, siguienteId);
    cout << "Se cargaron " << cargadas << " composiciones del archivo.\n";

    int opcion;

    do {
        cout << "\n===== Escuela de Musica: Clave de Sol =====\n";
        cout << "1. Ver composiciones (orden alfabetico)\n";
        cout << "2. Buscar composicion por titulo\n";
        cout << "3. Componer una melodia nueva\n";
        cout << "4. Ordenar por nivel\n";
        cout << "5. Ordenar por numero de notas\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        opcion = leerNumero();

        if (opcion == 1) {
            mostrarComposiciones(arbol.enOrden());
        }
        else if (opcion == 2) {
            string titulo;
            cout << "Titulo a buscar: ";
            getline(cin, titulo);

            Composicion *c = arbol.buscar(titulo);
            if (c == 0) {
                cout << "No se encontro ninguna composicion con ese titulo.\n";
            } else {
                mostrarComposicion(*c);
            }
        }
        else if (opcion == 3) {
            string titulo, alumno, instrumento, melodia;
            int nivel;

            cout << "Titulo: ";
            getline(cin, titulo);
            if (titulo == "" || arbol.buscar(titulo) != 0) {
                cout << "Ese titulo esta vacio o ya existe.\n";
                continue;
            }
            cout << "Nombre del alumno: ";
            getline(cin, alumno);
            cout << "Instrumento: ";
            getline(cin, instrumento);

            cout << "Nivel (1 = Principiante, 2 = Intermedio, 3 = Avanzado): ";
            nivel = leerNumero();
            while (nivel < 1 || nivel > 3) {
                cout << "Nivel no valido, escribe 1, 2 o 3: ";
                nivel = leerNumero();
            }

            cout << "Escribe tu melodia (Do Re Mi Fa Sol La Si, separadas por espacio):\n";
            getline(cin, melodia);
            while (!melodiaValida(melodia)) {
                cout << "Solo se permiten las notas Do Re Mi Fa Sol La Si. Intenta de nuevo:\n";
                getline(cin, melodia);
            }

            arbol.agregar(nuevaComposicion(siguienteId, titulo, alumno,
                                           instrumento, nivel, melodia));
            siguienteId++;
            cout << "Composicion guardada!\n";
        }
        else if (opcion == 4) {
            vector<Composicion> lista = arbol.enOrden();
            mergeSort(lista, 0, (int)lista.size() - 1, NIVEL);
            cout << "Ordenadas por nivel (de principiante a avanzado):";
            mostrarComposiciones(lista);
        }
        else if (opcion == 5) {
            vector<Composicion> lista = arbol.enOrden();
            mergeSort(lista, 0, (int)lista.size() - 1, NOTAS);
            cout << "Ordenadas por numero de notas (de menor a mayor):";
            mostrarComposiciones(lista);
        }
        else if (opcion != 0) {
            cout << "Opcion no valida\n";
        }

    } while (opcion != 0);

    cout << "Hasta luego!\n";
    return 0;
}
