//
//  Algo_Trees.cpp
//  Grindstone
//
//  Created by sphota on 8/11/16.
//  Copyright © 2016 Intellex. All rights reserved.
//

#include "Algo_Trees.hpp"

using namespace std;

/* Determine if tree is balanced */

static int depth(TreeNode* root) {
	if (!root) return 0;
	return 1 + fmax(depth(root->right), depth(root->left));
}

bool isBalanced(TreeNode* root) {
	if (!root) return true;
	int hRight = depth(root->right);
	int hLeft = depth(root->left);
	if (abs(hLeft - hRight) > 1) return false;
	return isBalanced(root->left) * isBalanced(root->right);
}

/* check if is Valid BST (slow) */

bool inorderTraversal(TreeNode* root, vector<int> & in) {
	if (root == NULL) return true;
	bool l = inorderTraversal(root->left, in);
	if (not in.empty() and in.back() >= root->val)
		return false;
	else
		in.push_back(root->val);
	bool r = inorderTraversal(root->right, in);
	return r & l;
}

bool isValidBST(TreeNode* root) {
	vector<int> in;
	return inorderTraversal(root, in);
}

/* inorder successor using stack */

TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
	if (p == NULL) return NULL;
	std::stack<TreeNode *> st;
	TreeNode *right = p->right;
	if (right != NULL) {
		if (right->left == NULL)
			return right;
		TreeNode *left = right->left;
		while (left->left) left = left->left;
		return left;
	} else {
		while (root || !st.empty()) {
			if (root == NULL) {
				root = st.top()->right;
				st.pop();
				if (root == p && !st.empty())
					return st.top();
				continue;
			}
			st.push(root);
			root = root->left;
			if (root == p && !st.empty())
				return st.top();
		}
		return NULL;
	}
}

/* extract leaves */

TreeNode* trim(TreeNode *root, vector<int> & v) {
	if (root) {
		if (root->left == NULL and root->right == NULL) {
			v.push_back(root->val);
			delete root;
			return NULL;
		}
		root->right = trim(root->right, v);
		root->left = trim(root->left, v);
	}
	return root;
}

vector<vector<int>> findLeaves(TreeNode* root) {
	vector<vector<int>> leaves;
	if (root == NULL)
		return leaves;
	while (root->right or root->left) {
		vector<int> l;
		trim(root, l);
		leaves.push_back(l);
	}
	vector<int> l;
	l.push_back(root->val);
	leaves.push_back(l);
	return leaves;
}

/* check if same tree */

bool isSameTree(TreeNode* p, TreeNode* q) {
	if (p == q) return true;
	if ((p == NULL and q != NULL) or (p != NULL and q == NULL))
		return false;
	if (p->val != q->val)
		return false;
	bool right, left;
	right = isSameTree(p->right, q->right);
	left = isSameTree(p->left, q->left);
	return right & left;
}

/* invert tree */

TreeNode* invertTree(TreeNode* root) {
	if (not root) return NULL;
	TreeNode *r = invertTree(root->right), *l = invertTree(root->left);
	root->right = l;
	root->left = r;
	return root;
}

/* node count */

unsigned int nodeCount(TreeNode* root) {
	unsigned int count = 1;
	if (root->left != NULL) {
		count += nodeCount(root->left);
	}
	if (root->right != NULL) {
		count += nodeCount(root->right);
	}
	return count;
}

/* Sum of left leaves */

void sumLeft(TreeNode* root, int & s) {
	if (root == NULL) return;
	if (root->left) {
		if (root->left->left == NULL and root->left->right == NULL)
			s += root->left->val;
	}
	sumLeft(root->left, s);
	sumLeft(root->right, s);
}

int sumOfLeftLeaves(TreeNode* root) {
	if (root == NULL) return 0;
	int s = 0;
	sumLeft(root, s);
	return s;
}

int findMaximumXOR(vector<int>& nums);

/* Max XOR */

Trie::Trie() {
	root = new TNode;
	root->datum = UINT_MAX;
	root->left = nullptr;
	root->right = nullptr;
}

Trie::~Trie() {
	//deleteNode(root);
}

TNode* Trie::getRoot() {
	return root;
}

//TNode* Trie::deleteNode(TNode *root) {
//	if (root == nullptr) return NULL;
//	TNode *r = deleteNode(root->right);
//	delete r;
//	TNode *l = deleteNode(root->left);
//	delete l;
//	return root;
//}

void Trie::insert(int num) {
	unsigned int bit = 0;
	if (num == 0) {
		this->root->left = new TNode;
		this->root->left->datum = 0;
		this->root->left->right = nullptr;
		this->root->left->left = nullptr;
		return;
	}
	int i = 0;
	vector<unsigned int> buffer;
	while (num) {
		bit = num & 1;
		num = num >> 1;
		buffer.insert(buffer.begin(), bit);
	}
	this->insertBit(buffer, i);
}

void Trie::insertBit(vector<unsigned int> & buffer, int & idx) {
	TNode* last = this->lastCommonNode(this->root->right, buffer, idx);
	if (last == nullptr) {
		root->right = new TNode;
		root->right->datum = 1;
		root->right->left = nullptr;
		root->right->right = nullptr;
		idx--;
		last = this->lastCommonNode(this->root->right, buffer, idx);
	}
	if (idx == buffer.size()) {
		return;
	}
	for (int j = idx; j < buffer.size(); j++) {
		TNode* p = new TNode;
		p->datum = buffer[j];
		if (p->datum == 0) {
			last->left = p;
		} else {
			last->right = p;
		}
		last = p;
	}
}

TNode* Trie::lastCommonNode(TNode* root, vector<unsigned int> & buffer, int & idx) {
	if (root == nullptr && idx == 0) {
		idx = idx + 1;
		return nullptr;
	}
	if (idx == buffer.size()) {
		return root;
	}
	if (buffer[++idx] == 0) {
		if (root->left) {
			return lastCommonNode(root->left, buffer, idx);
		} else {
			return root;
		}
	} else {
		if (root->right) {
			return lastCommonNode(root->right, buffer, idx);
		} else {
			return root;
		}
	}
}

int Trie::findMaxHeight(TNode *root) {
	if (!root) return 0;
	return 1 + fmax(findMaxHeight(root->right), findMaxHeight(root->left));
}

void Trie::largestPath(TNode* node, string & path, int & len, int & depth) {
	if ( node == nullptr ) return;
	
	string s = to_string(node->datum);
	path += s;
	len++;
	depth--;
	
	if ( depth == 0 ) {
		return;
	}
	
	largestPath(node->left, path, len, depth);
	largestPath(node->right, path, len, depth);
}

int findMaximumXOR(vector<int>& nums) {
	Trie* tree = new Trie;
	int max = -1;
	for (int i = 0; i < nums.size(); i++) {
		tree->insert(nums[i]);
	}
	TNode *root = tree->getRoot();
	TNode *p = root;
	while (p->left == nullptr || p->right == nullptr) {
		if (p->left) {
			p = p->left;
		} else if (p->right) {
			p = p->right;
		} else {
			max = 0;
			break;
		}
	}
	
	if (max == -1) {
		string leftBinary = "1";
		string rightBinary = "1";
		int lenL = 0, lenR = 0;
		int hL = tree->findMaxHeight(p->right);
		int hR = tree->findMaxHeight(p->left);
		tree->largestPath(p->left, leftBinary, lenL, hL);
		tree->largestPath(p->right, rightBinary, lenR, hR);
		max = stoi(leftBinary, nullptr, 2) ^ stoi(rightBinary, nullptr, 2);
	}
	
	return max;
}
