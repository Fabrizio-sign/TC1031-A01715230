# Clave de Sol - Sistema para una Escuela de Música

**Alumno:** Iker Fabrizio Hernández **Matrícula:** A01715230

## Descripción del proyecto

Clave de Sol es un proyecto enfocado en desarrollar un sistema para una escuela de música, en el que los alumnos pueden componer melodías sencillas directamente desde el programa.

Cada composición guarda su título, el alumno que la hizo, el instrumento, el nivel del alumno (principiante, intermedio o avanzado) y la melodía, escrita con las notas Do, Re, Mi, Fa, Sol, La y Si separadas por espacios. El programa cuenta automáticamente cuántas notas tiene cada melodía.

El sistema tendrá como objetivo organizar las composiciones de la escuela, permitiendo consultarlas y ordenarlas según distintos criterios para encontrar la información de manera más fácil.

Posteriormente, conforme avance el proyecto, se podrán analizar y utilizar diferentes algoritmos de búsqueda y ordenamiento, así como estructuras de datos, de acuerdo con las necesidades del sistema.

## Funcionalidades del primer avance

- Ver todas las composiciones de la escuela.
- Componer una melodía nueva y guardarla.
- Ordenar las composiciones por nivel del alumno.
- Ordenar las composiciones por número de notas.

## Cómo compilar y ejecutar

```
g++ main.cpp -o clave_de_sol
./clave_de_sol
```

## SICT0301: Evalúa los componentes

Para el primer avance se realiza un análisis de complejidad del algoritmo Merge Sort.

### Complejidad temporal

- **Mejor caso:** O(n log n)
- **Caso promedio:** O(n log n)
- **Peor caso:** O(n log n)

Merge Sort divide la lista a la mitad de forma recursiva hasta que quedan partes de un solo elemento, y después las va juntando ya ordenadas. Como la lista se divide a la mitad cada vez, hay aproximadamente log n niveles de división, y en cada nivel se recorren los n elementos para juntarlos. Por eso la complejidad es O(n log n).

A diferencia de otros algoritmos, Merge Sort siempre hace las divisiones y las mezclas completas sin importar si los datos ya estaban ordenados o no, por lo que el mejor, el promedio y el peor caso tienen la misma complejidad.

### Complejidad espacial

La complejidad espacial de Merge Sort es O(n), debido a que al juntar las mitades se usan vectores auxiliares para copiar los elementos, además de la memoria que ocupan las llamadas recursivas.

## SICT0302: Toma decisiones

Para este primer avance se seleccionó Merge Sort debido a que su tiempo es O(n log n) en todos los casos, sin importar cómo estén acomodadas las composiciones. Algoritmos como Bubble Sort, Selection Sort o Insertion Sort pueden llegar a O(n²), y Quick Sort también puede llegar a O(n²) en su peor caso.

Además, Merge Sort es estable, es decir, si dos composiciones tienen el mismo nivel o el mismo número de notas, se respeta el orden en el que ya estaban. Esto es útil para el sistema porque se pueden aplicar distintos criterios de ordenamiento sin perder el orden anterior.

Aunque usa más memoria que otros algoritmos, se considera adecuado porque conforme la escuela vaya teniendo más composiciones, el ordenamiento seguirá siendo rápido.
