
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
struct TreeInfo {
	bool isAVL;
	int altura;
	T min;
	T max;
};

// Complejidad lineal en n, siendo n el numero de nodos del arbol. Tiene que recorrer todo el arbol
template <typename T>
TreeInfo<T> isAVL(const BinTree<T>& t) {

	TreeInfo<T> info;

	if (t.empty()) {
		info.isAVL = true;
		info.altura = 0;
		info.min = T();
		info.max = T();
	}
	else {
		TreeInfo<T> leftI = isAVL(t.left());
		TreeInfo<T> rightI = isAVL(t.right());

		info.isAVL = leftI.isAVL && rightI.isAVL && (abs(leftI.altura - rightI.altura) < 2) && (t.left().empty() || leftI.max < t.root()) && (t.right().empty() || t.root() < rightI.min);
		info.altura = max(leftI.altura, rightI.altura) + 1;

		if (t.right().empty() && t.left().empty()) {
			info.min = t.root();
			info.max = t.root();
		}
		else if (t.right().empty()) {
			info.min = min(t.root(), leftI.min);
			info.max = max(t.root(),leftI.max);
		}
		else if (t.left().empty()) {
			info.min = min(t.root(), rightI.min);
			info.max = max(t.root(), rightI.max);
		}
		else {
			info.min = min(t.root(), min(leftI.min, rightI.min));
			info.max = max(t.root(), max(leftI.max, rightI.max));
		}
	}

	return info;
}


bool resuelveCaso() {
	// leer los datos de la entrada
	char mode;
	cin >> mode;

	if (!std::cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	bool isAVLTree;

	if (mode == 'N') {
		BinTree<int> t = read_tree<int>(cin);
		TreeInfo<int> info = isAVL(t);
		isAVLTree = info.isAVL;
	}
	else if (mode == 'P') {
		BinTree<string> t = read_tree<string>(cin);
		TreeInfo<string> info = isAVL(t);
		isAVLTree = info.isAVL;
	}

	// escribir la solución
	cout << (isAVLTree ? "SI" : "NO") << endl;

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
