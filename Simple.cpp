﻿#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstrcutor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestrcutor:\t" << this << endl;
		}
		friend class List;
	}*Head, *Tail;	//Сразу же после описания класса Element объявляем два указателя на Element
	size_t size;

	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp) :Temp(Temp)
		{
#ifdef DEBUG
			cout << "BaseItConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~ConstBaseIterator()
		{
#ifdef DEBUG
			cout << "BaseItDestructor:\t" << this << endl;
#endif // DEBUG
		}

		bool operator==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}

		const int& operator*()const
		{
			return Temp->Data;
		}
	};
public:
	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~ConstIterator()
		{
#ifdef DEBUG
			cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
		}

		//					Operators:
		ConstIterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
	};

	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "RItConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~ConstReverseIterator()
		{
#ifdef DEBUG
			cout << "RItDestructor:\t" << this << endl;
#endif // DEBUG
		}

		//					Operators:
		ConstReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstReverseIterator& operator++(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
	};

	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp) {}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) :ConstReverseIterator(Temp) {}
		int& operator*()
		{
			return Temp->Data;
		}
	};


	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ConstIterator cbegin()const
	{
		return Head;
	}
	ConstIterator cend()const
	{
		return nullptr;
	}

	ReverseIterator rbegin()
	{
		return Tail;
	}
	ReverseIterator rend()
	{
		return nullptr;
	}
	ConstReverseIterator crbegin()const
	{
		return Tail;
	}
	ConstReverseIterator crend()const
	{
		return nullptr;
	}

	int get_size()const
	{
		return size;
	}

	//						Constructor:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		/*for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}*/
		for (int i : il)push_back(i);
	}
	List(const List& other) :List()
	{
		*this = other;
		cout << "CopyConstructor:\t" << this << endl;
	}
	List(List&& other)
	{
		*this = std::move(other);
		cout << "MoveConstructor:\t" << this << endl;
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

	//						Operators:
	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		//Deep copy (Глубокое копирование) - Побитовое копирование:
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	List& operator=(List&& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		//Shallow copy - Поверхностное копирование:
		this->Head = other.Head;
		this->Tail = other.Tail;
		this->size = other.size;

		//Обнуление other:
		other.Head = nullptr;
		other.Tail = nullptr;
		other.size = 0;
		cout << "MoveAssignment:\t" << this << endl;
	}

	const int& operator[](size_t index)const
	{
		if (index >= size)throw std::exception("Error:out of range");
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;
		}
		return Temp->Data;
	}

	//						Adding elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			//Добавление элемента в пустой список:
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		//Общий случай:
		Element* New = new Element(Data);//1)
		New->pNext = Head;//2)
		Head->pPrev = New;//3)
		Head = New;
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)return push_front(Data);
		Element* New = new Element(Data);	//1)
		New->pPrev = Tail;	//2)
		Tail->pNext = New;	//3)
		Tail = New;	//4)
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index > size)	return;
		if (Index == 0)		return push_front(Data);
		if (Index == size)	return push_back(Data);

		Element* Temp;	//Создаем итератор, но мы пока не знаем, 
		//с какой стороны списка лучше зайти, с начала, или с конца.
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)
				Temp = Temp->pPrev;
		}

		//Неважно, с какой стороны мы добрались до нужной позиции,
		//вставка элемента будет осуществляться по одному и тому же алгоритму:
		Element* New = new Element(Data);	//1)
		New->pNext = Temp;	//2)
		New->pPrev = Temp->pPrev;//3)
		Temp->pPrev->pNext = New;//4)
		Temp->pPrev = New;
		size++;
	}

	//					Removing Elements:
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			//Удаление единственного элемента из списка:
			delete Head;
			Head = Tail = nullptr;
			size--;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	void erase(int Index)
	{
		if (Index >= size)return;
		if (Index == 0)return pop_front();
		if (Index == size - 1)return pop_back();
		//Доходим до нужного элемента:
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}

		//Исключаем элемент из списка:
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;

		//Удаляем элемент из памяти:
		delete Temp;
		size--;
	}

	//					Methods:
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
	void reverse_print()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
};

void print_list(const List& list)
{
	for (List::ConstIterator it = list.cbegin(); it != list.cend(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;
}
void reverse_print_list(const List& list)
{
	for (List::ConstReverseIterator rit = list.crbegin(); rit != list.crend(); rit++)
		cout << *rit << tab;
	cout << endl;
}

//#define BASE_CHECK
//#define ITERATORS_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	list.reverse_print();

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
	list.reverse_print();
#endif // BASE_CHECK

#ifdef ITERATORS_CHECK
	List list = { 3,5,8,13,21 };
	list.print();
	list.reverse_print();
	List list2 = list;
	/*list2.print();
	list2.reverse_print();*/
	for (int i : list2)cout << i << tab; cout << endl;

	for (List::ReverseIterator rit = list2.rbegin(); rit != list2.rend(); rit++)
	{
		cout << *rit << tab;
	}
	cout << endl;

	print_list(list);
	reverse_print_list(list);
#endif // ITERATORS_CHECK

	List list = { 3, 5, 8, 13, 21, 34, 55, 89 };
	try
	{
		for (int i = 0; i < list.get_size() * 2; i++)
		{
			cout << list[i] << tab;
		}
		cout << endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
	catch (...)
	{
		//	/EHa
		std::cerr << "Something happened" << endl;
	}
}