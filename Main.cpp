#include "composiciones.h"

int main() {
    vector<Composicion> lista;

    // Composiciones de ejemplo para probar el programa
    lista.push_back(nuevaComposicion(1, "Primer Vals", "Ana Lopez", "Piano", 2,
                                     "Do Mi Sol Mi Do Re Fa La"));
    lista.push_back(nuevaComposicion(2, "Rock Basico", "Luis Perez", "Guitarra", 1,
                                     "Mi Mi Sol La"));
    lista.push_back(nuevaComposicion(3, "Nocturno", "Sofia Ruiz", "Violin", 3,
                                     "La Si Do Re Mi Re Do Si La Sol"));
    lista.push_back(nuevaComposicion(4, "Escala Feliz", "Diego Mora", "Flauta", 1,
                                     "Do Re Mi Fa Sol La Si"));
    lista.push_back(nuevaComposicion(5, "Tormenta", "Carla Diaz", "Bateria", 2,
                                     "Do Do Sol"));

    int siguienteId = 6;
    int opcion;

    do {
        cout << "\n===== Escuela de Musica: Clave de Sol =====\n";
        cout << "1. Ver composiciones\n";
        cout << "2. Componer una melodia nueva\n";
        cout << "3. Ordenar por nivel\n";
        cout << "4. Ordenar por numero de notas\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            mostrarComposiciones(lista);
        }
        else if (opcion == 2) {
            string titulo, alumno, instrumento, melodia;
            int nivel;

            cin.ignore();
            cout << "Titulo: ";
            getline(cin, titulo);
            cout << "Nombre del alumno: ";
            getline(cin, alumno);
            cout << "Instrumento: ";
            getline(cin, instrumento);
            cout << "Nivel (1 = Principiante, 2 = Intermedio, 3 = Avanzado): ";
            cin >> nivel;
            cin.ignore();
            cout << "Escribe tu melodia (Do Re Mi Fa Sol La Si, separadas por espacio):\n";
            getline(cin, melodia);

            lista.push_back(nuevaComposicion(siguienteId, titulo, alumno,
                                             instrumento, nivel, melodia));
            siguienteId++;
            cout << "Composicion guardada!\n";
        }
        else if (opcion == 3) {
            mergeSort(lista, 0, lista.size() - 1, 1);
            cout << "Ordenadas por nivel (de principiante a avanzado):";
            mostrarComposiciones(lista);
        }
        else if (opcion == 4) {
            mergeSort(lista, 0, lista.size() - 1, 2);
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
