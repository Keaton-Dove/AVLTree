//
//  AVLTree.hpp
//  AVLTreeParentTemplate
//
//  Created by David M Reed on 5/18/21.
//  Keaton Dove 10-28-21
//

#ifndef AVLTree_h
#define AVLTree_h

#include "BinaryTreeNode.hpp"

template <typename T>
class AVLTree {

public:

    /**
     constructor
     */
    AVLTree() {
        _root = nullptr;
        _size = 0;
    }


    /** copy constructor
     @param source AVLTree to copy
     */
    AVLTree(const AVLTree<T>& source) {
        // Creates new tree that is copy of source

        // If source is not empty
        if (source._size > 0) {
            _root = _copyNodes(source._root);
            _size = source._size;
        }
        else {
            _root = nullptr;
            _size = 0;
        }
    }

    /** assignment operator

     @param source object to copy
     @returns *this which is now a copy of src
     */
    AVLTree<T>& operator=(const AVLTree<T>& source) {
        // Overwrites existing tree to be copy of source
        if (source._size > 0) {
            _root = _copyNodes(source._root);
            _size = source._size;
        }
        else {
            _root = nullptr;
            _size = 0;
        }

        // Returning address of AVLTree
        return *this;
    }

    /** insert item into tree
     @param item value to insert
     @pre item is not already in the tree
     @post item is inserted into tree and tree is balanced according to AVL rules
     */
    void insert(const T& item) {

        // Initializing the root node that will be passed to insertHelp
        std::shared_ptr<BinaryTreeNode<T>> rootNode = nullptr;
        std::shared_ptr<BinaryTreeNode<T>> currentNode = _root;

        // If size is 1, rootNode has to be root
        if (_size == 1) {
            if (currentNode->_item == item) {
                return;
            }
            rootNode = _root;
        }

        // If size is greater than 1, searching for root
        else if (_size > 1) {

            // Search for position to insert node / look for existing node with item
            for (int i = 0; i <= _root->height(); i++) {

                // If greater than item, check left
                if (currentNode->_item > item) {

                    if (currentNode->_left) {
                        currentNode = currentNode->_left;
                    }
                    // Item will be inserted here
                    else {
                        rootNode = currentNode;
                        break;
                    }
                }

                // If less than item, check right
                else if (currentNode->_item < item) {

                    if (currentNode->_right) {
                        currentNode = currentNode->_right;
                    }
                    // Item will be inserted here
                    else {
                        rootNode = currentNode;
                        break;
                    }
                }

                // If currentNode has the requested item, end the function - do not insert
                if (currentNode->_item == item) {
                    return;
                }
            }
        }

        insertHelp(rootNode, item);
    }

    /**
     search for item in tree

     @param item item value to search for
     @return BinaryTree containing item or nullptr if item not found
     */
    std::shared_ptr<BinaryTreeNode<T>> find(const T& item) const {

        // Only search if list is not empty
        if (_size > 0) {
            return findHelp(_root, item);
        }

        // Return nullptr if list is empty
        return nullptr;
    }

    /**
     returns the node containing the minimum value in the tree

     @return the node containing the minimum value in the tree
     */
    std::shared_ptr<BinaryTreeNode<T>> minimumNode() const {

        // If tree empty, no min node. Otherwise call minimumNodeHelp
        if (_size == 0) { return nullptr; }
        return minimumNodeHelp(_root);
    }

    /**
     returns the node containing the maximum value in the tree

     @return the node containing the maximum value in the tree
     */
    std::shared_ptr<BinaryTreeNode<T>> maximumNode() const {

        // If tree empty, no max node. Otherwise call maximumNodeHelp
        if (_size == 0) { return nullptr; }
        return maximumNodeHelp(_root);
    }

