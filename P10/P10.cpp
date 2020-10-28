#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

struct terna {
	terna(){}
	terna(int const& f, int const&s, int const& t) : first(f), second(s), third(t) {}
	int first;
	int second;
	int third;
};

using state = std::pair<int, terna>;

bool operator<(terna const&a, terna const&b) {
	return a.first != b.first ? a.first < b.first : a.second != b.second ? a.second < b.second : a.third < b.third;
}

class ord {
public:
	ord() {}
	bool operator()(state const& a, state const& b) const {
		return a > b;
	}
};

void resuelveCaso() {
	terna capacidad;
	int obj;
	std::cin >> capacidad.first >> capacidad.second >> capacidad.third >> obj;
	
	std::priority_queue<state, std::vector<state>, ord> cola;
	
	cola.push({ 0, {0,0,capacidad.third} });
	
	std::map<terna,bool> explored;
	
	std::pair<int,int> best = { 0, capacidad.third < obj ? capacidad.third : 0 };
	bool finded = false;
	while (!cola.empty() && !finded) {
		
		state aExp = cola.top(); cola.pop();

		if (explored.find(aExp.second) != explored.end()) continue;
		explored[aExp.second] = true;
		terna jarr = aExp.second;

		//Encontrada solucion
		if (jarr.first == obj || jarr.second == obj || jarr.third == obj) {
			best = { obj, aExp.first };
			finded = true;
		}
		else {
			if (jarr.first > best.first && jarr.first < obj) best = { jarr.first, aExp.first };
			if (jarr.second > best.first && jarr.second < obj) best = { jarr.second, aExp.first };
			if (jarr.third > best.first && jarr.third < obj) best = { jarr.third, aExp.first };
		}

		int vertidos;

		if (jarr.first > 0) {
			if (jarr.second < capacidad.second) {
				vertidos = std::min(jarr.first, capacidad.second - jarr.second);
				cola.push({ aExp.first + vertidos, {jarr.first - vertidos, jarr.second + vertidos, jarr.third} });
			}
			if (jarr.third < capacidad.third) {
				vertidos = std::min(jarr.first, capacidad.third - jarr.third);
				cola.push({ aExp.first + vertidos, {jarr.first - vertidos, jarr.second, jarr.third + vertidos} });
			}
		}

		if (jarr.second > 0) {
			if (jarr.first < capacidad.first) {
				vertidos = std::min(jarr.second, capacidad.first - jarr.first);
				cola.push({ aExp.first + vertidos, {jarr.first + vertidos, jarr.second - vertidos, jarr.third} });
			}
			if (jarr.third < capacidad.third) {
				vertidos = std::min(jarr.second, capacidad.third - jarr.third);
				cola.push({ aExp.first + vertidos, {jarr.first, jarr.second - vertidos, jarr.third + vertidos} });
			}
		}
		
		if (jarr.third > 0) {
			if (jarr.first < capacidad.first) {
				vertidos = std::min(jarr.third, capacidad.first - jarr.first);
				cola.push({ aExp.first + vertidos, {jarr.first + vertidos, jarr.second, jarr.third - vertidos} });
			}
			if (jarr.second < capacidad.second) {
				vertidos = std::min(jarr.third, capacidad.second - jarr.second);
				cola.push({ aExp.first + vertidos, {jarr.first, jarr.second + vertidos, jarr.third - vertidos} });
			}
		}
		
	}
	
	std::cout << best.second << " " << best.first << "\n";

}


int main() {
	int ncasos;
	std::cin >> ncasos;
	for (int i = 0; i < ncasos; ++i) resuelveCaso();
	return 0;
}