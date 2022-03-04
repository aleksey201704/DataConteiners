//ForwardLISt

#include <iostream>
#include <vector>
#include <list>
using namespace std;

namespace std {
	template <typename _CharT, typename _Traits>
	inline basic_ostream<_CharT, _Traits>&
		tab(basic_ostream<_CharT, _Traits>& __os) {
		return __os.put(__os.widen('\t'));
	}
}

class ForwardList;

  
//class Element 
//{
//	int Data; // Значние элемента
//	Element* pNext; // Адрес следующего элемента
//	static unsigned int count;
//public:
//	Element(int Data, Element* pNext = nullptr): 
//		Data(Data), pNext(pNext)
//	{
//		count++;
//		cout << "ElementConstructor: " << this << endl;
//	}
//	~Element()
//	{
//		count--;
//		cout << "ElementDestructor: " << this << endl;
//		
//	}
//	friend class Iterator;
//	friend class ForwardList;
//	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
//	//friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
//};
class Element
{
	int Data;		//Значение элемента
	Element* pNext;	//Адрес следующего элемента
	static unsigned int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class Iterator;
	friend class ForwardList;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

unsigned int Element::count = 0; // Иницилизация статической переменной

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp) :Temp(Temp)
	{
		cout << "IteratorConstructor: \t" << this << endl;
	}
	~Iterator()
	{
		cout << "ITeratorDestructor: \t" << this << endl;
	}
	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator operator++(int)
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}

	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}

	const int& operator*()const
	{
		return Temp->Data;
	}
	int& operator*()
	{
		return Temp->Data;
	}


};

class ForwardList
{
	Element* Head;
	unsigned int size;
public:
	Element* getHead()const { return Head; }
	unsigned int get_size()const { return size;}
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		// Если голова указвает на 0, то список пуст, т.е
		// не содержит элементов
		// Конструтктор списка
		cout << "LConstructor: " << this << endl;
	}
	ForwardList(const initializer_list<int>& il) :ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		{
			push_back(Temp->Data);
		}*/
		*this = other;
		cout << "CopyConstructor:\t" << endl;
	}
	ForwardList(ForwardList&& other)
	{
		*this = std::move(other);
		cout << "MoveConstructor:\t" << this << endl;
	}


	~ForwardList()
	{
		while (Head) pop_front();
		cout << "LDestructor: " << this << endl;
	}
	// Operators
	


	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		{
			push_back(Temp->Data);
		}
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "MoveAssignment:\t" << this << endl;
		return *this;
	}

	const int& operator[](unsigned int index)const
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}
	int& operator[](unsigned int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}

	//						Adding elements
	void push_front(int Data)
	{
		Head = new Element(Data,Head);
		size++;
		
		/*Element* New = new Element(Data)
		New->pNext = Head;
		Head = New;*/
	}
	//				Methods:

	void revers() {	
		Element* Temp = Head;
		for (int j = 0; j < size - 1; j++)
		{
			for (int i = 0; i < size - 1; i++)	Temp = Temp->pNext;
			(j==0) ? push_front(Temp->Data): insert(j, Temp->Data);
			pop_back();
			Temp = Head;
		}
	}

	void print()
	{
		Element* Temp = Head; // Temp - Это Итератор - это указатель при помощи
		//которого можно получить доступ к элменту структуру данных
		// указатель на ноль являтся признак конца списка
		/*while (Temp)
		{
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
			Temp = Temp->pNext;
		}*/

		for (Element* Temp=Head;Temp;Temp=Temp->pNext)
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
			
				
		cout << "Количесвто элементов списка: " << size << endl;
		cout << "Общее Количесвто элементов: " << Head->count << endl;
	}
	void push_back(int Data)
	{
		
		if (Head == nullptr) return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext) Temp = Temp->pNext;
		Temp->pNext = new Element(Data); // Добваление нового эле
		size++;

		
	}

	void insert(int index, int Data)
	{
		if (index > Head->count) return;
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext  = new Element(Data,Temp->pNext);
		/*Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;*/
		size++;
	}

	//			Removing elments
	void pop_front()
	{
		Element* Erased = Head;
		Head = Head->pNext;
		delete Erased;
		size--;
	}

	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext) Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	
	void erase(int index) {
		
		if (index == Head->count - 1) return pop_back();
		if (index >= Head->count) {
			cout << "Error: out of range" << endl;
			return;
		}
		if (index == 0) return pop_front();

		// 1) Доходим до нужного элемента:
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++) Temp = Temp->pNext;
		// 2) Запоминаема адрес удаляемого элемента
		Element* ToDel = Temp->pNext; 
		// 3) Исключаем удаляемый эелемнт из списка
		Temp->pNext = Temp->pNext->pNext;  

		delete ToDel; 
		size--;
					
	}

	void uniqe()
	{
		int* NewMassiv = new int[size];
		Element* Temp = Head;
		Element* DelTemp = Head;
		int r = 0,t=0,s=size;
		int NumDel = 0;
			
		for (int i = 0; i < size; i++) 
		{
			NewMassiv[i] = Temp->Data; // переписал в массив
			Temp = Temp->pNext;
		}

		Temp=Head;
		for (int i = 0; i < size; i++) // Перебираем ForwardLIst
		{
			for (int j = 0; j < s; j++) // Перебираем массив
			{
				if (NewMassiv[j]==Temp->Data) r++;

				if (r > 1)				// Если больше совпадений то есть одинаковые
				{ 
					NumDel = Temp->Data; // Запомнил число для удаления;
				}
			}
			// Удаляем все Совпадения
			for (int i = 0; i < size; i++) 
			{ 
				if (DelTemp->Data == NumDel) erase(i); 
				DelTemp = DelTemp->pNext;
			}


			if (r > 1) cout << "Есть совпадения";
			r = 0;
			Temp = Temp->pNext;
		}
	}
	
};
	
ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList cat = left;
	for (Element* Temp = right.getHead(); Temp; Temp = Temp->pNext)
		cat.push_back(Temp->Data);
	
	return cat;
}



void main()
{
	setlocale(LC_ALL, "");
	ForwardList list1 = { 3,5,5,13,21 };
	ForwardList list2 = { 34,5,89 };
	ForwardList list3 = list1 + list2;
	

	list3.print();
	//list3.revers();
	list3.uniqe();
	list3.print();

	//int n;
	//cout << "Веедите размер Списка "; cin >> n;
	//ForwardList list;
	//for (int i = 0; i < n; i++)
	//{
	//	//list.push_front(rand() % 100);
	//	list.push_back(rand() % 100);
	//}
	//int index;
	////int value;
	//list.print();
	///*cout << "Введите индеск добваляемого элемента: "; cin >> index;
	//cout << "Введите значение добваляемого элемента: "; cin >> value;
	//list.insert(index, value);*/
	//cout << "Введите индеск удаляемого элемента: "; cin >> index;
	//list.erase(index);
	//list.print();
	
	/*ForwardList list2;
	list2.push_back(123);
	list2.push_back(456);
	list2.push_back(789);
	list2.insert(2, 154);
	list2.print();*/


	/*ForwardList list = { 3, 5, 8, 13, 21 };

	for (int i : list)
	{
		cout << i << tab <<endl;
	}
	cout << endl;*/

}