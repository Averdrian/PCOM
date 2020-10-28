#include <iostream>
#include <vector>

enum color {rojo, azul, descoloreado};

using matriz_adyacencia = std::vector<std::vector<bool>>;
using ii = std::pair<int, int>;


bool resuelveCaso() {
	int n_nodes, n_edges;
	std::cin >> n_nodes;

	if (n_nodes == 0) return false;

	matriz_adyacencia matriz(n_nodes);
	for (int i = 0; i < matriz.size(); ++i)
		matriz[i] = std::vector<bool>(n_nodes, false);

	std::cin >> n_edges;
	for (int i = 0; i < n_edges; ++i) {
		ii frontera;
		std::cin >> frontera.first >> frontera.second;
		matriz[frontera.first][frontera.second] = true;
		matriz[frontera.second][frontera.first] = true;
	}

	std::vector<color> colores(n_nodes, descoloreado);
	colores[0] = rojo;
	bool bicoloreable = true;

	std::vector<int> next_fil(1,0);
	while (!next_fil.empty() && bicoloreable) {
		int i = next_fil[next_fil.size() - 1];
		next_fil.pop_back();

		for (int j = 0; j < n_nodes; ++j) {

			if (matriz[i][j]) {

				if (colores[i] == colores[j]) bicoloreable = false;
				else if (colores[j] == descoloreado) {
					colores[j] = (colores[i] == rojo) ? azul : rojo;
					next_fil.push_back(j);
				}

			}


		}



	}

	if (!bicoloreable) std::cout << "NOT ";
	std::cout << "BICOLORABLE.\n";

	return true;

}

int main() {
	while (resuelveCaso());
	return 0;
}