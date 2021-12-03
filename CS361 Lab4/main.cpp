// Keaton Dove
// CS-361
// 10-28-2021

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

#define private public

#include "AVLTree.hpp"

#define DAssert(condition, msg) do { if (!(condition)) { cerr << "assert failed: " << __FUNCTION__ << " : line " << __LINE__ << " " << msg << endl; }} while(0)

void checkTree(AVLTree<int>& items, const vector<int>& array) {
	DAssert(items._root->_parent.lock() == nullptr, "Root's parent is not nullptr");

	for (auto x : array) {

		auto node = items.find(x);
		DAssert(node != nullptr, "Specified item not found in tree");

		if (node->height() > 1) {
			DAssert(node->_left != nullptr || node->_right != nullptr, "Height >0 but node has no children");
		}
	}
}

void checkTreeEmpty(AVLTree<int>& items) {
	DAssert(items._root == nullptr, "Root is not nullptr");
	DAssert(items._size == 0, "Size is not zero");
}

void insertItems(AVLTree<int>& items, const vector<int>& array) {
	for (auto x : array) {
		items.insert(x);
	}
}


/* -========================================= TESTS =========================================- */

void testFind() {
	cerr << "testFind" << endl;

	AVLTree<int> items;

	vector<int> i = { 5, 1, 6, 8, 2 };
	insertItems(items, i);

	checkTree(items, i);
}

void testFindNotInList() {
	cerr << "testFindNotInList" << endl;

	AVLTree<int> items;

	vector<int> i = { 5, 1, 6, 8, 2 };
	insertItems(items, i);

	DAssert(items.find(10) == nullptr, "Find did not return nullptr for item not in tree");
}

void testInsertEmpty() {
	cerr << "testInsertEmpty" << endl;

	AVLTree<int> items;
	items.insert(10);

	checkTree(items, { 10 });
}

void testInsertDuplicate() {
	cerr << "testInsertDuplicate" << endl;

	AVLTree<int> items;
	items.insert(10);
	items.insert(10);

	checkTree(items, { 10 });
}

void testLsRotateAtRoot() {
	cerr << "testLsRotateAtRoot" << endl;

	AVLTree<int> items;

	vector<int> i = { 10, 8, 7 };
	insertItems(items, i);

	checkTree(items, i);
}

void testLsRotateBelowRoot() {
	cerr << "testLsRotateBelowRoot" << endl;

	AVLTree<int> items;

	vector<int> i = { 10, 7, 12, 5, 3 };
	insertItems(items, i);

	checkTree(items, i);
}

void testLsRotateWithNodeLRofRoot() {
	cerr << "testLsRotateWithNodeLRofRoot" << endl;

	AVLTree<int> items;

	vector<int> i = { 12, 10, 15, 11, 8, 7 };
	insertItems(items, i);

	checkTree(items, i);
}

void testRsRotateAtRoot() {
	cerr << "testRsRotateAtRoot" << endl;

	AVLTree<int> items;

	vector<int> i = { 7, 8, 10 };
	insertItems(items, i);

	checkTree(items, i);
}

void testRsRotateBelowRoot() {
	cerr << "testRsRotateBelowRoot" << endl;

	AVLTree<int> items;

	vector<int> i = { 5, 3, 7, 10, 12 };
	insertItems(items, i);

	checkTree(items, i);
}

void testRsRotateWithNodeRLofRoot() {
	cerr << "testRsRotateWithNodeRLofRoot" << endl;

	AVLTree<int> items;

	vector<int> i = { 8, 7, 11, 10, 12, 15 };
	insertItems(items, i);

	checkTree(items, i);
}

void testRlRotateAtRoot() {
	cerr << "testRlRotateAtRoot" << endl;

	AVLTree<int> items;

	vector<int> i = { 7, 10, 8 };
	insertItems(items, i);

	checkTree(items, i);
}

void testRlRotateBelowRoot() {
	cerr << "testRlRotateBelowRoot" << endl;

	AVLTree<int> items;

	vector<int> i = { 7, 3, 10, 11, 12 };
	insertItems(items, i);

	checkTree(items, i);
}

void testLrRotateAtRoot() {
	cerr << "testLrRotateAtRoot" << endl;

	AVLTree<int> items;

	vector<int> i = { 10, 7, 8 };
	insertItems(items, i);

	checkTree(items, i);
}

void testLrRotateBelowRoot() {
	cerr << "testLrRotateBelowRoot" << endl;

	AVLTree<int> items;

	vector<int> i = { 11, 10, 12, 3, 7 };
	insertItems(items, i);

	checkTree(items, i);
}

