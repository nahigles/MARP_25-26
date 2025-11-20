/*@ <authors>
 *
 * MARP40 Cristina Munoz Munoz
 * MARP28 Nahia Iglesias Calvo
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "EnterosInf.h"
using namespace std;

/*@ <answer>

 Sustituye este párrafo por un comentario general sobre la solución,
 explicando cómo se resuelve el problema y cuál es el coste de la solución,
 en función del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

vector<int> cambio_exacto(vector<int> const& M, int C) {
    // numero de monedas/billetes que tenemos
    int n = M.size();

    //  siendo C la cantidad a pagar (+ 1 por el 0), se inicializa con el valor infinito
    vector<EntInf> monedas(C + 1, Infinito);
    monedas[0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = M[i - 1]; j <= C; ++j) {
            monedas[j] = min(monedas[j], monedas[j - M[i - 1]]);
        }
    }

    vector<int>solucion;
    int i = n, j = C;
    // mientras no se haya pagado todo
    while (i > 0 && j > 0) {
        if (M[i - 1] <= j && monedas[j] == monedas[j - M[i - 1]]) {
            solucion.push_back(M[i - 1]);
            j = j - M[i - 1];
        }
        i--;
    }

    if (j != 0) {
        solucion.push_back(M[0]);
    }
    return solucion;
}

bool resuelveCaso() {

    int precio, n;
    cin >> precio >> n;

    if (!cin)
        return false;

    vector<int> M;

    int tipo;
    for (int i = 0; i < n; i++) {
        cin >> tipo;
        M.push_back(tipo);
    }

    // leer el resto del caso y resolverlo
    vector<int> sol = cambio_exacto(M, precio);
    int money = 0;
    for (int i = 0; i < sol.size(); i++) {
        money += sol[i];
        
    }
    cout <<money << " " << sol.size() << "\n";
    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    if (!in.is_open())
        cout << "Error: no se ha podido abrir el archivo de entrada." << endl;
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    // Resolvemos
    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
#endif
    return 0;
}
