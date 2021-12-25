#include<iostream>
#include<vector>
using namespace std;

// definition of user class
class user
{
	int id;
	bool operation; // false is read, true is write

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
};