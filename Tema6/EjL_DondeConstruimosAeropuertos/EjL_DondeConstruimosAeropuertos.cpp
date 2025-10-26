
/*@ <authors>
 *
 * MARP28 Nahia Iglesias Calvo
 * MARP40 Cristina Munoz Munoz
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"
/*@ <answer>
Para resolver el problema usamos un grafo valorado donde los vertices son las localidades y las aristas son
las carreteras que las unen con un valor que representa el coste de construir esa carretera.
Se obtiene el arbol de recubrimiento minimo de este grafo con el algoritmo de Kruskal, como recorre las aristas
de menor a mayor valor, nos garantiza que el coste es el minimo.
Pero somos nosotras quienes decidimos si es mas rentable construir un aeropuerto o construir la carretera.
Como un requisito es que si hay varias formas de conseguir el coste minimo se elige la que tenga mas aeropuertos,
a la hora de unir los conjuntos de localidades, si el coste de construir el aeropuerto es mayor o igual que el de construir
la carretera, elegimos construir el aeropuerto, si no, se construye la carretera.
Al terminar de crear el ARM, el numero de conjuntos disjuntos distintos es el numero de aeropuertos totales.

Siendo N el numero de localidades y M el numero de carreteras que las unen.
Coste en tiempo: O(M log M)

Coste en espacio: O(N + M)
 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

template <typename Valor>
class ARM_Kruskal {
private:
    vector<Arista<Valor>> _ARM;
    Valor coste;
    int conjuntosDistintos;
public:
    ARM_Kruskal(GrafoValorado<Valor> const& g, int costeA) : coste(0) {
        PriorityQueue<Arista<Valor>> pq(g.aristas());   //O(M)
        ConjuntosDisjuntos cjtos(g.V());                //O(N)

        //El bucle en caso peor da M vueltas
        while (!pq.empty()) {
            auto a = pq.top(); pq.pop();    //O(log M)
            int v = a.uno(), w = a.otro(v);
            if (a.valor() >= costeA) break;
            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                _ARM.push_back(a);
                coste += a.valor();
                if (_ARM.size() == g.V() - 1) break;
            }
        }
        conjuntosDistintos = cjtos.num_cjtos();
    }
    Valor costeARM() const {
        return coste;
    }
    vector<Arista<Valor>> const& ARM() const {
        return _ARM;
    }
    int numConjuntos() const {
        return conjuntosDistintos;
    }
};
bool resuelveCaso() {

    // leemos la entrada
    int N, M, A;
    cin >> N >> M >> A;
    if (!cin)
        return false;

    GrafoValorado<int> g(N);
    int X, Y, C;
    for (int i = 0; i < M; i++) {
        cin >> X >> Y >> C;
        X--; Y--;
        g.ponArista({ X,Y,C });
    }

    ARM_Kruskal<int> armKruskal(g, A);

    cout << (armKruskal.costeARM() + A * armKruskal.numConjuntos()) << " " << armKruskal.numConjuntos() << "\n";
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
