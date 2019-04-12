#include <bits/stdc++.h>
using namespace std;

class input_string {
    fstream fs;
    unsigned int sz;
    string *_S=nullptr;

    const unsigned int is_palindrome(const unsigned int idx) {
        string tmp = _S[idx];
        bool _palin = false, _psudo = false;
        #ifdef TEST
        cout << "Init" << "- " << tmp << endl;
        #endif // TEST
        while(true) {
            if (tmp.empty()) {_palin = true; break;}
            if (tmp.front() == tmp.back()) {
                tmp.erase(tmp.begin());
                if ( !tmp.empty() && tmp.begin() != ( tmp.end()-1 ) ) tmp.pop_back();
                }
            else if (tmp.front() == *(tmp.end()-2)) {
                tmp.erase(tmp.begin());
                if ( tmp.length() >= 2 && tmp.begin() != ( tmp.end()-2 ) ) tmp.erase(tmp.end()-2);
                _psudo = true;
                }
            else if (*(tmp.begin()+1) == tmp.back()) {
                tmp.pop_back();
                if ( tmp.length() >= 2 && tmp.begin() != ( tmp.end()-1 ) ) tmp.erase(tmp.begin());
                _psudo = true;
                }
            else { _palin = false; break;}
            #ifdef TEST
            cout << tmp << endl;
            #endif // TEST
            }
            if (_palin && _psudo) {
                #ifdef TEST
                cout << _S[idx] << " is pseudo_palindrome!" <<endl
                #endif // TEST
                return 2;
                }
            else if (_palin && !_psudo) {
                #ifdef TEST
                cout << _S[idx] << " is palindrome!" <<endl;
                #endif
                return 1;
                }
            else {
                #ifdef TEST
                cout << _S[idx] << " is not palindrome either psuedo_palindrome!" <<endl;
                #endif
                return 3;
                }
        }
public:
    input_string(){};
    ~input_string(){ delete[] _S; }
    void mount(string const& filename,const char _mode) {
        if(fs.is_open()) fs.close();
        else if (filename.size()==0) {cout << "Invalid Argument!"<<endl; return;}
        switch(_mode) {
            case 'O' : fs.open(filename, fstream::out)   ; break;
            case 'I' : fs.open(filename, fstream::in )   ; break;
            default  : cout << "Invalid Argument!" <<endl; break;
            }
        if (!fs.is_open()) {
            cout << "File is invalid. file isn't exist or is crashed!" <<endl;
            fs.close();
            }
        return;
        }
    void save() {
        if (!fs.is_open()) { cout << "Mount input file first!" <<endl; return; }
        string _ip;
        fs >> sz;
        _S = new string[sz];
        for (unsigned int i = 0U ; i<sz ; i++) { fs >>_ip; _S[i]=_ip; }
        }
    void result() {
            if (_S == nullptr ) return;
            this->mount("palin.out",'O');
            for (unsigned int i = 0U ; i<sz ; i++) {
                #ifdef TEST
                cout << is_palindrome(i) <<endl;
                #endif
                fs << is_palindrome(i);
                if ( i+1 != sz ) fs << '\n';
                }
    	    this->fs.close();
    	    }
    };

int main() {
    input_string INP;
    INP.mount("palin.inp",'I');
    INP.save();
    INP.result();
    return 0;
    }
