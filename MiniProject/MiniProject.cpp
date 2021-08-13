#include <iostream>
#include<vector>
#include<queue>
#include<map>
#include<string>
using namespace std;

struct ps {
	string to;
	int rs;
};

typedef map<string, vector<ps>>::iterator mIt;
typedef vector<ps>::iterator vIt;

class Graph {
private:
	ps nullPsVar = { "NULL",0 };
	map<string, vector<ps>> edge;
	
	// Inserts new edge in Graph
	void insertEdge(string from, string to, int val)
	{
		ps temp = { to, val };
		edge[from].push_back(temp);
	}

	// Deletes an specified edge from graph
	void deleteEdge(string from, string to) {
		vIt i;
		for (i = edge[from].begin(); i != edge[from].end(); i++)
		{
			if (i->to == to)
				break;
		}
		edge[from].erase(i);
	}

	// Updates value of specified edge
	void updateEdge(string from, string to, int val) {
		for (vIt i = edge[from].begin(); i != edge[from].end(); i++)
		{
			if (i->to == to)
			{
				i->rs = val;
				return;
			}
		}
	}

	// Checks if the object with specified name exists as key or not
	vector<ps> CheckIfIndexExists(string s)
	{
		for (mIt i = edge.begin(); i != edge.end(); i++)
		{
			if (i->first == s)
				return i->second;
		}
		return {};
	}
	
	vector<ps> checkIFxExists(string s) {
		return CheckIfIndexExists(s);
	}
	
	//Checks wether the specified name exists in the vector of struct we entered as value corresponding to the key.
	ps checkStringInVector(string s, vector<ps> v) {
		for (vIt i = v.begin(); i != v.end(); i++)
		{
			if (i->to == s)
				return *i;
		}
		ps temp = { "NULL",0 };
		return temp;
	}
	
	//Returns total rs that the specified person has to pay
	int totalDebtOfX(string s)
	{
		vector<ps> checkDebtor = checkIFxExists(s);
		if (checkDebtor.empty())
			return 0;
		else
		{
			int sum{};
			for (vIt j = edge[s].begin(); j != edge[s].end(); j++)
			{
				sum += j->rs;
			}
			for (mIt i = edge.begin(); i != edge.end(); i++)
			{
				if (sum < 0)
					return 0;
				if (i->first == s)
					continue;
				else
				{
					ps checkDebtorInVector = checkStringInVector(s, edge[i->first]);
					if (checkDebtorInVector.to != nullPsVar.to)
					{
						sum -= checkDebtorInVector.rs;
					}
				}
			}
			return sum;
		}
	}

public:
	void addNewEntry(string from, string to, int val) {
		
		if (from == to)
		{
			cout << "Invalid Entry!" << endl;
			return;
		}
		vector<ps> checkTo = checkIFxExists(to);
		if (!checkTo.empty())
		{
			ps checkFromInVector = checkStringInVector(from, checkTo);
			if (checkFromInVector.to != nullPsVar.to)
			{
				if (val <= checkFromInVector.rs)
				{
					if (val == checkFromInVector.rs)
					{
						deleteEdge(to, from);
						return;
					}
					else
						updateEdge(to, from, checkFromInVector.rs - val);
					return;
				}
				else
				{
					val = val - checkFromInVector.rs;
					deleteEdge(to, from);
					insertEdge(from, to, val);
					return;
				}
			}
		}
		vector<ps> checkFrom = checkIFxExists(from);
		if (!checkFrom.empty())
		{
			ps checkToInVector = checkStringInVector(to, checkFrom);
			if (checkToInVector.to != nullPsVar.to)
			{
				updateEdge(from, to, val + checkToInVector.rs);
				return;
			}
		}
		insertEdge(from, to, val);
		return;
	}
	void print()
	{
		for (mIt i = edge.begin(); i != edge.end(); i++)
		{
			for (vIt j = i->second.begin(); j != i->second.end(); j++)
			{
				cout << i->first << " owes " << j->rs << "rs to " << j->to << endl;
			}
		}
	}
	void getTotalDebtofX(string s)
	{
		cout << s << " has to pay " << totalDebtOfX(s) << endl;
	}
};