    /**
     returns the BinaryTreeNode containing the element in the tree that is the next smallest element compared to the element at the node passed as the parameter

     @param node BinaryTreeNode whose element we want to find the next smallest element
     @return the BinaryTreeNode containing the element in the tree that is the next smallest element compared to the element at the node passed as the parameter
     */
    std::shared_ptr<BinaryTreeNode<T>> nextSmallestNode(std::shared_ptr<BinaryTreeNode<T>> node) const {

        // Can only be a second smallest if there are at least 2 nodes
        if (_size < 2) {
            return nullptr;
        }

        // First getting smallest
        auto smallestNode = minimumNode();

        // Initializing pointer for nextSmallest
        std::shared_ptr<BinaryTreeNode<T>> nextSmallest = nullptr;

        // If smallest has parent, it will start as the nextSmallest
        if (smallestNode->_parent.lock()) {
            nextSmallest = smallestNode->_parent.lock();
        }

        // Then finding the smallest of the tree with root being the smallest's right child
        if (smallestNode->_right) {

            // Getting smallest of nodes right of smallest
            auto smallestOfSmallestRightChild = minimumNodeHelp(smallestNode->_right);

            // If there wasn't a parent to the smallest node or the smallestOfSmallestRightChild is less than the parent...
            if (nextSmallest == nullptr || smallestOfSmallestRightChild->_item < nextSmallest->_item) {
                // Set next smallest to new nextSmallest
                nextSmallest = smallestOfSmallestRightChild;
            }
        }

        return nextSmallest;
    }

    /**
     returns the BinaryTreeNode containing the element in the tree that is the next largest element compared to the element at the node passed as the parameter

     @param node BinaryTreeNode whose element we want to find the next largest element
     @return the BinaryTreeNode containing the element in the tree that is the next largest element compared to the element at the node passed as the parameter
     */
    std::shared_ptr<BinaryTreeNode<T>> nextLargestNode(std::shared_ptr<BinaryTreeNode<T>> node) const {

        // Same code as nextSmallestNode for inverse result
        if (_size < 2) {
            return nullptr;
        }

        auto largestNode = maximumNode();

        // Initializing pointer for nextLargest
        std::shared_ptr<BinaryTreeNode<T>> nextLargest = nullptr;

        if (largestNode->_parent.lock()) {
            nextLargest = largestNode->_parent.lock();
        }

        // Then finding the largest of the tree with root being the largest's left child
        if (largestNode->_left) {

            auto largestOfLargestLeftChild = maximumNodeHelp(largestNode->_left);

            if (nextLargest == nullptr || largestOfLargestLeftChild->_item < nextLargest->_item) {
                nextLargest = largestOfLargestLeftChild;
            }
        }

        return nextLargest;
    }

    /**
     print items (one item per line) tree using inorder traversal

     @pre items in tree must support operator<<
     @post items are output to stdout one per line in inorder order
     */
    void printInorder() const {
        printInorderHelp(_root);
    }

    /**
     print items (one item per line) tree using preorder traversal

     @pre items in tree must support operator<<
     @post items are output to stdout one per line in preorder order
     */
    void printPreorder() const {
        printPreorderHelp(_root);
    }

    /**
     print items (one item per line) tree using postorder traversal

     @pre items in tree must support operator<<
     @post items are output to stdout one per line in postorder order
     */
    void printPostorder() const {
        printPostorderHelp(_root);
    }

    /**
     returns number of items in tree

     @returns number of items in tree
     */
    int size() const { return _size; }

private:
    /**
     recursively makes a copy of the subtree rooted at node

     @param rootNode root of the subtree to copy
     @post a copy (new nodes) of the entire subtree rooted at node is created
     @returns the root BinaryTreeNode of a copy of the subtree rooted at node
     */
    std::shared_ptr<BinaryTreeNode<T>> _copyNodes(const std::shared_ptr<BinaryTreeNode<T>>& rootNode) const {

        // Preorder code traversal for inserting all nodes

        // Creating node first
        std::shared_ptr<BinaryTreeNode<T>> node = std::make_shared<BinaryTreeNode<T>>(rootNode->_item, nullptr, nullptr, nullptr, rootNode->height());

        // If there is a left node, traverse left
        if (rootNode->_left) {
            std::shared_ptr<BinaryTreeNode<T>> newNode = _copyNodes(rootNode->_left);
            node->_left = newNode;
            newNode->_parent = node;
        }

        // If there is right node, traverse right
        if (rootNode->_right) {
            std::shared_ptr<BinaryTreeNode<T>> newNode = _copyNodes(rootNode->_right);
            node->_right = newNode;
            newNode->_parent = node;
        }

        return node;
    }

