#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>
#include <string>
#include <vector>

using namespace std;

template <typename T>
class A {
public:
	T _a;
	A(T a);
};

template <typename T>
class B {
public:
	vector<A<T> > _b;
	void push(A<T> a);
};

template <typename T>
A<T>::A(T a) {
	_a = a;
}

template <typename T>
void B<T>::push(A<T> a) {
	_b.push_back(a);
}


int main()
{
	B<int> b;
	b.push(A<int>(1));
	b.push(A<int>(2));
	for (int i = 0; i < b._b.size(); ++i) {
		cout << b._b[i]._a << endl;
	}
    return 0;
}
