#include<iostream>
#include"q1.h"
using namespace std;

int main()
{
	user u1(1234, false), u2(3456, true);
	cout << u1 << u2 << u1 << endl;

	heap<int, user> h1;
	h1.insert(2, u1);
	h1.insert(4, u2);
	h1.insert(1, u1);

	system("pause");
	return 0;
}