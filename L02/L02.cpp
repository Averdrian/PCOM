#include <iostream>
#include <string>
#include <vector>
#include <queue>


struct medicine {

	medicine(std::string name, int frecuency, int pref) : name(name), frecuency(frecuency), next(frecuency), priority(pref) {};
	void ingest() { next += frecuency; }

	std::string name;
	int frecuency, next, priority;

};


class ord {
public:
	ord() {}

	bool operator()(const medicine &a, const medicine &b) const {
		if (a.next != b.next) return a.next > b.next;
		else return a.priority > b.priority;
	}

};




bool resuelveCaso() {
	int n, k;
	std::cin >> n >> k;

	std::priority_queue<medicine, std::vector<medicine>, ord> med;

	for (int i = 0; i < n; ++i) {
		std::string auxname;
		int auxfrec;
		std::cin >> auxname >> auxfrec;
		med.push({ auxname, auxfrec, i });
	}

	for (int i = 0; i < k; ++i) {
		medicine medAux = med.top();
		med.pop();
		std::cout << medAux.next << " " << medAux.name << "\n";
		medAux.ingest();
		med.push(medAux);
	}

	
	return true;
}




int main() {
	int nCasos;
	std::cin >> nCasos;
	for (int i = 0; i < nCasos; ++i) resuelveCaso();
}