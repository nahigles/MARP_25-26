
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

Para calcular el minimo esfuerzo que debe relizar para sumar los numeros, he utilizado una cola
de prioridad de minimos.
Voy leyendo e insertando los numeros de una en uno para que se ordenen por prioridad y una vez
anyadidos todos, voy sumando los dos primeros y guardando la suma en un acumulador llamado "esfuerzo".
Esa suma tambien se anyade en la cola de prioridades para que se coloque segun su prioridad y se
vuelve a sumar cuando toca. Ya que lo que nos interesa es la suma del esfuerzo minimo.

Complejidad en tiempo: O(N*log n), siendo N la cantidad de numeros a sumar y n el numero de elementos
que contiene la cola de prioridades.

Complejidad en espacio: O(N), la cola nunca contiene mas que la cantidad de numeros a sumar.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada
	int N;
	cin >> N;

	if (N == 0)
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	priority_queue<int64_t, vector<int64_t>, greater<int64_t>> nums; // Cola de minimos

	int e;
	for (int i = 0; i < N; i++) { // O(N)
		// Voy metiendo los numeros q leo
		cin >> e;
		nums.push(e); // log(n) siendo n el numero de elementos de la cola de prioridad
	}

	int64_t esfuerzo = 0;
	int64_t auxEsfuerzo;
	while (nums.size() > 1) {// O(N)

		// Sumo los dos mas prioritarios y los saco
		auxEsfuerzo = nums.top();
		nums.pop(); // log(n)
		auxEsfuerzo += nums.top();
		nums.pop(); // log (n)

		// Anyado la suma de los dos mas prioritarios
		nums.push(auxEsfuerzo); // log(n)

		// Me guardo la suma
		esfuerzo += auxEsfuerzo;
	}

	// escribir la solución
	cout << esfuerzo << endl;

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
