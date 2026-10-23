# Clave de Sol - Sistema para una Escuela de Música

**Alumno:** Iker Fabrizio Hernández **Matrícula:** A01715230

## Descripción del proyecto

Clave de Sol es un proyecto enfocado en desarrollar un sistema para una escuela de música, en el que los alumnos pueden componer melodías sencillas directamente desde el programa.

Cada composición guarda su título, el alumno que la hizo, el instrumento, el nivel del alumno (principiante, intermedio o avanzado) y la melodía, escrita con las notas Do, Re, Mi, Fa, Sol, La y Si separadas por espacios. El programa cuenta automáticamente cuántas notas tiene cada melodía.

El sistema tiene como objetivo organizar las composiciones de la escuela, permitiendo consultarlas y ordenarlas según distintos criterios para encontrar la información de manera más fácil.

## Avance 2

En este avance las composiciones ya no se escriben dentro del código: se cargan desde el archivo `composiciones.csv` y se guardan en un **árbol binario de búsqueda (BST)** ordenado por título. Gracias al árbol, las composiciones siempre están en orden alfabético y se pueden buscar por título de forma eficiente.

Cambios respecto al avance 1:

- Las composiciones se cargan desde un archivo al iniciar el programa.
- Se guardan en un árbol binario de búsqueda en lugar de un vector.
- Se agregó la búsqueda de una composición por título.
- Para ordenar por nivel o por número de notas se usa Merge Sort sobre una copia, así el árbol no se modifica.
- Se valida que el nivel sea 1, 2 o 3 y que la melodía solo tenga las notas Do, Re, Mi, Fa, Sol, La y Si.
- Se aplicó la retroalimentación del avance 1: los criterios de ordenamiento ahora son constantes (`#define NIVEL 1` y `#define NOTAS 2`).

## Funcionalidades

- Ver todas las composiciones en orden alfabético.
- Buscar una composición por su título (no importan mayúsculas o minúsculas).
- Componer una melodía nueva y guardarla.
- Ordenar las composiciones por nivel del alumno.
- Ordenar las composiciones por número de notas.

## Cómo compilar y ejecutar

```
g++ main.cpp -o clave_de_sol
./clave_de_sol
```

El archivo `composiciones.csv` debe estar en la misma carpeta desde donde se ejecuta el programa.

## Archivo de datos

Cada línea de `composiciones.csv` es una composición con el formato:

```
titulo,alumno,instrumento,nivel,melodia
```

Ejemplo:

```
Nocturno,Sofia Ruiz,Violin,3,La Si Do Re Mi Re Do Si La Sol
```

Las líneas incompletas, con un nivel distinto de 1, 2 o 3, con notas no válidas o con un título repetido no se cargan.

## Cómo usar el programa

Al iniciar, el programa indica cuántas composiciones cargó y muestra el menú:

1. **Ver composiciones:** muestra todas en orden alfabético por título.
2. **Buscar composición por título:** se escribe el título y se muestra su información, o un aviso si no existe.
3. **Componer una melodía nueva:** se escribe el título, el alumno, el instrumento, el nivel y la melodía. Si el título ya existe, la composición no se guarda.
4. **Ordenar por nivel:** muestra las composiciones de principiante a avanzado.
5. **Ordenar por número de notas:** muestra las composiciones de menor a mayor número de notas.
0. **Salir.**

## SICT0301: Evalúa los componentes

En el análisis, *n* es el número de composiciones y *h* la altura del árbol. Comparar dos títulos depende de su longitud, pero como los títulos son cortos se toma como O(1).

### Árbol binario de búsqueda (`arbol.h`)

| Uso en el programa | Mejor caso | Caso promedio | Peor caso |
|---|---|---|---|
| `agregar` (insertar una composición) | O(1) | O(log n) | O(n) |
| `buscar` (buscar por título) | O(1) | O(log n) | O(n) |
| `enOrden` (recorrido inorder) | O(n) | O(n) | O(n) |
| Destructor (liberar la memoria) | O(n) | O(n) | O(n) |

- **agregar:** baja desde la raíz comparando títulos hasta encontrar un lugar vacío, por lo que recorre un solo camino de la raíz a una hoja: O(h). El mejor caso es cuando el árbol está vacío. Si los títulos llegan en orden aleatorio, el árbol queda más o menos balanceado y h es aproximadamente log n. El peor caso es cuando los títulos llegan ya en orden alfabético: cada nodo queda a la derecha del anterior, el árbol se vuelve como una lista ligada y h = n.
- **buscar:** hace el mismo recorrido que `agregar`, descartando la mitad del árbol en cada comparación cuando está balanceado. El mejor caso es cuando el título buscado está en la raíz.
- **enOrden:** visita cada nodo una sola vez (izquierda, nodo, derecha) y lo agrega al final de un vector, que cuesta O(1) en promedio. Por eso siempre es O(n).
- **Destructor:** visita y libera cada nodo una vez: O(n).

