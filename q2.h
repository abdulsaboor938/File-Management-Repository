#include<iostream>
#include<string>
#include<Windows.h>
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
		hashitem<k,v> temp;
		temp.fileid = file_id;
		temp.waitinglist = nullptr;

		// checking if file is already present
		int index = file_id % this->hasharr.size();
		typename list<hashitem<k, v>> ::iterator i = this->hasharr[index].begin(); // making an iterator
		for (; i != this->hasharr[index].end(); i++) // loop in list
		{
			if (i->fileid == file_id) // checking if file ids match
			{
				cout << "\tFile already exists" << endl;
				return;
			}
		}
		this->hasharr[index].push_back(temp);
		cout << "\tFile inserted successfully" << endl;
	}
	void requestAccess(k file_id, v temp_user, k temp_priority)
	{
		// This function adds users in hashtable far accessing a file
		// 100 priority is highest
		// 0 priority is lowest
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
					cout << "\tAccess granted" << endl;
				}
				else
				{
					if (i->waitinglist == nullptr) // if waiting queue is empty
						i->waitinglist = new heap<int, v>(); // assigning a heap
					// code to check priority to insert
					if (temp_priority == 100) // checking if highest priority
					{
						heapItem<k, v> temp;
						// checking for highest reading priority
						v t_user = i->currentuser.front();
						if (t_user.operation == false && temp_user.operation == false) // if currentuser has read access
						{
							i->currentuser.push_back(temp_user); // pushing to current users
							cout << "\tAccess granted" << endl;
						}
						else
						{
							temp = i->waitinglist->findMax();
							i->waitinglist->insert(temp.key + 1, temp_user);
							cout << "\tAdded to waiting list" << endl;
						}
					}
					else if (temp_priority == 0) // checking if priority is minimum
					{
						heapItem<k, v> temp;
						temp = i->waitinglist->findMin();
						i->waitinglist->insert(temp.key - 1, temp_user); // inserting with maximum priority
						cout << "\tAdded to waiting list" << endl;
					}
					else // if minimum priority
					{
						i->waitinglist->insert(temp_priority, temp_user); // inserting with given priority
						cout << "\tAdded to waiting list" << endl;
					}
				}
				return; // returning after operation
			}
		}
		cout << "\tFile with id: "<<file_id<<" not found ... Operation unsuccessful" << endl;
	}
	void releasefile(k file_id, v temp_user)
	{
		bool found = false;
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
						cout << "\tOperation successful" << endl;
						found = true;
						break;
					}
				}
				if(!found)
					cout << "\tGiven user not working on file ... Operation unsuccessful" << endl;

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
				return;
			}
		}
		cout << "\tFile with id: " << file_id << " not found ... Operation unsuccessful" << endl; // prompt if file is not found
	}
	void deleteFile(k file_id)
	{
		bool found = false;
		// this function deletes a file if it is not in use
		int index = file_id % this->hasharr.size();
		typename list<hashitem<k, v>> ::iterator i = this->hasharr[index].begin(); // making an iterator
		for (; i != this->hasharr[index].end(); i++) // loop in list
		{
			if (i->fileid == file_id) // checking if file ids match
			{
				found = true;
				// checking if currentuser are empty
				if (i->currentuser.empty())
				{
					// deleting file
					this->hasharr[index].erase(i);
					cout << "\tFile delete successful" << endl;
					return;
				}
			}
		}
		if(!found)
			cout << "\tFile with id: " << file_id << " not found ... Operation unsuccessful" << endl; // prompt if file is not found
		else
			cout << "\tFilel still accessed by some user ... Operation Unsuccessful" << endl;
	}
	void printTable()
	{
		int found = 0; // variable to check
		// This function prints hashmap
		typename list<hashitem<k, v>>::iterator obj; // iterator for traversing array
		cout << "\n\t--------------------------------------------" << endl;
		cout << "\tCurrent Repository" << endl;
		cout << "\t--------------------------------------------" << endl << endl;
		for (int i = 0; i < this->hasharr.size(); i++)
		{
			if (!this->hasharr[i].empty()) // if node is not empty
			{
				found++;
				for (obj = this->hasharr[i].begin(); obj != this->hasharr[i].end(); obj++)
				{
					cout << "\tH" << i + 1 << "-> File:" << obj->fileid << " ... \n\tAccess granted to: ";
					if (obj->currentuser.empty()) // if no user has access
					{
						cout << "None" << endl;
						cout << "\t\tNext User:None" << endl;
						cout << "\t\tWaiting:None" << endl;
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
						cout << "\t\tNext User:";
						if (obj->waitinglist->isEmpty()) // checking if empty queue
						{
							cout << "None" << endl;
							cout << "\t\tWaiting:None" << endl;
						}
						else // if queue is not empty
						{
							v temp_v = obj->waitinglist->findMax().value; // temporary object of type v
							cout << temp_v.id;
							if (temp_v.operation) // checking read/ write
								cout << "(write)" << endl;
							else
								cout << "(read)" << endl;
							cout << "\t\tWaiting:" << obj->waitinglist->heapsize() << endl; // printing waiting users
						}
					}
					cout << endl;
				}
				cout << endl << endl;
			}
		}
		if (found == 0)
		{
			cout << "\tNo files in repository to show at this moment" << endl << endl;
			Sleep(2000);
		}
		else
			system("pause");
	}
	void loadfile(string path)
	{
		// This program loads data from a (complete) text file
		ifstream infile;
		infile.open(path, ios::in); // opening file
		if (!infile) // if there is an error in opening the file
		{
			cout << "\tError opening the data file ... Operation unsuccessful" << endl;
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

				this->insert(file_id); // inserting file in hashmap
				this->requestAccess(file_id, v(user_id, temp_op), priority); // inserting user in hashmap
			}
			infile.close(); // closing file
			system("cls");
			cout << "\n\n\t---------------- GITHUB ----------------" << endl << endl;
			cout << "\tFile read successful" << endl;
		}
	}
};

