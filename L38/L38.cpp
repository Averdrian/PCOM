#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>


const int MAXN = 26;
class Trie {
	int prefixes;
	int words;
	std::vector<Trie*> child;
public:
	Trie() :prefixes(0), words(0), child(MAXN, nullptr) {}
	~Trie() {
		for (int i = 0; i < MAXN; ++i)
			delete child[i];
	}
	void add(const char* s) {
		if (*s == '\0') ++words;
		else {
			Trie* t;
			if (child[*s - 'a'] == nullptr) {
				t = child[*s - 'a'] = new Trie();
				t->prefixes = 1;
			}
			else {
				t = child[*s - 'a'];
				t->prefixes++;
			}
			t->add(s + 1);
		}
	}

	int nChilds() {
		int count = 0;
		for (int i = 0; i < child.size(); ++i) 
			if (child[i] != nullptr) ++count;
		return count;
	}
	
	void keyStrokes(double& k_p, bool const& first = true, int k_pressed = 0) {
		int kStrokes = 0, chi = nChilds();
		if (words != 0) k_p += k_pressed;
	
		for (int i = 0; i < child.size(); ++i) {
			if (child[i] != nullptr) {
				child[i]->keyStrokes(k_p, false, (chi > 1 || first || (chi == 1 && words != 0)) ? k_pressed + 1 : k_pressed);
			}
		
		}

	}

};

bool resuelveCaso() {

	int N;
	std::cin >> N;
	if (!std::cin) return false;

	Trie diccionario = Trie();
	for (int i = 0; i < N; ++i) {
		std::string word;
		std::cin >> word;
		char* cstr = &word[0];
		diccionario.add(cstr);
	}
	double k_p = 0.00;
	diccionario.keyStrokes(k_p);
	double average = round((k_p / N) * 100) / 100;
	std::cout << std::fixed << std::setprecision(2) << average <<  "\n";
	
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}