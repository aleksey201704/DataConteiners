#include<iostream>
using namespace std;

void elevator(int floor)
{
	if (floor == 0)
	{
		cout << "Нулевой этаж" << endl;
		return;
	}
	cout << " " << floor << " Этаж" << endl;
	elevator(floor - 1);
	cout << "Вы на " << floor << " этаже" << endl;
}

int factorial(int n)
{
	
	if (n == 0 || n==1) return 1;
	return n * factorial(n - 1);

}
	
void main()
{
	setlocale(LC_ALL, "");
	//cout << "Hello";
	//main();
	int floor;
	int F;
	/*cout << "ВВедите на какой этаж: "; cin >> floor;
	elevator(floor);*/

	cout << "Введите число факториал n!=1*2*n! : "; cin >> F;
	cout << factorial(F);

}