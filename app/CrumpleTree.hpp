#ifndef __PROJ_FOUR_CRUMPLE_TREE_HPP
#define __PROJ_FOUR_CRUMPLE_TREE_HPP

#include <string>
#include <stdexcept>
#include <vector>
#include <utility>


class ElementNotFoundException : public std::runtime_error 
{
public:
	explicit ElementNotFoundException(const std::string & err) : std::runtime_error(err) {}
};

template<typename Key, typename Value>
struct Node
{
	// Node class for crumple tree
	Key key;
	Value val;
	unsigned level;
	Node* parent;
	Node* left;
	Node* right;
	Node(Key key, Value val, unsigned level = 1, Node* parent = nullptr):
		key(key), val(val), level(level), parent(parent), left(nullptr), right(nullptr){}
};

struct Shape
{
	unsigned left;
	unsigned right;
	Shape(unsigned left, unsigned right) : left(left), right(right) {}
};

template<typename Key, typename Value>
void postOrderDelete(Node<Key, Value>* root);

template<typename Key, typename Value>
Node<Key, Value>* findKeyHelper(Node<Key, Value>* root, Key key);

template<typename Key, typename Value>
void inOrderVectorPushBack(std::vector<Key> & vector, Node<Key, Value>* root);

template<typename Key, typename Value>
void preOrderVectorPushBack(std::vector<Key> & vector, Node<Key, Value>* root);

template<typename Key, typename Value>
void postOrderVectorPushBack(std::vector<Key> & vector, Node<Key, Value>* root);

template<typename Key, typename Value>
bool isLeafNode(Node<Key, Value>* node);

template<typename Key, typename Value>
Node<Key, Value>* getPredecessor(Node<Key, Value>* node);

template<typename Key, typename Value>
Node<Key, Value>* getSuccessor(Node<Key, Value>* node);

template<typename Key, typename Value>
Node<Key, Value>* swapNodeToRemoveToLeaf(Node<Key, Value>* node);

template<typename Key, typename Value>
Shape getShape(Node<Key, Value>* node);

template<typename Key, typename Value>
bool isValidNodeShape(Node<Key, Value>* node);

template<typename Key, typename Value>
char sideOfParent(Node<Key, Value>* childNode);

template<typename Key, typename Value>
void insertRebalanceCase1(Node<Key, Value>* risingNode, char side);

template<typename Key, typename Value>
Node<Key, Value>* insertRebalanceCase2(Node<Key, Value>* risingNode, char side);

template<typename Key, typename Value>
Node<Key, Value>* insertRebalanceCase345(Node<Key, Value>* risingNode, char side);

template<typename Key, typename Value>
Node<Key, Value>* insertRebalanceCase3(Node<Key, Value>* risingNode, char side);

template<typename Key, typename Value>
Node<Key, Value>* insertRebalanceCase4(Node<Key, Value>* risingNode, char side);

template<typename Key, typename Value>
Node<Key, Value>* insertRebalanceCase5(Node<Key, Value>* risingNode, char side);

template<typename Key, typename Value>
void setChildToSideOfAdoptingNode(Node<Key, Value>* origParent, Node<Key, Value>* adoptingParent, char side);

template<typename Key, typename Value>
Node<Key, Value>* removeRebalanceCase1(Node<Key, Value>* parent, char fallingSide);

template<typename Key, typename Value>
Node<Key, Value>* removeRebalanceCase3456(Node<Key, Value>* fallingNode, char fallingSide, bool deleteFlag);

template<typename Key, typename Value>
Node<Key, Value>* removeRebalanceCase3(Node<Key, Value>* fallingNode, char fallingSide);

template<typename Key, typename Value>
Node<Key, Value>* removeRebalanceCase5(Node<Key, Value>* fallingNode, char fallingSide);

template<typename Key, typename Value>
Node<Key, Value>* removeRebalanceCase5(Node<Key, Value>* fallingNode, char fallingSide);

template<typename Key, typename Value>
class CrumpleTree
{
private:
	// fill in private member data here
	// If you need to declare private functions, do so here too.
	Node<Key, Value>* root;
	unsigned numKeys;

public:
	CrumpleTree();

	// In general, a copy constructor and assignment operator
	// are good things to have.
	// For this quarter, I am not requiring these. 
	//	CrumpleTree(const CrumpleTree & st);
	//	CrumpleTree & operator=(const CrumpleTree & st);


