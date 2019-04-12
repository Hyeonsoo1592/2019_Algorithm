#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

typedef struct V3 {
    int  _x, _y, _z;

    const V3 operator- (const V3 &V) const {
        V3 result = {(_x - V._x),(_y - V._y),(_z - V._z)};
        return result;
        }

    double magnitude() const { return sqrt(pow((double)_x,2.0) + pow((double)_y,2.0) + pow((double)_z,2.0)); }

    const double innerproduct( const V3 &V ) {
        return (double)((this->_x * V._x)+(this->_y * V._y)+(this->_z * V._z));
        }

    const V3 outterproduct( const V3 &V ) {
        V3 result = { this->_y*V._z - this->_z*V._y,
                      this->_z*V._x - this->_x*V._z,
                      this->_x*V._y - this->_y*V._x,};
        return result;
        }

    const double distance( V3 &V ) {
        return pow((double)(this->_x - V._x),2.0)+pow((double)(this->_y - V._y),2.0)+pow((double)(this->_z - V._z),2.0);
        }

    }  _3d_vector;

const int calculation( _3d_vector *arr) {
    double result = 0;
    _3d_vector AB = arr[1] - arr[0], AP = arr[2] - arr[0], BP = arr[1] - arr[0];

    if ( AB.innerproduct(AP) * AB.innerproduct(BP) < 0 ) {
        if (AB.innerproduct(AP) < 0) result = AP.magnitude();
        else result = BP.magnitude();
    }
    else {
        result = AB.outterproduct(AP).magnitude() / AB.magnitude();
        }
    return (int)(ceil(result));
    }

int main() {
    fstream fs("bridge.inp", ios::in);
    _3d_vector p[3];
    if ( !fs.is_open() ) return -1;
    for (int i = 0; i< 3; i++) {
        fs >> p[i]._x >> p[i]._y >> p[i]._z;
        }
    fs.close();

    fs.open("bridge.out", ios::out);
    fs << calculation(p) <<endl;
    fs.close();

    return 0;
    }
