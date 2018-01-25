/*
 * BinarySearchTree.cpp
 */

#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>

#include "BinarySearchTree.h"

using namespace std;


BinarySearchTree::BinarySearchTree()
{
        root = NULL;
}

BinarySearchTree::~BinarySearchTree()
{
        //walk tree in post-order traversal and delete
        post_order_delete(root);
}

void BinarySearchTree::post_order_delete(Node *node)
{
        if (node == NULL)
                return;

        post_order_delete(node->left);
        post_order_delete(node->right);
        delete node;
}

//copy constructor
BinarySearchTree::BinarySearchTree(const BinarySearchTree &source)
{
        //use pre-order traversal to copy the tree
        root = pre_order_copy(source.root);
}

//assignment overload
BinarySearchTree &BinarySearchTree::operator= (const BinarySearchTree &source)
{
        //check for self-assignment
        if (this != &source) {
                //delete current tree if it exists
                if (root != NULL)
                        post_order_delete(root);
                //use pre-order traversal to copy the tree
                root = pre_order_copy(source.root);
        }
        //return pointer to self
        return *this;
}

Node *BinarySearchTree::pre_order_copy(Node *node) const
{
        // base case reaches child of leaf
        if (node == NULL) return NULL;

        //create copy of node
        Node *newNode = new Node;
        newNode->data = node->data;
        newNode->count = node->count;
        newNode->left = pre_order_copy(node->left);
        newNode->right = pre_order_copy(node->right);
        
        return newNode; 
}

int BinarySearchTree::find_min() const
{
        if (root == NULL)
                return INT_MIN;
        return find_min(root)->data;
}

Node *BinarySearchTree::find_min(Node *node) const
{
        if (node->left == NULL)
                return node;
        return find_min(node->left);
}

int BinarySearchTree::find_max() const
{
        if (root == NULL)
                return INT_MAX;
        return find_max(root)->data;
}

Node *BinarySearchTree::find_max(Node *node) const
{
        if (node->right == NULL)
                return node;
        return find_max(node->right);
}

bool BinarySearchTree::contains(int value) const
{
        if (root == NULL)
                return false;
        return contains(root, value);

}

bool BinarySearchTree::contains(Node *node, int value) const
{
        //base case, reaches child of leaf
        if (node == NULL) return false;

        //value found
        if (node->data == value)
                return true;

        //traverse left
        if (node->data > value)
                return contains(node->left, value);

        //traverse right
        if (node->data < value)
                return contains(node->right, value);

        return false;
}

void BinarySearchTree::insert(int value)
{
        insert(root, NULL, value);
}

void BinarySearchTree::insert(Node *node, Node *parent, int value)
{
        if (node == NULL) {
                //create a new node with value
                Node *newNode = new Node;
                newNode->data = value;
                newNode->count = 1;
                newNode->left = NULL;
                newNode->right = NULL;
                //if tree empty, create root
                if (parent == NULL)
                        root = newNode;
                //place on correct side of parent
                else if (parent->data > value)
                        parent->left = newNode;
                else
                        parent->right = newNode;
        }
        //if node already exists increment count
        else if (node->data == value) 
                node->count++;
        
        else if (node->data > value)
                insert(node->left, node, value);
        
        else if (node->data < value)    
                insert(node->right, node, value);
}

bool BinarySearchTree::remove(int value)
{
        return remove(root, NULL, value);
}

bool BinarySearchTree::remove(Node *node, Node *parent, int value)
{
        if (node == NULL) return false;

        if (node->data == value) {
                //only remove node if count is 1
                if (node->count > 1) {
                        node->count--;
                        return false;
                }
                //node has two children, use full removal
                else if (node->right != NULL && node->left != NULL) {
                        //make node a copy of the leftmost node of it's right child
                        Node *temp = find_min(node->right);
                        node->count = temp->count;
                        node->data = temp->data;
                        //reset count of copied node, so it is removed
                        temp->count = 1;
                        return remove(node->right, node, temp->data);
                }
                //point parent at correct node child, delete node
                else return non_and_single_leaf_removal(node, parent, value);
        }
        else { 
                if (node->data > value)
                        return remove(node->left, node, value);
                if (node->data < value)
                        return remove(node->right, node, value);
        }
        return false;
}

bool BinarySearchTree::non_and_single_leaf_removal(Node *node, Node *parent, int value)
{
        if (parent == NULL) {                           //node is root
                if (node->right == NULL)
                        root = node->left;              //left tree or null
                else                                    
                        root = node->right;             //right tree
        }
        else if (node->right == NULL) {                 //node->left
                if (parent->data > value)               //parent->left
                        parent->left = node->left;
                else                                    //parent->right
                        parent->right = node->left; 
        }
        else {                                          //node->right
                if (parent->data > value)               //parent->left
                        parent->left = node->right;
                else                                    //parent->right
                        parent->right = node->right; 
        }
        delete node;
        return true;
}

int BinarySearchTree::tree_height() const
{
        return tree_height(root);
}

int BinarySearchTree::tree_height(Node *node) const
{
        if (node == NULL) return -1;      //counts pointers not nodes
        
        //return largest subtree height
        return max_height(tree_height(node->left), tree_height(node->right)) + 1;
}

int BinarySearchTree::max_height(int left, int right) const
{
        if (left > right) return left;
        else return right;
}

//returns the total number of nodes
int BinarySearchTree::node_count() const
{
        return node_count(root);
}

int BinarySearchTree::node_count(Node *node) const
{
        if (node == NULL) return 0;

        //return total number of nodes
        return (node_count(node->left) + node_count(node->right) + 1);
}

//return the sum of all the node values (including duplicates)
int BinarySearchTree::count_total() const
{
        return count_total(root);
}

int BinarySearchTree::count_total(Node *node) const
{
        if (node == NULL) return 0;

        //return sum of all nodes
        return (count_total(node->left) + count_total(node->right) + (node->data * node->count));
}

// use the printPretty helper to make the tree look nice
void BinarySearchTree::print_tree() const
{
        printPretty(root, 1, 0, std::cout);
}

/*Node *BinarySearchTree::find_parent(Node *node, Node *child) const
{
        if (node == NULL) return NULL;

        // if either the left or right is equal to the child,
        // we have found the parent
        if (node->left==child or node->right == child) {
                return node;
        }

        // Use the binary search tree invariant to walk the tree
        if (child->data > node->data) {
                return find_parent(node->right, child);
        } else {
                return find_parent(node->left, child);
        }
}*/