	// The destructor is required. 
	~CrumpleTree();

	// size() returns the number of distinct keys in the tree.
	size_t size() const noexcept;

	// isEmpty() returns true if and only if the tree has no values in it. 
	bool isEmpty() const noexcept;

	// contains() returns true if and only if there
	//  is a (key, value) pair in the tree
	//	that has the given key as its key.
	bool contains(const Key & k) const noexcept; 

	// returns the level on which the node with this key resides.
	// If !contains(k), this will throw an ElementNotFoundException
	unsigned getLevel(const Key & k) const;

	// find returns the value associated with the given key
	// If !contains(k), this will throw an ElementNotFoundException
	// There needs to be a version for const and non-const CrumpleTrees.
	Value & find(const Key & k);
	const Value & find(const Key & k) const;

	// Inserts the given key-value pair into 
	// the tree and performs the balancing operation(s) if needed
	// operation, as described in lecture. 
	// If the key already exists in the tree, 
	// you may do as you please (no test cases in
	// the grading script will deal with this situation)
	void insert(const Key & k, const Value & v);

	// Sets the parent's pointer of a leaf node to nullptr
	void removeChildFromParent(Node<Key, Value>* leafNode);

	// Delete a leaf node from the tree
	// If the leaf is the root set that to nullptr
	// If it isn't the node then set the parent's child pointer to nullptr
	void deleteLeaf(Node<Key, Value>* leafNode);

	// Deletes the given key from the tree
	// and performs the balancing operation(s) if needed.
	// If the key does not exist in the tree, 
	// do not modify the tree.
	void remove(const Key &k);


	// The following three functions all return
	// the set of keys in the tree as a standard vector.
	// Each returns them in a different order.
	std::vector<Key> inOrder() const;
	std::vector<Key> preOrder() const;
	std::vector<Key> postOrder() const;

	// NOTE FUNCTIONS BELOW ARE ONLY USED FOR TESTING PURPOSES
	Node<Key, Value>* testFindKey(Key key);
	Node<Key, Value>*& testGetRoot();
	void setNumKeys(unsigned numKeys);
	// NODE FUNCTIONS ABOVE ARE ONLY USED FOR TESTING PURPOSES

	// Rebalancing functions
	void insertRebalance(Node<Key, Value>* risingNode);
	void removeRebalance(Node<Key, Value>* fallingNode, bool deleteFlag);
};

template<typename Key, typename Value>
Node<Key, Value>* findKeyHelper(Node<Key, Value>* root, Key key)
{
	// Finds where the key should be in the tree
	// 1. If the key is already in the tree it will return that node
	// 2. If the key isn't in the tree it will return the parent to where it should be inserted
	// 3. If the root is empty just return nullptr
	Node<Key, Value>* currNode = root;
	while(currNode != nullptr)
	{
		// If the key is less than the current node and the current node has a left child move the node to there
		if(key < currNode->key && currNode->left != nullptr){
			currNode = currNode->left;
		}
		// If the key is greater than the current node and the current node has a right child move the node to there
		else if(currNode->key < key && currNode->right != nullptr){
			currNode = currNode->right;
		}
		// This will get reached if the key is equal to the current node or the current node has an child spot open
		else{
			return currNode;
		}
	}
	return currNode;
}

template<typename Key, typename Value>
void postOrderDelete(Node<Key, Value>* root)
{
	// Deletes the nodes based on postorder
	if(root != nullptr)
	{
		postOrderDelete(root->left);
		postOrderDelete(root->right);
		delete root;
	}
}

// NOTE FUNCTIONS BELOW ARE ONLY USED FOR TESTING PURPOSES
template<typename Key, typename Value>
Node<Key, Value>* CrumpleTree<Key,Value>::testFindKey(Key key)
{
	return findKeyHelper(root, key);
}

template<typename Key, typename Value>
Node<Key, Value>*& CrumpleTree<Key,Value>::testGetRoot()
{
	return root;
}

template<typename Key, typename Value>
void CrumpleTree<Key,Value>::setNumKeys(unsigned numKeys)
{
	this->numKeys = numKeys;
}

// NOTE FUNCTIONS ABOVE ARE ONLY USED FOR TESTING PURPOSES

