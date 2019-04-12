//====================================================================
// Assignment 5,6
// Copy
// copy.cpp
// Algorithm, Spring 2019
// Hyeonsoo Kim
// Major of CSE, PNU
// alcatraz@pusan.ac.kr
// 2019.04.09
//====================================================================
#include <iostream>
#include <fstream>
#include <locale>
#include <algorithm>
#include <vector>
#include <regex>
using namespace std;

#ifdef LINUX
locale utf8_loc("ko_KR.UTF-8");
#endif
#ifdef WINDOWS
locale utf8_loc("utf-8_unicode");
#endif // WINDOWS

const bool kocond(wchar_t a, wchar_t b) {
    if ( a == L'은')
        return (b == L'는');
    if ( a == L'는')
        return (b == L'은');
    if ( a == L'을')
        return (b == L'를');
    if ( a == L'를')
        return (b == L'을');
    return false;
    }

const unsigned int max_lcs(const wstring &_w1, const wstring &_w2) {
    unsigned int **table = new unsigned int*[_w1.size() + 1];
    for (unsigned int i = 0; i< _w1.size()+1 ; i++ ) {
        table[i] = new unsigned int[_w2.size()+ 1];
        fill(&table[i][0],&table[i][_w2.size()+ 1],0);
        }

    for (unsigned int i = 1; i <= _w1.size(); i++) {
        for (unsigned int j = 1; j <= _w2.size(); j++) {
            if ( _w1[i-1] == _w2[j - 1] || kocond(_w1[i-1], _w2[j-1])) {
                table[i][j] = table[i - 1][j - 1] + 1;
                }
            else {
                table[i][j] = max(table[i - 1][j], table[i][j - 1]);
                }
            }
        }
    unsigned int res = table[_w1.size()][_w2.size()];
    for (unsigned int i = 0; i< _w1.size()+1 ; i++ ) {
        delete[] table[i];
        }
    delete[] table;
    return res;
    }

const bool pred ( pair<double, unsigned int> &A, pair<double, unsigned int> &B) {
    return A.first < B.first;
    }

class hangul_strings {
    private:
        wstring *lists = nullptr;
        unsigned int size;
        void list_write(wfstream &win) {
            if (!win.is_open())
                exit(-1);
            win >> size;
            win.imbue(utf8_loc);
            lists = new wstring[size];
            wregex space(L"\\s+",regex::ECMAScript);
            for ( unsigned int i = 0U; i< size; i++) {
                getline(win, lists[i]);
                if (lists[i].empty())
                    getline(win, lists[i]);
                lists[i].pop_back();
                lists[i] = regex_replace(lists[i], space, L" ");
#ifdef TEST
                wcout.imbue(utf8_loc);
                wcout << lists[i] <<endl;
#endif
                }
#ifdef TEST
            getchar();
#endif
            }
    public:
        hangul_strings() {}
        hangul_strings(wfstream &win) {
            list_write(win);
            }
        ~hangul_strings() {
            if(lists != nullptr)
                delete[] lists;
            }
        void readfile(wfstream &file ) {
            list_write(file);
            }
        friend wostream& operator<< (wostream& wos, hangul_strings &_H ) {
            wos.imbue(utf8_loc);
            for (unsigned int i = 0; i< _H.size; i++) {
                wos << _H.lists[i] << flush;
                if ( i != _H.size-1)
                    wos << '\n';
                }
            return wos;
            }

        operator wstring*() {
            return lists;
            }
        const unsigned int max_sim() {
            vector<pair<double, unsigned int>> sim;
            double _s;
            for (unsigned int i = 1; i < size ; i++ ) {
                _s = (double)( 2.0 * max_lcs(lists[0],lists[i] ) ) / (double) (lists[0].size() + lists[i].size());
                sim.push_back(pair<double,unsigned int>(_s,i));
#ifdef TEST
                cout << "sim ( q, "<< i+1 << " ) = " << sim.back().first <<endl;
#endif
                }
            sort(sim.begin(), sim.end(),pred);
            return (*max_element(sim.begin(), sim.end(),pred)).second + 1;
            }
    };


int main() {
// iostream locale not be synced to filesystem
    ios::sync_with_stdio(false);

// file input
    wfstream wfs("copy.inp",ios::in);
    hangul_strings documents(wfs);
    wfs.close();

// file output
    wfs.open("copy.out", ios::out);
    wfs.imbue(utf8_loc);
#ifdef TEST
    cout << documents.max_sim() <<flush;
#else
    wfs << documents.max_sim() <<flush;
#endif
    wfs.close();

    return 0;
    }