    /**
     search for item in subtree rooted at node

     @param node BinaryTreeNode root of subtree to search in
     @param item value to search for
     @returns BinaryTreeNode containing item or nullptr if not item not found
     */
    std::shared_ptr<BinaryTreeNode<T>> findHelp(const std::shared_ptr<BinaryTreeNode<T>> node, const T& item) const {

        // currentNode starts at node
        std::shared_ptr<BinaryTreeNode<T>> currentNode = node;

        // Looping for the height of the tree
        for (int i = 0; i <= _root->height(); i++) {

            // Checking node
            if (currentNode->_item == item) {
                // Node found, returning node
                return currentNode;
            }

            // Shifting accordingly unless at bottom of tree
            if (i < _root->height()) {

                if (currentNode->_item > item) {
                    if (currentNode->_left == nullptr) { break; }
                    currentNode = currentNode->_left;
                }

                else {
                    if (currentNode->_right == nullptr) { break; }
                    currentNode = currentNode->_right;
                }
            }
        }

        // Item not found
        return nullptr;
    }

    /**
     helper method for minimumNode

     @param node the root of the tree to find the smallest element in this subtree
     @return the node containing the smallest element in the tree rooted at node
     */
    std::shared_ptr<BinaryTreeNode<T>> minimumNodeHelp(const std::shared_ptr<BinaryTreeNode<T>> node) const {

        // Follow left path to bottom left of tree for smallest item
        auto smallestNode = node;

        while (smallestNode->_left != nullptr) {
            smallestNode = smallestNode->_left;
        }

        return smallestNode;
    }

    /**
     helper method for maximumNode

     @param node the root of the tree to find the largest element in this subtree
     @return the node containing the largest element in the tree rooted at node
     */
    std::shared_ptr<BinaryTreeNode<T>> maximumNodeHelp(const std::shared_ptr<BinaryTreeNode<T>> node) const {

        // Follow right path to bottom right of tree for biggest item
        auto largestNode = node;

        while (largestNode->_right != nullptr) {
            largestNode = largestNode->_right;
        }

        return largestNode;
    }

    /**
     deallocates entire tree

     @post entire tree is deallocated and _root is set to nullptr
     */
    void clear() {
        // Setting root to null and size to 0, the rest will be automatically deallocated
        _root = nullptr;
        _size = 0;
    }

    /**
     insert item into subtree with root node

     @param node BinaryTreeNode root of tree to insert into
     @param item value to insert
     @pre item is not already in the tree
     @post item is inserted into tree and tree is balanced according to AVL rules
     */
    void insertHelp(std::shared_ptr<BinaryTreeNode<T>>& node, const T& item) {

        // Edge case for first node
        if (node == nullptr) {
            _root = std::make_shared<BinaryTreeNode<T>>(item);
        }

        // Every other node
        else {

            // If item is less than node, creating new node as left child
            if (item < node->_item) {
                node->_left = std::make_shared<BinaryTreeNode<T>>(item, node);
            }
            // Otherwise item is greater than node and is the right child
            else {
                node->_right = std::make_shared<BinaryTreeNode<T>>(item, node);
            }

            // Updating current node height first if applicable
            if (node->height() == 0) {
                node->setHeight(1);
            }

            // Updating sizes
            while (node->_parent.lock()) {

                std::shared_ptr<BinaryTreeNode<T>> childNode = node;
                node = node->_parent.lock();

                // Checking if parent's height needs updated
                if (childNode->height() == node->height()) {

                    // Updating parent node's height
                    node->setHeight(node->height() + 1);

                    // Checking for imbalance - only if the node has a height of at least 2 in the first place
                    if (node->height() >= 2) {

                        // Left imbalance
                        if ((node->_left) && ((node->_left->height() == 1 && node->_right == nullptr) || (node->_left->height() == node->_right->height() + 2))) {

                            // Left-left insert
                            if ((childNode->_left) && (childNode->_right == nullptr || childNode->_right->height() < childNode->_left->height())) {
                                leftSingleRotate(node);
                            }
                            // Left-right insert
                            else {
                                leftRightRotate(node);
                            }
                        }

                        // Right imbalance
                        else if ((node->_right) && ((node->_right->height() == 1 && node->_left == nullptr) || (node->_right->height() == node->_left->height() + 2))) {

                            // Right-left insert
                            if ((childNode->_left) && (childNode->_right == nullptr || childNode->_right->height() < childNode->_left->height())) {
                                rightLeftRotate(node);
                            }
                            // Right-right insert
                            else {
                                rightSingleRotate(node);
                            }
                        }
                    }
                }
            }
        }

        // Increment size
        _size++;
    }