int main()
{
	int choice{};
	Graph gph;
	while (choice != 4)
	{
		system("CLS");
		cout << "DISCLAIMER: ENTER ONLY FIRST NAME OF PERSON AND USE FIRST CHARACTER AS CAPITAL AND REST AS LOWERCASE LETTERS\n\nFor adding new Entry, enter 1.\nTo view the Graph, enter 2.\nTo know the debt of any person, enter 3.\nTo exit, enter 4;\n\nEnter your choice:";
		cin >> choice;
		switch (choice)
		{
			case 1:
			{	
				int val;
				string from, to;
				cout << "Enter the name of the Debtor:";
				cin >> from;
				cout << "Enter the name of the Creditor:";
				cin >> to;
				cout << "Enter amount:";
				cin >> val;
				gph.addNewEntry(from, to, val);
				break;
			}
			case 2:
			{
				gph.print();
				cin.ignore();
				cin.ignore();
				break;
			}
			case 3:
			{
				string name;
				cout << "Enter the name of person whose total debt you want:";
				cin >> name;
				gph.getTotalDebtofX(name);
				cin.ignore();
				cin.ignore();
				break;
			}
			case 4:
			{
				exit(0);
			}
			default:
			{
				cout << "Invalid Entry!\nRestart the program and enter correct option." << endl;
				exit(0);
			}
		}
	}
	
	//gph.addNewEntry("C", "A", 20);
	//gph.addNewEntry("A", "B", 30);
	//gph.addNewEntry("D", "F", 10);
	//gph.addNewEntry("D", "A", 50);
	//gph.print();// c -> a, a-b, d-f-a
	//cout << endl;
	//gph.addNewEntry("B", "A", 50);
	//gph.print();// c-a, b-a-20, d-f-a
	//cout << endl;
	//gph.addNewEntry("C", "A", 10);
	//gph.print();//c-a-30, b-a-20, d-f-a
	//cout << endl;
	//gph.addNewEntry("A", "C", 50);
	//gph.print();//a-c-20, b-a-20, d-f-a
	//cout << endl;
	//gph.addNewEntry("A", "A", 100);
	//gph.print();// invalid ''
}



/*
* // First "To", "From"
* 
* map<string,vector<struct(string, int)>>
* B -> ([A]->50), ([C]->60)
* [B] -> [A]->70
* A - 20 -> B
* 
* 
* B -> (A,30)
* 
* A -20 -> B

 B -> (A,10) 

 A - 30 -> B

 after check
   A - 20 -> B
A -> (B,20)


A has to pay B 30		
* A has to B 40* 
* A - 70 -> B			
* 180 > 100
* 80
* B has to pay 80 // B - 180 -> A
* B - 10 -> A	
	AddNew-> int Check(bool, int)-> Insert
	Check
	Insert (A, B, val)

  B -> (A,50), (C,10)
*
* A - 20 -> B

	Methods:
	vector<> CheckIfIndexExists(string s)
	{
		
	}
	vector<> checkIFFromExists(string from){
		return CheckIfIndexExists(from);
	}
	vector<> checkIfToExists(string to){
		return CheckIfIndexExists(to);
	}
	
	pair<string,int> checkStringInVector(string s , vector v){}

	void insert(string from, string to, int val)
	{
		
	}

	void delete(string from, string to){}

	void update(string from, string too, int val){}

  B -> (A,50), (C,10)

* A - 20 -> B
* A - from
* B - to
* x = 20
* vector checkTo = checkIfToExists("B");
* if(checkTo != NULL)
* {
*	checkFromInVector = checkStringInVector(A, checkTo)
*	if(checkFromInVector != NULL)
*	{
*		if(x <= val)
*			update(to, from, val - x) // add if update delete
*			return;
*		else
*		{
*			x = x - val;
*			delete(to, from)
*			insert(from, to, x)
*			return;
*		}
*	}
* }
*
*	checkFrom = checkIfFromExists(A);
*	if(checkFrom != NULL)
*	{
*		checkToInVector = checkStringInVector(B, checkFrom)
*		if(checkToInVector != NULL)
*		{
*			update(from, to, x + val);
*			return;
*		}
*	
*	
*insert(from, to, x);
* return;
*/ 