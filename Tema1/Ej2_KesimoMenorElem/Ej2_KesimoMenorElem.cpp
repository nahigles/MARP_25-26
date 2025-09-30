
/*@ <authors>
 *
 * MARPV28 Nahia Iglesias Calvo
 * 
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <ostream>
#include <exception>
using namespace std;

#include "TreeSet_AVL.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada
	int numElems;
	cin >> numElems;

	if (numElems == 0)
		return false;

	// Inserto elementos en el conjunto
	Set<int> set;
	for (int i = 0; i < numElems; i++) {
		int e;
		cin >> e;
		set.insert(e);
	}

	// Elementos a consultar
	int numConsultas;
	cin >> numConsultas;

	// resolver el caso posiblemente llamando a otras funciones
	for (int i = 0; i < numConsultas; i++) {
		int k;
		cin >> k;

		try
		{
			cout << set.kesimo(k) << endl;

		}
		catch (const std::exception& e)
		{
			cout << "??" << endl;
		}

	}

	// escribir la solución
	cout << "---" << endl;

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
