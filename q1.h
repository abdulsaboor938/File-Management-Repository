#include<iostream>
#include<vector>
using namespace std;

// definition of user class
class userClass
{
	int id;
	bool operation; // false is read, true is write

public:
	// constructor of class
	userClass(int temp_id, bool temp_op) :id(temp_id), operation(temp_op) {}
	friend ostream& operator<<(ostream& out, userClass& temp)
	{
		if (temp.operation == false)
			out << "User ID : " << temp.id << ", wants to read from this file" << endl;
		else
			out << "User ID : " << temp.id << ", wants to write on this file" << endl;
		return out;
	}
};

// implementation of priority queue
class qItem
{
	int key;
	userClass user;

	// default constructor of class
	qItem(int temp_key, userClass temp_user) :key(temp_key), user(temp_user) {}

	friend class queue;
};

// implemetation of queue class
class minHeap
{
	qItem* arr;
	int capacity;
	int totalitems;

public:
	minHeap() :arr(nullptr),capacity(0), totalitems(0) {}
	minHeap(int _capcacity)
	{
		this->capacity = _capcacity;
		while (this->capacity < 1)
		{
			cout << "Please enter a number >1 : ";
			cin >> this->capacity;
		}
		arr = new heapItem<k, v>[this->capacity]; // allocation of memory
		this->totalitems = 0;
	}
	~minHeap()
	{
		delete[] this->arr;
		this->totalitems = this->capacity = 0;
	}
	bool isEmpty()
	{
		return(this->arr == nullptr);
	}

	void insert(k key, v value)
	{
		if (this->totalitems == this->capacity) // code to grow heap
		{
			heapItem<k, v>* temp = new heapItem<k, v>[this->capacity * 2];
			for (int i = 0; i < totalitems; i++)
				temp[i] = this->arr[i];
			delete[] this->arr;
			arr = temp;
			this->capacity *= 2;
		}
		// code to insert key value pair in accordance with keys
		heapItem<k, v>* temp = &this->arr[this->totalitems++];
		temp->key = key;
		temp->value = value;
		
		// reheaping to minimum heap
		int i = this->totalitems - 1; // pointing to last element
		while (i != 0 && (arr + ((i - 1) / 2))->key > (arr+i)->key )
		{
			swap((arr + ((i - 1) / 2))->key, (arr + i)->key);
			swap((arr + ((i - 1) / 2))->value, (arr + i)->value);
			i = (i - 1) / 2;
		} 
	}
	void deleteMin()
	{
		assert(this->totalitems > 0);
		swap(arr->key, (arr + (totalitems-1))->key);
		swap(arr->value, (arr + (totalitems-1))->value);
		this->totalitems--;

		int i=0; // pointing to first element
		while (i <(totalitems-1))
		{
			if ((arr + i)->key > max((arr + ((i * 2) + 1))->key, (arr + ((i * 2) + 2))->key))
			{
				// if left child is lesser than left
				if ((arr + ((i * 2) + 1))->key < (arr + ((i * 2) + 2))->key)
				{
					swap((arr + ((i * 2) + 1))->key, (arr + i)->key);
					swap((arr + ((i * 2) + 1))->key, (arr + i)->key);
					i = ((i * 2) + 1);
				}
				else // if right child is lesser than right
				{
					swap((arr + ((i * 2) + 2))->key, (arr + i)->key);
					swap((arr + ((i * 2) + 2))->key, (arr + i)->key);
					i = ((i * 2) + 2);

				}
			}
		}
	}
	void getMin(v& _value)
	{
		assert(this->totalitems > 0);
		_value = this->arr->value;
	}
};