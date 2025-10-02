/*@ <authors>
 *
 * MARP28 Nahia Iglesias Calvo
 * MARP40 Cristina Munoz Munoz
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

#include "IndexPQ.h"
/*@ <answer>

 Sustituye este párrafo por un comentario general sobre la solución,
 explicando cómo se resuelve el problema y cuál es el coste de la solución,
 en función del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

bool resuelveCaso() {

	// leemos la entrada
	int D, C, N;
	cin >> D >> C >> N;
	if (!cin) return false;

	// leer el resto del caso y resolverlo
	int ultimoMin = 0;
	IndexPQ<int, greater<int>> canales(C+1);
	unordered_map<int, int> minutosPrime; // <Canal, Minutos de PrimeTime>

	for (int i = 1; i <= C; i++) {
		int audiencia;
		cin >> audiencia;

		canales.update(i, audiencia);
	}

	for (int i = 0; i < N; i++) {
		int min;
		cin >> min;

		auto canal_prime = canales.top();
		int tiempo = min - ultimoMin;

		minutosPrime[canal_prime.elem] += tiempo;

		int canal, audiencia;
		cin >> canal;

		while (canal != -1) {
			cin >> audiencia;

			canales.update(canal, audiencia);

			cin >> canal;
		}

		ultimoMin = min;
	}

	if (ultimoMin != D) {
		auto canal_prime = canales.top();
		int tiempo = D - ultimoMin;

		minutosPrime[canal_prime.elem] += tiempo;
	}

	vector<pair<int, int>> v_minutosPrime(minutosPrime.begin(), minutosPrime.end());

	std::sort(v_minutosPrime.begin(), v_minutosPrime.end(),
		[](const auto& a, const auto& b) {
			if (a.second == b.second) {
				return a.first < b.first;
			}
			return b.second < a.second;
		});

	for (const auto& par : v_minutosPrime) {

		cout << par.first << " " << par.second << "\n";
	}

	cout << "---\n";

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
