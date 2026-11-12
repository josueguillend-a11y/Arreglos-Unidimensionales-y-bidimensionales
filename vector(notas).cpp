#include <iostream>
#include <vector>
using namespace std;

int main() {

    vector<double> notas(5);
    double suma = 0;
    double promedio;

    // Registrar las 5 notas
    for (int i = 0; i < 5; i++) {
        cout << "Ingrese la nota " << i + 1 << ": ";
        cin >> notas[i];

        suma = suma + notas[i];
    }

    // Calcular promedio
    promedio = suma / 5;

    // Mostrar las notas
    cout << "\n--- NOTAS REGISTRADAS ---" << endl;

    for (int i = 0; i < 5; i++) {
        cout << "Nota " << i + 1 << ": "
             << notas[i] << endl;
    }

    cout << "\nPromedio: " << promedio << endl;

    return 0;
}