
// chuletario geometria

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip>
#include <cmath>
#include <random>
#include <tuple>
#include <cassert>
using namespace std;

const double EPS = 1e-9;
const double PI = acos(-1);

using T = double;
//bool lt(double a, double b) { return a - EPS < b; };
//bool eq(double a, double b) { return fabs(a - b) < EPS; }

//using T = int;
//bool lt(int a, int b) { return a < b; }
//bool eq(int a, int b) { return a == b; }

struct pt {
    pt(){}
    pt(T const& X, T const& Y) : x(X), y(Y) {}
    pt(T const& X, T const& Y, T const& Z) : x(X), y(Y), z(Z) {}
    T x, y, z;
    pt operator+(pt p) const { return { x + p.x, y + p.y }; }
    pt operator-(pt p) const { return { x - p.x, y - p.y }; }
    pt operator*(T d) const { return { x * d, y * d }; }
    pt operator/(T d) const { return { x / d, y / d }; } // only for floating-point

    bool operator==(pt o) const { return x == o.x && y == o.y; }
    bool operator!=(pt o) const { return !(*this == o); }

    bool operator<(pt o) const { // sort points lexicographically
        if (x == o.x) return y < o.y;
        return x < o.x;
    }
};


T sq(pt v) { return v.x * v.x + v.y * v.y; }
double abs(pt v) { return sqrt(sq(v)); }

ostream& operator<<(ostream& os, pt p) {
    return os << "(" << p.x << "," << p.y << ")";
}

double dist(pt a, pt b) { // Euclidean distance
    return hypot(a.x - b.x, a.y - b.y);
}
T dist2(pt a, pt b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

// PRODUCTOS

T dot(pt v, pt w) { return v.x * w.x + v.y * w.y; }

bool isPerp(pt v, pt w) { return dot(v, w) == 0; }

double angle(pt v, pt w) {
    double cosTheta = dot(v, w) / abs(v) / abs(w);
    return acos(max(-1.0, min(1.0, cosTheta)));
}

T cross(pt v, pt w) { return v.x * w.y - v.y * w.x; }

// positivo/cero/negativo: c a la izquieda/sobre/derecha de a-b
T orient(pt a, pt b, pt c) { return cross(b - a, c - a); }

bool inAngle(pt a, pt b, pt c, pt p) {
    assert(orient(a, b, c) != 0);
    if (orient(a, b, c) < 0) swap(b, c);
    return orient(a, b, p) >= 0 && orient(a, c, p) <= 0;
}

double orientedAngle(pt a, pt b, pt c) {
    if (orient(a, b, c) >= 0)
        return angle(b - a, c - a);
    else
        return 2 * PI - angle(b - a, c - a);
}


// ORDENACI�N POLAR

bool half(pt p) { // true if in blue half
    assert(p.x != 0 || p.y != 0); // the argument of (0,0) is undefined
    return p.y > 0 || (p.y == 0 && p.x < 0);
}

void polarSort(vector<pt>& v) {
    sort(v.begin(), v.end(), [](pt v, pt w) {
        return make_tuple(half(v), 0, sq(v)) < make_tuple(half(w), cross(v, w), sq(w));
        });
}


// TRANSFORMACIONES

pt translate(pt v, pt p) { return p + v; }

// scale p by a certain factor around a center c
pt scale(pt c, double factor, pt p) {
    return c + (p - c) * factor;
}

// rotate p by a certain angle a counter-clockwise around origin
pt rotate(pt p, double a) {
    return { p.x * cos(a) - p.y * sin(a), p.x * sin(a) + p.y * cos(a) };
}

// rotate 90� counterclockwise
pt perp(pt p) { return { -p.y, p.x }; }


// LINEAS

struct line {
    pt v; T c;
    // from direction vector v and offset c
    line(pt v, T c) : v(v), c(c) {}
    // from equation ax + by = c
    line(T a, T b, T c) : v({ b,-a }), c(c) {}
    // from points p and q
    line(pt p, pt q) : v(q - p), c(cross(v, p)) {}

    T side(pt p) { return cross(v, p) - c; }

    double dist(pt p) { return abs(side(p)) / abs(v); }

    line translate(pt t) { return { v, c + cross(v,t) }; }

    pt proj(pt p) { return p - perp(v) * side(p) / sq(v); }
};

bool inter(line l1, line l2, pt& out) {
    T d = cross(l1.v, l2.v);
    if (d == 0) return false;
    out = (l2.v * l1.c - l1.v * l2.c) / d; // requires floating-point coordinates
    return true;
}


// POLIGONOS, el primer y �ltimo puntos coinciden

double areaTriangle(pt a, pt b, pt c) {
    return abs(cross(b - a, c - a)) / 2.0;
}

double areaPolygon(vector<pt> const& p) {
    double area = 0.0;
    for (int i = 0, n = int(p.size()) - 1; i < n; ++i) {
        area += cross(p[i], p[i + 1]);
    }
    return abs(area) / 2.0;
}
/*
// if strict, returns false when A is on the boundary
bool inPolygon(vector<pt> const& p, pt a, bool strict = true) {
    int numCrossings = 0;
    for (int i = 0, n = int(p.size()) - 1; i < n; ++i) {
        if (onSegment(p[i], p[i + 1], a))
            return !strict;
        numCrossings += crossesRay(a, p[i], p[i + 1]);
    }
    return numCrossings & 1; // inside if odd number of crossings
}
*/

bool isConvex(vector<pt> const& p) {
    bool hasPos = false, hasNeg = false;
    for (int i = 0, n = (int)p.size(); i < n; ++i) {
        int o = orient(p[i], p[(i + 1) % n], p[(i + 2) % n]);
        if (o > 0) hasPos = true;
        if (o < 0) hasNeg = true;
    }
    return !(hasPos && hasNeg);
}


// ENVOLVENTE CONVEXA

// para aceptar puntos colineales cambia a >=
// returns true if point r is on the left side of line pq
bool ccw(pt p, pt q, pt r) {
    return orient(p, q, r) > 0;
}

// devuelve un pol�gono con la envolvente convexa de una nube de puntos P.
vector<pt> convexHull(vector<pt>& P) {
    int n = int(P.size()), k = 0;
    vector<pt> H(2 * n);
    sort(P.begin(), P.end());
    // build lower hull
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && !ccw(H[k - 2], H[k - 1], P[i])) --k;
        H[k++] = P[i];
    }
    // build upper hull
    for (int i = n - 2, t = k + 1; i >= 0; --i) {
        while (k >= t && !ccw(H[k - 2], H[k - 1], P[i])) --k;
        H[k++] = P[i];
    }
    H.resize(k);
    return H;
}


