#define _CRT_SECURE_NO_WARNINGS
#include"vector.h"
void textvector1()
{
	zjh::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);
	v.push_back(8);
	v.push_back(9);
	v.push_back(10);
	for (auto e : v)
	{
		cout << e << ' ';
	}
	cout << endl;
	v.insert(v.begin()+3, 666);
	for (auto e : v)
	{
		cout << e << ' ';
	}
	cout << endl;
	v.erase(v.begin() + 3);
	for (auto e : v)
	{
		cout << e << ' ';
	}
	cout << endl;
}
int main()
{	
	textvector1();
	return 0;
}
