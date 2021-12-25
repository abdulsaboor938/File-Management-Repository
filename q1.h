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
	heapItem<k,v> minItem; // variable to maintain minimum priority user

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

	v findMin()
	{
		assert(this->totalitems > 0);
		return this->minItem.value;
	}
	v findMax()
	{
		assert(this->totalitems > 0);
		return this->arr[0].value;
	}

	void insert(k const key, v const value)
	{
		if (this->totalitems == this->capacity) // code to grow heap if capacity reached
		{
			this->capacity *= 2;
			this->arr.resize(this->capacity); // resizing array to accomodate
		}

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
		reheapup(this->totalitems - 1); // reheaping upwards from inserted item
	}
	void deleteMax()
	{
		assert(this->totalitems > 0);
		swap(arr[0], arr[--this->totalitems]);
		reheapdown(0);
	}

	void reheapup(int index)
	{
		// reheaping to maximum heap
		while (index != 0 && (arr[(index - 1) / 2].key < arr[index].key))
		{
			swap(this->arr[index], this->arr[(index - 1) / 2]);
			index = (index - 1) / 2; // updating pointer to parent
		}
	}
	void reheapdown(int index)
	{
		while (index < (this->totalitems - 1))
		{
			if (arr[index].key < min(arr[(index * 2) + 1].key, arr[(index * 2) + 2].key))
			{
				// if left child is greater than left
				if (arr[(index * 2) + 1].key > arr[(index * 2) + 2].key)
				{
					swap(arr[(index * 2) + 1], arr[index]);
					index = ((index * 2) + 1);
				}
				else // if right child is greater than right
				{
					swap(arr[(index * 2) + 2], arr[index]);
					index = ((index * 2) + 2);

				}
			}
			else
				break;
		}
	}
};