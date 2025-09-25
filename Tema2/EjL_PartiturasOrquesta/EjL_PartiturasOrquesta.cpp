/*@ <authors>
 *
 * MARP28 Nahia Iglesias Calvo
 * MARP40 Cristina Munyoz Munyoz
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <queue>
using namespace std;


/*@ <answer>

	Tenemos una cola de prioridad de maximos con N elementos (numero de instrumentos distintos) 
	que se ordenan dependiendo del peloton, numero de personas por partitura de cada instrumento.

	Cada instrumento tiene minimo una partitura que anyadimos al comienzo. Si quedan partituras
	por repartir, cogemos el elemento  mas prioritario (mayor peloton), se le da una partitura y
	volvemos a calcular el peloton.

	Complejidad temporal: O(P*log N), siendo P numero de partituras y N numero de instrumentos
	diferentes (Se explica con mas detalle abajo).

	Complejidad espacial: O(N), siendo N numero de elementos de la priority_queue.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

struct InfoInstrumento {
	int personasTotales; // numero de personas por instrumento
	int partituras; // partituras por instrumento
	int peloton; // numero de personas / numero de partituras
};

bool operator<(InfoInstrumento const& a, InfoInstrumento const& b) {
	return a.peloton < b.peloton;
}

bool resuelveCaso() {

	// leemos la entrada
	int P, N;
	cin >> P >> N;

	if (!cin)
		return false;

	// leer el resto del caso y resolverlo
	// Leer instrumentos
	priority_queue<InfoInstrumento> cola;

	// O(N*logN), siendo N el numero de instrumentos distintos
	for (int i = 0; i < N; ++i) {
		int numPersonas;
		cin >> numPersonas;
		cola.push({ numPersonas, 1, numPersonas });
	}

	// Resolver caso
	P -= N; // partituras restantes

	// Mienstras queden partituras por repartir
	while (P > 0) {

		// O(1)
		InfoInstrumento i = cola.top(); cola.pop();

		// Damos partitura
		i.partituras += 1;
		P--;

		// Calculo nuevo peloton
		int resto = i.personasTotales % i.partituras;
		i.peloton = i.personasTotales / i.partituras;

		// Si la division no da exacta
		if (resto > 0)
			i.peloton += 1;

		// O(P*log N), se hacen P inserciones en una cola de N elementos
		cola.push(i);
	}

	// Escribo solucion
	cout << cola.top().peloton << endl;

	return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("casos.txt");
	if (!in.is_open())
		cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
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
