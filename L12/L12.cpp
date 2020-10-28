#include <iostream>
#include <vector>


using lista_adj = std::vector<std::vector<int>>;

enum color {white, gray, black};

void dfs(int const& in, lista_adj const& l, std::vector<color> &col, bool &alw) {

	col[in] = gray;
	for (int i = 0; i < l[in].size(); ++i) {
		if(col[l[in][i]] == white)
			dfs(l[in][i], l, col, alw);
		else if(col[l[in][i]] == gray) alw = false;
	}
	col[in] = black;

}

void resuelveCaso() {
	int nlines;
	std::cin >> nlines;
	bool always = true;
	lista_adj adj(nlines + 1);
	std::vector<color> col(nlines + 1, white);
	for (int i = 0; i < nlines; ++i) {
		char op;
		std::cin >> op;
		if (op == 'A' || op == 'C') {
			adj[i].push_back(i + 1);
		}
		if (op == 'C' || op == 'J') {
			int jp;
			std::cin >> jp;
			adj[i].push_back(jp - 1);
		}
	}
	dfs(0, adj, col, always);
	if (col[nlines] == white) std::cout << "NEVER\n";
	else if (always) std::cout << "ALWAYS\n";
	else std::cout << "SOMETIMES\n";
}

int main() {
	int ncasos;
	std::cin >> ncasos;
	for (int i = 0; i < ncasos; ++i) resuelveCaso();
	return 0;
}