#include <iostream>
#include <vector>

constexpr int values[] = {
        75,
        95,64,
        17,47,82,
        18,35,87,10,
        20,4,82,47,65,
        19,1,23,75,3,34,
        88,2,77,73,7,63,67,
        99,65,4,28,6,16,70,92,
        41,41,26,56,83,40,80,70,33,
        41,48,72,33,47,32,37,16,94,29,
        53,71,44,65,25,43,91,52,97,51,14,
        70,11,33,28,77,73,17,78,39,68,17,57,
        91,71,52,38,17,14,91,43,58,50,27,29,48,
        63,66,4,68,89,53,67,30,73,16,69,87,40,31,
        4,62,98,27,23,9,70,98,73,93,38,53,60,4,23
};

class Finder {
	struct Node {
		int n;
		Node *left, *right;
	} root;

	size_t levelWidth(size_t index)
	{
		size_t currWidth = 1;
		for (size_t i = 0, perLevel = 0; i <= index; ++i, ++perLevel) {
			if (perLevel == currWidth) {
				++currWidth;
				perLevel = 0;
			}
		}
		return currWidth;
	}

	void constructTree(const std::vector<int> &values, size_t i, Node *root)
	{
		root->n = values[i];

		size_t l = i + levelWidth(i);
		if (l >= values.size())
			root->left = nullptr;
		else
			constructTree(values, l, root->left = new Node);
		
		if (l + 1 >= values.size())
			root->right = nullptr;
		else
			constructTree(values, l + 1, root->right = new Node);
	}

	void destructTree(Node *root)
	{
		root->left ? destructTree(root->left) : delete root;

		if (root->right)
			destructTree(root->right);
		else
			if (root->left)
				delete root;
	}

	void find(Node *root, int &longest, int length)
	{
		if (root->left)
			find(root->left, longest, length + root->left->n);
		else
			if (length > longest)
				longest = length;
		
		if (root->right)
			find(root->right, longest, length + root->right->n);
		else
			if (length > longest)
				longest = length;
	}

	public:
	explicit Finder(const std::vector<int> &values)
	{
		constructTree(values, 0, &root);
	}

	~Finder()
	{
		destructTree(&root);
	}

	int operator()()
	{
		int length = 0;
		find(&root, length, 0);
		return length;
	}
};



int main()
{
	std::cout << Finder{{values, values + sizeof(values) / sizeof(*values)}}() << std::endl;
}