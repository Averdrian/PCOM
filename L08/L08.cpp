#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>


const int INF = 2000000;

using ii = std::pair<int, int>;
using vii = std::vector<ii>;
using lista_adjuntos = std::vector<vii>;

void dijkstra(lista_adjuntos const& adjList, int const& ini, std::vector<int> & dist) {

	std::priority_queue<ii, vii, std::greater<ii>> pq;
	dist.assign(adjList.size(), INF);
	dist[ini] = 0;
	pq.push({ 0,ini });

	while (!pq.empty()) {
		ii front = pq.top();
		pq.pop();
		int d = front.first, u = front.second;
		if (d > dist[u]) continue;

		for (auto a : adjList[u]) {
			if (dist[u] + a.second < dist[a.first]) {
				dist[a.first] = dist[u] + a.second;
				pq.push({ dist[a.first], a.first });
			}
		}

	}


}

bool resuelveCaso(int const& n_caso) {
	
	lista_adjuntos adjList;
	int ini, fin;
	std::cin >> ini >> fin;
	if (ini == fin && ini == 0) return false;;
	while (ini != 0 && fin != 0) {
		
		if (ini + 1 > adjList.size() || fin + 1 > adjList.size()) {
			int hasta = std::max(ini, fin);
			while (hasta + 1 > adjList.size()) {
				adjList.push_back({});
			}
		}

		adjList[ini].push_back({ fin, 1 });

		

		

		std::cin >> ini >> fin;
	}

	int n_vertices = 0;
	std::vector<int> distancias;
	int total = 0;
	for (int i = 0; i < adjList.size(); ++i) {
		if (adjList[i].size() > 0) {
			++n_vertices;
			dijkstra(adjList, i, distancias);
			
			for (int j = 0; j < distancias.size(); ++j) {
				if (distancias[j] != 0 && distancias[j] != INF)
					total += distancias[j];
			}

		}
	}
	int n_caminos = n_vertices * (n_vertices - 1);

	double resul = (double)total / (double)n_caminos;

	std::cout << "Case " << n_caso << ": average length between pages = " << std::fixed << std::setprecision(3) << resul << " clicks\n";

	return true;
}


int main() {
	for (int i = 1; resuelveCaso(i); ++i);
	return 0;
}