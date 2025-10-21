/*@ <authors>
 *
 * MARP28 Nahia Iglesias Calvo
 * MARP40 Cristina Munoz Munoz
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#include "Digrafo.h"
/*@ <answer>

Se quiere saber si un programa termina siguiendo unas instrucciones que saltan de un vertice
a otro de un grafo dirigido.
Se realiza un dfs solo desde el vertice origen, con esto solo se van a visitar los vertices que esten en el camino
desde el origen hasta el ultimo que alcance este.
El grafo se crea con un vertice "fantasma" que se refiere al siguiente de la ultima instruccion.
Si no se alcanza nunca ese vertice, el programa no acaba nunca.
Si se alcanza pero hay algun ciclo en el grafo, el programa termina a veces.
Si se alcanza y no hay ciclos, acaba siempre.
Los ciclos solo se van a detectar si se visitan, porque solo se recorre el dfs una vez desde el origen.

 Siendo V = L+1 el numero de instrucciones (vertices) y
 A el numero de aristas del grafo, que en este caso cada vertice como maximo salen de el 2 aristas.
 Como es un grafo disperso y el numero de aristas es bajo, casi igual que el numero de vertices
 Coste en tiempo: O(V)

Coste en espacio: O(V + A)
 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

class DFSDirigido {

private:
    vector<bool> visit;     //visit[v] = ¿se ha alcanzado a v en el dfs?
    vector<bool> apilado;   //apilado[v] = ¿esta el vertice v en la pila?
    bool _hayCiclo;

    void dfs(Digrafo const& g, int v) {
        apilado[v] = true;
        visit[v] = true;

        for (int w : g.ady(v)) {
            //no paramos dfs aunque haya ciclo

            if (!visit[w]) {
                dfs(g, w);
            }
            else if (apilado[w]) {
                _hayCiclo = true;
            }
        }
        apilado[v] = false;
    }

public:
    DFSDirigido(Digrafo const& g) : visit(g.V(), false), apilado(g.V(), false), _hayCiclo(false) {
        //solo hacemos dfs desde el origen
        //si no hay un ciclo en el camino desde el origen, aunque haya uno en el grafo, no lo vamos a visitar ni detectar 
        dfs(g, 0);
    }

    //devuelve si hay un ciclo en el grafo
    bool hayCiclo() const {
        return _hayCiclo;
    }

    //devuelve si un vertice ha sido alcanzado
    bool alcanzable(int v) const {
        return visit[v];
    }
};


bool resuelveCaso() {

    // leemos la entrada
    int L;
    cin >> L;
    if (!cin)
        return false;

    // leer el resto del caso y resolverlo
    Digrafo g(L + 1);

    for (int v = 0; v < L; v++) {

        char c;
        cin >> c;

        if (c == 'A' || c == 'C') {
            g.ponArista(v, v + 1);
        }

        if (c == 'J' || c == 'C') {
            int N; cin >> N; N--;
            g.ponArista(v, N);
        }
    }

    DFSDirigido sol(g);

    //si no se alcanza al vertice detras de la ultima instruccion no acaba nunca
    if (!sol.alcanzable(L)) {

        cout << "NUNCA\n";
    }
    //si es alcanzable
    else {

        // y no hay ciclo el programa termina siempre
        if (!sol.hayCiclo()) {
            cout << "SIEMPRE\n";
        }
        // y tiene algun ciclo el programa termina a veces
        else {
            cout << "A VECES\n";
        }
    }
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