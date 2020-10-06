#include <iostream>
#include <vector>
#include <algorithm>

#define n_dardos first
#define valor second

bool resuelveCaso() {

	int punt, seg;
	std::cin >> punt >> seg;

	if (!std::cin) return false;

	std::vector<int> sectores;

	for (int i = 0; i < seg; ++i) {
		int aux;
		std::cin >> aux;
		sectores.push_back(aux);
	}


	std::vector<std::pair<int, int>> dardos;
	dardos.push_back({ 0,0 });

	for (int i = 1; i <= punt; ++i) {

		dardos.push_back({ -1,-1 });
		for (int j = sectores.size() - 1; j >= 0; --j) {
			int diff = i - sectores[j];

			if (diff >= 0 && dardos[diff].n_dardos != -1 && (dardos[i].n_dardos == -1 || dardos[i].n_dardos > dardos[diff].n_dardos + 1))
				dardos[i] = { dardos[diff].n_dardos + 1, sectores[j] };
		}

	}

	if (dardos[punt].n_dardos == -1) std::cout << "Imposible\n";
	else {
		std::cout << dardos[punt].n_dardos << ":";
		int punt_res = punt;
		
		while (punt_res > 0) {

			std::cout << " " << dardos[punt_res].valor;
			punt_res -= dardos[punt_res].valor;

		}
		std::cout << "\n";
	}

	return true;
}



int main() {
	while (resuelveCaso());
}