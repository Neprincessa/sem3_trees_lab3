#include "sequence.h"
#include "impl_seq.h"
#include "student.h"


using namespace std;


struct foundPare {
	int index;
	void *node;  
};

template <typename TElement>
class BTreeNode
{
	TElement *keys;
	int t; //minimum degree
	BTreeNode<TElement> **C; //an array of child pointers
 	int n; //current numbers of keys
	bool leaf;

public:

	BTreeNode(int _t, bool _leaf);
	void traverse();  // A function to traverse all nodes in a subtree rooted with this node 
	foundPare search(TElement k);
	int findKey(TElement k); // A function that returns the index of the first key that is greater or equal to k 
	// A utility function to insert a new key in the subtree rooted with 
	//this node. The assumption is, the node must be non-full when this function is called 
	void insertNonFull(TElement k);   
	// A utility function to split the child y of this node. i is index 
	// of y in child array C[].  The Child y must be full when this 
	// function is called 
	void splitChild(int i, BTreeNode<TElement> *y);
	void remove(TElement k);
	void removeFromLeaf(int idx);
	void removeFromNonLeaf(int idx);
	TElement getPred(int idx); // A function to get the predecessor of the key- where the key is present in the idx-th position in the node
	TElement getSucc(int idx);  // A function to get the successor of the key- where the key is present in the idx-th position in the node 
	void fill(int idx); // A function to fill up the child node present in the idx - th position in the C[] array if that child has less than t-1 keys
	void borrowFromPrev(int idx);  // A function to borrow a key from the C[idx-1]-th node and place it in C[idx]th node 
	void borrowFromNext(int idx); // A function to borrow a key from the C[idx+1]-th node and place it in C[idx]th node
	void merge(int idx);

	template <typename TElement>
	friend class BTree;
};

template <typename TElement>
class BTree
{
	BTreeNode<TElement> *root;
	int t;
	int studentFlag;
public:

	BTree(int _t, int _studentFlag)
	{
		root = NULL;
		t = _t;
		studentFlag = _studentFlag;
	}

	void traverse()
	{
		if (root != NULL) root->traverse();
	}
	
	foundPare search(TElement k) // A function to search a key in subtree rooted with this node. 
	{
		return/* (root == NULL) ? NULL :*/ root->search(k);
	}
	int getRootLength() {
		return this->root->n;
	}

	void insert(TElement k);

	void remove(TElement k);

};

template <typename TElement>
BTreeNode<TElement>::BTreeNode(int t1, bool leaf1)
{
	t = t1;
	leaf = leaf1;
	keys = new TElement[2 * t - 1];
	C = new BTreeNode<TElement> *[2 * t];
	n = 0;
}

template <typename TElement>
int BTreeNode<TElement>::findKey(TElement k)
{
	int idx = 0;
	while (idx<n && keys[idx] < k)
		++idx;
	return idx;
}

template <typename TElement>
void BTreeNode<TElement>::remove(TElement k)
{
	int idx = findKey(k);

	if (idx < n && keys[idx] == k)
	{

		if (leaf)
			removeFromLeaf(idx);
		else
			removeFromNonLeaf(idx);
	}
	else
	{

		if (leaf)
		{
			cout << "The key does not exist in the tree\n";
			return;
		}

		// The key to be removed is present in the sub-tree rooted with this node 
		// The flag indicates whether the key is present in the sub-tree rooted 
		// with the last child of this node 
		bool flag = ((idx == n) ? true : false);

		// If the child where the key is supposed to exist has less that t keys, 
		// we fill that child
		if (C[idx]->n < t)
			fill(idx);

		// If the last child has been merged, it must have merged with the previous 
		// child and so we recurse on the (idx-1)th child. Else, we recurse on the 
		// (idx)th child which now has atleast t keys
		if (flag && idx > n)
			C[idx - 1]->remove(k);
		else
			C[idx]->remove(k);
	}
	return;
}

template <typename TElement>
void BTreeNode<TElement>::removeFromLeaf(int idx)
{

	for (int i = idx + 1; i<n; ++i)
		keys[i - 1] = keys[i];

	n--;

	return;
}

template <typename TElement>
void BTreeNode<TElement>::removeFromNonLeaf(int idx)
{

	TElement k = keys[idx];

	// If the child that precedes k (C[idx]) has atleast t keys, 
	// find the predecessor 'pred' of k in the subtree rooted at 
	// C[idx]. Replace k by pred. Recursively delete pred 
	// in C[idx] 
	if (C[idx]->n >= t)
	{
		TElement pred = getPred(idx);
		keys[idx] = pred;
		C[idx]->remove(pred);
	}

	// If the child C[idx] has less that t keys, examine C[idx+1]. 
	// If C[idx+1] has atleast t keys, find the successor 'succ' of k in 
	// the subtree rooted at C[idx+1] 
	// Replace k by succ 
	// Recursively delete succ in C[idx+1] 
	else if (C[idx + 1]->n >= t)
	{
		int succ = getSucc(idx);
		keys[idx] = succ;
		C[idx + 1]->remove(succ);
	}

	// If both C[idx] and C[idx+1] has less that t keys,merge k and all of C[idx+1] 
	// into C[idx] 
	// Now C[idx] contains 2t-1 keys 
	// Free C[idx+1] and recursively delete k from C[idx] 
	else
	{
		merge(idx);
		C[idx]->remove(k);
	}
	return;
}

