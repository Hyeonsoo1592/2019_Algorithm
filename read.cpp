#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

class read {
    private:
        string data;
        unsigned int frequency;
    public:
        read(const string& S):frequency(1U) {
            data = S;
            }
        void increment_freq(read &R) {
            frequency+=R.frequency;
            }
        const bool operator< (const read &R) {
            if ( frequency == R.frequency )
                return data < R.data;
            else
                return frequency > R.frequency;
            }
        const bool operator==(const read &R) {
            return (data.size() == R.data.size()) && (data == R.data);
            }
        const bool operator==(const string &S) {
            return data == S;
            }
        friend ostream& operator<< (ostream &os, const read &R) {
            os << R.data;
            return os;
            }
    };


int main() {
    vector<read> List;
    string _inp;
    fstream file("read.inp", ios::in);
    if (!file.is_open()) {
        cerr << "Cannot open 'read.inp'! " << flush;
        file.close();
        return -1;
        }
    while ( file >> _inp ) {
        List.push_back(read(_inp));
        }
    file.close();
    sort(List.begin(), List.end());
    for ( size_t i = 1; i< List.size() ; i++) if ( List[i] == List[i-1] ) List[i].increment_freq(List[i-1]);
    sort(List.begin(), List.end());
    file.open("read.out", ios::out);
    file << List[0] << endl;
    file.close();

    return 0;

    }

