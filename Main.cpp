#include<iostream>
#include<ctime>
using namespace std;

struct Node
{
	int key;
	Node* left;
	Node* right;
	int height;
};

Node* newNode(int a)
{
	Node * node = new Node;
	node->key = a;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	return node;
}
int max(int a, int b)
{
	return (a > b) ? a : b;
}
int height(struct Node *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}
Node* rightRotate(Node* node)
{
	Node* x = node->left;
	Node* y = x->right;
	x->right = node;
	node->left = y;
	node->height = max(height(node->left), height(node->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;
	return x;
}

Node* leftRotate(Node* node)
{
	Node* x = node->right;
	Node* y = x->left;
	x->left = node;
	node->right = y;
	node->height = max(height(node->left), height(node->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;
	return x;

}

int getBalance(Node* node)
{
	if (node == NULL) return 0;
	return height(node->left) - height(node->right);
}

Node* insert(Node* node, int data)
{
	if (node == NULL) return newNode(data);
	if (data < node->key) node->left= insert(node->left, data);
	else node->right= insert(node->right, data);
	node->height = max(height(node->left), height(node->right)) + 1;
	int balance = getBalance(node);
	if (balance > 1 && data < node->left->key)
		return rightRotate(node);
	if (balance < -1 && data > node->right->key)
		return leftRotate(node);
	if (balance > 1 && data > node->left->key)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	if (balance < - 1 && data < node->right->key)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	return node;
}
Node* minRight(Node* node)
{
	Node* current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}
Node* deleteNode(Node* node, int data)
{
	if (node == NULL)
		return node;
	if (data < node->key)
		node->left = deleteNode(node ->left, data);
	else if (data > node->key)
		node->right = deleteNode(node->right, data);
	else
	{

		if ((node->left == NULL) || (node->right == NULL))
		{
			struct Node *temp = node->left ? node->left : node->right;
			if (temp == NULL)
			{
				temp = node;
				node = NULL;
			}
			else 
				*node = *temp;
			delete temp; temp = NULL;
		}
		else
		{
			struct Node* temp = minRight(node->right);
			node->key = temp->key;
			node->right = deleteNode(node->right, temp->key);
		}
	}

	node->height = max(height(node->left), height(node->right)) + 1;

	int balance = getBalance(node);
	if (balance > 1 && data < node->left->key)
		return rightRotate(node);
	if (balance < -1 && data > node->right->key)
		return leftRotate(node);
	if (balance > 1 && data > node->left->key)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);

	}
	if (balance < -1 && data < node->right->key)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);

	}
	return node;
}
void LNR(Node* node)
{
	if (node == NULL) return;
	LNR(node->left);
	cout << node->key << ' ';
	LNR(node->right);

}
Node* search(Node* node, int data)
{
	Node* current = node;
	bool checker = false;
	while (current!=NULL)
	{
		if (data > current->key)
			current = current->right;
		else if (data < current->key)
			current = current->left;
		else
		{
			checker = true;
			break;

		}
	}
	if (checker)
		return current;
	else return NULL;
}
Node* random(Node* node, int num)
{
	srand(time(0));
	for (int i = 0; i < num; i++)
		node = insert(node, rand() % 1000);
	return node;
}
int main()
{
	Node *root = NULL;

	
	root=random(root, 10);

	LNR(root);
	cout << endl;
	/*root = deleteNode(root, 10);
	LNR(root);
	Node* s = search(root, 5);
	if  (s!=NULL)
	cout << s->key;
	else cout << "Ko tim thay.";*/
	system("pause");
}