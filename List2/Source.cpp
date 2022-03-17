#include<iostream>
#include "List.h"
#include "List.cpp"


using namespace std;

#define tab "\t"


//#define BASE_CHECK
//#define COPY_METHODS_CHECHK
#define HOME_WORK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK

	List list;
	int n;
	cout << "Input list: "; cin >> n;

	for (int i = 0; i < n; i++) 
	{
		list.push_back(rand() % 10);
		//list.push_front(rand() % 100);
	}

	list.print();
	list.revers_print();
	int index;
	int value;
	cout << "Input index: "; cin >> index;
	cout << "Input Value: "; cin >> value;
	list.insert(index, value);
	list.print();
	list.revers_print();
	cout << "Input Delete: "; cin >> index;
	list.erase(index);
	list.print();
	list.revers_print();
#endif // BASE_CHECK

#ifdef COPY_METHODS_CHECHK

	List list = { 5,3,6,7,8,9,713,7 };
	//List list2 = list;
	List list2;
	list2 = list;
	list2.print();
#endif // COPY_METHODS_CHECHK

#ifdef HOME_WORK
	List<int> list = { 3,5,8,13,21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // HOME_WORK

}