#include <iostream>
#include <vector>
#include <algorithm>


bool resuelveCaso() {
	int n, m;
	std::cin >> n >> m;
	if (n == 0 && m == 0) return false;

	std::vector<int> head_tall;
	std::vector<int> knight_tall;

	for (int i = 0; i < n; ++i) {
		int aux;
		std::cin >> aux;
		head_tall.push_back(aux);
	}

	for (int i = 0; i < m; ++i) {
		int aux;
		std::cin >> aux;
		knight_tall.push_back(aux);
	}

	
	std::sort(knight_tall.begin(), knight_tall.end());
	std::sort(head_tall.begin(), head_tall.end());

	int it = -1, chopped = 0, coins = 0;
	


	while (chopped < head_tall.size() && ++it < knight_tall.size()) {

		if (knight_tall[it] >= head_tall[chopped]) {
			++chopped;
			coins += knight_tall[it];
		}

	}

	if (chopped == head_tall.size()) std::cout << coins << "\n";
	else std::cout << "Loowater is doomed!\n";
	

	return true;
}


int main() {
	while (resuelveCaso());
	return 0;
}

