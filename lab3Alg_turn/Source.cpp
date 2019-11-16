#include <iostream>
#include <fstream>
#include <string>

using namespace std;

enum PrintEnum 
{
	TOFILE = 0,
	TOCONSOLE = 1
};

struct QElement
{
	QElement() 
	{
		cout << sizeof(this) << " bytes of memory allocated\tto address: " << this << endl;
	}
	~QElement() 
	{
		cout << sizeof(this) << " bytes of memory cleared\tfrom address: " << this << endl;
	}
	string name;
	int index;
	QElement* QNEXT;
};


typedef struct
{
	QElement* QHEAD = nullptr;
	QElement* QTAIL = nullptr;

	void CreateQueueFromFile(string path)
	{	
		// Init lines
		ifstream fin(path);
		int FileLines = 0;
		string Line;

		while (!fin.eof())
		{
			getline(fin, Line);
			FileLines++;
		}
		fin.close();
		fin.open(path);

		// read
		for (int i = 0; i < FileLines; i++)
		{
			QElement* newItem = nullptr;
			try
			{
				newItem = new QElement();
			}
			catch (bad_alloc exc)
			{
				cout << "Exception: " << exc.what() << endl;
				break;
			}
			
			fin >> newItem->name;
			newItem->index = i;
			#pragma region Linking
			if (QHEAD == nullptr && QTAIL == nullptr) 
			{ 
				QHEAD = newItem; 
				QTAIL = newItem;
			}
			else 
			{
				QTAIL->QNEXT = newItem;
				QTAIL = newItem;
			}
			newItem->QNEXT = nullptr;
		
			#pragma endregion

		}
		cout << "Descriptor: HEAD: " << QHEAD << "\tTAIL: " << QTAIL << endl;
		fin.close();
	}

	void PrintQueue(PrintEnum prenum)
	{
		if (QHEAD != nullptr && QTAIL != nullptr) 
		{
			QElement* CurrentElement = QHEAD;
			while (CurrentElement != nullptr)
			{
				cout << CurrentElement->index << ") " << CurrentElement->name << endl;
				CurrentElement = CurrentElement->QNEXT;
			}
		}
		else 
		{
			cout << "Queue is empty" << endl;
		}
	}

	void ClearQueue() 
	{
		if (QTAIL != nullptr && QHEAD != nullptr) 
		{
			QElement* CurrentElement = QHEAD;
			QElement* NextElement;
			while (CurrentElement != nullptr)
			{
				NextElement = CurrentElement->QNEXT;
				delete CurrentElement;
				CurrentElement = NextElement;
			}
			QHEAD = nullptr;
			QTAIL = nullptr;
		}
		else 
		{
			cout << "Queue is empty" << endl;
		}
	}

	void PushElement(QElement* element)
	{
		element->QNEXT = nullptr;
		if (QHEAD != nullptr && QTAIL != nullptr) 
		{
			element->index = QTAIL->index + 1;
			QTAIL->QNEXT = element;
			QTAIL = element;
		}
		else 
		{
			element->index = 0;
			QTAIL = element;
			QHEAD = element;
		}
		ReIndex();
	}

	void PopElement()
	{
		if (QHEAD != nullptr && QTAIL != nullptr) 
		{
			if (QHEAD == QTAIL) // 1 element
			{
				delete QHEAD;
				QHEAD = nullptr;
				QTAIL = nullptr;
			}
			else 
			{
				QElement* Head = QHEAD;
				QHEAD = QHEAD->QNEXT;
				delete Head;
			}
			ReIndex();
		}
		else 
		{
			cout << "Queue is empty" << endl;
		}
	}

	void ReIndex() 
	{
		if (QHEAD != nullptr && QTAIL != nullptr)
		{
			QElement* CurrentElement = QHEAD;
			int index = 0;
			while (CurrentElement != nullptr) 
			{
				CurrentElement->index = index;
				index++;
				CurrentElement = CurrentElement->QNEXT;
			}
		}
	}

}Queue,CppQueue;

int main() 
{
	setlocale(LC_ALL, "Rus");
	int userChoice;
	string name;
	QElement* newElement;
	string path = "Users.txt";
	Queue* queune = new Queue();

	userChoice = 1;
	while (userChoice >= 1 && userChoice <= 5)
	{
		cout << endl;
		cout << "Menu" << endl;
		cout << "1. Create queue from file" << endl;
		cout << "2. Print queue" << endl;
		cout << "3. Clear queue" << endl;
		cout << "4. Push to queue" << endl;
		cout << "5. Pop from queue" << endl;
		cout << "Else - Exit" << endl;
		cout << "> ";
		cin >> userChoice;
		
		switch (userChoice) 
		{
			case 1: 
				queune->CreateQueueFromFile(path);
				break;
			case 2: 
				queune->PrintQueue(TOCONSOLE);
				break;
			case 3: 
				queune->ClearQueue();
				break;
			case 4: 
				cout << "Name: ";
				cin >> name;
				newElement = new QElement();
				newElement->name = name;
				queune->PushElement(newElement);
				break;
			case 5: 
				queune->PopElement();
				break;
			default: break;
		}
	}

	return 0;
}