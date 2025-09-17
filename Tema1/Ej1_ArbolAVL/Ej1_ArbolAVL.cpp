
/*@ <authors>
 *
 * Nahia Iglesias Calvo
 * MARP28
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#include "bintree.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

template <typename T>
bool isAVL(const BinTree<T>& t, T& minT, T& maxT) {
	if (t.empty()) {
		return true;
	}
	else {
		T minLeft; T maxLeft;
		T minRight; T maxRight;

		bool isAVLLeft = isAVL(t.left(), minLeft, maxLeft);
		bool isAVLRight = isAVL(t.right(), minRight, maxRight);

		minT = min(minLeft, minRight, t.root());
		maxT = max(maxLeft, maxRight, t.root());

		return isAVLLeft && isAVLRight && maxLeft < t.root() && t.root() < minRight ;
	}
}

template <typename T>
bool resuelveCaso() {
	// leer los datos de la entrada
	char mode;
	cin >> mode;

	if (mode == 'N') {

		BinTree<int> t = read_tree(cin);
	}
	else if (mode == 'P') {

		BinTree<string> t = read_tree(cin);
	}

	if (!std::cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	T min = T();
	T max = T();
	bool isAVLTree = isAVL(t, min, max);

	// escribir la solución


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