template<typename Key, typename Value>
CrumpleTree<Key,Value>::CrumpleTree(): root(nullptr), numKeys(0)
{

}

template<typename Key, typename Value>
CrumpleTree<Key,Value>::~CrumpleTree()
{
	postOrderDelete(root);
}

template<typename Key, typename Value>
size_t CrumpleTree<Key, Value>::size() const noexcept
{
	return numKeys;
}

template<typename Key, typename Value>
bool CrumpleTree<Key, Value>::isEmpty() const noexcept
{
	return numKeys == 0;
}

template<typename Key, typename Value>
bool CrumpleTree<Key, Value>::contains(const Key &k) const noexcept
{
	// Uses the findKeyHelper to check if the key is already in the tree
	// If the helper returns
	// 		1. nullptr that means the tree was empty
	// 		2. A matching node that means it was found
	// 		3. A non-matching node that means it wasn't found
	if(numKeys == 0) return false;
	Node<Key, Value>* keyOrParent = findKeyHelper(root, k);
	return keyOrParent->key == k;
}

template<typename Key, typename Value>
Value & CrumpleTree<Key, Value>::find(const Key & k)
{
	// Uses the findKeyHelper to look for the key
	// If the tree is empty or the node returned doesn't match throw the error
	Node<Key, Value>* keyOrParent = findKeyHelper(root, k);
	if(numKeys == 0 || keyOrParent->key != k)
	{
		throw ElementNotFoundException("Key not found in find()");

	}
	return keyOrParent->val;
}

template<typename Key, typename Value>
const Value & CrumpleTree<Key, Value>::find(const Key & k) const
{
	// Same as non-const find
	Node<Key, Value>* keyOrParent = findKeyHelper(root, k);
	if(numKeys == 0 || keyOrParent->key != k)
	{
		throw ElementNotFoundException("Key not found in find()");

	}
	return keyOrParent->val;
}

template<typename Key, typename Value>
void inOrderVectorPushBack(std::vector<Key> & vector, Node<Key, Value>* root)
{
	if(root != nullptr)
	{
		inOrderVectorPushBack(vector, root->left);
		vector.push_back(root->key);
		inOrderVectorPushBack(vector, root->right);
	}
}

template<typename Key, typename Value>
std::vector<Key> CrumpleTree<Key, Value>::inOrder() const
{
	std::vector<Key> foo;
	inOrderVectorPushBack(foo, root);
	return foo; 
}

template<typename Key, typename Value>
void preOrderVectorPushBack(std::vector<Key> & vector, Node<Key, Value>* root)
{
	if(root != nullptr)
	{
		vector.push_back(root->key);
		preOrderVectorPushBack(vector, root->left);
		preOrderVectorPushBack(vector, root->right);
	}
}

template<typename Key, typename Value>
std::vector<Key> CrumpleTree<Key, Value>::preOrder() const
{
	std::vector<Key> foo;
	preOrderVectorPushBack(foo, root);
	return foo; 
}

template<typename Key, typename Value>
void postOrderVectorPushBack(std::vector<Key> & vector, Node<Key, Value>* root)
{
	if(root != nullptr)
	{
		postOrderVectorPushBack(vector, root->left);
		postOrderVectorPushBack(vector, root->right);
		vector.push_back(root->key);
	}
}

template<typename Key, typename Value>
std::vector<Key> CrumpleTree<Key, Value>::postOrder() const
{
	std::vector<Key> foo;
	postOrderVectorPushBack(foo, root);
	return foo;
}

template<typename Key, typename Value>
unsigned CrumpleTree<Key, Value>::getLevel(const Key & k) const
{
	Node<Key, Value>* keyOrParent = findKeyHelper(root, k);
	if(numKeys == 0 || keyOrParent->key != k)
	{
		throw ElementNotFoundException("Key not found in find()");

	}
	return keyOrParent->level;
}

