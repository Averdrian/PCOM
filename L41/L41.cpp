#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <algorithm>

struct point {
	double x;
	int i;
	bool start;
	bool operator()(point const& p1, point const& p2) {
		return p1.x > p2.x;
	}
};

void resuelveCaso() {
	
	std::cin.get();

	int nfilms;
	std::cin >> nfilms;

	if (nfilms == 0) {
		std::cout << "1\n -inf +inf 1.000\n";
		return;
	}

	std::priority_queue<point, std::vector<point>, point > point_queue;
	

	std::vector<double> films;

	for (int i = 0; i < nfilms; ++i) {
		double x1, x2, y1, y2, transp;
		std::cin >> x1 >> y1 >> x2 >> y2 >> transp;
		point aux;
		aux.x = x1;
		aux.i = i;
		aux.start = x1 < x2 ? true : false;
		point_queue.push(aux);
		aux.x = x2;
		aux.start = x2 < x1 ? true : false;
		point_queue.push(aux);
		films.push_back(transp);
	}
	
	std::vector<int> films_below;
	
	std::cout << point_queue.size() + 1 << "\n";

	std::cout << "-inf " << std::fixed << std::setprecision(3) << point_queue.top().x << " 1.000\n";
	films_below.push_back(point_queue.top().i);
	double last_P = point_queue.top().x;
	point_queue.pop();
	

	for (int i = 1; i < nfilms * 2; ++i) {
		double c_transparency = 1.000;
		point toEv = point_queue.top(); point_queue.pop();
		
		for (int j = 0; j < films_below.size(); ++j) c_transparency *= films[films_below[j]];
		


		std::cout << std::fixed << std::setprecision(3) << last_P << " " << toEv.x << " " << c_transparency << "\n";
		
		if (toEv.start) films_below.push_back(toEv.i);
		else {
			std::vector<int>::iterator position = std::find(films_below.begin(), films_below.end(), toEv.i);
			if(position != films_below.end()) films_below.erase(position);
		}
		
		last_P = toEv.x;

	}

	std::cout << std::fixed << std::setprecision(3) << last_P << " +inf 1.000\n";

}

int main() {
	int ncasos;
	std::cin >> ncasos;
	for (int i = 0; i < ncasos; ++i)
		resuelveCaso();
	return 0;
}