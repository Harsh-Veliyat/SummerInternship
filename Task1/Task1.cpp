	#include <iostream>

using namespace std;

enum Color{black,red};

struct RBT_Node {
	int val; 
	RBT_Node* parent; 
	RBT_Node* lchild; 
	RBT_Node* rchild; 
	Color color; 
};

typedef RBT_Node* nptr;

class RBTree {
private:
	nptr root;
	nptr NullNode;

	void printPreOrder(nptr node) {
		if (node != NullNode) {
			cout << node->val << " ";
			printPreOrder(node->lchild);
			printPreOrder(node->rchild);
		}
	}

	void printInOrder(nptr node) {
		if (node != NullNode) {
			printInOrder(node->lchild);
			cout << node->val << " ";
			printInOrder(node->rchild);
		}
	}

	void printPostOrder(nptr node) {
		if (node != NullNode) {
			printPostOrder(node->lchild);
			printPostOrder(node->rchild);
			cout << node->val << " ";
		}
	}

	nptr findVal(nptr node, int key) {
		if (node == NullNode || key == node->val) {
			return node;
		}

		if (key < node->val) {
			return findVal(node->lchild, key);
		}
		return findVal(node->rchild, key);
	}

	void fixDelete(nptr x) {
		nptr s;
		while (x != root && x->color == black) {
			if (x == x->parent->lchild) {
				s = x->parent->rchild;
				if (s->color == red) {
					// case 3.1
					s->color = black;
					x->parent->color = red;
					leftRotate(x->parent);
					s = x->parent->rchild;
				}

				if (s->lchild->color == black && s->rchild->color == black) {
					// case 3.2
					s->color = red;
					x = x->parent;
				}
				else {
					if (s->rchild->color == black) {
						// case 3.3
						s->lchild->color = black;
						s->color = red;
						rightRotate(s);
						s = x->parent->rchild;
					}

					// case 3.4
					s->color = x->parent->color;
					x->parent->color = black;
					s->rchild->color = black;
					leftRotate(x->parent);
					x = root;
				}
			}
			else {
				s = x->parent->lchild;
				if (s->color == red) {
					// case 3.1
					s->color = black;
					x->parent->color = red;
					rightRotate(x->parent);
					s = x->parent->lchild;
				}

				if (s->lchild->color == black && s->rchild->color == black) {
					// case 3.2
					s->color = red;
					x = x->parent;
				}
				else {
					if (s->lchild->color == black) {
						// case 3.3
						s->rchild->color = black;
						s->color = red;
						leftRotate(s);
						s = x->parent->lchild;
					}

					// case 3.4
					s->color = x->parent->color;
					x->parent->color = black;
					s->lchild->color = black;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = black;
	}


	void rbTransplant(nptr u, nptr v) {
		if (u->parent == nullptr) {
			root = v;
		}
		else if (u == u->parent->lchild) {
			u->parent->lchild = v;
		}
		else {
			u->parent->rchild = v;
		}
		v->parent = u->parent;
	}

	void deleteNode(nptr node, int key) {
		// find the node containing key
		nptr z = NullNode;
		nptr x, y;
		while (node != NullNode) {
			if (node->val == key) {
				z = node;
			}

			if (node->val <= key) {
				node = node->rchild;
			}
			else {
				node = node->lchild;
			}
		}

		if (z == NullNode) {
			cout << "Couldn't find key in the tree" << endl;
			return;
		}

		y = z;
		int y_original_color = y->color;
		if (z->lchild == NullNode) {
			x = z->rchild;
			rbTransplant(z, z->rchild);
		}
		else if (z->rchild == NullNode) {
			x = z->lchild;
			rbTransplant(z, z->lchild);
		}
		else {
			y = minimum(z->rchild);
			y_original_color = y->color;
			x = y->rchild;
			if (y->parent == z) {
				x->parent = y;
			}
			else {
				rbTransplant(y, y->rchild);
				y->rchild = z->rchild;
				y->rchild->parent = y;
			}

			rbTransplant(z, y);
			y->lchild = z->lchild;
			y->lchild->parent = y;
			y->color = z->color;
		}
		delete z;
		if (y_original_color == black) {
			fixDelete(x);
		}
	}

	void fixInsert(nptr k) {
		nptr u;
		while (k->parent->color == red) {
			if (k->parent == k->parent->parent->rchild) {
				u = k->parent->parent->lchild; // uncle
				if (u->color == red) {
					// case 3.1
					u->color = black;
					k->parent->color = black;
					k->parent->parent->color = red;
					k = k->parent->parent;
				}
				else {
					if (k == k->parent->lchild) {
						// case 3.2.2
						k = k->parent;
						rightRotate(k);
					}
					// case 3.2.1
					k->parent->color = black;
					k->parent->parent->color = red;
					leftRotate(k->parent->parent);
				}
			}
			else {
				u = k->parent->parent->rchild; // uncle

				if (u->color == red) {
					// mirror case 3.red
					u->color = black;
					k->parent->color = black;
					k->parent->parent->color = red;
					k = k->parent->parent;
				}
				else {
					if (k == k->parent->rchild) {
						// mirror case 3.2.2
						k = k->parent;
						leftRotate(k);
					}
					// mirror case 3.2.1
					k->parent->color = black;
					k->parent->parent->color = red;
					rightRotate(k->parent->parent);
				}
			}
			if (k == root) {
				break;
			}
		}
		root->color = black;
	}

	void printT(nptr root, string indent, bool last) {
		// print the tree structure on the screen
		if (root != NullNode) {
			cout << indent;
			if (last) {
				cout << "R---> ";
				indent += "     ";
			}
			else {
				cout << "L---> ";
				indent += "|    ";
			}

			string sColor = root->color ? "RED" : "BLACK";
			cout << root->val << "(" << sColor << ")" << endl;
			printT(root->lchild, indent, false);
			printT(root->rchild, indent, true);
		}
		// cout<<root->lchild->val<<endl;
	}

public:
	RBTree() {
		NullNode = new RBT_Node;
		NullNode->color = black;
		NullNode->lchild = nullptr;
		NullNode->rchild = nullptr;
		root = NullNode;
	}

	void preorder() {
		printPreOrder(this->root);
	}

	void inorder() {
		printInOrder(this->root);
	}

	void postorder() {
		printPostOrder(this->root);
	}

	nptr searchTree(int k) {
		return findVal(this->root, k);
	}

	nptr minimum(nptr node) {
		while (node->lchild != NullNode) {
			node = node->lchild;
		}
		return node;
	}

	void leftRotate(nptr x) {
		nptr y = x->rchild;
		x->rchild = y->lchild;
		if (y->lchild != NullNode) {
			y->lchild->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->lchild) {
			x->parent->lchild = y;
		}
		else {
			x->parent->rchild = y;
		}
		y->lchild = x;
		x->parent = y;
	}

	void rightRotate(nptr x) {
		nptr y = x->lchild;
		x->lchild = y->rchild;
		if (y->rchild != NullNode) {
			y->rchild->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->rchild) {
			x->parent->rchild = y;
		}
		else {
			x->parent->lchild = y;
		}
		y->rchild = x;
		x->parent = y;
	}

	void insert(int key) {

		nptr node = new RBT_Node;
		node->parent = nullptr;
		node->val = key;
		node->lchild = NullNode;
		node->rchild = NullNode;
		node->color = red; 

		nptr y = nullptr;
		nptr x = this->root;

		while (x != NullNode) {
			y = x;
			if (node->val < x->val) {
				x = x->lchild;
			}
			else {
				x = x->rchild;
			}
		}

		node->parent = y;
		if (y == nullptr) {
			root = node;
		}
		else if (node->val < y->val) {
			y->lchild = node;
		}
		else {
			y->rchild = node;
		}

		if (node->parent == nullptr) {
			node->color = black;
			return;
		}

		if (node->parent->parent == nullptr) {
			return;
		}
		fixInsert(node);
	}

	nptr getRoot() {
		return this->root;
	}

	void deleteVal(int val) {
		deleteNode(this->root, val);
	}

	void printTree() {
		if (root) {
			printT(this->root, "", true);
		}
	}

};

int main() {
	RBTree rbtree;
	rbtree.insert(18);
	rbtree.insert(6);
	rbtree.insert(20);
	rbtree.insert(3);
	rbtree.insert(4);
	rbtree.insert(25);
	rbtree.insert(11);
	rbtree.insert(10);
	rbtree.insert(5);
	rbtree.insert(1);
	rbtree.printTree();
	cout << endl;
	rbtree.deleteVal(17);
	cout << endl;
	rbtree.printTree();
	cout << endl;
	rbtree.deleteVal(10);
	cout << endl;
	rbtree.printTree();
	return 0;
}