template<typename Key, typename Value>
void CrumpleTree<Key, Value>::insert(const Key & k, const Value & v)
{
	Node<Key, Value>* parentNodeToPlace = findKeyHelper(root, k);
	// If the findKeyHelper returns a matching node just return and don't insert anything
	if(parentNodeToPlace != nullptr && parentNodeToPlace->key == k) return;
	// If findKeyHelper is nullptr that means the tree is empty and we insert at the root
	Node<Key, Value>* insertedNode;
	if(parentNodeToPlace == nullptr)
	{
		insertedNode = new Node<Key, Value>(k, v, 1);
		root = insertedNode;
	}
	else
	{
		// Insert to left child
		if(k < parentNodeToPlace->key)
		{
			insertedNode = new Node<Key, Value>(k, v, 1, parentNodeToPlace);
			parentNodeToPlace->left = insertedNode;
		}
		// Insert to right child
		else
		{
			insertedNode = new Node<Key, Value>(k, v, 1, parentNodeToPlace);
			parentNodeToPlace->right = insertedNode;
		}
	}
	++numKeys;
	insertRebalance(insertedNode);
}

template<typename Key, typename Value>
bool isLeafNode(Node<Key, Value>* node)
{
	// Returns true if the node is a leaf node
	return node != nullptr && node->left == nullptr && node->right == nullptr;
}

template<typename Key, typename Value>
Node<Key, Value>* getPredecessor(Node<Key, Value>* node)
{
	// Gets the predecessor of a node if there is none then return nullptr
	node = node->left;
	if(node == nullptr)
	{
		return nullptr;
	}
	else
	{
		while(node->right != nullptr)
		{
			node = node->right;
		}
	}
	return node;
}

template<typename Key, typename Value>
Node<Key, Value>* getSuccessor(Node<Key, Value>* node)
{
	// Gets the successor of a node if there is none then return nullptr
	node = node->right;
	if(node == nullptr)
	{
		return nullptr;
	}
	else
	{
		while(node->left != nullptr)
		{
			node = node->left;
		}
	}
	return node;
}

template<typename Key, typename Value>
Node<Key, Value>* swapNodeToRemoveToLeaf(Node<Key, Value>* node)
{
	// Takes in a node to remove and swaps it with the inorder predecessor/successor
	// Always swap with the predecessor if possible
	// If that swapped node is a leaf node return it else recursively call the function again till you get a leaf

	// Base case
	if(isLeafNode(node))
	{
		return node;
	}
	// Try to get the predecessor
	Node<Key, Value>* nodeToSwap = getPredecessor(node);
	// If there is none then get the successor
	if(nodeToSwap == nullptr)
	{
		nodeToSwap = getSuccessor(node);
	}
	std::swap(node->key, nodeToSwap->key);
	std::swap(node->val, nodeToSwap->val);
	// Recursive call
	return swapNodeToRemoveToLeaf(nodeToSwap);
}

template<typename Key, typename Value>
void CrumpleTree<Key, Value>::removeChildFromParent(Node<Key, Value>* leafNode)
{
	// This takes a leafnode and removes it from its parent

	// If the leaf node is the root then just set the root to nullptr
	if(leafNode->parent == nullptr)
	{
		root = nullptr;
	}
	else
	{
		// If the leafNode is the left child of the parent then set that to null else the leaf must be the right child of the parent
		if(sideOfParent(leafNode) == 'l')
		{
			leafNode->parent->left = nullptr;
		}
		else
		{
			leafNode->parent->right = nullptr;
		}
	}
}

template<typename Key, typename Value>
void CrumpleTree<Key, Value>::deleteLeaf(Node<Key, Value>* leafNode)
{
	// Delete a leaf node
	// Make sure to set the node's parent if it has one to nullptr
	removeChildFromParent(leafNode);
	delete leafNode;
}

template<typename Key, typename Value>
void CrumpleTree<Key, Value>::remove(const Key &k)
{
	// Use findKeyHelper to see if the key is in the tree
	// 1. If it isn't do nothing
	// 2. If it is find inorder predecessor and successor and swap the keys and values
	// 3. Delete the swapped node

	Node<Key, Value>* nodeToRemove = findKeyHelper(root, k);
	// If the tree is empty or the key isn't found just return to do nothing
	if(numKeys == 0 || nodeToRemove->key != k) return;
	// While the nodeToRemove isn't a leaf swap it down
	nodeToRemove = swapNodeToRemoveToLeaf(nodeToRemove);

	// If the node to remove is a not at the root do rebalancing
	if(nodeToRemove->parent != nullptr)
	{
		// Remove rebalance with the flag to remove the node
		removeRebalance(nodeToRemove, true);
	}
	// Else the node was the root and we can just safely delete
	else
	{
		deleteLeaf(nodeToRemove);
	}
	--numKeys;
}

