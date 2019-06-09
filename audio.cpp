#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <functional>
#include <cmath>
using namespace std;


const bool comp (const pair<int, int> &a, const pair<int, int> &b) {
    return a.second < b.second;
}

const int factorial ( const int x ) {
    if ( x == 0 || x == 1) return 1;
    else return factorial(x-1) * x;
}

class graph_table {
    private:
        int **mat = nullptr;
        vector <int> permutation;
        unsigned int vertex_numbers;
        vector <int> *shortest_path;
        int shortest_path_len = 0;
        const int init_permutation(unsigned int first) {
            int res = -1; /* target1 = 0, target2 = 0 ,mx = 0;*/
            if ( vertex_numbers == 0 || mat == nullptr) return res;
            for (int i = 0; i< vertex_numbers; i++) {
                //if ( shortest_path.size() != 0 && find(shortest_path.begin(), shortest_path.end(), first) != shortest_path.end()) res = -2 ;
                if ( i == first -1 ) permutation.push_back(0);
                else permutation.push_back(-1);
            }

            int p = 0;
            for (int i = 0; i< vertex_numbers; i++) {
                //if ( shortest_path.size() != 0 && find(shortest_path.begin(), shortest_path.end(), first) != shortest_path.end()) res = -2 ;
                if ( permutation[i] == 0 )  { p++;  continue; }
                else permutation[i] = i+1-p;
            }
            res = 0;
            return res;
         }
    public:
        graph_table( const char *filename ) {
            int radix, connect;
            fstream file (filename, ios::in);
            if ( !file.good() )
                exit(-1);
            file >> vertex_numbers;
            mat  = new int*[vertex_numbers];
            for (int i = 0; i < vertex_numbers ; i++) {
                mat[i] = new int[vertex_numbers];
                fill(mat[i], mat[i]+vertex_numbers , -1);
                }
            for (size_t i = 0; i< vertex_numbers ; i++) {
                file >> radix;
                while (true) {
                    file >> connect;
                    if (connect == 0)
                        break;
                    else
                        mat[radix-1][connect-1] = 1;
                    }
                }
            }
        int optimize_path( const int x) {
            int length = 0, mx = 0, target1, target2, res=0, prev_res=99999, cnt = 0;
            vector<int> _perm;
            #ifdef TEST
            cout << "Leftmost Point = " << x <<endl;
            #endif
            for (int i = 0; i< vertex_numbers ; i++)
                if ( i != x-1 ) _perm.push_back(permutation[i]);

            do {

            permutation.clear();
            permutation.insert(permutation.begin(), _perm.begin(), _perm.end());
            permutation.insert(permutation.begin()+x-1, 0);

            for (int i = 0; i< vertex_numbers ; i++) {
                int j;
                for (j = 0; j< vertex_numbers ; j++) {
                    if ( mat[i][j] == 1 ) {
                        if ( mat[j][i] == 1 &&  i > j) continue;
                        res += abs( permutation[j] - permutation[i] );
                    }
                }

            }
            #ifdef TEST
            for (int i = 0; i< vertex_numbers ; i++) { cout << permutation[i] << ' '; }
            #endif
            res = min(prev_res,res);
            #ifdef TEST
            cout << " => " << res << endl;
            #endif // TEST
            prev_res = res;

            } while ( next_permutation(_perm.begin(), _perm.end()) );
            return res;
        }

        void search_path( const int x , const int s) {
            vector<int> _perm;
            int prev_res = 99999, res = 0;
            init_permutation(x);
            for (int i = 0; i< vertex_numbers ; i++)
                if ( i != x-1 ) _perm.push_back(permutation[i]);

            do {

            permutation.clear();
            permutation.insert(permutation.begin(), _perm.begin(), _perm.end());
            permutation.insert(permutation.begin()+x-1, 0);

            for (int i = 0; i< vertex_numbers ; i++) {
                int j;
                for (j = 0; j< vertex_numbers ; j++) {
                    if ( mat[i][j] == 1 ) {
                        if ( mat[j][i] == 1 &&  i > j) continue;
                        res += abs( permutation[j] - permutation[i] );
                    }
                }

            }
            res = min(prev_res,res);
            if ( res == s ) break;
            prev_res = res;
            res = 0;
            } while ( next_permutation(_perm.begin(), _perm.end()) );

        }

        void minimum_path() {
            vector <pair<int,int>> maximum_summtations;
            int init, opt;
            for (int i  = 0; i< vertex_numbers ; i++) {
                if ( init_permutation(i+1) == -1 ) return;
                opt = optimize_path(i+1);

                maximum_summtations.push_back(pair<int,int>(i+1,opt ));
                permutation.clear();
            }

            sort(maximum_summtations.begin(), maximum_summtations.end(),comp);

            init = (maximum_summtations.front()).first;
            shortest_path_len = (maximum_summtations.front()).second;

            search_path(init,shortest_path_len);

            fstream output("audio.out", ios::out);
            output << shortest_path_len<< '\n';

            for (int i = 0; i< vertex_numbers ;i++) {
                int n = distance( permutation.begin(), find( permutation.begin(), permutation.end(), i ) ) +1 ;
                output << n << ' ';
            }
            output << flush;
            output.close();
        }
    };


int main() {
    graph_table G("audio.inp");
    G.minimum_path();
    return 0;
}