**Complejidad espacial:** el árbol ocupa O(n) porque tiene un nodo por composición. Las funciones recursivas usan O(h) de memoria por las llamadas: O(log n) en promedio y O(n) en el peor caso.

### Vector de composiciones

El vector solo se usa como copia temporal para mostrar las composiciones y para ordenarlas.

| Uso en el programa | Complejidad |
|---|---|
| Llenarlo con `enOrden` | O(n) |
| Ordenarlo con Merge Sort | O(n log n) |
| Mostrarlo | O(n) |

**Complejidad espacial:** O(n), porque guarda una copia de cada composición.

### Merge Sort

- **Mejor caso:** O(n log n)
- **Caso promedio:** O(n log n)
- **Peor caso:** O(n log n)

Merge Sort divide la lista a la mitad de forma recursiva hasta que quedan partes de un solo elemento, y después las va juntando ya ordenadas. Como la lista se divide a la mitad cada vez, hay aproximadamente log n niveles de división, y en cada nivel se recorren los n elementos para juntarlos. Por eso la complejidad es O(n log n), sin importar si los datos ya estaban ordenados o no.

**Complejidad espacial:** O(n), por los vectores auxiliares que se usan al juntar las mitades.

### Operaciones del programa

| Operación | Caso promedio | Peor caso |
|---|---|---|
| Cargar el archivo (por cada línea se busca el título y se inserta) | O(n log n) | O(n²) |
| Ver composiciones | O(n) | O(n) |
| Buscar por título | O(log n) | O(n) |
| Componer una melodía (se busca el título y se inserta) | O(log n) | O(n) |
| Ordenar por nivel o por número de notas (`enOrden` + Merge Sort) | O(n log n) | O(n log n) |

## SICT0302: Toma decisiones

### Algoritmo de ordenamiento

Se seleccionó Merge Sort debido a que su tiempo es O(n log n) en todos los casos, sin importar cómo estén acomodadas las composiciones. Algoritmos como Bubble Sort, Selection Sort o Insertion Sort pueden llegar a O(n²), y Quick Sort también puede llegar a O(n²) en su peor caso.

Además, Merge Sort es estable: si dos composiciones tienen el mismo nivel o el mismo número de notas, se respeta el orden en el que ya estaban. Como la copia que se ordena sale del árbol en orden alfabético, las composiciones empatadas quedan también en orden alfabético sin hacer un segundo ordenamiento.

En este avance Merge Sort se aplica sobre una copia, para que el árbol siga ordenado por título.

### Estructura de datos

Se seleccionó un árbol binario de búsqueda ordenado por título porque:

- **Organiza los datos de forma natural:** cada composición se coloca en su lugar al insertarla, y con el recorrido inorder salen siempre en orden alfabético, sin tener que ordenarlas.
- **La búsqueda por título es más rápida:** en promedio cuesta O(log n). En un vector desordenado o en una lista ligada costaría O(n) porque habría que revisar una por una.
- **Insertar también es eficiente:** en promedio cuesta O(log n). Un vector ordenado permitiría búsqueda binaria, pero cada inserción tendría que recorrer los elementos para hacer espacio: O(n).
- **Evita títulos repetidos:** antes de guardar una composición se busca su título en el árbol, así el título funciona como clave única.

La desventaja del árbol es que no se balancea solo, y si las composiciones llegaran en orden alfabético, buscar e insertar costarían O(n). Por eso el archivo de datos no está en orden alfabético.

Se usa un vector solo para ordenar por nivel o por número de notas, porque Merge Sort necesita acceder a los elementos por posición, y eso el árbol no lo permite.

## SICT0303: Implementa acciones científicas

### Mecanismos de consulta

- **Ver composiciones** (`enOrden`): recorre el árbol en inorder y regresa todas las composiciones en orden alfabético.
- **Buscar por título** (`buscar`): baja por el árbol comparando el título buscado con el de cada nodo, a la izquierda si es menor y a la derecha si es mayor. Regresa la composición encontrada, o un aviso si no existe. La comparación se hace en minúsculas, por lo que "primer vals" encuentra "Primer Vals".
- **Ordenar por nivel o por número de notas:** obtiene las composiciones del árbol, las ordena con Merge Sort y las muestra.

### Lectura de archivos

La función `cargarComposiciones` en `main.cpp` lee `composiciones.csv` línea por línea con `getline` y separa los campos por comas con un `stringstream`. Cada composición válida se inserta en el árbol con un ID consecutivo.

Para que los datos se carguen correctamente:

- Si el archivo no existe, se muestra un aviso y el programa continúa sin composiciones.
- Se quita el `\r` que deja Windows al final de cada línea.
- Se ignoran las líneas incompletas, con nivel inválido, con notas que no sean Do, Re, Mi, Fa, Sol, La o Si, o con un título repetido.
- Al terminar se muestra cuántas composiciones se cargaron.