template<typename Key, typename Value>
Shape getShape(Node<Key, Value>* node)
{
	unsigned left = node->left == nullptr ? node->level : node->level - node->left->level;
	unsigned right = node->right == nullptr ? node->level : node->level - node->right->level;
	return Shape(left, right);
}

template<typename Key, typename Value>
bool isValidNodeShape(Node<Key, Value>* node)
{
	Shape shape = getShape(node);
	return (shape.left == 1 && shape.right == 1) || (shape.left == 1 && shape.right == 2) || (shape.left == 2 && shape.right == 1) || (shape.left == 2 && shape.right == 2);
}

template<typename Key, typename Value>
char sideOfParent(Node<Key, Value>* childNode)
{
	// Returns which side the child is on of the parent
	if(childNode->parent->left != nullptr && childNode->parent->left->key == childNode->key)
	{
		return 'l';
	}
	else
	{
		return 'r';
	}
}

template<typename Key, typename Value>
Node<Key, Value>* insertRebalanceCase2(Node<Key, Value>* risingNode, char side)
{
	// Rebalance for Case 2 is to just raise the parent's level and return the parent
	++risingNode->parent->level;
	return risingNode->parent;
}

template<typename Key, typename Value>
void setChildToSideOfAdoptingNode(Node<Key, Value>* childNode, Node<Key, Value>* adoptingParent, char side)
{
	// Takes in a child node, a parent node, and the side of which the child node will go to the parent
	if(side == 'l')
	{
		adoptingParent->left = childNode;
	}
	else
	{
		adoptingParent->right = childNode;
	}
	if(childNode != nullptr)
	{
		childNode->parent = adoptingParent;
	}
}

template<typename Key, typename Value>
Node<Key, Value>* insertRebalanceCase3(Node<Key, Value>* risingNode, char side)
{
	// Set the rising node to the parent's parent correct side
	Node<Key, Value>* parent = risingNode->parent;
	Node<Key, Value>* parentOfParent = parent->parent;
	if(parentOfParent != nullptr)
	{
		char parentSide = sideOfParent(parent);
		setChildToSideOfAdoptingNode(risingNode, parentOfParent, parentSide);
	}
	else
	{
		risingNode->parent = nullptr;
	}
	// Handles rebalancing insert case 3
	if(side == 'l')
	{
		setChildToSideOfAdoptingNode(risingNode->right, parent, 'l');
		risingNode->right = parent;
	}
	else
	{
		setChildToSideOfAdoptingNode(risingNode->left, parent, 'r');
		risingNode->left = parent;
	}
	parent->parent = risingNode;
	--parent->level;
	return risingNode;
}

template<typename Key, typename Value>
Node<Key, Value>* insertRebalanceCase4(Node<Key, Value>* risingNode, char side)
{
	// Set the rising node to the parent's parent correct side
	Node<Key, Value>* parent = risingNode->parent;
	Node<Key, Value>* parentOfParent = parent->parent;
	if(parentOfParent != nullptr)
	{
		char parentSide = sideOfParent(parent);
		setChildToSideOfAdoptingNode(risingNode, parentOfParent, parentSide);
	}
	else
	{
		risingNode->parent = nullptr;
	}
	// Handles rebalancing insert case 4
	if(side == 'l')
	{
		setChildToSideOfAdoptingNode(risingNode->right, parent, 'l');
		risingNode->right = parent;
	}
	else
	{
		setChildToSideOfAdoptingNode(risingNode->left, parent, 'r');
		risingNode->left = parent;
	}
	parent->parent = risingNode;
	++risingNode->level;
	return risingNode;
}

