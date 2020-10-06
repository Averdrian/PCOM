#include <iostream>
#include <vector>
#include <algorithm>


#define ini first
#define fin second

class ord {
public:
	ord(){}
	
	bool operator()(std::pair<int, int> a, std::pair<int, int> b) {
		return a.fin > b.fin; //not sure
	}



};



bool resuelveCaso() {

	int C, F, N;

	std::cin >> C >> F >> N;
	//ya que F es estrictamente mayor que C, se terminara con F = C
	if (F == C) return false;

	std::vector<std::pair<int, int>> trabajos;


	for (int i = 0; i < N; ++i) {
		int in, fi;
		std::cin >> in >> fi;
		trabajos.push_back({ in,fi });
	}
	std::sort(trabajos.begin(), trabajos.end(), ord());
	

	int end = F;

	int n_sel = 0;

	bool valid = true;

	int it = 0;

	while (end > C && valid) {
		
		int candidato = it;
		int mejor = -1;

		while (candidato < trabajos.size() && trabajos[candidato].fin >= end) {
			if (mejor == -1 || trabajos[candidato].ini < trabajos[mejor].ini) mejor = candidato;
			++candidato;
		}
		
		if (mejor == -1) valid = false;
		else {
			end = trabajos[mejor].ini;
			it = mejor+1;
			++n_sel;
		}
		
		
	}
	if (!valid) std::cout << "Imposible\n";
	else std::cout << n_sel << "\n";


	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}