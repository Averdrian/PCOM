#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cmath>

const int wheels = 4;
enum color {white, gray, black};

struct node {
	node(std::vector<int> stat, int dep) : state(stat), depth(dep){}
	std::vector<int> state;
	int depth;
};

int numb_comb(std::vector<int> const& comb) {
	int com = 0;
	for (int i = 0; i < comb.size(); ++i) {
		com += comb[i] * std::pow(10, comb.size() - i - 1);
	}
	return com;
}

void resuelveCaso() {

	std::vector<int> init(wheels);
	std::vector<int> target(wheels);

	for (int i = 0; i < wheels; ++i) std::cin >> init[i];
	for (int i = 0; i < wheels; ++i) std::cin >> target[i];

	int targ = numb_comb(target);

	std::vector<color>col(std::pow(10, wheels), white);

	int n_forbidden;
	std::cin >> n_forbidden;

	bool finded = false;

	for (int i = 0; i < n_forbidden; ++i) {
		std::vector<int> aux(wheels);
		for (int j = 0; j < wheels; ++j) std::cin >> aux[j];

		if (numb_comb(aux) == targ && numb_comb(init) != targ) {
			 std::cout << "-1\n";
			finded = true;
		}

		col[numb_comb(aux)] = black;
	}

	std::queue<node> queue;
	node initial{init, 0};

	
	if (numb_comb(init) == targ) {
			finded = true;
			if (col[numb_comb(init)] == black)  std::cout << "0\n";
			else  std::cout << "0\n";
	}
	
	col[numb_comb(initial.state)] = gray;
	queue.push(initial);

	while (!queue.empty() && !finded) {

		node exp = queue.front(); queue.pop();
		

		for (int i = 0; i < wheels; ++i) {

			std::vector<int> lf = exp.state, rg = exp.state;
			lf[i] = --lf[i] % 10;
			if (lf[i] < 0) lf[i] = 9;
			rg[i] = ++rg[i] % 10;
			if (rg[i] < 0) rg[i] = 9;
			
			int lfval = numb_comb(lf);
			int rgval = numb_comb(rg);

			
			
			if (col[lfval] == white) {
				if (lfval == targ) {
					 std::cout << exp.depth + 1 << "\n";
					finded = true;
				}
				col[lfval] = gray;
				queue.push({ lf, exp.depth + 1 });
			}
				

			if (col[rgval] == white) {
				if (rgval == targ) {
					 std::cout << exp.depth + 1 << "\n";
					finded = true;
				}
				col[rgval] = gray;
				queue.push({ rg, exp.depth + 1 });
			}

		}
		col[numb_comb(exp.state)] = black;
	}
	if (!finded)  std::cout << "-1\n";

	


}


int main() {
	int n_casos;
	std::cin >> n_casos;
	for (int i = 0; i < n_casos; ++i) 		resuelveCaso();
	return 0;
}

