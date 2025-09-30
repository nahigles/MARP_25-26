
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

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


struct Registro {
	int momento;
	int id;
	int periodo;
};

bool operator>(Registro const& a, Registro const& b) {
	return b.momento < a.momento || (a.momento == b.momento && b.id < a.id);
}
bool resuelveCaso() {
	// leer los datos de la entrada
	int n;
	cin >> n;

	if (n == 0)
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	
	priority_queue<Registro> cola;

	for (int i = 0; i < n; i++) {
		int idU, p;
		cin >> idU >> p;
		cola.push({ p,idU,p });
	}

	// escribir la solución
	int envios;
	cin >> envios;

	while (envios--) {
		auto e = cola.top(); cola.pop();
		cout << e.id << '\n';
		e.momento += e.periodo;
		cola.push(e);
	}

	cout << "---\n";

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