template<typename Key, typename Value>
Node<Key, Value>* insertRebalanceCase5(Node<Key, Value>* risingNode, char side)
{
	// Set the rising node to the parent's parent correct side
	Node<Key, Value>* parent = risingNode->parent;
	Node<Key, Value>* parentOfParent = parent->parent;
	// Handles rebalancing insert case 5
	Node<Key, Value>* newRisingNode;
	if(side == 'l')
	{
		newRisingNode = risingNode->right;
		setChildToSideOfAdoptingNode(newRisingNode->right, parent, 'l');
		setChildToSideOfAdoptingNode(newRisingNode->left, risingNode, 'r');
		newRisingNode->right = parent;
		newRisingNode->left = risingNode;
	}
	else
	{
		newRisingNode = risingNode->left;
		setChildToSideOfAdoptingNode(newRisingNode->left, parent, 'r');
		setChildToSideOfAdoptingNode(newRisingNode->right, risingNode, 'l');
		newRisingNode->left = parent;
		newRisingNode->right = risingNode;
	}
	// Changes the newRisingNode's parent to parentOfParent
	if(parentOfParent != nullptr)
	{
		char parentSide = sideOfParent(parent);
		setChildToSideOfAdoptingNode(newRisingNode, parentOfParent, parentSide);
	}
	else
	{
		newRisingNode->parent = nullptr;
	}
	risingNode->parent = newRisingNode;
	parent->parent = newRisingNode;
	++newRisingNode->level;
	--risingNode->level;
	--parent->level;
	return newRisingNode;
}

template<typename Key, typename Value>
Node<Key, Value>* insertRebalanceCase345(Node<Key, Value>* risingNode, char side)
{
	// Handles rebalancing insert cases 3,4,5
	Node<Key, Value>* parent;
	Shape risingShape = getShape(risingNode);
	// This is case 3
	if( (risingShape.left == 1 && risingShape.right == 2 && side == 'l') || (risingShape.left == 2 && risingShape.right == 1 && side == 'r') )
	{
		parent = insertRebalanceCase3(risingNode, side);
	}
	// This is case 4
	if( (risingShape.left == 1 && risingShape.right == 1) )
	{
		parent = insertRebalanceCase4(risingNode, side);
	}
	// This is case 5
	if( (risingShape.left == 2 && risingShape.right == 1 && side == 'l') || (risingShape.left == 1 && risingShape.right == 2 && side == 'r'))
	{
		parent = insertRebalanceCase5(risingNode, side);
	}
	return parent;
}

template<typename Key, typename Value>
void CrumpleTree<Key, Value>::insertRebalance(Node<Key, Value>* risingNode)
{
	// Base case: If the rising node doesn't have a parent that means you have reached the root and don't have to do anything
	if(risingNode->parent == nullptr) return;
	// Base case: If the rising node has a parent that has a valid shape then you don't have to do anything
	if(isValidNodeShape(risingNode->parent)) return;

	// If the two base cases fail that means that some rebalancing is needed
	// First get whether the rising node is left rising or right rising and the parent shape
	char risingSide = sideOfParent(risingNode);
	Shape parentShape = getShape(risingNode->parent);
	Node<Key, Value>* parent;
	// Handle Cases Here (CASE 1 is irrelevant)

	// Case 2: Parent shape is (0,1) or (1,0)
	if( (parentShape.left == 0 && parentShape.right == 1) || (parentShape.left == 1 && parentShape.right == 0) )
	{
		parent = insertRebalanceCase2(risingNode, risingSide);
	}

	// Case 3,4,5: Parent shape is (0,2) or (2,0)
	if( (parentShape.left == 0 && parentShape.right == 2) || (parentShape.left == 2 && parentShape.right == 0) )
	{
		parent = insertRebalanceCase345(risingNode, risingSide);
	}

	// Reset the root if needed
	while(root->parent != nullptr)
	{
		root = root->parent;
	}
	// Recursive Case where it gets pushed up a level and you just keep rebalancing parents
	insertRebalance(parent);
}

template<typename Key, typename Value>
Node<Key, Value>* removeRebalanceCase1(Node<Key, Value>* fallingNode, char fallingSide)
{
	Shape parentShape = getShape(fallingNode->parent);

	// Handles case 1
	if(fallingSide == 'l')
	{
		if(parentShape.right == 2)
		{
			--fallingNode->parent->level;
		}
	}
	else
	{
		if(parentShape.left == 2)
		{
			--fallingNode->parent->level;
		}
	}
	return fallingNode->parent;
}

