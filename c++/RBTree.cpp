#define _CRT_SECURE_NO_WARNINGS
#include"RBTree.h"
void testRB1()
{
	zjh::RBTree<int, int> R;
	R.Insert(make_pair(1, 1));
	cout << R.Is_RBTree() << endl;
	R.Insert(make_pair(12, 12));
	cout << R.Is_RBTree() << endl;
	R.Insert(make_pair(31, 31));
	cout << R.Is_RBTree() << endl;
	R.Insert(make_pair(3, 3));
	cout << R.Is_RBTree() << endl;
	R.Insert(make_pair(4, 4));
	cout << R.Is_RBTree() << endl;
	R.Insert(make_pair(15, 15));
	cout << R.Is_RBTree() << endl;
	R.Insert(make_pair(11, 11));
	cout << R.Is_RBTree() << endl;
	R.Insert(make_pair(123, 123));
	cout << R.Is_RBTree() << endl;
	R.Insert(make_pair(14, 14));
	cout << R.Is_RBTree() << endl;
	R.Insert(make_pair(155, 155));
	cout << R.Is_RBTree() << endl;
	R.Insert(make_pair(71, 71));
	cout << R.Is_RBTree() << endl;
	R.Insert(make_pair(13, 13));
	cout << R.Is_RBTree() << endl;
	R.Insert(make_pair(7, 7));
	cout << R.Is_RBTree() << endl;
	R.Insert(make_pair(5, 5));
	cout << R.Is_RBTree() << endl;
	R.Inorder();
}
int main()
{
	testRB1();
	return 0;
}
