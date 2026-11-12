Arreglos unidimensionales (vectores) y bidimensionales (matrices)
Un arreglo es una estructura de datos que guarda una colección de elementos del mismo tipo en posiciones consecutivas de memoria, accesibles mediante un índice.
1. Arreglo unidimensional (vector)
Características
Tiene una sola dimensión: se accede con un único índice.
Todos los elementos son del mismo tipo (int, float, char, etc.).
Tamaño fijo al declararlo (en arreglos estáticos).
Los índices empiezan en 0 y terminan en n-1.
Los elementos están contiguos en memoria, así que el acceso por índice es muy rápido (O(1)).
Ejemplo en C++
#include <iostream>
using namespace std;

int main() {
    int notas[5] = {80, 90, 75, 60, 100};

    for (int i = 0; i < 5; i++) {
        cout << "notas[" << i << "] = " << notas[i] << endl;
    }
    return 0;
}

¿Para qué se usa?
Guardar listas de datos: notas, precios, edades, temperaturas.
Buscar y ordenar datos (búsqueda binaria, burbuja, etc.).
Calcular sumas, promedios, máximos y mínimos.
Implementar pilas, colas y otras estructuras.
2. Arreglo bidimensional (matriz)
Características
Tiene dos dimensiones: se accede con dos índices, [fila][columna].
Se puede ver como una tabla o un "arreglo de arreglos".
Todos los elementos son del mismo tipo.
Tamaño fijo: tipo nombre[filas][columnas].
En C++ se almacena en memoria fila por fila (row-major order).
Se recorre normalmente con dos ciclos anidados.
Ejemplo en C++
#include <iostream>
using namespace std;