// Menu Implementaion
void insertfile(hashmap<int, user>& htable)
{
	// function to validate and insert a file
	int file_id = 0;
	do
	{
		system("cls");
		cout << "\n\n\t---------------- GITHUB ----------------" << endl << endl;
		cout << "\tEnter file ID (5000 - 99999): ";
		cin >> file_id;
	} while (file_id < 5000 || file_id>99999); // validating range
	Sleep(500);
	system("cls");
	cout << "\n\n\t---------------- GITHUB ----------------" << endl << endl;
	htable.insert(file_id); // calling insert function
	Sleep(2000);
	system("cls");
}
void accessfile(hashmap<int, user>& htable)
{
	// function to validate and insert a file
	int file_id = 0;
	int user_id = 0;
	int priority = 0;
	char operation;
	do
	{
		system("cls");
		cout << "\n\n\t---------------- GITHUB ----------------" << endl << endl;
		cout << "\tEnter file ID (5000 - 99999): ";
		cin >> file_id;
	} while (file_id < 5000 || file_id>99999); // validating range of fileid
	do
	{
		system("cls");
		cout << "\n\n\t---------------- GITHUB ----------------" << endl << endl;
		cout << "\tEnter file ID (5000 - 99999): " << file_id << endl;
		cout << "\tEnter user ID (0 - 10000): ";
		cin >> user_id;
	} while (user_id < 0 || user_id>10000); // validating range of userid
	do
	{
		system("cls");
		cout << "\n\n\t---------------- GITHUB ----------------" << endl << endl;
		cout << "\tEnter file ID (5000 - 99999): " << file_id << endl;
		cout << "\tEnter user ID (0 - 10000): " << user_id << endl;
		cout << "\tEnter access type (r=read, w=write): ";
		cin >> operation;
	} while (!(operation=='r' || operation=='w')); // validating operation type
	bool temp_op = false;
	if (operation == 'w')
		temp_op = true;
	// converted to boolean type

	do
	{
		system("cls");
		cout << "\n\n\t---------------- GITHUB ----------------" << endl << endl;
		cout << "\tEnter file ID (5000 - 99999): " << file_id << endl;
		cout << "\tEnter user ID (0 - 10000): " << user_id << endl;
		cout << "\tEnter access type (r=read, w=write): " << operation << endl;
		cout << "\tEnter priority (0=min - 100=max): ";
		cin >> priority;
	} while (priority < 0 || priority>100); // validating priority

	Sleep(500);
	system("cls");
	cout << "\n\n\t---------------- GITHUB ----------------" << endl << endl;
	htable.requestAccess(file_id, user(user_id, temp_op), priority);
	Sleep(2000);
	system("cls");
}
void removeaccess(hashmap<int, user>& htable)
{
	// function to validate and insert a file
	int file_id = 0;
	int user_id = 0;
	do
	{
		system("cls");
		cout << "\n\n\t---------------- GITHUB ----------------" << endl << endl;
		cout << "\tEnter file ID (5000 - 99999): ";
		cin >> file_id;
	} while (file_id < 5000 || file_id>99999); // validating range of fileid
	do
	{
		system("cls");
		cout << "\n\n\t---------------- GITHUB ----------------" << endl << endl;
		cout << "\tEnter file ID (5000 - 99999): " << file_id << endl;
		cout << "\tEnter user ID (0 - 10000): ";
		cin >> user_id;
	} while (user_id < 0 || user_id>10000); // validating range of userid
	Sleep(500);
	system("cls");
	cout << "\n\n\t---------------- GITHUB ----------------" << endl << endl;
	htable.releasefile(file_id, user(user_id,false));
	Sleep(2000);
	system("cls");
}
void readfile(hashmap<int, user>& htable)
{
	// function to read file from a path
	string path;
	system("cls");
	cout << "\n\n\t---------------- GITHUB ----------------" << endl << endl;
	cout << "\tEnter text file path: ";
	cin >> path;
	Sleep(500);
	system("cls");
	cout << "\n\n\t---------------- GITHUB ----------------" << endl << endl;
	htable.loadfile(path); // calling load function
	Sleep(2000);
	system("cls");
}
void removefile(hashmap<int, user>& htable)
{
	// function to validate and insert a file
	int file_id = 0;
	do
	{
		system("cls");
		cout << "\n\n\t---------------- GITHUB ----------------" << endl << endl;
		cout << "\tEnter file ID (5000 - 99999): ";
		cin >> file_id;
	} while (file_id < 5000 || file_id>99999); // validating range
	Sleep(500);
	system("cls");
	cout << "\n\n\t---------------- GITHUB ----------------" << endl << endl;
	htable.deleteFile(file_id); // calling delete function
	Sleep(2000);
	system("cls");
}

