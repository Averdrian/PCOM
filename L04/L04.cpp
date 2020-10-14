#include <iostream>
#include <vector>

const int MAX_HEIGH = 10;

int main() {
	int nCasos;
	std::cin >> nCasos;
	
	for (int caso = 0; caso < nCasos;++caso) {
	
		std::vector<std::vector<int>> aire;	
		
		
		
		int dist;
		std::cin >> dist;
		for (int i = 0; i < MAX_HEIGH; ++i) {
			std::vector<int> airaux;
			for (int j = 0; j < dist / 100; ++j) {
				int cell;
				std::cin >> cell;
				airaux.push_back(cell);
			}
			aire.push_back(airaux);
		}
		std::vector<std::vector<int>> fuel;

		for(int i = 0; i < MAX_HEIGH; ++i)
			fuel.push_back(std::vector<int>(dist / 100 + 1 , -1));

		//Caso base
		fuel[MAX_HEIGH - 1][0] = 0;


		for (int j = 1; j < dist / 100 + 1; ++j) {

			for (int i = 0; i < MAX_HEIGH; ++i) {
				int aux;
				if (fuel[i][j - 1] != -1) fuel[i][j] = fuel[i][j - 1] + 30 - aire[i][j - 1];
				if (i > 0 && fuel[i - 1][j - 1] != -1 && (fuel[i][j] == -1 || fuel[i - 1][j - 1] + 20 - aire[i-1][j - 1] < fuel[i][j]))
					fuel[i][j] = fuel[i - 1][j - 1] + 20 - aire[i-1][j - 1];
				if (i < MAX_HEIGH - 1 && fuel[i + 1][j - 1] != -1 && (fuel[i][j] == -1 || fuel[i + 1][j - 1] + 60 - aire[i+1][j - 1] < fuel[i][j]))
					fuel[i][j] = fuel[i + 1][j - 1] + 60 - aire[i+1][j - 1];
			}


		}
	
	/*  Output of full matrix for testing
		for (int i = 0; i < fuel.size(); ++i) {
			for (int j = 0; j < fuel[0].size(); ++j) {
				std::cout << fuel[i][j] << " ";
			}
			std::cout << std::endl;
		}
	*/

		std::cout << fuel[MAX_HEIGH - 1][dist / 100] << "\n";


	}


	return 0;
}