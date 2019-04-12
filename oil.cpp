#include "oil.h"
#include <utility>
#include <iostream>

using namespace std;

pair<int,int> valid(-1,-1);


ostream& operator<< (ostream& os, pair<int, int> &_P) {
    os << _P.first << " , " << _P.second;
    return os;
    }

pair<int, int> check(int i, int j) {
    cout << "Function! ===================" <<endl;
    if ( i!=0 && valid.second == i-1 ) {
        if (valid == pair<int,int>(-1,-1)) valid = pair<int, int>(i,j);
        else valid.second = j;
    }
    int obs = observe(i,j);
    if (obs <= 0)
        return pair<int, int>(-1,-1);
    else if ( obs == 1 ) {
        if (valid == pair<int,int>(-1,-1)) valid = pair<int, int>(i,j);
        else valid.second = j;
        return valid;
    }
    else {
        int start = i, terminus = j, middle = (i+j)/2;
        pair<int, int> left = check(start,middle), right;
        cout << left << endl;
        right = check(middle+1, terminus);
        cout << right << endl;

        if (left == pair<int,int>(-1,-1)) {
            return right;
            }
        else if (right == pair<int,int>(-1,-1))
            return left;
        else {
            if (left.second == right.first+1) return left;
            return pair<int,int> (left.first, right.second);
        }
    }
}

int main() {
    initial();
    unsigned int _N = oil_size();
    pair<int, int> result = check(0,_N-1);
    oil_report(result.first, result.second);
    return 0;
    }
