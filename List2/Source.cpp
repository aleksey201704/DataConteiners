#include<iostream>
using namespace std;

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
			cout << "EConstructor:" << tab << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:" << tab << this << endl;
		}
		friend class List;
		friend class Iterator;


	}*Head,*Tail;
	size_t size; // Натуральное число

public:
	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp=nullptr):Temp(Temp) 
		{ 
			cout << "CIterator: \t" << this << endl; 
		}
		
		~Iterator()
		{ 
			cout << "DIterator: \t" << this << endl; 
		}

		bool operator !=(const Iterator& other)const
		{
			return this->Temp != other.Temp;
		}

		Iterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}

		const int& operator*()const 
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



	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor" << tab << this << endl;
	}
	List(const std::initializer_list<int>& il) : List()
	{
		for (int const* it = il.begin(); it != il.end();it++) push_back(*it);
	}
	List(const List& other) :List()
	{
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) 
			push_back(Temp->Data);
		cout << "copyConstrucrot:" << this << endl;
	}
	~List()
	{
		//while (Head) pop_front();
		//while (Tail)pop_back();
		cout << "LDestructor" << tab << this << endl;
	}
	// Operators

	List& operator=(const List& other)
	{
		if (this == &other) return *this;
		while (Head) pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "CopyAssigment: \t" << this << endl;
		return *this;

	}
	// Adding Elements
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr) {
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		Element* New = new Element(Data);
		New->pNext = Head;
		Head->pPrev = New;
		Head = New;
		size++;
	}

	void print()const
	{
		for (Element*Temp=Head;Temp;Temp=Temp->pNext)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
			cout << "size:" << tab << size << endl;
	}

	void revers_print()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
	}
	
	// Adding Elements
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr) return push_front(Data);
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}

	void insert(int index,int Data) 
	{
		if (index > size) return;
		if (index == 0) return push_front(Data);
		if (index == size) return push_back(Data);
		Element* Temp;
		if (index < size / 2) {
			Temp = Head;
			for (int i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - 1 - index; i++)Temp = Temp = Temp->pPrev;	
		}
		Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;
		size++;

	}

	// Removing Elements
	void pop_front() 
	{
		if (Head == nullptr && Tail == nullptr)  return;
		if (Head ==  Tail) 
		{
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
		if (Head == Tail) return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}

	void erase(int index)
	{
		if (index == 0) return pop_front();
		if (index == size-1) return pop_back();
		if (index >= size) return;
		Element* Temp;
		if (index < size / 2) {
			Temp = Head;
			for (int i = 0; i < index; i++) Temp = Temp->pNext;
			
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size-index-1; i++) Temp = Temp->pPrev;
			
		}
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
		size--;
	}


};

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
	List list = { 3,5,8,13,21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // HOME_WORK

}