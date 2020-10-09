#include <iostream>
#include <vector>


void resuelveCaso() {

	int tam_caja;
	std::cin >> tam_caja;
	std::vector<long long int> comb(tam_caja);
	std::vector<long long int> un_p(tam_caja);
	std::vector<long long int> no_p(tam_caja);
	std::vector<long long int> dos_p(tam_caja);

	comb[0] = 1;
	un_p[0] = 0;
	dos_p[0] = 1;
	no_p[0] = 0;



	for (int i = 1; i < tam_caja; ++i) {
		un_p[i] = dos_p[i-1] * 2;
		no_p[i] = un_p[i - 1] + dos_p[i-1] * 2;
		dos_p[i] = comb[i - 1];
		comb[i] = un_p[i] + no_p[i] + dos_p[i];
	}

	std::cout << comb[comb.size() - 1] << "\n";



}


int main() {
	int n_casos;
	std::cin >> n_casos;
	for (int i = 0; i < n_casos; ++i) resuelveCaso();
	return 0;
}