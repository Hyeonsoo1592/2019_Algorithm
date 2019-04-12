#include <iostream>
#include <fstream>
#include <queue>
#include <utility>
#include <list>
#include <algorithm>
#include <cmath>
using namespace std;

class point {
    private:
        pair<int,int> data;
    public:
        point(int x = 0, int y = 0) {
            data = pair<int, int>(x,y);
            }
        const int dist(const point &P) {
            int delta_X = P.data.first - this->data.first, delta_Y = P.data.second - this->data.second ;
            return delta_X * delta_X + delta_Y * delta_Y;
            }
        point& operator=(const point &P) {
            this->data = P.data;
            return (*this);
            }
        const bool operator==(const point &P) {
            return data == P.data;
            }
        pair<int, int> const & getdata() {
            return data;
            }
        friend ostream& operator<< (ostream &os, const point &P) {
            os << '(' << P.data.first << ", " << P.data.second << ')';
            return os;
            }

    };

class Map {
    private:
        int N,Z; // Number of Point to Charge and distance of endpoint
        point *stations;
        list<point> *adj;
        const bool traversal(const int limit_weight);
    public:
        explicit Map(fstream &fs) {
            int ix,iy;
            if (!fs.is_open())
                exit(-1);
            fs >> N >>Z;
            adj = new list<point>[N+2];
            stations = new point[N+2];
            stations[0] = point(0,0);
            stations[N+1] = point(Z,Z);

            for (int i = 1; i< N+1 ; i++) {
                fs >> ix >> iy;
                stations[i] = point(ix,iy);
                }
            }
        ~Map() {
            delete[] stations;
            delete[] adj;
            }
        const int minimum_weight_of_battery() {
            int lower = 0, upper = 0, maximum = (int)ceil( (double)sqrt(2.0) * Z );
            for (int i = 0; i <=maximum/2 ; i++ ) {
                if (this->traversal(i)) {
                    lower = i;
                    break;
                    }
                }
            for (int i = maximum ; i >= (maximum/2) + 1 ; i--) {
                if (this->traversal(i)) {
                    upper = i;
                    break;
                    }
                }
            if (lower && !upper)
                return lower;
            else if ( !lower && upper)
                return upper;
            else
                return lower;
            }

    };


const bool Map::traversal(const int limit_weight) {
    int limit = limit_weight * limit_weight;
    //
    for (int j = 0; j< N+2; j++) {
        point tg = stations[j];
        for (int i = 0; i< N+2; i++) {
            int _dist = tg.dist(stations[i]);
            if ( _dist > 0 && _dist <= limit) {
                adj[j].push_back(stations[i]);
                }
            }
        }


    //
    bool *visit = new bool[N+2];
    queue<point> Q;
    int idx = 0;
    point endpoint;

    visit[idx] =  true;
    Q.push(stations[idx]);

    while(!Q.empty()) {
        point* it = find(stations, stations+(N+2),Q.front());
        idx = distance(stations, it);
        endpoint = Q.front();
        Q.pop();
        for (list<point>::iterator lit = adj[idx].begin(); lit != adj[idx].end(); lit++ ) {
            it = find(stations, stations+(N+2),*lit);
            int lidx = distance(stations, it);
            if (!visit[lidx] && !adj[lidx].empty()) {
                visit[lidx] = true;
                Q.push(*lit);
                }
            }
        }
    if ( stations[N+1] == endpoint )
        return true;
    else
        return false;
    }


int main() {
    fstream file;
    file.open("battery.inp",ios::in);
    Map m(file);
    file.close();
    file.open("battery.out",ios::out);
    file <<m.minimum_weight_of_battery() <<flush;
    file.close();
    return 0;
    }