template<typename Key, typename Value>
Node<Key, Value>* removeRebalanceCase3(Node<Key, Value>* fallingNode, char fallingSide)
{
	Node<Key, Value>* parent = fallingNode->parent;
	Node<Key, Value>* parentOfParent = parent->parent;
	Node<Key, Value>* otherChild;
	char parentSide;
	if(parentOfParent != nullptr)
	{
		parentSide = sideOfParent(parent);
	}
	if(fallingSide == 'l')
	{
		otherChild = parent->right;
		setChildToSideOfAdoptingNode(otherChild->left, parent, 'r');
	}
	else
	{
		otherChild = parent->left;
		setChildToSideOfAdoptingNode(otherChild->right, parent, 'l');
	}
	setChildToSideOfAdoptingNode(parent, otherChild, fallingSide);
	if(parentOfParent != nullptr)
	{
		setChildToSideOfAdoptingNode(otherChild, parentOfParent, parentSide);
	}
	else
	{
		otherChild->parent = nullptr;
	}
	++otherChild->level;
	--parent->level;
	return otherChild;
}

template<typename Key, typename Value>
Node<Key, Value>* removeRebalanceCase5(Node<Key, Value>* fallingNode, char fallingSide)
{
	// Set the falling node to the parent's parent correct side
	Node<Key, Value>* parent = fallingNode->parent;
	Node<Key, Value>* parentOfParent = parent->parent;
	Node<Key, Value>* otherChild;
	char parentSide;
	if(parentOfParent != nullptr)
	{
		parentSide = sideOfParent(parent);
	}
	// Handles rebalancing remove case 5
	Node<Key, Value>* newFallingNode;
	if(fallingSide == 'l')
	{
		otherChild = parent->right;
		newFallingNode = otherChild->left;
		setChildToSideOfAdoptingNode(newFallingNode->left, parent, 'r');
		setChildToSideOfAdoptingNode(newFallingNode->right, otherChild, 'l');
		newFallingNode->right = otherChild;
		newFallingNode->left = parent;
	}
	else
	{
		otherChild = parent->left;
		newFallingNode = otherChild->right;
		setChildToSideOfAdoptingNode(newFallingNode->right, parent, 'l');
		setChildToSideOfAdoptingNode(newFallingNode->left, otherChild, 'r');
		newFallingNode->left = otherChild;
		newFallingNode->right = parent;
	}
	// Changes the newRisingNode's parent to parentOfParent
	if(parentOfParent != nullptr)
	{
		setChildToSideOfAdoptingNode(newFallingNode, parentOfParent, parentSide);
	}
	else
	{
		newFallingNode->parent = nullptr;
	}
	parent->parent = newFallingNode;
	otherChild->parent = newFallingNode;
	++++newFallingNode->level;
	----parent->level;
	--otherChild->level;
	return newFallingNode;
}

template<typename Key, typename Value>
Node<Key, Value>* removeRebalanceCase3456(Node<Key, Value>* fallingNode, char fallingSide, bool deleteFlag)
{
	// Shape parentShape = getShape(fallingNode->parent);
	Node<Key, Value>* newFallingNode;
	if(fallingSide == 'l')
	{
		Shape otherChildShape = getShape(fallingNode->parent->right);
		// Case 3
		if(otherChildShape.left == 1 && otherChildShape.right == 1)
		{
			newFallingNode = removeRebalanceCase3(fallingNode, fallingSide);
		}
		// Case 4
		else if(otherChildShape.left == 2 && otherChildShape.right == 1)
		{
			newFallingNode = removeRebalanceCase3(fallingNode, fallingSide);
			// Case 4B
			if(newFallingNode->left->right == nullptr && (deleteFlag || isLeafNode(fallingNode)))
			{
				--newFallingNode->level;
				--newFallingNode->left->level;
			}
		}
		// Case 5
		else if(otherChildShape.left == 1 && otherChildShape.right == 2)
		{
			newFallingNode = removeRebalanceCase5(fallingNode, fallingSide);
		}
		// Case 6
		else if(otherChildShape.left == 2 && otherChildShape.right == 2)
		{
			newFallingNode = fallingNode->parent;
			--newFallingNode->right->level;
			--newFallingNode->level;
		}
	}
	else
	{
		Shape otherChildShape = getShape(fallingNode->parent->left);
		// Case 3
		if(otherChildShape.left == 1 && otherChildShape.right == 1)
		{
			newFallingNode = removeRebalanceCase3(fallingNode, fallingSide);
		}
		// Case 4
		else if(otherChildShape.left == 1 && otherChildShape.right == 2)
		{
			newFallingNode = removeRebalanceCase3(fallingNode, fallingSide);
			// Case 4B
			if(newFallingNode->right->left == nullptr && (deleteFlag || isLeafNode(fallingNode)) )
			{
				--newFallingNode->level;
				--newFallingNode->right->level;
			}
		}
		// Case 5
		else if(otherChildShape.left == 2 && otherChildShape.right == 1)
		{
			newFallingNode = removeRebalanceCase5(fallingNode, fallingSide);
		}
		// Case 6
		else if(otherChildShape.left == 2 && otherChildShape.right == 2)
		{
			newFallingNode = fallingNode->parent;
			--newFallingNode->left->level;
			--newFallingNode->level;
		}
	}
	return newFallingNode;
}

