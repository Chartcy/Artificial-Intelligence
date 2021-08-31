#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

enum item {Monkey, Banana, Box};
enum place {a, b, c};

class state {
public:
	place monkeyplace;
	place boxplace;
	place bananaplace;
	bool onbox;
	bool hasbanana;
	int id, prev;
	string move;
}s;

vector <state> v;

int getrand(int L, int R) {
	int ret = --L;
	while(ret == L) ret = rand() * rand() % (R - L + 1) + L;
	return ret;
}

string place_to_string(int p) {
	return p == 0 ? "a" : p == 1 ? "b" : "c";
}

void printstate(state s) {
    cout << "monkey: " << place_to_string((int)s.monkeyplace) << endl;
    cout << "box: " << place_to_string((int)s.boxplace) << endl;
    cout << "banana: " << place_to_string((int)s.bananaplace) << endl << endl;
}

void printprocess(state s) {
	if(s.id != 0) {
		printprocess(v[s.prev]);
        cout << s.move << endl;
	}
}

int main() {
	srand(time(NULL));
	s.monkeyplace = (place)getrand(0, 2);
	s.boxplace = (place)getrand(0, 2);
	s.bananaplace = (place)getrand(0, 2);
	s.onbox = false;
	s.hasbanana = false;
	s.id = 0;
	s.prev = -1;
	v.push_back(s);
	printstate(s);

	for(int p = 0; v.size() < 10000; ++p) {
		state f = v[p];
		if(f.hasbanana) {
			printprocess(f);
			break;
		}
		for(int i = a; i <= c; i++) {
			for(int j = a; j <= c; j++) {
				if(i == j) continue;
				if(!f.onbox && f.monkeyplace == i) {//goto
					state news = f;
					news.monkeyplace = (place)j;
					news.id = v.size();
					news.prev = f.id;
					news.move = "Goto(" + place_to_string(i) + ", " + place_to_string(j) + ")";
					v.push_back(news);
				}
				if(!f.onbox && f.monkeyplace == i && f.boxplace == i) {//pushbox
					state news = f;
					news.monkeyplace = (place)j;
					news.boxplace = (place)j;
					news.id = v.size();
					news.prev = f.id;
					news.move = "Pushbox(" + place_to_string(i) + ", " + place_to_string(j) + ")";
					v.push_back(news);
				}
			}
			if(!f.onbox && f.monkeyplace == i && f.boxplace == i) {//climb
				state news = f;
				news.onbox = true;
				news.id = v.size();
				news.prev = f.id;
				news.move = "Climb";
				v.push_back(news);
			}
			if(f.onbox && f.monkeyplace == i && f.bananaplace == i) {//grasp
				state news = f;
				news.hasbanana = true;
				news.id = v.size();
				news.prev = f.id;
				news.move = "Grasp";
				v.push_back(news);
			}
		}
	}
}
