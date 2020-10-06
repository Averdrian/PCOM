#include <iostream>
#include <vector>
#include <map>

bool resuelveCaso() {
	
	

	//numero de datos y consultas
	int m, n;
	std::cin >> n >> m;
	
	if (!std::cin) return false;

	//introducimos en un mapa los numeros como claves y sus valores las posiciones en las que aparecen
	std::map<int, std::vector<int>> v;	
	for (int i = 0; i < n; ++i) {
		int aux;
		std::cin >> aux;
		v[aux].push_back(i + 1);
	}

	//realiza las consultas
	for (int i = 0; i < m; ++i) {
		int k, x;
		std::cin >> k >> x;

		//se consulta si la posicion consultada esta en los valores de su clave
		if (v.find(x) == v.end() || v[x].size() < k)  std::cout << "0\n";
		else std::cout << v[x][k - 1] << "\n";


	}
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}