template<typename Key, typename Value>
void CrumpleTree<Key, Value>::removeRebalance(Node<Key, Value>* fallingNode, bool deleteFlag)
{
	// Base case: If the falling node doesn't have a parent that means you are rebalancing at the root and do nothing
	if(fallingNode->parent == nullptr) return;

	// Base case: If the falling node's parent isn't a leaf node and has a valid shape then do nothing
	if(isValidNodeShape(fallingNode->parent) && !isLeafNode(fallingNode->parent) && !deleteFlag) return;

	// If the base case fails we must check for rebalancing here we see what side we are falling on and the shape of the parent
	Shape parentShape = getShape(fallingNode->parent);
	char fallingSide = sideOfParent(fallingNode);
	Node<Key, Value>* newFallingNode;

	// Case 1
	if( (parentShape.left == 1 && parentShape.right == 1) || (parentShape.left == 2 && parentShape.right == 1 && fallingSide == 'r') || (parentShape.left == 1 && parentShape.right == 2 && fallingSide == 'l') )
	{
		newFallingNode = removeRebalanceCase1(fallingNode, fallingSide);
	}

	// Case 2
	else if( (parentShape.left == 2 && parentShape.right == 2) || (parentShape.left == 3 && parentShape.right == 2) || (parentShape.left == 2 && parentShape.right == 3))
	{
		// Case two you just move the level down of the parent
		--fallingNode->parent->level;
		newFallingNode = fallingNode->parent;
	}

	// Case 3,4,5,6
	else if( (parentShape.left == 2 || parentShape.right == 2) || (parentShape.left == 3 && parentShape.right == 1) || (parentShape.left == 1 && parentShape.right == 3))
	{
		newFallingNode = removeRebalanceCase3456(fallingNode, fallingSide, deleteFlag);
	}

	// If the deleteFlag is true delete the fallingNode
	if(deleteFlag)
	{
		deleteLeaf(fallingNode);
	}

	// Reset the root if needed
	while(root->parent != nullptr)
	{
		root = root->parent;
	}

	// If the new falling node doesn't have a parent we check for rebalancing
	if(newFallingNode->parent != nullptr)
	{
		removeRebalance(newFallingNode, false);
	}
}

template<typename Key, typename Value>
bool crumpleTreeChecker(CrumpleTree<Key, Value>& tree)
{
	return checkAdjacentNodes(tree.testGetRoot());
}

template<typename Key, typename Value>
bool checkAdjacentNodes(Node<Key, Value>* root)
{
	// If the node is a leafnode and the level is correct return true
	if(root == nullptr)
	{
		return true;
	}
	if(isLeafNode(root))
	{
		if(root->level != 1)
		{
			return false;
		}
		return true;
	}
	// If the BST ordering property isn't correct return false
	if(!(root->left != nullptr && root->left->key < root->key) && !(root->right != nullptr && root->key < root->right->key))
	{
		return false;
	}
	// Making sure each node's shape is valid
	if(!isValidNodeShape(root))
	{
		return false;
	}
	Shape rootShape = getShape(root);
	// Checks the shapes match the level of the nodes below
	if(rootShape.left != root->level - (root->left == nullptr ? 0 : root->left->level))
	{
		return false;
	}
	if(rootShape.right != root->level - (root->right == nullptr ? 0 : root->right->level))
	{
		return false;
	}
	return checkAdjacentNodes(root->left) && checkAdjacentNodes(root->right);
}

#endif 