// Brandon Alvino
// null793@gmail.com
// Project 6

#define MAX_FILE_SIZE 50
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct Node
{
	int data;
	Node * right = NULL;
	Node * left = NULL;
};

class Btree
{
private:
	Node * root = NULL;
	int * storage;
	int count;

	// Just put this in so I could test somt stuff with the binary tree
	void DebugMenu()
	{
		int in;
		Node * current = root;
		string nl = "\n\n\n\n\n\n\n\n\n\n"; // weird output formatting
		system("color a"); // cool green font
		while (true)
		{
			cout << "Debug Menu..." << endl;
			cout << "1:  Value of Current    6:  Get num children" << endl;
			cout << "2:  Advance Root left   7:  Get left child" << endl;
			cout << "3:  Advance Root right  8:  Get right child " << endl;
			cout << "4:  Size of tree        9:  Current is leaf" << endl;
			cout << "5:  Return to root      10: Exit" << endl;
			cout << "Input: ";
			cin >> in;
			cout << endl;

			if (current || in == 10) // in == 10 so we can exit if we have an empty tree
			{
				switch (in)
				{
				case 1:
					if (current)
						cout << "Value of Current: " << current->data << endl;
					break;

				case 2:
					if (current->left)
					{
						current = current->left;
						cout << "Current node advanced to the left." << endl;
					}
					else
						cout << "Current doesn't have a left child." << endl;
					break;

				case 3:
					if (current->right)
					{
						current = current->right;
						cout << "Current node advanced to the right" << endl;
					}
					else
						cout << "Current doesn't have a right child." << endl;
					break;

				case 4:
					cout << "Tree is of size " << count << "." << endl;
					break;

				case 5:
					current = root;
					cout << "Current node was reset to root node." << endl;
					break;

				case 6:
					in = 0;
					if (current->left)
						in++;
					if (current->right)
						in++;
					cout << "Current node has " << in << " children." << endl;
					break;

				case 7:
					if (current->left)
						cout << "Left child: " << current->left->data << endl;
					break;

				case 8:
					if (current->right)
						cout << "Right child: " << current->right->data << endl;
					break;

				case 9:
					in = 0;
					if (current->left)
						in++;
					if (current->right)
						in++;
					cout << ((in == 0) ? "Yes" : "No") << endl;
					break;

				case 10:
					cout << "Returned to main menu." << nl << endl;
					system("color 7"); // change back the color
					return;
				}
			}

			else
			{
				cout << "Tree is empty..." << endl;
			}

			cout << "\n\n\n\n" << nl << endl;
			system("pause");
			system("cls");
		}

	}

	// Left Visit Right
	void recinorder(Node * temp)
	{
		if (temp)
		{
			if (temp->left)
				recinorder(temp->left);
			cout << temp->data << " ";
			if (temp->right)
				recinorder(temp->right);
		}
	}

	// Visit Left Right
	int c; // counter for array indeces
	void ar_recpreorder(Node * temp)
	{
		storage[c++] = temp->data; // storage gets it's size in Save()
		if (temp->left)
			ar_recpreorder(temp->left);
		if (temp->right)
			ar_recpreorder(temp->right);

	}

	// Left Right Visit, postorder to delete the tree
	void Clear(Node * temp)
	{
		if (temp)
		{
			if (temp->left)
				Clear(temp->left);
			if (temp->right)
				Clear(temp->right);
			delete temp;
		}
	}

	void Balance(int * data, int low, int high)
	{
		if (low == high) // Since we include mid in our lower bound I believe this works
			return;

		int mid = (low + high) / 2; // cals mid so we can define our recursive functions

		Additem(data[mid]);
		Balance(data, low, mid);
		Balance(data, mid + 1, high);
	}

public:
	Btree()
	{
		//Don't need anything in here.
	}

	~Btree()
	{
		Clear(root);
	}

	// Not needed method but chose to use a count variable so we could have our
	//   saving and balancing of arrays to be dynamic and not fixed.
	int Size()
	{
		return count;
	}

	void Clear()
	{
		Clear(root);
		root = NULL;
		count = 0;
	}

	void menu()
	{
		DebugMenu();
	}

	void inorder()
	{
		cout << "Tree: [ ";
		recinorder(root);
		cout << "]" << endl;
	}

	bool Search(int item)
	{
		Node * temp = root;
		if (count == 0) // empty list
			return false;
		while (true) // non empty list
		{
			if (temp->data == item) // found data
				return true;

			else // not found
			{
				if (item < temp->data)
				{
					if (!temp->left) // nothing to the left
						return false;
					else
						temp = temp->left; // advance left
				}
				else if (item >= temp->data)
				{
					if (!temp->right) // nothing to the right
						return false;
					else
						temp = temp->right; // advance right
				}
			}
		}
	}

	void Additem(int item)
	{
		if (!root) // empty list
		{
			root = new Node;
			root->data = item;
		}

		else
		{
			Node * temp = root;

			while (true) // search for an insertion point
			{
				if (item < temp->data) // go left
				{
					if (!temp->left) // insert left
					{
						temp->left = new Node;
						temp->left->data = item;
						break;
					}

					else
					{
						temp = temp->left; // advance left
					}
				}

				else if (item >= temp->data) // go right
				{
					if (!temp->right) // insert to the right
					{
						temp->right = new Node;
						temp->right->data = item;
						break;
					}

					else
					{
						temp = temp->right; // advance temp node
					}
				}
			}
		}

		count++;
	}

