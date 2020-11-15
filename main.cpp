#include <iostream>
#include <vector>

using namespace std;

bool founded = false;

typedef struct link
{
	int id;
	int weight;
	link* left, * right;
} tree;

void push(link*& top, int D, int W)
{
	if (top == NULL)
	{
	link* a = new link;
	a->id = D;
	a->weight = W;
	a->left = NULL;
	a->right = NULL;
		top = a;
	}
	else if (D <= top->id)
	{
		push(top->left, D, W);
	}
	else
	{
			push(top->right, D, W);
	}
}

bool tree_empty(link*& top)
{
	if (top == NULL)
		return true;
	else
		return false;
}

int found_right(link*& top)
{
	if (top->right != NULL)
		return found_right(top);
	else
	{
		int buf = top->id;
		top = NULL;
		return buf;
	}
}

link* delete_id(link*& top, int D)
{
	if (top == NULL)
	{
		return top;
	}
	else if (D < top->id)
	{
		top->left = delete_id(top->left, D);
	}
	else if (D > top->id)
	{
		top->right = delete_id(top->right, D);
	}
	else
	{
		founded = true;
		if (top->left == NULL && top->right == NULL)
		{
			top = NULL;
		}
		else
		{
			if (top->left != NULL && top->right != NULL)
			{
				top->id = found_right(top->left);
			}
			else
			{
				if (top->left != NULL)
				{
					top = top->left;
				}
				else if (top->right != NULL)
				{
					top = top->right;
				}
			}
		}
	}
	return top;
}

void show_inorder(link*& top)
{
	if (top->left != NULL)
	{
		show_inorder(top->left);
	}
	cout << "Verth: " << top->id << ", weight:" << top->weight << '\n';
	if (top->right != NULL)
	{
		show_inorder(top->right);
	}
}

void show_preorder(link*& top)
{
	cout << "Verth: " << top->id << ", weight:" << top->weight << '\n';
	if (top->left != NULL)
	{
		show_preorder(top->left);
	}
	if (top->right != NULL)
	{
		show_preorder(top->right);
	}
}

void show_postorder(link*& top)
{
	if (top->left != NULL)
	{
		show_postorder(top->left);
	}
	if (top->right != NULL)
	{
		show_postorder(top->right);
	}
	cout << "Verth: " << top->id << ", weight:" << top->weight << '\n';
}

int sum_vector(vector<pair<int, int>> A)
{
	int S = 0;
	for (int i = 0; i < A.size(); i++)
	{
		S += A[i].second;
	}
	return S;
}

vector<pair<int, int>> max_way(link*& top)
{
	vector<pair<int, int>> result;
	if (top->left != NULL && top->right != NULL)
	{
		vector<pair<int, int>> left_vector = max_way(top->left);
		vector<pair<int, int>> right_vector = max_way(top->right);
		if (sum_vector(left_vector) > sum_vector(right_vector))
		{
			result = left_vector;
		}
		else
		{
			result = right_vector;
		}
		result.push_back(make_pair(top->id, top->weight));
	}
	else if (top->left == NULL && top->right == NULL)
	{
		result.push_back(make_pair(top->id, top->weight));
	}
	else if (top->left == NULL)
	{
		result = max_way(top->right);
		result.push_back(make_pair(top->id, top->weight));
	}
	else
	{
		result = max_way(top->left);
		result.push_back(make_pair(top->id, top->weight));
	}
	return result;
}


void menu(int com, link*& top)
{
	switch (com)
	{
	case 1:
	{
		int D, W;
		cout << "Enter new id: ";
		cin >> D;
		cout << "Enter weight: ";
		cin >> W;
		push(top, D, W);
		break;
	}
	case 2:
	{
		cout << "Enter ";
		int D;
		cin >> D;
		link* buf = delete_id(top, D);
		if (!founded)
			cout << "Id not found\n";
		founded = false;
		break;
	}
	case 3:
	{
		if (!tree_empty(top))
		{
			cout << "Tree(inorder):\n";
			show_inorder(top);
			cout << '\n';
		}
		else
		{
			cout << "Tree is empty\n";
		}
		break;
	}
	case 4:
	{
		if (!tree_empty(top))
		{
			cout << "Tree(preorder):\n";
			show_preorder(top);
			cout << '\n';
		}
		else
		{
			cout << "Tree is empty\n";
		}
		break;
	}
	case 5:
	{
		if (!tree_empty(top))
		{
			cout << "Tree(postorder):\n";
			show_postorder(top);
			cout << '\n';
		}
		else
		{
			cout << "Tree is empty\n";
		}
		break;
	}
	case 6:
	{
		if (!tree_empty(top))
		{
			vector<pair<int, int>> MW = max_way(top);
			cout << "Max way: ";
			for (int i = MW.size() - 1; i >= 0; i--)
			{
				cout << MW[i].first << ' ';
			}
			cout << endl;
		}
		else
		{
			cout << "Tree is empty\n";
		}
		break;
	}
	case 7:
	{
		break;
	}
	default:
	{
		cout << "Uknown command\n";
		break;
	}
	}
}

void print_menu()
{
	cout << "Menu:\n"
		<< "1. Push new id;\n"
		<< "2. Delete id;\n"
		<< "3. Show tree(inorder)\n"
		<< "4. Show tree(preorder)\n"
		<< "5. Show tree(postorder)\n"
		<< "6. Find max path\n";
}

void create_nonempty_tree(link *&top)
{
	push(top, 10, 0);
	push(top, 3, 1);
	push(top, 1, 0);
	push(top, 4, -1);
	push(top, 6, -1);
	push(top, 21, 1);
	push(top, 19, 0);
	push(top, 15, 1);
}

int main()
{
	link* top = NULL;
	create_nonempty_tree(top);
	print_menu();
	int c = 0;
	while (c != 7)
	{
		cout << "Enter the command: ";
		cin >> c;
		menu(c, top);
	}

	return 0;
}
