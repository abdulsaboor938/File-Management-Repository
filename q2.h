#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<fstream>
#include"q1.h"

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
	~hashitem()
	{
		this->currentuser.clear();
		if (this->waitinglist != nullptr)
			delete this->waitinglist;
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
	~hashmap()
	{
		this->hasharr.clear();
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

		// checking if file is already present
		int index = file_id % this->hasharr.size();
		typename list<hashitem<k, v>> ::iterator i = this->hasharr[index].begin(); // making an iterator
		for (; i != this->hasharr[index].end(); i++) // loop in list
		{
			if (i->fileid == file_id) // checking if file ids match
				return;
		}
		this->hasharr[index].push_back(temp);
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
						// checking for highest reading priority
						v t_user = i->currentuser.front();
						if (t_user.operation == false && temp_user.operation == false) // if currentuser has read access
							i->currentuser.push_back(temp_user); // pushing to current users
						else
						{
							temp = i->waitinglist->findMax();
							i->waitinglist->insert(temp.key + 1, temp_user);
						}
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
	void releasefile(k file_id, v temp_user)
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

				typename list<v>::iterator curr_user = i->currentuser.begin();
				for (; curr_user != i->currentuser.end(); curr_user++)
				{
					// if current user is found in active users then delete
					if (curr_user->id == temp_user.id)
					{
						i->currentuser.erase(curr_user);
						break;
					}
				}

				// do all this work when last user is removed
				if (!i->waitinglist->isEmpty()) // if waiting list is not empty and curretn is empty
				{
					heapItem<k, v> temp;
					if (i->currentuser.empty())
					{
						temp = i->waitinglist->extractMax(); // extracting maximum user
						i->currentuser.push_back(temp.value); // pushing in vector
					}
					else
					{
						temp.value = i->currentuser.front(); // front of curretn user
					}

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
	void deleteFile(k file_id)
	{
		// this function deletes a file if it is not in use
		int index = file_id % this->hasharr.size();
		typename list<hashitem<k, v>> ::iterator i = this->hasharr[index].begin(); // making an iterator
		for (; i != this->hasharr[index].end(); i++) // loop in list
		{
			if (i->fileid == file_id) // checking if file ids match
			{
				// checking if currentuser are empty
				if (i->currentuser.empty())
				{
					// deleting file
					this->hasharr[index].erase(i);
					return;
				}
			}
		}

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
	void loadfile(string path,hashmap<k,v> &temp_hash)
	{
		// This program loads data from a (complete) text file
		ifstream infile;
		infile.open(path, ios::in); // opening file
		if (!infile) // if there is an error in opening the file
		{
			cout << "Error opening the file." << endl;
		}
		else
		{
			string temp;
			int file_id, user_id, priority, count=0;
			char operation;

			while (getline(infile, temp))
				count++; // counting number of lines in file
			infile.close();

			infile.open(path, ios::in); // going to file start
			getline(infile,temp); // to remove headers
			for(;count>1;count--)
			{
				infile >> file_id >> operation >> user_id >> operation >> priority >> operation >> operation; // reading from file

				bool temp_op = false; // operation flag
				if (operation == 'W') // if write operation
					temp_op = true; // changing access type

				temp_hash.insert(file_id); // inserting file in hashmap
				temp_hash.requestAccess(file_id, v(user_id, temp_op), priority); // inserting user in hashmap
			}
			infile.close(); // closing file
		}
	}
};