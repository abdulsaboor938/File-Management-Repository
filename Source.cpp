#include<iostream>
#include"q2.h"
using namespace std;

//int main()
//{
//	user u1(1234, false), u2(3456, true);
//	cout << u1 << u2 << u1 << endl;
//
//	heap<int, user> h1,h2;
//	heapItem<int, user> utemp;
//	utemp = h1.findMax();
//	utemp = h1.extractMax();
//	h1.insert(2, u1);
//	h1.insert(4, u2);
//	h1.insert(6, u2);
//	h1.insert(8, u1);
//	h1.insert(1, u2);
//	h1.insert(7, u1);
//	utemp = h1.findMax();
//	utemp = h1.findMin();
//	utemp = h1.extractMax();
//	utemp = h1.extractMax();
//	utemp = h1.extractMax();
//	utemp = h1.extractMax();
//	utemp = h1.extractMax();
//	utemp = h1.extractMax();
//	h1.insert(2, u1);
//	cout << u1;
//
//	utemp = h1.findMax();
//	cout << u1;
//	utemp = h1.findMin();
//	cout << u1;
//
//	vector<heapItem<int, user>> arr;
//	arr.resize(8);
//	heapItem<int, user> temp;
//	temp.key = 0; temp.value = u1;
//	for (int i = 0; i < 6; i++)
//	{
//		arr[i] = temp;
//		temp.key++;
//	}
//
//	h2.buildQueue(arr,6);
//	
//	system("pause");
//	return 0;
//}

int main()
{
	hashmap <int,user>h1(11);
	h1.insert(3);
	h1.insert(14);
	h1.requestAccess(3, user(12,false), 2);
	h1.requestAccess(3, user(13,false), 3);
	h1.requestAccess(3, user(14,false), -1);
	h1.requestAccess(3, user(12,false), -2);
	h1.requestAccess(3, user(12,true), -2);
	h1.requestAccess(3, user(12,false), -2);
	h1.requestAccess(3, user(12,false), -2);
	h1.releasefile(3);
	h1.releasefile(3);
	h1.releasefile(3);
	h1.printTable();
	system("pause");
	return 0;
}