	void Delete(int item)
	{
		Node ** temp = &root;
		Node * curr;

		while (true) // keep searching till we either find the item or can't find it
		{
			if ((*temp)) // if tree is non empty
			{
				if ((*temp)->data == item) // if the current pointer to pointer node is what we want to delete
				{
					if (!(*temp)->left && !(*temp)->right) // no children
					{
						delete *temp;
						*temp = NULL;
					}

					else if (!(*temp)->left || !(*temp)->right) // needs one operand to be true so one child must be present
					{
						if (!(*temp)->left) // only have right child
							curr = (*temp)->right;

						else // only have left child
							curr = (*temp)->left;

						delete *temp;
						*temp = curr;
					}

					else // two children
					{
						Node ** t2 = NULL;
						t2 = &((*temp)->right); // memory location of pointer to pointer nodes right child

						while ((*t2)->left) // find new values for t2 while left is non-null
						{
							t2 = &((*t2)->left);
						}

						(*temp)->data = (*t2)->data; // swap
						curr = *t2;
						(*t2) = curr->right; // rehooking
						delete curr;
					}

					count--;
					break;
				}

				else if (item < (*temp)->data) // recursive cases
					temp = &((*temp)->left);

				else if (item >(*temp)->data)
					temp = &((*temp)->right);
			}
		}
	}

	bool Save()
	{
		if (count > 0) // ony wish to save a binary tree
		{
			Balance(); // want the tree to be leveled
			c = 0; // dynamicly save the tree
			storage = new int[count];
			char file[MAX_FILE_SIZE]; // file sizese are only supported of up to 50 chars

			cout << "Save to file: ";
			cin >> file;

			ofstream f(file);
			ar_recpreorder(root); // populates storage array

			for (int i = 0; i < count; i++)
				f << storage[i] << " ";

			f.close();
			return true;
		}

		return false;
	}

	bool Load()
	{
		string data; // so we can parse info
		char file[50];

		cout << "Load file: ";
		cin >> file;

		fstream f(file);

		if (f.good()) // if nothing bad happened while opening files
		{
			getline(f, data);
			istringstream ss(data);

			while (getline(ss, data, ' ')) // while we have more information
			{
				Additem(stoi(data)); // add the integer equivalent of that info
			}

			f.close();
			return true;
		}

		f.close();
		return false;

	}

	void Balance()
	{
		int temp_c = 0; // temporary counter
		int * storage = new int[count];
		Node * temp = root;
		Node * p; // previous

		while (temp)
		{
			if (!temp->left) // nothing to the left
			{
				storage[temp_c++] = temp->data;
				temp = temp->right; // try to go to the right
			}

			else
			{
				p = temp->left; // save previous

				while (p->right && p->right != temp)
					p = p->right; // advance to right

				if (!p->right) // if theres nothing to the right
				{
					p->right = temp; // swap-like functionality
					temp = temp->left;
				}

				else
				{
					p->right = NULL;
					storage[temp_c++] = temp->data;
					temp = temp->right;
				}
			}
		}

		Clear();
		Balance(storage, 0, temp_c); // needs some funny parameters
	}
};

int main()
{
	Btree b;
	int options, temp;
	bool c = true;
	string l4 = "\n\n\n\n";

	do
	{
		cout << "Binary search tree Menu options..." << endl;
		cout << "1 : Add node \t  6 : Delete node" << endl;
		cout << "2 : Balance tree  7 : Save current tree" << endl;
		cout << "3 : Clear tree \t  8 : Load a tree" << endl;
		cout << "4 : Print tree \t  9 : Search tree" << endl;
		cout << "5 : Size of tree  10: Exit" << endl;
		cout << "Enter input: ";
		cin >> options;
		cout << endl;

		switch (options)
		{
		case 1:
			cout << "Add node: ";
			cin >> temp;
			b.Additem(temp);
			cout << temp << " was added to the tree." << endl;
			break;

		case 2:
			b.Balance();
			cout << "Balanced tree." << endl << endl;
			break;

		case 3:
			b.Clear();
			cout << "Cleared tree." << endl << endl;
			break;

		case 4:
			b.inorder();
			cout << endl;
			break;

		case 5:
			cout << "The tree contains " << b.Size() << " Node" << (b.Size() > 1 ? "s" : "") << ".\n" << endl;
			break;

		case 6:
			cout << "Delete node: ";
			cin >> temp;

			if (b.Search(temp))
			{
				b.Delete(temp);
				cout << "Deleted " << temp << " from the tree." << endl;
			}

			else
				cout << "Can't delete " << temp << " because it wasn't found in the tree." << endl;
			break;

		case 7:
			if (b.Save())
				cout << "Finished Saving..." << endl;
			else
				cout << "Couldn't Save the tree." << endl << endl;
			break;

		case 8:
			if (b.Load())
				cout << "Finished Loading tree..." << endl;
			else
				cout << "Couldn't load the tree" << endl;
			break;

		case 9:
			cout << "Node to search for: ";
			cin >> temp;

			if (b.Search(temp))
				cout << "Found " << temp << " in the tree." << endl;

			else
				cout << temp << " wasn't found in the tree." << endl;

			break;

		case 1337:
			system("cls");
			b.menu();
			break;

		case 10:
			c = false;
			cout << "Exiting..." << endl << endl;
			break;
		default: cout << "Invalid input." << endl << endl;

		}

		cout << l4 << l4 << l4 << "\n\n"; //worst output format ever
		system("pause");
		system("cls");

	} while (c);

	return 0;
}