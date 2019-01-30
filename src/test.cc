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
	vector<vector<int>> x(3, vector<int>(3, 100));
	cout << x[0][0] << endl;
    return 0;
}
