Funciones y registros (struct) en C++
Guía práctica con explicaciones y ejemplos para archivos .cpp
1. Introducción
En C++, las funciones permiten dividir un programa en tareas pequeñas y reutilizables. Una estructura (struct) agrupa varios datos relacionados bajo un solo nombre. Al combinar ambas herramientas podemos crear, consultar, modificar y procesar registros, por ejemplo estudiantes, productos o empleados.
Un registro es un conjunto de campos que describen una misma entidad. En C++, normalmente se representa mediante una estructura declarada con la palabra clave struct.
2. ¿Qué es una función?
Una función es un bloque de instrucciones que realiza una tarea específica. Puede recibir datos mediante parámetros y devolver un resultado. Ayuda a evitar código repetido y facilita la lectura y el mantenimiento.
tipo_retorno nombreFuncion(tipo parametro1, tipo parametro2) {\n    // instrucciones\n    return valor;\n}
•	Tipo de retorno: indica qué dato devuelve. Puede ser int, double, string, una estructura o void.
•	Nombre: identifica la función y debe describir su propósito.
•	Parámetros: datos que recibe para trabajar.
•	Cuerpo: instrucciones que ejecuta.
•	return: devuelve un resultado. Una función void no devuelve un valor.
Ejemplo 1. Función que calcula un promedio
#include <iostream>
using namespace std;

double calcularPromedio(double nota1, double nota2) {
    return (nota1 + nota2) / 2.0;
}

int main() {
    double promedio = calcularPromedio(4.0, 5.0);
    cout << "Promedio: " << promedio << endl;
    return 0;
}
La función recibe dos notas, calcula el promedio y devuelve un double. main() la llama y muestra el resultado.
3. ¿Qué es un registro struct?
struct crea un tipo de dato propio que reúne variables de distintos tipos. Cada variable dentro de la estructura se denomina miembro o campo. A diferencia de un arreglo común, una estructura puede combinar int, string, double, bool y otros tipos.
#include <string>
using namespace std;

struct Estudiante {
    int codigo;
    string nombre;
    double nota;
};
Estudiante es el nuevo tipo de dato. codigo, nombre y nota son sus campos.
Cómo declarar y usar un registro
Estudiante alumno;
alumno.codigo = 101;
alumno.nombre = "Laura";
alumno.nota = 4.5;
El operador punto (.) permite acceder a cada campo de una variable struct.
Inicialización directa
Estudiante alumno2 = {102, "Carlos", 3.8};
Los valores se asignan en el mismo orden en que aparecen los campos en la definición.
4. Funciones que trabajan con struct
Una función puede recibir una estructura como parámetro, devolver una estructura o modificar sus campos. Esto permite separar el procesamiento de los datos de su almacenamiento.
Ejemplo 2. Recibir un struct por valor
struct Producto {
    string nombre;
    double precio;
};

double calcularPrecioConIVA(Producto p) {
    return p.precio * 1.19;
}
Al recibir p por valor, la función trabaja con una copia. Los cambios hechos a esa copia no modifican la variable original.
Ejemplo 3. Recibir un struct por referencia
void aplicarDescuento(Producto &p, double porcentaje) {
    p.precio = p.precio * (1 - porcentaje / 100.0);
}
El símbolo & indica que p hace referencia al registro original. Por eso, el cambio en el precio sí se refleja en la variable que se pasó a la función.
Ejemplo 4. Pasar por referencia constante
void mostrarProducto(const Producto &p) {
    cout << p.nombre << " cuesta $" << p.precio << endl;
}
const impide modificar el registro. La referencia evita copiarlo. Es una buena opción cuando la función solo consulta información.
5. Arreglos y vectores de registros
Para almacenar varios registros del mismo tipo se puede usar un arreglo o un vector. Un arreglo tiene tamaño fijo; un vector de la biblioteca <vector> puede crecer o reducirse durante la ejecución.
Ejemplo 5. Arreglo de estudiantes
Estudiante grupo[3] = {
    {1, "Ana", 4.2},
    {2, "Luis", 3.7},
    {3, "Marta", 4.8}
};

for (int i = 0; i < 3; i++) {
    cout << grupo[i].nombre << " - " << grupo[i].nota << endl;
}
grupo[i] representa un registro del arreglo y grupo[i].nombre accede al campo nombre de ese registro.
Ejemplo 6. Vector y función para mostrar registros
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Estudiante {
    int codigo;
    string nombre;
    double nota;
};

void mostrarEstudiantes(const vector<Estudiante> &lista) {
    for (const Estudiante &e : lista) {
        cout << e.codigo << " | " << e.nombre
             << " | Nota: " << e.nota << endl;
    }
}

int main() {
    vector<Estudiante> lista = {
        {1, "Ana", 4.2},
        {2, "Luis", 3.7},
        {3, "Marta", 4.8}
    };

    mostrarEstudiantes(lista);
    return 0;
}
El vector almacena una cantidad variable de estudiantes. La función lo recibe por referencia constante, lo recorre y muestra cada registro sin modificarlo.
6. Programa completo: registrar y consultar productos
Este programa define un registro Producto, utiliza una función para leer los datos, otra para mostrarlos y un vector para guardar varios registros durante la ejecución.
#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

struct Producto {
    int codigo;
    string nombre;
    double precio;
};

Producto leerProducto() {
    Producto p;
    cout << "Codigo: ";
    cin >> p.codigo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Nombre: ";
    getline(cin, p.nombre);
    cout << "Precio: ";
    cin >> p.precio;
    return p;
}

void mostrarProducto(const Producto &p) {
    cout << "Codigo: " << p.codigo
         << " | Nombre: " << p.nombre
         << " | Precio: $" << p.precio << endl;
}

int main() {
    vector<Producto> inventario;
    int cantidad;

    cout << "Cuantos productos desea registrar? ";
    cin >> cantidad;

    for (int i = 0; i < cantidad; i++) {
        cout << "\nProducto " << i + 1 << endl;
        inventario.push_back(leerProducto());
    }

    cout << "\n--- INVENTARIO ---\n";
    for (const Producto &p : inventario) {
        mostrarProducto(p);
    }
    return 0;
}
Este ejemplo conserva los registros en memoria mientras el programa se ejecuta. Al cerrarlo, los datos se pierden. Para conservarlos entre ejecuciones se pueden guardar en archivos usando fstream.
7. Diferencia entre struct, registro y función
Concepto	¿Qué representa?	Ejemplo
struct	Definición de un tipo de dato compuesto.	struct Estudiante { ... };
Registro	Variable concreta creada con ese tipo.	Estudiante alumno;
Campo	Dato que pertenece al registro.	alumno.nombre
Función	Tarea que recibe o devuelve datos.	mostrarEstudiante(alumno)
8. Errores frecuentes y recomendaciones
•	Olvidar el punto y coma al cerrar la estructura: debe escribirse };
•	Confundir el tipo con una variable: Estudiante es el tipo; alumno es una variable.
•	Acceder a un campo sin indicar el registro: se usa alumno.nombre.
•	Pasar por valor cuando se necesita modificar el original. En ese caso, usar una referencia.
•	Para consultar sin modificar, usar const Tipo &.
•	Validar los datos ingresados por el usuario, por ejemplo que la cantidad y el precio sean válidos.
9. Cómo compilar un archivo .cpp
Guarda el código en un archivo con extensión .cpp, por ejemplo inventario.cpp. Con el compilador g++ puedes compilarlo desde una terminal:
g++ inventario.cpp -o inventario
En Windows, si se generó inventario.exe, puedes ejecutarlo con:
.\inventario.exe
La extensión .cpp identifica un archivo de código fuente C++. No es una instrucción del lenguaje: el archivo contiene definiciones de estructuras, funciones y el punto de entrada main().
10. Resumen
Las funciones organizan el programa en tareas reutilizables. Las estructuras struct agrupan datos relacionados y permiten representar registros. Al combinarlas se pueden crear programas para registrar, consultar y modificar información. Para consultar suele convenir const Tipo &, para modificar se usa Tipo &, y una función también puede devolver una estructura mediante return.