    /**
     print items (one item per line) in subtree rooted at node using inorder traversal;

     @pre items in tree must support operator<<
     @post items in subtree are output to stdout one per line in postorder order
     */
    void printInorderHelp(const std::shared_ptr<BinaryTreeNode<T>> node) const {

        // If there is a left node, traverse left
        if (node->_left) {
            printInorderHelp(node->_left);
        }

        // No more left nodes, print out item
        cout << node->_item << endl;

        // If there is right node, traverse right
        if (node->_right) {
            printInorderHelp(node->_right);
        }
    }

    /**
     print items (one item per line) in subtree rooted at node using preorder traversal;

     @pre items in tree must support operator<<
     @post items in subtree are output to stdout one per line in postorder order
     */
    void printPreorderHelp(const std::shared_ptr<BinaryTreeNode<T>> node) const {

        // Print node first
        cout << node->_item << endl;

        // If there is a left node, traverse left
        if (node->_left) {
            printPreorderHelp(node->_left);
        }

        // If there is right node, traverse right
        if (node->_right) {
            printPreorderHelp(node->_right);
        }

    }

    /**
     print items (one item per line) in subtree rooted at node using postorder traversal;

     @pre items in tree must support operator<<
     @post items in subtree are output to stdout one per line in postorder order
     */
    void printPostorderHelp(const std::shared_ptr<BinaryTreeNode<T>> node) const {

        // If there is a left node, traverse left
        if (node->_left) {
            printPostorderHelp(node->_left);
        }

        // If there is right node, traverse right
        if (node->_right) {
            printPostorderHelp(node->_right);
        }

        // Print node last
        cout << node->_item << endl;

    }

    /**
     rebalances tree when node's left subtree has height two more than its right subtree and insertion was made into left subtree of left child of node by performing a clockwise rotation

     @param node root of subtree that needs rebalanced and only one insertion has been performed since tree was balanced
     @pre node is deepest node whose left subtree has height two more than its right subtree and only one insertion has been performed since tree was balanced
     @post tree is rebalanced
     */
    void leftSingleRotate(std::shared_ptr<BinaryTreeNode<T>>& node) {

        // nullptr or pointer to parent of node
        std::shared_ptr<BinaryTreeNode<T>> parentNode = node->_parent.lock();
        // Getting left child of node which will become the new root of the subtree
        std::shared_ptr <BinaryTreeNode<T>> newRoot = node->_left;

        // Overwriting the parent of newRoot to be parent of node (could be nullptr if node is _root)
        newRoot->_parent = parentNode;
        // And node's parent will now be newRoot
        node->_parent = newRoot;

        // If the newRoot already has a right subtree/node, it needs to be moved
        if (newRoot->_right) {
            if (newRoot->_right->_item > newRoot->_item) {
                newRoot->_right->_parent = node;
                node->_left = newRoot->_right;
            }
            // Right child of newRoot may be less than newRoot in one case via RL rotate
            else {
                newRoot->_right->_parent = newRoot->_left;
                newRoot->_left->_right = newRoot->_right;
                node->_left = nullptr;
            }
        }
        else {
            node->_left = nullptr;
        }

        // If the node was the root, the newRoot will now be the root
        if (parentNode == nullptr) {
            _root = newRoot;
        }
        // Otherwise, overwriting the parent root's respective link
        else {
            if (newRoot->_item > parentNode->_item) {
                parentNode->_right = newRoot;
            }
            else {
                parentNode->_left = newRoot;
            }

        }

        // Updating final link and decreasing node's height
        newRoot->_right = node;
        node->setHeight(node->height() - 2);
    }

