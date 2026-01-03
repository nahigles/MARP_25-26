
/*@ <authors>
 *
 * MARPV28 Nahia Iglesias Calvo
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

/*@ <answer>

Para calcular la caja a la que le toca ir a Ismael, he utilizado una cola de prioridad de minimos
de "Cliente". Es un struct que tiene la informacion de la caja en la que esta el cliente y los segundos
que tarda en ella.
Para resolver el problema, primero anyado los clientes que entre en las cajas libres, si no se han llegado
escribo la caja que le toca a Ismael.
En caso de que se hayan llenado voy sacando el cliente mas prioritario y metiendo el siguiente hasta que me
quedo sin clientes que meter, entonces ya sabemos la caja que le toca a Isamael.
Voy sumando los segundos que llevan y acumulandolos para que los nuevos clientes al meterlos en la cola
tengan los segundos actualizados.

Por lo tanto:
Complejidad en tiempo: O(C*log n), siendo C la cantidad de clientes y n el numero de elementos
que contiene la cola de prioridades.

Complejidad en espacio: O(N), la cola nunca contiene mas que la cantidad de cajas. (N: numero de cajas)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Cliente {
	int caja;
	int segundos;
};

bool operator<(Cliente const& a, Cliente const& b) {
	return b.segundos < a.segundos ||
		(a.segundos == b.segundos && b.caja < a.caja);
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N;
	cin >> N; // numemro de cajas

	if (N == 0)
		return false;

	int C;
	cin >> C; // Numero de clientes

	priority_queue<Cliente> clientesEnCaja; // Cola de clientes que estan en las cajas

	// Lleno las cajas que hay
	int segs;
	int i = 0;
	while (i < C && clientesEnCaja.size() < N) { //El mayor entre O(N*log n) y  O(C*log n), siendo N el numero de cajas y C de clientes
		cin >> segs;
		clientesEnCaja.push({ i + 1,segs }); // O(log n), siendo n el num de elementos de la cola
		i++;
	}

	// Si no ha llegado al final
	if (i < N) {
		cout << (i+1) << endl;
	}
	else {
		// Mienstras sigan quedando clientes
		int segAc = 0;
		while (i < C) { // O(C)

			// Saco el mas prioritario (El q menos segundos tenga)
			auto cPriori = clientesEnCaja.top(); // O(1)
			clientesEnCaja.pop(); // O(log n)

			// Leo siguientes segundos del
			cin >> segs;
			segAc += segs;

			// Anyado siguiente cliente
			clientesEnCaja.push({ cPriori.caja,segAc }); // O(log n)
		}

		// Saco el mas prioritario y ya es la solucion
		cout << clientesEnCaja.top().caja << "\n";
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
