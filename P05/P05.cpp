#include <iostream>
#include <vector>
#include <queue>

using ii = std::pair<int, int>;


void resuelveCaso() {
	
	int n_filas, n_columnas;
	std::cin >> n_filas >> n_columnas;

	std::vector<std::vector<char>>tablero(n_filas, std::vector<char>(n_columnas));

	ii inicio, objetivo;

	for (auto col : tablero) {
		col = std::vector<char>(n_columnas);
	}

	std::vector<std::vector<bool>> visited(n_filas, std::vector<bool> (n_columnas, false));

	for (int i = 0; i < n_filas; ++i) {
		for (int j = 0; j < n_columnas; ++j) {
			std::cin >> tablero[i][j];
			if (tablero[i][j] == 'A') inicio = { i,j };
			else if (tablero[i][j] == 'B') objetivo = { i,j };
			else if (tablero[i][j] == 'Z') {
				visited[i][j] = true;
				bool ar1 = i > 0, ar2 = i > 1, ab1 = i < n_filas - 1, ab2 = i < n_filas - 2, dr1 = j < n_columnas - 1, dr2 = j < n_columnas - 2, iz1 = j > 0, iz2 = j > 1;
				if (ar1 && iz2) visited[i - 1][j - 2] = true;
				if (ar2 && iz1) visited[i - 2][j - 1] = true;
				if (ar1 && dr2) visited[i - 1][j + 2] = true;
				if (ar2 && dr1) visited[i - 2][j + 1] = true;
				if (ab1 && iz2) visited[i + 1][j - 2] = true;
				if (ab2 && iz1) visited[i + 2][j - 1] = true;
				if (ab1 && dr2) visited[i + 1][j + 2] = true;
				if (ab2 && dr1) visited[i + 2][j + 1] = true;
			}
		}
	}
	visited[objetivo.first][objetivo.second] = false;
	std::queue<std::pair<ii, int>> cola;
	cola.push({ inicio, 0 });
	bool finded = false;
	int d = -1;
	while (!cola.empty() && !finded) {

		std::pair<ii, int> aExp = cola.front(); cola.pop();

		if (aExp.first == objetivo) {
			finded = true;
			d = aExp.second;
		}

		int i = aExp.first.first, j = aExp.first.second, depth = aExp.second;
		visited[i][j] = true;
		bool ar = i > 0, ab = i < n_filas - 1, dr = j < n_columnas - 1, iz = j > 0;
		if (ar) {
			if(!visited[i - 1][j])cola.push({ {i - 1, j}, depth + 1 });
			if (dr && !visited[i - 1][j + 1]) cola.push({ {i - 1, j + 1}, depth + 1 });
			if (iz && !visited[i - 1][j - 1]) cola.push({ {i - 1,j - 1},depth + 1 });
		}
		if (ab) {
			if(!visited[i + 1][j]) cola.push({ {i + 1, j}, depth + 1 });
			if (dr && !visited[i + 1][j + 1]) cola.push({ {i + 1, j + 1}, depth + 1 });
			if (iz && !visited[i + 1][j - 1]) cola.push({ {i + 1,j - 1},depth + 1 });
		}
		if (dr && !visited[i][j + 1]) cola.push({ {i,j + 1}, depth + 1 });
		if (iz && !visited[i][j - 1]) cola.push({ {i, j - 1}, depth + 1 });
	}

	if (finded) std::cout << "Minimal possible length of a trip is " << d << "\n";
	else std::cout << "King Peter, you can't go now!\n";
}



int main() {
	int ncasos;
	std::cin >> ncasos;
	for (int i = 0; i < ncasos; ++i) resuelveCaso();
	return 0;
}