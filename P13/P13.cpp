#include <iostream>
#include <vector>
#include <string>

class SegmentTree {
	std::vector<int> st;
	int tam; // Numero de hojas que manejamos
public:

	SegmentTree(int maxN) {
		st.assign(4 * maxN + 10, 0);
	}

	int query(int a, int b) {
		return query(1, 0, tam - 1, a, b);
	}
	int query(int vertex, int L, int R, int i, int j) {
		if (i > R || j < L) {
			return 0;
		}
		if (L >= i && R <= j)
			// Segmento completamente dentro de la consulta
			return st[vertex];
		int mitad = (L + R) / 2;
		return query(2 * vertex, L, mitad, i, j) +
			query(2 * vertex + 1, mitad + 1, R, i, j);
	}

	void update(int pos, int newVal) {
		update(1, 0, tam - 1, pos, newVal);
	}
	void update(int vertex, int l, int r,
		int pos, int newVal) {
		if ((pos < l) || (r < pos)) return;
		if (l == r) {
			st[vertex] = newVal;
			return;
		}
		int m = (l + r) / 2;
		if ((l <= pos) && (pos <= m))
			update(2 * vertex, l, m, pos, newVal);
		else
			update(2 * vertex + 1, m + 1, r, pos, newVal);
		st[vertex] = st[2 * vertex] + st[2 * vertex + 1];
	}

	void build(int *values, int n) {
		tam = n;
		build(values, 1, 0, n - 1);
	}
	void build(int *values, int p, int l, int r) {
		if (l == r) {
			st[p] = values[l];
			return;
		}
		int m = (l + r) / 2;
		build(values, 2 * p, l, m);
		build(values, 2 * p + 1, m + 1, r);
		st[p] = st[2 * p] + st[2 * p + 1];
	}

};

bool resuelveCaso(int const& caso) {
	int nCond;
	std::cin >> nCond;
	if (nCond == 0) return false;

	int *cond = new int[nCond];

	for (int i = 0; i < nCond; ++i) {
		std::cin >> cond[i];
	}
	SegmentTree st(nCond);
	st.build(cond, nCond);

	std::cout << "Case " << caso << ":\n";

	std::string op;
	std::cin >> op;
	while (op != "END") {

		int a, b;
		std::cin >> a >> b;
		if (op == "M") {
			std::cout << st.query(a-1, b-1) << "\n";
		}

		else if (op == "S") {
			st.update(a-1, b);
		}
		std::cin >> op;
	}
	std::cout << "\n";
	return true;
}

int main() {
	int i = 0;
	while (resuelveCaso(++i));
	return 0;
}