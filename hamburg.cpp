#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>

using namespace std;

class table {
	private:
	int eating_hanburg = 0;
	char *placing = nullptr;
	int length;
	int maximum_distance;
	bool all_erased() {
		bool result = true;
		for (int i = 0; i< length ; i++) {
			 result = result && (placing[i] == 'X');
		}
		return result;
	}
	bool no_hamburger() {
		if (placing == nullptr || all_erased() ) return true;
		return find( placing, (placing + length+1), 'H') == (placing + length+1);
	}
	int eating_hamburger(int idx, int direction) {
	    if (direction == 0) return -1;
	    else if (direction >0) direction = 1;
	    else direction  = -1;
		if (placing == nullptr || all_erased() || maximum_distance <= 0) return -1;
		if (placing[idx] == 'H' || placing[idx] == 'X') return -2;
		if (placing[idx] == 'P' && placing[idx+(maximum_distance * direction)] == 'H' ) {
			erase(idx);
			erase(idx+(maximum_distance* direction));
			return 0;
		}
		else if ( placing[idx] == 'P' && placing[idx-(maximum_distance * direction)] == 'H')  {
			erase(idx-(maximum_distance * direction));
			erase(idx);
			return 0;
		}
		if (idx >= length || idx <0) return -3;
        return -2;
	}
	void erase(const int idx) {
		if ( placing == nullptr || idx >= length || idx <0) return;
		placing[idx] = 'X';
		}
   const int alloc_hamburg(const int dir) {
        int result = 0;
        if( dir != -1 && dir != 1) return -1;

        int maxd = maximum_distance;
        char *tmp = new char[length];
	    strcpy(tmp, placing);

        int status = -4;
		int loc = 0;

		while (!no_hamburger()) {
			status = eating_hamburger(loc,dir);
			if ( status == -1) break;
			switch(status) {
				case -2 : loc++; break;
				case -3 : maximum_distance--; loc = 0; break;
				case  0 : result++; loc++; break;
			}

		}

		maximum_distance = maxd;
        strcpy(placing, tmp);

        return result;
    }
	public:
	table(){};
	~table(){ delete[] placing;}
	int read_file() {
		fstream fs("hamburg.inp",ios::in);
		if (!fs.is_open()) return -1;
		fs >> maximum_distance >> length;
		if (length <= 0) return -1;
		placing = new char[length+1];
		for (unsigned int i = 0; i< (unsigned int) length ; i++)
		       fs >> placing[i];
		placing[length] = 0;
		fs.close();
		return 0;
		}

	int calculate() {
		int result_l, result_r, rresult_l, rresult_r;
		result_l = alloc_hamburg(-1);
		result_r = alloc_hamburg( 1);

        char *tmp = new char[length];
	    strcpy(tmp, placing);

	    reverse(placing, placing+length);

		rresult_l = alloc_hamburg(1);
		rresult_r = alloc_hamburg(-1);

	    strcpy(placing, tmp);

		return max( max(result_l, result_r), max(rresult_l, rresult_r) );
	}
#ifdef TEST
	friend ostream& operator<<(ostream& os, table& _T) {
		os << "Size : " << _T.length << '\n';
		os << "Reachable Distance : " << _T.maximum_distance << '\n';
		os << _T.placing <<flush;
		return os;
	}
#endif
};

int main() {
	table TBL;
	if (TBL.read_file() == -1) {cerr << "File CANNOT Open!" << endl; return -1;}
        int result = TBL.calculate();
#ifdef TEST
	cout << TBL<< '\n';
	cout << result << flush;
#endif
	fstream res("hamburg.out", ios::out);
	res << result << flush;
	res.close();
	return 0;
}
