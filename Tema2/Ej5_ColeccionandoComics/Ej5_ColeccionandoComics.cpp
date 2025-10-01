
/*@ <authors>
 *
 * MARP28 Nahia Iglesias Calvo
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

//#include "..."  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct InfoPila {
	int menor;
	stack<int> pilaLibros;
};

bool operator<(InfoPila const& a, InfoPila const& b) {

	return  b.pilaLibros.size() == 0 || a.pilaLibros.size() > 0 && b.pilaLibros.size() > 0 && a.pilaLibros.top() < b.pilaLibros.top();
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int n;
	cin >> n; // numero de pilas libros

	if (!std::cin)  // fin de la entrada
		return false;

	vector<InfoPila> infoPilas = vector<InfoPila>(n);

	for (int i = 0; i < n; i++) {
		int k;
		cin >> k;

		for (int j = 0; j < k; j++) {
			int e;
			cin >> e;

			// Miro si es el menor q tengo guardado y sino lo actualizo
			if (j == 0) {
				// Meto el primer elem
				infoPilas[i].menor = e;
			}
			else {
				infoPilas[i].menor = min(infoPilas[i].menor, e);
			}

			infoPilas[i].pilaLibros.push(e);
		}
	}

	// Anyado a una cola de prioridad las pilas de libros
	int menorTotal;
	priority_queue<InfoPila> pilasQueue;
	//priority_queue<InfoPila, greater<InfoPila>> pilasQueue; // Cola prioridad de minimos
	for (int i = 0; i < infoPilas.size(); i++) {
		if (i == 0)
			menorTotal = infoPilas[i].menor;
		else
			menorTotal = min(menorTotal, infoPilas[i].menor);

		pilasQueue.push(infoPilas[i]);
	}

	// resolver el caso posiblemente llamando a otras funciones
	int i = 1;
	while (/*pilasQueue.top().pilaLibros.size() > 0 &&*/ pilasQueue.top().pilaLibros.top() != menorTotal) {
		// Quito el eelemento de arriba de la pila qu toque
		auto p = pilasQueue.top();
		p.pilaLibros.pop();

		if (p.pilaLibros.empty()) {
			pilasQueue.pop(); // Quita el ultimo que deberia ser el que este vacio
			// segun el operador < que he programado
		}

		cout << i << endl;
		i++;
	}
	// Cuando sale del bucle ya ha contado donde se tiene que colocar


	// escribir la solución
	cout << i << endl;

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
