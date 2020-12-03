#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <queue>

using lista_ady = std::vector<std::vector<int>>;


bool resuelveCaso() {

	
	int n_employees;
	std::cin >> n_employees;
	if (!std::cin) return false;
	lista_ady amigo(n_employees);
	for (int i = 0; i < n_employees; ++i) {

		int nfriends;
		std::cin >> nfriends;
		for (int j = 0; j < nfriends; ++j) {
			int fr;
			std::cin >> fr;
			amigo[i].push_back(fr);
		}


	}

	int n_consultas;
	std::cin >> n_consultas;
	for (int i = 0; i < n_consultas; ++i) {
		int ini;
		std::cin >> ini;

		std::vector<bool> visited(n_employees, false);
		std::queue<std::pair<int, int>> cola;
		visited[ini] = true;
		cola.push({ ini, 0 });
		
		int max = -1, piv = -1, count = 0,i_max = 0, depth;

		while (!cola.empty()) {



			depth = cola.front().second;
			int nodo = cola.front().first;
			cola.pop();
			if (depth > piv) {
				piv = depth;
				if (count > max) {

					max = count;
					i_max = depth;

				}
				count = 0;
			}

			for (int j = 0; j < amigo[nodo].size(); ++j) {


				if (!visited[amigo[nodo][j]]) {
					
					cola.push({ amigo[nodo][j], depth + 1 });
					visited[amigo[nodo][j]] = true;
					++count;

				}

			}


		}

		if (count > max) {

			max = count;
			i_max = depth;
			count = 1;

		}


		if (max == 0) std::cout << "0\n";
		else std::cout << max << " " << i_max << "\n";

	}



	return true;
}



int main() {
	while (resuelveCaso());
	return 0;
}