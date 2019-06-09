#include <iostream>
#include <fstream>
#include <functional>
#include <algorithm>
#include <cstring>
using namespace std;

typedef pair<unsigned int, unsigned int> Point;

const bool operator< ( const Point& L, const Point &R ) {
    if ( L.first == R.first )
        return L.second < R.second;
    else
        return L.first < R.first;
    }

const double signed_surface_tri ( const Point &p1, const Point &p2, const Point &p3) {
    double res = 0;
    unsigned int matrix[2][4] = { { p1.first, p2.first, p3.first, p1.first }, {p1.second, p2.second, p3.second, p1.second} };

    for (int i = 0; i< 3 ; i++) {
        res += static_cast<double> (matrix[0][ i ] * matrix[1][ i+1 ]);
        res -= static_cast<double> (matrix[0][3-i] * matrix[1][3-i-1]);
        }
    res /= 2.0;
    return res;
    }

class polygon {
    private:
        unsigned int number_point;
        Point *verteces;
        unsigned int config = 0;
		unsigned int concave_count = 0;
    public:
        polygon():number_point(0), verteces(nullptr) {}
        polygon(const char*);
		void configure() {
			this->config = 1;
		}
		friend ostream& operator<< ( ostream& os, const polygon& P ) {
			switch(P.config) {
				case 1: os << "Convex"; break;
				case 2: os << "Concave " << P.concave_count; break;
				default: os << "None"; break;
				}
			return os;
			}	
    };

polygon::polygon(const char* filename) {
    fstream file;
    unsigned int x, y;
    if (!filename || strlen(filename) <= 0 ) {
        cerr << "Invalid Filename!" << flush;
        exit(-1);
        }
    file.open(filename, ios::in);
    if ( !file.is_open() ) {
        cerr << "'" << filename << "' cannot open" << flush;
        file.close();
        exit(-1);
        }
    file >> this->number_point;
    this->verteces = new Point[this->number_point];
    for (size_t i = 0; i< this->number_point ; i++) {
        file >> x >> y;
        this->verteces[i] = Point(x,y);
#ifdef TEST
	cout << "(" << verteces[i].first << ", " << verteces[i].second <<")" <<endl;
#endif
        }
    file.close();
    }

int main() {
    polygon p("polygon.inp");
  	p.configure();	
#ifdef TEST
	cout << p << endl;
#else
	fstream file("polygon.out", ios::out);
	file << p << endl;
	file.close();
#endif	
    return 0;
    }
