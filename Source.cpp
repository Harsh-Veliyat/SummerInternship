#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<math.h>
using namespace std;


class Node 
{
public:
	int val;
	Node* lchild;
	Node* rchild;
	Node() : val{}, lchild{NULL}, rchild{NULL}
	{
	}
	Node(int val) : val{ val }
	{
		lchild = NULL;
		rchild = NULL;
	}
};

class Tree
{
public:
	Tree() : root{ NULL } {}
	
	bool isEmpty() {
		if (root == NULL)
			return true;
		else
			return false;
	}

	Node* getRoot()
	{
		return root;
	}

	void insert(int val)
	{
		Node* nnode = new Node(val);
		
		if(root == NULL)
		{
			root = nnode;
		}
		else
		{
			Node* temp = root;
			while (temp != NULL)
			{
				if (nnode->val == temp->val)
				{
					cout << "No duplicate value allowed!" << endl;
				}
				else if (nnode->val < temp->val && temp->lchild == NULL)
				{
					temp->lchild = nnode;
					break;
				}
				else if (nnode->val < temp->val)
					temp = temp->lchild;
				else if (nnode->val > temp->val && temp->rchild == NULL)
				{
					temp->rchild = nnode;
					break;
				}
				else
					temp = temp->rchild;
			}
		}
	}

	void preOrder(Node* temp)
	{ 
		if (temp == NULL)
			return;
		cout << temp->val << " ";
		preOrder(temp->lchild);
		preOrder(temp->rchild);
	}
	void inOrder(Node* temp)
	{
		if (temp == NULL)
			return;
		inOrder(temp->lchild);
		cout << temp->val << " ";
		inOrder(temp->rchild);
	}
	void postOrder(Node* temp)
	{
		if (temp == NULL)
			return;
		postOrder(temp->lchild);
		postOrder(temp->rchild);
		cout << temp->val << " ";
	}
	
	void levelOrder(Node* temp)
	{
		int h = height(temp);
		int hev{ h };
		bool bo = true;
		for (int i{}; i <= hev; i++)
		{
			printLevelOrder(temp, i, i, h, hev, bo);
			cout << endl;
			h--;
			bo = true;
		}
	}

	void printLevelOrder(Node* temp, int level, int lev, int h, int hev, bool bo)
	{
		if (temp == NULL)
			return;
		else if (level == 0)
		{
			print2d(temp->val, h, lev, hev, bo);// Adding tree print thing; lev = level for print, h height, hev height;
		}
		else
		{
			printLevelOrder(temp->lchild,level-1,lev,h,hev, bo);
			bo = false;
			printLevelOrder(temp->rchild, level -1,lev, h, hev, bo);
		}
	}

	int heightRootSpace(int h)
	{
		if (h == 0)
			return 0;
		else if (h == 1)
			return 5;
		else
			return 2*heightRootSpace(h - 1) + 5;
	}

	void print2d(int val, int height, int level, int hev, bool bo)
	{
		double h{};
		if(bo == true)
			h = heightRootSpace(height);
		else
			h = (10 * pow(2, hev - level));
		if (hev - level != 0)
			h += 1;
		for (int j{}; j < (h); j++)
			cout << " ";
		if (val < 10)
			cout << " " << val;
		else
			cout << val;
	}

	Node* findVal(Node* temp, int val)
	{
		if (temp == NULL)
		{
			cout << val << " Not found!" << endl;
			return NULL;
		}
		if (temp->val == val)
		{
			cout << temp->val << " is present!" << endl;
			return temp;
		}
		else if (temp->val > val)
			return findVal(temp->lchild, val);
		else
			return findVal(temp->rchild, val);
	}
	
	Node* getMinimumValNode(Node* temp)
	{
		while (temp->lchild != NULL)
			temp = temp->lchild; 
		return temp;
	}

	Node* deleteVal(Node* temp, int val)
	{
		if (temp == NULL)
		{
			cout << "Tree Empty!" << endl;
			return NULL;
		}
		Node* ptr = findVal(temp, val);
		if (ptr == NULL)
		{
			cout << "Value not found!" << endl;
			return NULL;
		}
		if (temp->val > val)
		{
			temp->lchild = deleteVal(temp->lchild, val);
		}
		else if (temp->val < val)
			temp->rchild = deleteVal(temp->rchild, val);
		else
		{
			if (temp->lchild == NULL)
			{
				ptr = temp->rchild;
				delete temp;
				return ptr;
			}
			else if (temp->rchild == NULL)
			{
				ptr = temp->lchild;
				delete temp;
				return ptr;
			}
			else
			{
				ptr = getMinimumValNode(temp->rchild);
				temp->val = ptr->val;
				temp->rchild = deleteVal(temp->rchild, ptr->val);
			}
		}
		return temp;
	}

	int height(Node* temp)
	{
		if (temp == NULL)
			return -1;
		else
		{
			int lheight = height(temp->lchild);
			int rheight = height(temp->rchild);

			if (lheight > rheight)
				return (lheight + 1);
			else
				return(rheight + 1);
		}
	}
	
private:
	Node* root;
	vector<int> arr;
};

int main() {
	/*Tree t = Tree()	;
	t.insert(35);
	t.insert(5);
	t.insert(25);
	t.insert(45);
	t.insert(65);
	t.insert(0);
	t.insert(10);
	t.insert(20);
	t.insert(30);
	t.insert(40);
	t.insert(50);
	t.levelOrder(t.getRoot());
	cout << "\n" << endl;
	t.preOrder(t.getRoot());
	cout << endl;
	t.inOrder(t.getRoot());
	cout << endl;
	t.postOrder(t.getRoot());
	cout << endl;
	cout << "Height: " << t.height(t.getRoot()) << endl;
	t.findVal(t.getRoot(), 10);
	t.findVal(t.getRoot(), 1);
	t.findVal(t.getRoot(), 7);
	t.deleteVal(t.getRoot(), 10);
	t.postOrder(t.getRoot());
	cout << endl;
	cout << t.heightRootSpace(4) << endl;*/
	enum  color {red,black};
	color c = color::black;
	cout << c;
	return 0;
}