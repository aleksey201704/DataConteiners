//ForwardLISt

#include <iostream>
using namespace std;

class Element 
{
	int Data; // Значние элемента
	Element* pNext; // Адрес следующего элемента
	static unsigned int count;
public:
	Element(int Data, Element* pNext = nullptr): 
		Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor: " << this << endl;
	}
	~Element()
	{
		count--;
		cout << "Destructor: " << this << endl;
		
	}

	friend class ForwardList;
};

unsigned int Element::count = 0; // Иницилизация статической переменной


class ForwardList
{
	Element* Head;
	
public:
	ForwardList()
	{
		Head = nullptr;
		// Если голова указвает на 0, то список пуст, т.е
		// не содержит элементов
		// Конструтктор списка
		cout << "LConstructor: " << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor: " << this << endl;
		if (clear()) {
			delete Head;
			Head = nullptr;
			Head->count = 0;
			cout << "Список очищен: " << Head << endl;
			cout << "Количестов: " << Head->count << endl;
		}
	}
	
	//						Adding elements
	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
	}
	//				Methods:
	void print()
	{
		Element* Temp = Head; // Temp - Это Итератор - это указатель при помощи
		//которого можно получить доступ к элменту структуру данных
		// указатель на ноль являтся признак конца списка
		while (Temp)
		{
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		cout << "Количесвто элементов списка: " << Head->count << endl;
	}
	void push_back(int Data)
	{
		if (Head == nullptr) return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext) Temp = Temp->pNext;
		Temp->pNext = new Element(Data); // Добваление нового эле
	}
	//			Removing elments
	void pop_front()
	{
		Element* Erased = Head;
		Head = Head->pNext;
		delete Erased;
	}

	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext) Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
	}

	void insert(int index, int Data)
	{
		if (index > Head->count) return;
		Element* Temp = Head;
		for (int i = 0; i < index-1; i++)
		{
			Temp = Temp->pNext;
		}
		Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;
	}
	bool clear()
	{
		return true;
	}
	void erase(int index) {
		
		if (index == 0)
		{
			pop_front();
		}
		else {
			Element* Temp = Head;
			for (int i = 0; i < index - 1; i++) Temp = Temp->pNext;
//=========================================
			Element* ToDel = Temp->pNext; // Запутался в связи с элементами ??????????
			Temp->pNext = ToDel->pNext;  // Как устанавливается связь между элементами?????????

			delete ToDel;
//========================================
		}	
	}

	void Move(int index,int indexM) 
	{
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++) Temp = Temp->pNext;


	}
};
	

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Веедите размер Списка "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	/*list.print();
	list.push_back(841);
	list.print();
	list.pop_front();
	list.print();*/
	//list.pop_back();
	//list.print();

	int index;
	int value;
	list.print();
	/*cout << "Введите индеск добваляемого элемента: "; cin >> index;
	cout << "Введите значение добваляемого элемента: "; cin >> value;
	list.insert(index, value);*/
	cout << "Введите индеск удаляекмого элемента: "; cin >> index;
	list.erase(index);
	list.print();
	list.clear();
	list.print();



}