template <typename TElement>
TElement BTreeNode<TElement>::getPred(int idx)
{
	BTreeNode *cur = C[idx];
	while (!cur->leaf)
		cur = cur->C[cur->n];

	// Return the last key of the leaf 
	return cur->keys[cur->n - 1];
}

template <typename TElement>
TElement BTreeNode<TElement>::getSucc(int idx)
{

	BTreeNode *cur = C[idx + 1];
	while (!cur->leaf)
		cur = cur->C[0];

	return cur->keys[0];
}

template <typename TElement>
void BTreeNode<TElement>::fill(int idx)
{

	// If the previous child(C[idx-1]) has more than t-1 keys, borrow a key 
	// from that child
	if (idx != 0 && C[idx - 1]->n >= t)
		borrowFromPrev(idx);

	// If the next child(C[idx+1]) has more than t-1 keys, borrow a key 
	// from that child
	else if (idx != n && C[idx + 1]->n >= t)
		borrowFromNext(idx);

	// Merge C[idx] with its sibling 
	// If C[idx] is the last child, merge it with with its previous sibling 
	// Otherwise merge it with its next sibling 
	else
	{
		if (idx != n)
			merge(idx);
		else
			merge(idx - 1);
	}
	return;
}

template <typename TElement>
void BTreeNode<TElement>::borrowFromPrev(int idx)
{

	BTreeNode *child = C[idx];
	BTreeNode *sibling = C[idx - 1];


	// The last key from C[idx-1] goes up to the parent and key[idx-1] 
	// from parent is inserted as the first key in C[idx]. Thus, the  loses 
	// sibling one key and child gains one key 

	// Moving all key in C[idx] one step ahead 
	for (int i = child->n - 1; i >= 0; --i)
		child->keys[i + 1] = child->keys[i];

	// If C[idx] is not a leaf, move all its child pointers one step ahead 
	if (!child->leaf)
	{
		for (int i = child->n; i >= 0; --i)
			child->C[i + 1] = child->C[i];
	}

	// Setting child's first key equal to keys[idx-1] from the current node
	child->keys[0] = keys[idx - 1];

	// Moving sibling's last child as C[idx]'s first child
	if (!child->leaf)
		child->C[0] = sibling->C[sibling->n];

	// Moving the key from the sibling to the parent 
	// This reduces the number of keys in the sibling 
	keys[idx - 1] = sibling->keys[sibling->n - 1];

	child->n += 1;
	sibling->n -= 1;

	return;
}

template <typename TElement>
void BTreeNode<TElement>::borrowFromNext(int idx)
{

	BTreeNode *child = C[idx];
	BTreeNode *sibling = C[idx + 1];

	// keys[idx] is inserted as the last key in C[idx]
	child->keys[(child->n)] = keys[idx];

	// Sibling's first child is inserted as the last child 
	// into C[idx]
	if (!(child->leaf))
		child->C[(child->n) + 1] = sibling->C[0];

	//The first key from sibling is inserted into keys[idx] 
	keys[idx] = sibling->keys[0];

	// Moving all keys in sibling one step behind 
	for (int i = 1; i<sibling->n; ++i)
		sibling->keys[i - 1] = sibling->keys[i];

	// Moving the child pointers one step behind
	if (!sibling->leaf)
	{
		for (int i = 1; i <= sibling->n; ++i)
			sibling->C[i - 1] = sibling->C[i];
	}

	// Increasing and decreasing the key count of C[idx] and C[idx+1] 
	// respectively 
	child->n += 1;
	sibling->n -= 1;

	return;
}

template <typename TElement>
void BTreeNode<TElement>::merge(int idx)
{
	BTreeNode *child = C[idx];
	BTreeNode *sibling = C[idx + 1];

	// Pulling a key from the current node and inserting it into (t-1)th 
	// position of C[idx] 
	child->keys[t - 1] = keys[idx];

	// Copying the keys from C[idx+1] to C[idx] at the end
	for (int i = 0; i<sibling->n; ++i)
		child->keys[i + t] = sibling->keys[i];

	// Copying the child pointers from C[idx+1] to C[idx]
	if (!child->leaf)
	{
		for (int i = 0; i <= sibling->n; ++i)
			child->C[i + t] = sibling->C[i];
	}

	// Moving all keys after idx in the current node one step before - 
	// to fill the gap created by moving keys[idx] to C[idx]
	for (int i = idx + 1; i<n; ++i)
		keys[i - 1] = keys[i];

	// Moving the child pointers after (idx+1) in the current node one 
	// step before 
	for (int i = idx + 2; i <= n; ++i)
		C[i - 1] = C[i];

	// Updating the key count of child and the current node
	child->n += sibling->n + 1;
	n--;

	delete(sibling);
	return;
}

