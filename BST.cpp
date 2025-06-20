#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "BST.hpp"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}


//Assignment question (b)
//deepestNodes function
int BST::getHeight(BTNode* root) {
	int leftHeight, rightHeight;
	if (root == NULL) return 0;
	// Recursively calculate the height of the left and right subtrees.
	leftHeight = getHeight(root->left);
	rightHeight = getHeight(root->right);

	return max(leftHeight, rightHeight) + 1; //height is number of nodes plus 1 for current node
}

bool BST::deepestNodes() {
	if (empty()) return false;
	int max = getHeight(root); // Get the height of the tree.
	cout << "The deepest nodes of tree (Deepest Level: " << max << "): ";
	printDeepestNodes(root, 0, max - 1);
	return true;
}
// Recursive function to print the deepest nodes of the tree.
void BST::printDeepestNodes(BTNode* root, int curLevel, int deepestLevel) {
	if (root == NULL) return;
	if (curLevel == deepestLevel) {//if current level matches deepest level, print ID
		cout << root->item.id << " ";
		return;
	}
	// Recursively explore the left and right subtrees.
	printDeepestNodes(root->left, curLevel + 1, deepestLevel);
	printDeepestNodes(root->right, curLevel + 1, deepestLevel);
}

//Assignment question (c)
//display function
bool BST::display(int order, int source) {
	if (empty()) {
		cout << "\nEmpty tree!\n";
		return false;
	}
	ofstream outfile;
	outfile.open("student-info.txt", ios::trunc);
	if (outfile.fail()) {
		cout << "\nCould not open student-info.txt\n";
		return false;
	}
	// Check the user's choice for order and source and call the appropriate display function.
	if (order == 1 && source == 1) {
		displayAsc(root, cout);
	}
	else if (order == 2 && source == 1) {
		displayDesc(root, cout);
	}
	else if (order == 1 && source == 2) {
		displayAsc(root, outfile);
	}
	else if (order == 2 && source == 2) {
		displayDesc(root, outfile);
	}
	else {
		cout << "\nINVALID OPTION!\n";
		outfile.close();
		return false;
	}
	outfile.close();
	return true;
}
//display ID in ascending order
void BST::displayAsc(BTNode* cur, ostream& output) {
	if (cur == NULL) return;
	displayAsc(cur->left, output);
	cur->item.print(output);
	displayAsc(cur->right, output);
}
//display ID in descending order
void BST::displayDesc(BTNode* cur, ostream& output) {
	if (cur == NULL) return;
	displayDesc(cur->right, output);
	cur->item.print(output);
	displayDesc(cur->left, output);
}

//Assignment question (d)
//CloneSubtree function
bool BST::CloneSubtree(BST t1, type item) 
{
	//Exception: t1 is empty, hence cannot be cloned, terminate function
	if (t1.empty()) {
		return false;
	}
	//Find the pointer of node "item" in tree t1, store it as subtreeRoot
	BTNode* subtreeRoot = findNode(t1.root, item);
	//Exception: cannot find node "item", terminate function
	if (subtreeRoot == NULL)
		return false;
	//Clone subtree into t2 starting from subtreeRoot
	clone(subtreeRoot);
	//Print the contents of the original and cloned subtree in the current BST.
	cout << "\n ***********Tree************ \n";
	t1.preOrderPrint();
	cout << "\n **********Subtree********** \n";
	preOrderPrint(); 
	return true;
}

BTNode* BST::findNode(BTNode* cur, type item) 
{
	//Base case 1: reach end of tree without finding node
	if (cur == NULL)
		//return null
		return cur;
	//Base case 2: node found
	if (cur->item.compare2(item))
		return cur; 
	//Recursive case 1: current node data larger than target node data
	else if (cur->item.compare1(item))
		//traverse left subtree
		return findNode(cur->left, item);
	//Recursive case 2: current node data smaller than target node data
	else
		//traverse right subtree
		return findNode(cur->right, item);
}

void BST::clone(BTNode* cur) 
{
	//Base case 1: after reaching leaf node
	if (cur == NULL)
		return;
	insert(cur->item);
	//Traverse left subtree
	clone(cur->left);
	//Traverse right subtree
	clone(cur->right);
	
}
//The following function is used in app.cpp in order to make sure that t2 is empty before cloning
void BST::clear() {
	clear(root);
	//Only root left in tree after function
	root = NULL;
	//No more nodes in tree
	count = 0;
}

void BST::clear(BTNode* cur) {
	//Base case: after reaching leaf node
	if (cur == NULL) {
		return;
	}
	//Traverse left son
	clear(cur->left);
	//Traverse right son
	clear(cur->right);
	//Delete current node, must delete only after traversing to access next pointer
	delete cur;
}

//Assignment question (e)
//printLevelNodes function
bool BST::printLevelNodes()
{
	//Exception: t2 is empty, terminate function
	if (empty()) {
		return false;
	}
	
	BTNode* cur;
	Queue buffer;
	buffer.enqueue(root);
	int level = 0, count;
	
	do {
		//Number of nodes in current level
		count = buffer.size();
		cout << "Level " << level << " nodes:\t";
		for (int i = 0; i < count; i++) {
			//Obtain each node for current level
			buffer.dequeue(cur);
			cout << cur->item.id << "\t";
			//Store left and right nodes for next level
			if (cur->left != NULL)
				buffer.enqueue(cur->left);
			if (cur->right != NULL)
				buffer.enqueue(cur->right);
		}
		cout << endl;
		//Procede to next level
		level++;
	//Repeat while there are still nodes for next level
	} while (!buffer.empty());
	return true;
}

//Assignment question (f)
//printPath function
bool BST::printPath() {
	string path;

	if (empty()) return false; //empty tree
	cout << "Below are all the external paths for the tree: \n";
	printPathHelper(root, path); // Start the recursive process to print paths from the root
	return true;
}

void BST::printPathHelper(BTNode* node, string path) {

	if (node == NULL) {
		return;
	}

	// Add the current node's id to the path
	path += to_string(node->item.id); //to_string convert an int to a string

	// If it's a leaf node, print the path
	if (node->left == NULL && node->right == NULL) {

		cout << path << endl;
		return;
	}

	// Otherwise, continue recursively for left and right subtrees
	path += " ";
	printPathHelper(node->left, path);
	printPathHelper(node->right, path);
}