    /**
     rebalances tree when node's right subtree has height two more than its left subtree and insertion was made into right subtree of right child of node by performing a counter-clockwise rotation

     @param node root of subtree that needs rebalanced
     @pre node is deepest node whose right subtree has height two more than its left subtree and only one insertion has been performed since tree was balanced
     @post tree is rebalanced
     */
    void rightSingleRotate(std::shared_ptr<BinaryTreeNode<T>>& node) {

        // nullptr or pointer to parent of node
        std::shared_ptr<BinaryTreeNode<T>> parentNode = node->_parent.lock();
        // Getting left child of node which will become the new root of the subtree
        std::shared_ptr<BinaryTreeNode<T>> newRoot = node->_right;

        // Overwriting the parent of newRoot to be parent of node (could be nullptr if node is _root)
        newRoot->_parent = parentNode;
        // And node's parent will now be newRoot
        node->_parent = newRoot;

        // If the newRoot already has a left subtree/node, it needs to be moved
        if (newRoot->_left) {
            if (newRoot->_left->_item < newRoot->_item) {
                newRoot->_left->_parent = node;
                node->_right = newRoot->_left;
            }
            // Left child of newRoot may be greater than newRoot in one case via LR rotate
            else {
                newRoot->_left->_parent = newRoot->_right;
                newRoot->_right->_left = newRoot->_left;
                node->_right = nullptr;
            }
        }
        else {
            node->_right = nullptr;
        }

        // If the node was the root, the newRoot will now be the root
        if (parentNode == nullptr) {
            _root = newRoot;
        }
        // Otherwise, overwriting the parent root's respective link
        else {
            if (newRoot->_item > parentNode->_item) {
                parentNode->_right = newRoot;
            }
            else {
                parentNode->_left = newRoot;
            }

        }

        // Updating final link and decreasing node's height
        newRoot->_left = node;
        node->setHeight(node->height() - 2);
    }

    /**
     rebalances tree when node's left subtree has height two more than its right subtree and insertion was made into right subtree of left child of node by performing two rotations

     @param node root of subtree that needs rebalanced
     @pre node is deepest node whose left subtree has height two more than its right subtree
     @post tree is rebalanced
     */
    void rightLeftRotate(std::shared_ptr<BinaryTreeNode<T>>& node) {

        // No edge cases, the left rotate method will handle if node is _root
        std::shared_ptr<BinaryTreeNode<T>> rNode = node->_right;
        std::shared_ptr<BinaryTreeNode<T>> rlNode = rNode->_left;

        // Updating lNode links and decreasing size by 1
        rNode->_parent = rlNode;
        rNode->_left = nullptr;
        rNode->setHeight(rNode->height() - 1);

        // Updating lrNode links and increasing size by 1
        rlNode->_parent = node;
        // Setting rlNode's right subtree to it's left child before overwriting
        if (rlNode->_right) {
            rlNode->_left = rlNode->_right;
        }
        rlNode->_right = rNode;
        rlNode->setHeight(rlNode->height() + 1);

        // Updating root node's left link
        node->_right = rlNode;

        rightSingleRotate(node);
    }

    /**
     rebalances tree when node's right subtree has height two more than its left subtree and insertion was made into left subtree of right child of node by performing two rotations

     @param node root of subtree that needs rebalanced
     @pre node is deepest node whose right subtree has height two more than its left subtree and only one insertion has been performed since tree was balanced
     @post tree is rebalanced
     */
    void leftRightRotate(std::shared_ptr<BinaryTreeNode<T>>& node) {

        // No edge cases, the right rotate method will handle if node is _root
        std::shared_ptr<BinaryTreeNode<T>> lNode = node->_left;
        std::shared_ptr<BinaryTreeNode<T>> lrNode = lNode->_right;

        // Updating lNode links and decreasing size by 1
        lNode->_parent = lrNode;
        lNode->_right = nullptr;
        lNode->setHeight(lNode->height() - 1);

        // Updating lrNode links and increasing size by 1
        lrNode->_parent = node;
        // Setting lrNode's left subtree to it's right child before overwriting
        if (lrNode->_left) {
            lrNode->_right = lrNode->_left;
        }
        lrNode->_left = lNode;
        lrNode->setHeight(lrNode->height() + 1);

        // Updating root node's left link
        node->_left = lrNode;

        leftSingleRotate(node);
    }

    // pointer to root node of tree
    std::shared_ptr<BinaryTreeNode<T>> _root;
    // number of items in the tree
    int _size;
};

//--------------------------------------------------------------------

// maximum function for use with tree heights
inline int max(int a, int b) {
    return a > b ? a : b;
}

//--------------------------------------------------------------------

//--------------------------------------------------------------------

#endif /* AVLTree_h */