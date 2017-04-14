//
//  Algo_Trees.hpp
//  Grindstone
//
//  Created by sphota on 8/11/16.
//  Copyright © 2016 Intellex. All rights reserved.
//

#ifndef Algo_Trees_hpp
#define Algo_Trees_hpp

#include "include.h"

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

template <typename T>
class BSTNode {
public:
	T data;
	std::shared_ptr<BSTNode> left, right;
	BSTNode(T d) : data(d), left(nullptr), right(nullptr) {}
};

struct TNode {
	unsigned int datum;
	TNode *right = nullptr, *left = nullptr;
};

class Trie {
private:
	TNode *root;
	void insertBit(vector<unsigned int> & buffer, int & idx);
	TNode* lastCommonNode(TNode* root, vector<unsigned int> & buffer,  int & idx);
public:
	Trie();
	~Trie();
	void insert(int num);
	//TNode* deleteNode(TNode *root);
	TNode* getRoot();
	int findMaxHeight(TNode *root);
	void largestPath(TNode* node, string & path, int & len, int & depth);
};

int findMaximumXOR(vector<int>& nums);


#endif /* Algo_Trees_hpp */
