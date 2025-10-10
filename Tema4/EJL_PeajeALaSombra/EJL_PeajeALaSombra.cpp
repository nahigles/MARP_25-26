/*@ <authors>
 *
 * MARP28 Nahia Iglesias Calvo
 * MARP40 Cristina Munoz Munoz
 *
 *@ </authors> */

#include <iostream>
#include <algorithm>
#include <fstream>
#include <queue>
#include "Grafo.h"
#include "vector"
#include <climits>

using namespace std;

/*@ <answer>

Queremos encontrar el camino que minimice el gasto desde la casa de Alex, la casa de Lucas y el trabajo.
Con un recorrido en anchura, guardamos la distancia desde cada uno de los tres vertices al resto de vertices de la ciudad.
Despues, buscamos el mejor camino, que consiste en encontrar la suma mas pequenya desde los tres vertices a un punto en comun.

Siendo V el numero de vertices y A el numero de aristas del grafo
Coste en tiempo: O(V + A),  el recorrido en anchura encuentra caminos mas cortos a todos los vertices conectados al origen
Coste en espacio: O(V + A)
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

class CaminoMasCorto {

private:
    vector<bool> visit;         //vertices visitados
    vector<int> dist;           //distancia a un vertice desde el origen
    int s;                      //vertice origen

    //recorrido en anchura
    void bfs(Grafo const& g) {
        queue<int>q;
        visit[s] = true;
        dist[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int w : g.ady(v)) {
                if (!visit[w]) {
                    dist[w] = dist[v] + 1;
                    visit[w] = true;
                    q.push(w);
                }
            }
        }
    }
public:
    CaminoMasCorto(Grafo const& g, int s) : visit(g.V(), false), dist(g.V()), s(s) {

        bfs(g);
    }

    //distancia entre el origen y v
    int distancia(int v) const {
        return dist[v];
    }
};


bool resuelveCaso() {

    // leemos la entrada
    int N, C, A, L, T;
    cin >> N >> C >> A >> L >> T;
    if (!cin)
        return false;

    Grafo g(N);

    for (int i = 0; i < C; i++) {
        int v, w;
        cin >> v >> w;
        v--; w--;
        g.ponArista(v, w);
    }

    CaminoMasCorto caminoAlex(g, A - 1);
    CaminoMasCorto caminoLucas(g, L - 1);
    CaminoMasCorto caminoTrabajo(g, T - 1);

    int mejorCamino = INT_MAX;

    for (int i = 0; i < N; i++) {

        int total = caminoAlex.distancia(i) + caminoLucas.distancia(i) + caminoTrabajo.distancia(i);

        if (total < mejorCamino) mejorCamino = total;
    }
    // leer el resto del caso y resolverlo
    cout << mejorCamino << "\n";

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
#endif // !DOMJUDGE

    // Resolvemos
    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
#endif
    return 0;
}
