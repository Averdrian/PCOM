#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using ii = std::pair<int, int>;
using matriz_ady = std::vector<std::vector<int>>;

void bfs(int const &s, int const& t, matriz_ady&matrix, std::vector<int> &parent, std::vector<bool> &visited) {
	visited = std::vector<bool>(matrix.size(), false);
	std::queue<int> q;
	q.push(s);
	visited[s] = true;
	while (!q.empty() && !visited[t]) {
		int u = q.front(); q.pop();
		for (int i = 0; i < matrix[u].size(); ++i) {
			if (!visited[i] && matrix[u][i] > 0) {
				visited[i] = true;
				parent[i] = u;
				q.push(i);
			}
		}
	}
}

int sendFlow(int const& s, int const& t, matriz_ady &matrix, std::vector<bool> &visited) {
	matriz_ady orig = matrix;
	std::vector<int> parent(matrix.size(), -1);
	bfs(s, t, matrix, parent, visited);
	if (!visited[t]) return 0;
	int flow = 2000000;
	int v = t;
	while (v != s) {
		flow = std::min(matrix[parent[v]][v], flow);
		v = parent[v];
	}
	v = t;
	while (v != s) {
		matrix[parent[v]][v] -= flow;
		matrix[v][parent[v]] += flow;
		v = parent[v];
	}

	return flow;
}

bool resuelveCaso(int const& n_caso) {

	int n;
	std::cin >> n;
	if (n ==  0) return false;

	int ini, fin, m;
	std::cin >> ini >> fin >> m;
	matriz_ady matrix(n, std::vector<int>(n, 0));

	for (int x = 0; x < m; ++x) {
		int i, j, cap;
		std::cin >> i >> j >> cap;
		matrix[i - 1][j - 1] += cap;
		matrix[j - 1][i - 1] += cap;
	}
	matriz_ady original = matrix;
	std::vector<int> parent(n, -1);
	std::vector<bool> visited(matrix.size(), false);
	int flow, ret = 0;
	do {
		flow = sendFlow(ini-1, fin-1, matrix, visited);
		ret += flow;
	} while (flow > 0);
	std::cout << "Network " << n_caso << "\n";
	std::cout << "The bandwidth is " << ret << ".\n";
	
	return true;
}




int main() {
	int i = 0;
	while (resuelveCaso(++i));
	return 0;
}