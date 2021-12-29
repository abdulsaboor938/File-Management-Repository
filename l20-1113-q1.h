/*
* Abdul Saboor
* 20L-1113
* BDS-3A
*/

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
	user() :id(-1), operation(false) {}

public:
	// constructor of class
	user(int temp_id, bool temp_op) :id(temp_id), operation(temp_op) {}
	friend ostream& operator<<(ostream& out, user& temp) // stream output function
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
	template<class k, class v>
	friend class hashitem;
	template<class k, class v>
	friend class hashmap;
};

// definition of heap class
template<class k, class v>
class heapItem
{
	// public for making an array in main
public:
	k key; // template variable to maintain key
	v value; // template variable to maintain value

	heapItem() :key(), value() {}

	template<class k, class v>
	friend class heap; // making friend class for easier access
};

template<class k, class v>
class heap
{
	vector<heapItem<k, v>> arr; // vector to maintain heap
	int capacity; // variable to maintain total capacity of vector
	int totalitems; // variable to maintain total filled items of vector
	heapItem<k, v> minItem; // variable to maintain minimum priority user

public:
	// class fucntions
	heap() :capacity(1), totalitems(0) // default constructor of class
	{
		this->arr.resize(1); // resizing vector to minmum value
	}
	~heap() // destructor of class
	{
		arr.clear(); // clearig vector
		this->totalitems = this->capacity = 0; // clearing varaibles
	}
	bool isEmpty()
	{
		if (this == nullptr)
			return true;
		return(this->totalitems == 0); // returns true if no items are present
	}
	int heapsize() // function to return current heapsize
	{
		return this->totalitems;
	}

	// building queue function
	void buildQueue(vector<heapItem<k, v>>& temp_arr, int size) // function to build queue from a given array
	{
		for (int i = (size / 2) - 1; i >= 0; i--) // loop from middle to first element
			reheapdown(temp_arr, i, size); // reheaping each node
	}

	// finding max / min functions
	heapItem<k, v> findMin() // function to give minimum value in O(1) time
	{
		if (this->totalitems > 0)
			return this->minItem; // returning minimum item
		else
		{
			heapItem<k, v> temp;
			temp.key = 0;
			return temp;
		}
	}
	heapItem<k, v> findMax() // function to return maximum item in o(1) time
	{
		if (this->totalitems > 0)
			return this->arr[0]; // returning maximum value
		else
		{
			heapItem<k, v> temp;
			temp.key = 0;
			return temp;
		}
	}

	// insertion / deletion functions
	void insert(k const key, v const value) // function to insert an item in heap according to its priority
	{
		if (this->totalitems == this->capacity) // code to grow heap if capacity reached
		{
			this->capacity *= 2; // doubling heap capacity
			this->arr.resize(this->capacity); // resizing array to accomodate
		}

		// validating and updating minimum variable
		if (this->totalitems == 0) // if first insertion
		{
			// updating minimum item
			this->minItem.key = key;
			this->minItem.value = value;
		}
		else // if not the first insertion
		{
			if (key < this->minItem.key) // checking if minimum item
			{
				// updating minimum item
				this->minItem.key = key;
				this->minItem.value = value;
			}
		}

		// adding new user to last of array
		this->arr[this->totalitems].key = key;
		this->arr[this->totalitems++].value = value;
		reheapup(this->arr, 0, this->totalitems - 1); // reheaping upwards from inserted item
	}
	heapItem<k, v> extractMax() // function to find and remove maximum priority item from heap
	{
		if (this->totalitems <= 0)
		{
			cout << "Heap is empty" << endl;
			heapItem<k, v> temp;
			return temp;
		}
		swap(arr[0], arr[--this->totalitems]); // swapping with minimum
		reheapdown(this->arr, 0, this->totalitems - 1); // reheaping down from top
		// code to shrink array
		if (this->capacity / 2 > this->totalitems) // checking if less than half is filled
		{
			this->capacity /= 2; // reducing capacity
			this->arr.resize(this->capacity); // resizing array
		}
		return arr[totalitems]; // returning maximum item
	}

	// reheaping functions
	void reheapup(vector<heapItem<k, v>>& data, int root, int last) // recursive code to reheap up from a given node
	{
		int parent;
		if (last > root) { // tree is not empty
			parent = (last - 1) / 2;
			if (data[parent].key < data[last].key)  // if parent is smaller
			{
				swap(data[parent], data[last]); // swapping from parent
				reheapup(data, root, parent); // recursive call to parent
			}
		}
	}
	void reheapdown(vector<heapItem<k, v>>& data, int cnode, int last) // recursive code to reheapdown from a given node
	{
		int maxChild, rightChild, leftChild; // local variables to check maximum child
		leftChild = 2 * cnode + 1; // calculating left child
		rightChild = 2 * cnode + 2; // calculating right child
		if (leftChild <= last) // if left child is part of the heap
		{
			if (leftChild == last) // if only one child
				maxChild = leftChild;
			else // if both child exist
			{
				if (data[leftChild].key <= data[rightChild].key) // if right child is greater than left
					maxChild = rightChild;
				else // if left child is greater than right
					maxChild = leftChild;
			}
			if (data[cnode].key < data[maxChild].key) // checking if child's data is less than parent
			{
				swap(data[cnode], data[maxChild]); // swapping with maximum child
				reheapdown(data, maxChild, last); // recursive call from maximum child
			}
		}
	}
};