// DIVISI�N DE UN POL�GONO

vector<pt> cutPolygon(pt a, pt b, vector<pt> const& P) {
    vector<pt> R; pt c;
    for (int i = 0; i < int(P.size()) - 1; i++) {
        double left1 = cross(b - a, P[i] - a),
            left2 = cross(b - a, P[i + 1] - a);
        if (left1 >= 0) R.push_back(P[i]);  // P[i] is on the left of ab
        if (left1 * left2 < 0) {  // edge (P[i], P[i+1]) crosses line ab
            inter({ P[i], P[i + 1] }, { a,b }, c);
            R.push_back(c);
        }
    }
    if (!R.empty())
        R.push_back(R[0]); // make R's first point = R's last point
    return R;
}

#include <fstream>

bool resuelveCaso(int const& caso) {
	
    int nPoles;
    std::cin >> nPoles;
    if (nPoles == 0) return false;

    std::vector<pt> poles;
    std::vector<double> heigh;

    for (int i = 0; i < nPoles; ++i) {
        double X, Y, Z;
        std::cin >> X >> Y >> Z;
        poles.push_back({ X,Y,Z });
    }

    polarSort(poles);

    std::vector<pt> notVisible;
  
    T h = poles[0].z;
    for (int i = 1; i < poles.size(); ++i) {
        if (((poles[i].x == 0 || poles[i - 1].x == 0) && poles[i].x != poles[i - 1].x) || ((poles[i].y == 0 || poles[i - 1].y == 0) && poles[i].y != poles[i - 1].y)) {
			h = poles[i].z;
        }
        else if ((poles[i].x == 0 && poles[i - 1].x == 0) || (poles[i].y == 0 && poles[i - 1].y == 0)) {
            if (poles[i].z <= h) notVisible.push_back(poles[i]);
            else h = poles[i].z;
        }
        else if (poles[i].x / poles[i - 1].x == poles[i].y / poles[i - 1].y) {
            if (poles[i].z <= h) notVisible.push_back(poles[i]);
            else h = poles[i].z;
        }
        else h = poles[i].z;
    }

    std::cout << "Data set " << caso << ":\n";

    if (notVisible.size() == 0) {
        std::cout << "All the lights are visible.\n";
    }
    else {
        std::sort(notVisible.begin(), notVisible.end());
        std::cout << "Some lights are not visible:\n";

        for (int i = 0; i < notVisible.size() - 1; ++i) {
            std::cout << "x = " << notVisible[i].x << ", y = " << notVisible[i].y << ";\n";

        }
        std::cout << "x = " << notVisible[notVisible.size() - 1].x << ", y = " << notVisible[notVisible.size() - 1].y << ".\n";
    }




    return true;
}


int main() {
    int caso = 0;
    while (resuelveCaso(++caso));
    return 0;
}