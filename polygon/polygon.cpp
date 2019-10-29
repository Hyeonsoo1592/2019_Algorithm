#include <iostream>
#include <fstream>
#include <functional>
#include <algorithm>
#include <cstring>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

typedef pair<int, int> Point;

const bool operator< ( Point& L, Point &R ) {
    if ( L.first == R.first )
        return L.second < R.second;
    else
        return L.first < R.first;
    }

const double mag(const Point &A) {
    return pow(((double)(A.first * A.first)+(double)(A.second * A.second)),0.5);
    }

const double signed_surface_tri ( const Point &p1, const Point &p2, const Point &p3) {
    double res = 0;
    int matrix[2][4] = { { p1.first, p2.first, p3.first, p1.first }, {p1.second, p2.second, p3.second, p1.second} };

    for (int i = 0; i< 3 ; i++) {
        res += static_cast<double> (matrix[0][ i ] * matrix[1][i+1]);
        res -= static_cast<double> (matrix[0][3-i] * matrix[1][2-i]);
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
        const double cross(Point &a, Point &b, Point &c) {
            Point vec_a = Point((b.first - a.first), (b.second - a.second));
            Point vec_b = Point((c.first - b.first), (c.second - b.second));
            double outer = static_cast<double>(vec_a.first * vec_b.second) - static_cast<double>(vec_a.second * vec_b.first);
            return outer;
            }
        const double theta_is_neg(Point &a, Point &b, Point &c) {
            Point vec_a = Point((b.first - a.first), (b.second - a.second));
            Point vec_b = Point((c.first - b.first), (c.second - b.second));
            double outer = cross(a,b,c);
            outer /= (mag(vec_a) * mag(vec_b));
            return outer;
            }
    public:
        polygon():number_point(0), verteces(nullptr) {}
        polygon(const char*);
        void configure();
        friend ostream& operator<< ( ostream& os, const polygon& P ) {
            switch(P.config) {
                case 1:
                    os << "Convex";
                    break;
                case 2:
                    os << "Concave " << P.concave_count;
                    break;
                default:
                    os << "None";
                    break;
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

void polygon::configure() {
    bool is_positive[number_point];
    double theta = 0.0, sum_theta = 0.0;
    // intersection check;
    double _cross1 = 1, _cross2 = 1;
    bool crossed;
     for (int i = 0; i< number_point ; i++) {
        _cross1 = cross(verteces[i%number_point], verteces[(i+1)%number_point], verteces[(i+2)%number_point]);
        _cross1 *= cross(verteces[i%number_point], verteces[(i+1)%number_point], verteces[(i+3)%number_point]);
        _cross2 = cross(verteces[(i+2)%number_point], verteces[(i+3)%number_point], verteces[i%number_point]);
        _cross2 *= cross(verteces[(i+2)%number_point], verteces[(i+3)%number_point], verteces[(i+1)%number_point]);
        if (_cross1 ==0 && _cross2 == 0)
        crossed =  !(max(verteces[(i)%number_point], verteces[(i+1)%number_point]) < min(verteces[(i+2)%number_point]), verteces[(i+3)%number_point] ||
                 min(verteces[(i)%number_point], verteces[(i+1)%number_point]) > max(verteces[(i+2)%number_point]), verteces[(i+3)%number_point] )
        else crossed = (_cross1<0 && _cross2 <0);
             }
    if (crossed) this->config=3; return;
    // convex - concave check
    for (int i = 0; i< number_point ; i++) {
        theta = theta_is_neg(verteces[i%number_point], verteces[(i+1)%number_point], verteces[(i+2)%number_point]);
#ifdef TEST
        cout << i%number_point << "->" << (i+1)%number_point << "->" << (i+2)%number_point << " " ;
#endif

        if ( theta  > 0 ) {
            is_positive[i] = true;
            concave_count++;
            }
        else
            is_positive[i] = false;
        }
    if ( concave_count == 0 )
        this->config = 1;
    else if (  concave_count > 0  )
        this->config = 2;

    }



int main() {
#ifdef TEST
    char filename[256];
    cin >> filename;
    polygon p(filename);
#else
    polygon p("polygon.inp");
#endif

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
