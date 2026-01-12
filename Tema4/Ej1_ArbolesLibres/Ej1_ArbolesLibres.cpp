
/*@ <authors>
 *
 * MARP28 Nahia Iglesias Calvo
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "Grafo.h"

/*@ <answer>

 Complejidad en tiempo: O(V+A)
 Complejidad en espacio: O(V+A)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
class CaminosDFS {
private:
	std::vector<bool> visit; // visit[v] = ¿hay camino de s a v?
	int s; // vértice origen
	void dfs(Grafo const& G, int v) {
		visit[v] = true;
		for (int w : G.ady(v)) {
			if (!visit[w]) {
				dfs(G, w);
			}
		}
	}

public:
	CaminosDFS(Grafo const& g, int s) : visit(g.V(), false), s(s) {
		dfs(g, s);
	}
	// ¿hay camino del origen a v?
	bool hayCamino(int v) const {
		return visit[v];
	}

	bool esConexo() const {
		// Si todos los vertices tienen camino desde el origen
		bool conexo = true;
		int i = 0;
		while (i < visit.size() && conexo) { // O(V)
			conexo = hayCamino(i); // O(1)
			i++;
		}
		return conexo;
	}
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int V, A;
	cin >> V >> A;

	if (!std::cin)  // fin de la entrada
		return false;

	Grafo g(V);

	for (int i = 0; i < A; i++) { // O(A)
		int a, b;
		cin >> a >> b;
		g.ponArista(a, b); //O(1)
	}

	// resolver el caso posiblemente llamando a otras funciones
	if (A != (V - 1)) {
		cout << "NO\n";
	}
	else {
		// escribir la solución
		CaminosDFS arbolLibre(g, 0);
		cout << (arbolLibre.esConexo() ? "SI\n" : "NO\n"); // O(V)
	}


	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	if (!in.is_open())
		std::cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout << "Pulsa Intro para salir..." << std::flush;
	std::cin.get();
#endif
	return 0;
}