template <typename TElement>
void BTree<TElement>::insert(TElement k)
{
	if (root == NULL)
	{
		root = new BTreeNode<TElement>(t, true);
		root->keys[0] = k;
		root->n = 1;
	}
	else
	{
		if (root->n == 2 * t - 1)
		{
			BTreeNode<TElement> *s = new BTreeNode<TElement>(t, false);

			s->C[0] = root;

			// Split the old root and move 1 key to the new root
			s->splitChild(0, root);

			// New root has two children now.  Decide which of the 
			// two children is going to have new key
			int i = 0;
			if (s->keys[0] < k)
				i++;
			s->C[i]->insertNonFull(k);

			root = s;
		}
		else
			// If root is not full, call insertNonFull for root
			root->insertNonFull(k);
	}
	return;
}


template <typename TElement>
void BTreeNode<TElement>::insertNonFull(TElement k)
{
	int i = n - 1;

	if (leaf == true)
	{
		// The following loop does two things 
		// a) Finds the location of new key to be inserted 
		// b) Moves all greater keys to one place ahead 
		while (i >= 0 && keys[i] > k)
		{
			keys[i + 1] = keys[i];
			i--;
		}
		// Insert the new key at found location 
		keys[i + 1] = k;
		n = n + 1;
	}
	else
	{
		while (i >= 0 && keys[i] > k)
			i--;

		if (C[i + 1]->n == 2 * t - 1)
		{
			splitChild(i + 1, C[i + 1]);

			// After split, the middle key of C[i] goes up and 
			// C[i] is splitted into two.  See which of the two 
			// is going to have the new key 
			if (keys[i + 1] < k)
				i++;
		}
		C[i + 1]->insertNonFull(k);
	}
}


template <typename TElement>
void BTreeNode<TElement>::splitChild(int i, BTreeNode *y)
{

	BTreeNode *z = new BTreeNode(y->t, y->leaf);
	z->n = t - 1;

	for (int j = 0; j < t - 1; j++)
		z->keys[j] = y->keys[j + t];

	if (y->leaf == false)
	{
		for (int j = 0; j < t; j++)
			z->C[j] = y->C[j + t];
	}

	y->n = t - 1;

	// Since this node is going to have a new child, 
	// create space of new child 
	for (int j = n; j >= i + 1; j--)
		C[j + 1] = C[j];

	// Link the new child to this node
	C[i + 1] = z;

	// A key of y will move to this node. Find location of 
	// new key and move all greater keys one space ahead
	for (int j = n - 1; j >= i; j--)
		keys[j + 1] = keys[j];

	keys[i] = y->keys[t - 1];

	n = n + 1;
}

template <typename TElement>
void BTreeNode<TElement>::traverse()
{
	// There are n keys and n+1 children, travers through n keys 
	// and first n children 
	int i;
	for (i = 0; i < n; i++)
	{
		// If this is not leaf, then before printing key[i], 
		// traverse the subtree rooted with child C[i]. 
		if (leaf == false)
			C[i]->traverse();
		cout << /*" " <<*/ keys[i]<<endl;
	}

	if (leaf == false)
		C[i]->traverse();
}

template <typename TElement>
foundPare BTreeNode<TElement>::search(TElement k)
{
	int i = 0;
	while (i < n && k > keys[i])
		i++;

	if (keys[i] == k) {
		foundPare myPare;
		myPare.node = this;
		myPare.index = i;
		return myPare;
	}

	if (leaf == true) {
		throw NoElement();
		//return NULL;
	}

	return C[i]->search(k);
}

template <typename TElement>
void BTree<TElement>::remove(TElement k)
{
	if (!root)
	{
		cout << "The tree is empty\n";
		return;
	}

	root->remove(k);

	// If the root node has 0 keys, make its first child as the new root 
	//  if it has a child, otherwise set root as NULL 
	if (root->n == 0)
	{
		BTreeNode<TElement> *tmp = root;
		if (root->leaf)
			root = NULL;
		else
			root = root->C[0];

		delete tmp;
	}
	return;
}

template <typename TElement>
class BTreeBuilder {
	int t;
public:
	BTreeBuilder(int _t) {
		t = _t;
	}
	~BTreeBuilder() { ; }



	BTree<Student> build(ArraySequence<Student> *array, int length, int flag) {

		BTree<Student> myBTree(t, flag);
		Student bufer;
		for (int i = 0; i < length; i++) {
			bufer = *array->Get(i);
			bufer.set_flag(flag);
			myBTree.insert(bufer);
		}
		return myBTree;
	}

	BTree<int> build(ArraySequence<int> *array, int length) {

		BTree<int> myBTree(t, NULL);
		int bufer;
		for (int i = 0; i < length; i++) {
			bufer = array->Get(i);
			myBTree.insert(bufer);
		}
		return myBTree;
	}

	BTree<TElement> build(TElement *array, int length) {

		BTree<TElement> myBTree(t, flag);
		for (int i = 0; i < length; i++) {
			myBTree.insert(array[i]);
		}
		return myBTree;
	}
};