void testMinNode() {
	cerr << "testMinNode" << endl;

	AVLTree<int> items;

	vector<int> i = { 19, 3, 7, 35, 34, 18, 23, 5 };
	insertItems(items, i);

	DAssert(items.minimumNode()->_item == 3, "Minimum node is incorrect");
}

void testMaxNode() {
	cerr << "testMaxNode" << endl;

	AVLTree<int> items;

	vector<int> i = { 19, 3, 7, 35, 34, 18, 23, 5 };
	insertItems(items, i);

	DAssert(items.maximumNode()->_item == 35, "Maximum node is incorrect");
}

void testNextSmallestNode() {
	cerr << "testNextSmallestNode" << endl;

	AVLTree<int> items;

	vector<int> i = { 19, 3, 7, 35, 34, 18, 23, 5 };
	insertItems(items, i);

	DAssert(items.nextSmallestNode(items._root)->_item == 5, "Next smallest node is incorrect, test 1");

	AVLTree<int> items2;

	vector<int> i2 = { 8, 13, 47, 27, 25, 24, 43, 9, 29 };
	insertItems(items2, i2);

	DAssert(items2.nextSmallestNode(items2._root)->_item == 9, "Next smallest node is incorrect, test 2");
}

void testNextLargestNode() {
	cerr << "testNextLargestNode" << endl;

	AVLTree<int> items;

	vector<int> i = { 19, 3, 7, 35, 34, 18, 23, 5 };
	insertItems(items, i);

	DAssert(items.nextLargestNode(items._root)->_item == 34, "Next largest node is incorrect, test 1");

	AVLTree<int> items2;

	vector<int> i2 = { 8, 13, 47, 27, 25, 24, 43, 9, 29 };
	insertItems(items2, i2);

	DAssert(items2.nextLargestNode(items2._root)->_item == 43, "Next largest node is incorrect, test 2");
}

void testCopyConstructor() {
	cerr << "testCopyConstructor" << endl;

	AVLTree<int> items;

	vector<int> i = { 1, 36, 4, 43, 17, 21, 50, 42 };
	insertItems(items, i);

	AVLTree<int> itemsCopy = AVLTree<int>(items);
	checkTree(itemsCopy, i);
}

void testEqualsOperator() {
	cerr << "testEqualsOperator" << endl;

	AVLTree<int> items;

	vector<int> i = { 1, 36, 4, 43, 17, 21, 50, 42 };
	insertItems(items, i);

	AVLTree<int> itemsCopy = items;
	checkTree(itemsCopy, i);
}

void testCopyConstructorEmpty() {
	cerr << "testCopyConstructorEmpty" << endl;

	AVLTree<int> items;

	AVLTree<int> itemsCopy = AVLTree<int>(items);

	checkTreeEmpty(itemsCopy);
}

void testEqualsOperatorEmpty() {
	cerr << "testEqualsOperatorEmpty" << endl;

	AVLTree<int> items;

	vector<int> i = { 1, 36, 4, 43, 17, 21, 50, 42 };
	AVLTree<int> itemsCopy;
	insertItems(itemsCopy, i);

	itemsCopy = AVLTree<int>(items);
	checkTreeEmpty(itemsCopy);
}

void testPrintInorder() {
	cerr << "testPrintInorder" << endl;

	AVLTree<int> items;

	vector<int> i = { 42, 10, 26, 23, 16, 10, 27, 6 };
	insertItems(items, i);

	items.printInorder();
}

void testPrintPreorder() {
	cerr << "testPrintPreorder" << endl;

	AVLTree<int> items;

	vector<int> i = { 42, 10, 26, 23, 16, 10, 27, 6 };
	insertItems(items, i);

	items.printPreorder();
}

void testPrintPostorder() {
	cerr << "testPrintPostorder" << endl;

	AVLTree<int> items;

	vector<int> i = { 42, 10, 26, 23, 16, 10, 27, 6 };
	insertItems(items, i);

	items.printPostorder();
}


int main(int argc, const char* argv[]) {

	testFind();
	testFindNotInList();
	testInsertEmpty();
	testInsertDuplicate();
	testLsRotateAtRoot();
	testLsRotateBelowRoot();
	testLsRotateWithNodeLRofRoot();
	testRsRotateAtRoot();
	testRsRotateBelowRoot();
	testRsRotateWithNodeRLofRoot();
	testRlRotateAtRoot();
	testLrRotateAtRoot();
	testRlRotateBelowRoot();
	testLrRotateBelowRoot();
	testMinNode();
	testMaxNode();
	testNextSmallestNode();
	testNextLargestNode();
	testCopyConstructor();
	testEqualsOperator();
	testCopyConstructorEmpty();
	testEqualsOperatorEmpty();
	testPrintInorder();
	testPrintPreorder();
	testPrintPostorder();

	return 0;
}