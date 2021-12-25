#include<iostream>
#include<assert.h>
#include<vector>
using namespace std;

// definition of user class
class user
{
	int id;
	bool operation; // false is read, true is write

	// default constructor for use in heap
	user() :id(0), operation(false) {}

public:
	// constructor of class
	user(int temp_id, bool temp_op) :id(temp_id), operation(temp_op) {}
	friend ostream& operator<<(ostream& out, user& temp)
	{
		if (temp.operation == false)
			out << "User ID : " << temp.id << ", wants to read from this file" << endl;
		else
			out << "User ID : " << temp.id << ", wants to write on this file" << endl;
		return out;
	}
	
	// friend classes
	template<class k, class v>
	friend class heapItem;
	template<class k, class v>
	friend class heap;
};

// definition of heap class
template<class k, class v>
class heapItem
{
	k key;
	v value;

	template<class k, class v>
	friend class heap;
};

template<class k, class v>
class heap
{
	vector<heapItem<k, v>> arr;
	int capacity;
	int totalitems;
	heapItem<k, v> minItem; // variable to maintain minimum priority user

public:
	heap() :capacity(1), totalitems(0)
	{
		this->arr.resize(1); // resizing vector to minmum
	}
	~heap()
	{
		arr.clear(); // clearig vector
		this->totalitems = this->capacity = 0;
	}
	bool isEmpty()
	{
		return(this->totalitems == 0); // returns true if no items are present
	}

	void insert(k const key, v const value)
	{
		if (this->totalitems == this->capacity) // code to grow heap if capacity reached
		{
			this->capacity *= 2;
			this->arr.resize(this->capacity); // resizing array to accomodate
		}

		// code to insert key value pair in accordance with keys

		// validating and updating minimum variable
		if (this->totalitems == 0)
		{
			this->minItem.key = key;
			this->minItem.value = value;
		}
		else
		{
			if (key < this->minItem.key)
			{
				this->minItem.key = key;
				this->minItem.value = value;
			}
		}
		// adding new user to last of array
		this->arr[this->totalitems].key = key;
		this->arr[this->totalitems++].value = value;

		// reheaping to maximum heap
		int i = this->totalitems - 1; // pointing to last element
		while (i != 0 && (arr[(i - 1) / 2].key < arr[i].key))
		{
			swap(this->arr[i], this->arr[(i - 1) / 2]);
			i = (i - 1) / 2; // updating pointer to parent
		}
	}

	//void deleteMin()
	//{
	//	assert(this->totalitems > 0);
	//	swap(arr->key, (arr + (totalitems - 1))->key);
	//	swap(arr->value, (arr + (totalitems - 1))->value);
	//	this->totalitems--;

	//	int i = 0; // pointing to first element
	//	while (i < (totalitems - 1))
	//	{
	//		if ((arr + i)->key > max((arr + ((i * 2) + 1))->key, (arr + ((i * 2) + 2))->key))
	//		{
	//			// if left child is lesser than left
	//			if ((arr + ((i * 2) + 1))->key < (arr + ((i * 2) + 2))->key)
	//			{
	//				swap((arr + ((i * 2) + 1))->key, (arr + i)->key);
	//				swap((arr + ((i * 2) + 1))->key, (arr + i)->key);
	//				i = ((i * 2) + 1);
	//			}
	//			else // if right child is lesser than right
	//			{
	//				swap((arr + ((i * 2) + 2))->key, (arr + i)->key);
	//				swap((arr + ((i * 2) + 2))->key, (arr + i)->key);
	//				i = ((i * 2) + 2);

	//			}
	//		}
	//	}
	//}
	//void getMin(v& _value)
	//{
	//	assert(this->totalitems > 0);
	//	_value = this->arr->value;
	//}
};