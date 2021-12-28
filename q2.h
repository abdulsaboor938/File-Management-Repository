#include<iostream>
#include<assert.h>
#include<vector>
#include<list>
#include"q1.h"

// This is an implementation of HashItem class
//#ifndef HASHITEM
//#define HASHITEM
//template<class v>
//class HashItem
//{
//	int key;
//	v value;
//	HashItem<v>* next;
//
//public:
//	HashItem() :key(0), value(NULL), next(nullptr) {}
//	HashItem(int temp_key, v temp_val, HashItem<v>* temp_next = nullptr) :
//		key(temp_key), value(temp_val), next(temp_next) {}
//	template<class v>
//	friend class HashMap;
//};
//#endif
//
//#ifndef HASHMAP
//#define HASHMAP
//template<class v>
//class HashMap
//{
//private:
//	vector<HashItem<v>>hashVector;
//	int currentElements;
//public:
//	HashMap();
//	HashMap(int const capacity);
//	void insert(int const key, v const value);
//	bool deleteKey(int const key) const;
//	v* get(int const key) const;
//	~HashMap();
//
//};
//
//template<class v>
//HashMap<v>::HashMap()
//{
//	this->hashVector.resize(10);
//	this->currentElements = 0;
//}
//template<class v>
//HashMap<v>::HashMap(int const capacity)
//{
//	assert(capacity > 1);
//	this->hashVector.resize(capacity);
//	this->currentElements = 0;
//}
//
//template<class v>
//void HashMap<v>::insert(int const key, v const value)
//{
//	int index = key % (this->hashVector.capacity());
//	hashVector[index].next = new HashItem<v>(key, value, hashVector[index].next);
//	this->currentElements++;
//}
//
//template<class v>
//bool HashMap<v>::deleteKey(int const key) const
//{
//	int index = key % (this->hashVector.capacity());
//	HashItem<v>* temp = hashVector[index].next;
//	{
//		while (temp != nullptr)
//		{
//			if (temp->key == key)
//			{
//				if (temp->next != nullptr)
//				{
//					HashItem<v>* temp2 = temp->next;
//					temp->key = temp->next->key;
//					temp->value = temp->next->value;
//					temp->next = temp->next->next;
//					delete temp2;
//				}
//				else {
//					HashItem<v>* temp_ptr = hashVector[index].next;
//					while (temp_ptr->next != temp)
//					{
//						temp_ptr = temp_ptr->next;
//					}
//					temp_ptr->next = temp_ptr->next->next;
//					delete temp;
//				}
//				return true;
//			}
//			temp = temp->next;
//		}
//		return false;
//	}
//}
//
//template<class v>
//v* HashMap<v>::get(int const key) const
//{
//	int index = key % (this->hashVector.capacity());
//	HashItem<v>* temp = hashVector[index].next;
//	while (temp != nullptr)
//	{
//		if (temp->key == key)
//		{
//			return &temp->value;
//		}
//		temp = temp->next;
//	}
//	return nullptr;
//}
//
//template<class v>
//HashMap<v>::~HashMap()
//{
//	for (int i = 0; i < hashVector.capacity(); i++)
//	{
//		HashItem<v>* temp = hashVector[i].next;
//		if (temp != nullptr)
//		{
//			HashItem<v>* temp1 = temp;
//			while (temp != nullptr)
//			{
//				temp1 = temp;
//				temp = temp->next;
//				delete temp1;
//			}
//		}
//	}
//	hashVector.resize(0);
//	this->currentElements = 0;
//}
//#endif

// definition of hashitem class
template<class v>
class hashitem
{
	v fileid; // variable to maintain fileid
	user currentuser; // a variable to maintain current user accessing the file
	heap<int, user>* waitinglist; // pointer to the heap of waiting users

public:
	hashitem() :currentuser(user()) // default constructor
	{
		this->waitinglist = nullptr;
	}
	template<class v>
	friend class hashmap;
};

// definition of hashhing class
template<class v>
class hashmap
{
	vector<list<hashitem<v>>*> hasharr; // vector to maintain hashtable of all the files

public:
	hashmap(int t_size)
	{
		while (t_size < 1)
		{
			cout << "Please enter table size (>0): ";
			cin >> t_size;
		}
		this->hasharr.resize(t_size); // resizing vector to defined size
		for (int i = 0; i < t_size; i++) // updating all elements to nullptr initially
			this->hasharr[i] = nullptr;
	}

};