// main menu function
void menu()
{
	hashmap<int, user> repo(11); // creating hash table to work on
	START:
	// this function prints a menu and calls corresponding functions
	int choice = 0;
	do
	{
		system("cls");
		cout << "\n\n\t---------------- GITHUB ----------------" << endl << endl;
		cout << "\t1: I want insert a file" << endl;
		cout << "\t2: I want to access a file" << endl;
		cout << "\t3: I am done working on a file" << endl;
		cout << "\t4: I want to load data from a text file" << endl;
		cout << "\t5: I want to delete a file" << endl;
		cout << "\t6: I want to view repository" << endl;
		cout << "\t7: I want to close application" << endl;

		cout << "\n\tPlease Select one of the above options (1-7): ";
		cin >> choice;

	} while (choice > 7 || choice < 1);
	Sleep(500);
	switch (choice)
	{
		case 1:
		{
			insertfile(repo);
			break;
		}
		case 2:
		{
			accessfile(repo);
			break;
		}
		case 3:
		{
			removeaccess(repo);
			break;
		}
		case 4:
		{
			readfile(repo);
			break;
		}
		case 5:
		{
			removefile(repo);
			break;
		}
		case 6:
		{
			system("cls");
			cout << "\n\n\t---------------- GITHUB ----------------" << endl << endl;
			repo.printTable();
			break;
		}
		case 7:
		{
			goto END;
			break;
		}
	}
	goto START;
END:
	system("cls");
	cout << "\n\n\t---------------- GITHUB ----------------" << endl << endl;
	cout << "\tSee you soon ... exiting" << endl;
	Sleep(500);
	system("cls");
}