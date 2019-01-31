#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <set>
#include <string>
#include <vector>

using namespace std;

class A {
public:
	int _a;
	A(int a){_a = a;}
	~A(){ cout << "dec A" << endl;}

	void fuck() {
		cout << "fuck A" << endl;
	}
};

class B : public A {
public:
	B(int a) : A(a){}
	~B(){}
};

int main()
{
	srand(time(NULL));
	cout << rand() << endl;
	for (int i= 0; i < 20; ++i) {
		cout << rand() << endl;
	double theta = (((rand() % 1000000) * 1.0) / 1000000) * 10 + 5;
	cout << theta << endl;
	}
    return 0;
}
