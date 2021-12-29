#include<iostream>
#include<string>
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
// k is type of file id, whereas v is type of priority queue
template<class k,class v>
class hashitem
{
	k fileid; // variable to maintain fileid
	list<v> currentuser; // a variable to maintain current user accessing the file
	heap<int, v>* waitinglist; // pointer to the heap of waiting users

public:
	hashitem() :fileid() // default constructor
	{
		this->currentuser.clear();
		this->waitinglist = nullptr;
	}
	template<class k,class v>
	friend class hashmap;
};

// definition of hashhing class
// k is type of file id, whereas v is type of priority queue
template<class k,class v>
class hashmap
{
	vector<list<hashitem<k,v>>> hasharr; // vector to maintain hashtable of all the files

public:
	hashmap(int t_size) // overloaded constructor
	{
		while (t_size < 1)
		{
			cout << "Please enter table size (>0): ";
			cin >> t_size;
		}
		this->hasharr.resize(t_size); // resizing vector to defined size
	}

	void insert(k file_id)
	{
		// insertion of a file into hash table
		while (file_id < 0)
		{
			cout << "Input FileID (>0): ";
			cin >> file_id;
		}
		hashitem<k,v> temp;
		temp.fileid = file_id;
		temp.waitinglist = nullptr;
		this->hasharr[(file_id % this->hasharr.size())].push_back(temp);
	}
	void requestAccess(k file_id, v temp_user, k temp_priority)
	{
		// This function adds users in hashtable far accessing a file
		// -1 priority is highest
		// -2 priority is lowest
		int index = file_id % this->hasharr.size(); // calculating index of hashtable
		typename list<hashitem<k, v>> ::iterator i = this->hasharr[index].begin(); // making an iterator
		for (; i != this->hasharr[index].end(); i++) // loop in list
		{
			if (i->fileid == file_id) // checking if file ids match
			{
				// file is found at this point
				if (i->currentuser.empty() && i->waitinglist == nullptr) // if first user
				{
					i->currentuser.push_back(temp_user); // giving access to user
				}
				else
				{
					if (i->waitinglist == nullptr) // if waiting queue is empty
						i->waitinglist = new heap<int, v>(); // assigning a heap
					// code to check priority to insert
					if (temp_priority == -1) // checking if highest priority
					{
						heapItem<k, v> temp;
						temp = i->waitinglist->findMax();
						i->waitinglist->insert(temp.key + 1, temp_user);
					}
					else if (temp_priority == -2) // checking if priority is minimum
					{
						heapItem<k, v> temp;
						temp = i->waitinglist->findMin();
						i->waitinglist->insert(temp.key - 1, temp_user); // inserting with maximum priority
					}
					else // if minimum priority
						i->waitinglist->insert(temp_priority, temp_user); // inserting with minimum priority
				}
				return; // returning after operation
			}
		}
		cout << "\nFile with id: "<<file_id<<" not found\n" << endl;
	}
	void releasefile(k file_id)
	{
		// this function releases a file and gives access to next highest priority user
		int index = file_id % this->hasharr.size(); // calculating index of hashtable
		typename list<hashitem<k, v>> ::iterator i = this->hasharr[index].begin(); // making an iterator
		for (; i != this->hasharr[index].end(); i++) // loop in list
		{
			if (i->fileid == file_id) // checking if file id's match
			{
				// clear current users
				// add top user
				// if top user is not write the
				// extract users while not empty and a write is found
				// print if null or vector

				i->currentuser.clear(); // clearing vector of current user
				if (!i->waitinglist->isEmpty()) // if waiting list is not empty
				{
					heapItem<k, v> temp = i->waitinglist->extractMax(); // extracting maximum user
					i->currentuser.push_back(temp.value); // pushing in vector

					// code to read further users (if any)
					if (!temp.value.operation) // if operation of current user was read
					{
						// finding and pushing all read users
						bool check = true;
						while (!i->waitinglist->isEmpty() && check) // while not empty and read
						{
							temp = i->waitinglist->findMax(); // getting maximum value
							if (temp.value.operation) // if write operation
							{
								check = false; // to break the loop
							}
							else
							{
								temp = i->waitinglist->extractMax(); // extracting maximum value
								i->currentuser.push_back(temp.value); // pushing back maximum value
							}
							// going back to loop
						}
					}

				}
				
				// code to print users granted access
				cout << "H" << index + 1 << "-> File:" << i->fileid << " ... \n\tAccess granted to: ";
				if (i->currentuser.empty()) // if no user has access
				{
					cout << "None" << endl;
				}
				else
				{
					// printing current user's vector in case access granted to multiple users
					typename list<v>::iterator temp_obj = i->currentuser.begin(); // iterator for list of currentaccess users
					for (; temp_obj != i->currentuser.end(); temp_obj++) // loop till end
					{
						// printing
						cout << "User:" << temp_obj->id;
						if (temp_obj->operation) // checking type of access
							cout << "(write)  ";
						else
							cout << "(read)  ";
					}
					cout << endl;
				}
				return;
			}
		}
		cout << "\nFile with id: " << file_id << " not found\n" << endl; // prompt if file is not found
	}
	void printTable()
	{
		// This function prints hashmap
		typename list<hashitem<k, v>>::iterator obj; // iterator for traversing array
		cout << "Current Repository" << endl;
		cout << "********************************************" << endl;
		for (int i = 0; i < this->hasharr.size(); i++)
		{
			if (!this->hasharr[i].empty()) // if node is not empty
			{
				for (obj = this->hasharr[i].begin(); obj != this->hasharr[i].end(); obj++)
				{
					cout << "H" << i + 1 << "-> File:" << obj->fileid << " ... \n\tAccess granted to: ";
					if (obj->currentuser.empty()) // if no user has access
					{
						cout << "None" << endl;
						cout << "\tNext User:None" << endl;
						cout << "\tWaiting:None" << endl;
					}
					else
					{
						// printing current user's vector in case access granted to multiple users
						typename list<v>::iterator temp_obj = obj->currentuser.begin(); // iterator for list of currentaccess users
						for (; temp_obj != obj->currentuser.end(); temp_obj++) // loop till end
						{
							// printing
							cout << "User:" << temp_obj->id;
							if (temp_obj->operation) // checking type of access
								cout << "(write)  ";
							else
								cout << "(read)  ";
						}
						cout << endl;

						// code to print next user from priority queue
						cout << "\tNext User:";
						if (obj->waitinglist->isEmpty()) // checking if empty queue
						{
							cout << "None" << endl;
							cout << "\tWaiting:None" << endl;
						}
						else // if queue is not empty
						{
							v temp_v = obj->waitinglist->findMax().value; // temporary object of type v
							cout << temp_v.id;
							if (temp_v.operation) // checking read/ write
								cout << "(write)" << endl;
							else
								cout << "(read)" << endl;
							cout << "\tWaiting:" << obj->waitinglist->heapsize() << endl; // printing waiting users
						}
					}
					cout << endl;
				}
				cout << endl << endl;
			}
		}
	}

};