int main() {
    int matriz[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    for (int i = 0; i < 2; i++) {         // filas
        for (int j = 0; j < 3; j++) {     // columnas
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

¿Para qué se usa?
Representar tablas de datos: notas de varios estudiantes en varias materias, ventas por mes y producto.
Operaciones matemáticas con matrices: suma, multiplicación, transpuesta, determinantes.
Juegos de tablero: ajedrez, tres en raya, buscaminas, sudoku.
Procesamiento de imágenes: una imagen es una matriz de píxeles.
Grafos: matriz de adyacencia.
Mapas, cuadrículas y laberintos.
3. Comparación rápida
Aspecto
Vector (1D)
Matriz (2D)
Dimensiones
1
2
Índices
a[i]
a[i][j]
Analogía
Una fila de casillas
Una tabla de filas y columnas
Recorrido
1 ciclo
2 ciclos anidados
Declaración
int a[5];
int a[3][4];
Uso típico
Listas simples
Tablas, imágenes, tableros

4. Cosas importantes a tener en cuenta
Fuera de rango: acceder a a[5] en un arreglo de tamaño 5 es un error de comportamiento indefinido; C++ no lo avisa.
Inicialización: si no inicializas, los elementos locales contienen basura. Usa int a[5] = {0}; para ponerlos en cero.
Alternativas modernas en C++: std::vector (tamaño dinámico) y std::array (tamaño fijo, más seguro). Una matriz dinámica se puede hacer con vector<vector<int>>.
Más dimensiones: el concepto se extiende a 3D o más (por ejemplo, int cubo[3][3][3]).
Arreglos en profundidad: lo que va más allá de lo básico
1. Cómo se organizan realmente en memoria
El nombre de un arreglo es, en la mayoría de contextos, la dirección del primer elemento. Por eso a[i] equivale a *(a + i): el compilador suma i * sizeof(tipo) bytes a la dirección base.
int a[4] = {10, 20, 30, 40};
cout << a[2]      << endl;   // 30
cout << *(a + 2)  << endl;   // 30 (aritmética de punteros)
cout << 2[a]      << endl;   // 30 (válido, aunque raro: *(2 + a))

En una matriz int m[3][4] los 12 enteros están en un solo bloque contiguo. El elemento m[i][j] está en la posición lineal i * COLUMNAS + j. Esta fórmula es la base de las matrices aplanadas (sección 5).
2. Decaimiento a puntero (array decay) y sizeof
Cuando pasas un arreglo a una función, pierde su tamaño: llega como puntero.
void f(int arr[]) {
    cout << sizeof(arr);          // tamaño de un puntero (8 bytes en 64 bits), NO del arreglo
}

int main() {
    int a[10];
    cout << sizeof(a);            // 40 bytes
    cout << sizeof(a) / sizeof(a[0]);  // 10 elementos
    f(a);
}

Por eso hay que pasar el tamaño como parámetro aparte:
int suma(const int arr[], int n) {
    int s = 0;
    for (int i = 0; i < n; i++) s += arr[i];
    return s;
}

const indica que la función no modificará el arreglo. Los arreglos siempre se pasan por referencia implícita (por la dirección), así que los cambios dentro de la función afectan al original.
3. Pasar matrices a funciones
Para matrices, el compilador necesita conocer todas las dimensiones menos la primera, para poder calcular i * COLUMNAS + j:
const int COLS = 4;

void imprimir(int m[][COLS], int filas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < COLS; j++)
            cout << m[i][j] << " ";
        cout << endl;
    }
}

Esta rigidez es una de las razones principales para preferir vector o matrices aplanadas.
4. Memoria dinámica
Los arreglos estáticos viven en la pila (stack), que es pequeña (típicamente ~1 MB en Windows). Un int a[1000000] local puede provocar un stack overflow. Para tamaños grandes o desconocidos en compilación se usa el heap:
int n = 1000000;
int* a = new int[n]();    // () inicializa en cero
// ... usar a ...
delete[] a;               // delete[] y no delete, obligatorio con new[]

Matriz dinámica con punteros dobles (cada fila se reserva por separado):
int filas = 3, cols = 4;
int** m = new int*[filas];
for (int i = 0; i < filas; i++) m[i] = new int[cols]();

// liberar en orden inverso
for (int i = 0; i < filas; i++) delete[] m[i];
delete[] m;

Es propenso a fugas de memoria. En C++ moderno casi siempre se evita con std::vector.
5. Matrices aplanadas (1D simulando 2D)
Un solo bloque contiguo, más eficiente y simple de reservar y liberar:
vector<int> m(filas * cols);
auto at = [&](int i, int j) -> int& { return m[i * cols + j]; };

at(1, 2) = 99;

Ventajas: una sola reserva de memoria, mejor localidad de caché, copia rápida. Es el enfoque que usan librerías numéricas como Eigen o NumPy internamente.
6. Arreglos irregulares (jagged arrays)
Con vector<vector<int>> cada fila puede tener longitud distinta, algo imposible en una matriz clásica:
vector<vector<int>> triangulo(5);
for (int i = 0; i < 5; i++)
    triangulo[i].assign(i + 1, 1);   // fila i con i+1 elementos

Útil para el triángulo de Pascal, listas de adyacencia de grafos o datos con longitud variable.
7. Rendimiento: el orden de recorrido importa
La CPU trae datos a la caché en bloques contiguos. Como C++ guarda por filas, recorrer por filas aprovecha la caché y recorrer por columnas no:
// Rápido: acceso secuencial en memoria
for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
        suma += m[i][j];

// Lento: salta N elementos en cada acceso
for (int j = 0; j < N; j++)
    for (int i = 0; i < N; i++)
        suma += m[i][j];

En matrices grandes la diferencia puede ser de varias veces en tiempo, aunque ambas son O(N²) en teoría. Esto también afecta la multiplicación de matrices: cambiar el orden de los ciclos (i-k-j en lugar de i-j-k) mejora notablemente el rendimiento.
8. Algoritmos clásicos sobre vectores
Suma de prefijos: permite responder "suma del rango [l, r]" en O(1) tras O(n) de preparación.
vector<int> v = {3, 1, 4, 1, 5, 9};
vector<int> pre(v.size() + 1, 0);
for (size_t i = 0; i < v.size(); i++) pre[i + 1] = pre[i] + v[i];

int l = 2, r = 4;                     // suma de v[2..4]
cout << pre[r + 1] - pre[l];          // 4 + 1 + 5 = 10

Dos punteros: invertir un arreglo sin memoria extra.
for (int i = 0, j = n - 1; i < j; i++, j--) swap(a[i], a[j]);

Búsqueda binaria (requiere arreglo ordenado, O(log n)):
int buscar(const vector<int>& v, int x) {
    int lo = 0, hi = (int)v.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;   // evita desbordamiento de (lo+hi)
        if (v[mid] == x) return mid;
        if (v[mid] < x) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

9. Algoritmos clásicos sobre matrices
Transpuesta (para matriz cuadrada, en el lugar):
for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
        swap(m[i][j], m[j][i]);

Multiplicación de A (n×p) por B (p×m), complejidad O(n·p·m):
for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
        C[i][j] = 0;
        for (int k = 0; k < p; k++)
            C[i][j] += A[i][k] * B[k][j];
    }

La condición clave: columnas de A = filas de B.
Rotar 90°: transponer y luego invertir cada fila.
Diagonales en una matriz cuadrada n×n:
Principal: i == j
Secundaria: i + j == n - 1
Recorrido en espiral y recorrido por diagonales son problemas típicos de entrevistas técnicas.
10. Errores comunes y cómo detectarlos
Error
Consecuencia
Prevención
Acceso fuera de rango
Comportamiento indefinido, corrupción de memoria
Usar v.at(i) (lanza excepción) en depuración
Usar sizeof dentro de una función
Tamaño erróneo
Pasar n o usar std::vector/std::span
delete en lugar de delete[]
Comportamiento indefinido
Evitar new[]; usar vector
Arreglos locales enormes
Stack overflow
Usar heap o vector
Comparar int con size_t
Advertencias y errores con negativos
Usar size_t o convertir explícitamente
Variable sin inicializar
Valores basura
Inicializar siempre: = {} o ()

Compilar con advertencias activadas ayuda mucho: g++ -Wall -Wextra -g archivo.cpp. En VS Code puedes añadir esas banderas en tasks.json.
11. Alternativas modernas de la biblioteca estándar
std::array<int, 5>: tamaño fijo en compilación, conoce su .size(), no decae a puntero, se puede copiar y comparar con ==.
std::vector<T>: tamaño dinámico, memoria contigua, .push_back(), .resize(), .at().
std::span<T> (C++20): una "vista" ligera sobre un arreglo o vector existente, sin copiarlo. Ideal para funciones que reciben arreglos:
#include <span>
int suma(std::span<const int> datos) {
    int s = 0;
    for (int x : datos) s += x;
    return s;
}
// funciona con arreglos clásicos, array y vector

Bucle por rango: for (int x : v) o for (auto& x : v) para modificar.
<algorithm> y <numeric>: sort, reverse, accumulate, max_element, binary_search, fill.
#include <algorithm>
#include <numeric>
vector<int> v = {5, 2, 8, 1};
sort(v.begin(), v.end());
int total = accumulate(v.begin(), v.end(), 0);

12. Complejidad de operaciones (resumen)
Operación
Vector estático
std::vector
Acceso por índice
O(1)
O(1)
Insertar al final
no aplica
O(1) amortizado
Insertar/eliminar en medio
O(n)
O(n)
Búsqueda lineal
O(n)
O(n)
Búsqueda binaria (ordenado)
O(log n)
O(log n)


