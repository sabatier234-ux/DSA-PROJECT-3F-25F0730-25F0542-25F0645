#include "BSTflight.h"

BSTflight::BSTflight() {
	root = nullptr; 
}
BSTflight::~BSTflight() { 
	destroyTree();
}
// Recursively inserts a flight into the BST, ordered by callsign.
// Returns the (possibly new) root of the subtree it was called on.
BSTNode* BSTflight::insertHelper(BSTNode* node, Flight* flight) {
    if (node == nullptr) {
        BSTNode* n = new BSTNode();
        n->flight = flight;
        n->left = nullptr;
        n->right = nullptr;
        return n;
    }
    if (flight->callsign < node->flight->callsign) 
		node->left = insertHelper(node->left, flight);
    else if (flight->callsign > node->flight->callsign)
		node->right = insertHelper(node->right, flight);
    return node;
}
// Recursively searches for a callsign
Flight* BSTflight::searchHelper(BSTNode* node, const string& callsign) {
    if (node == nullptr) 
		return nullptr;
    if (callsign == node->flight->callsign)
		return node->flight;
    if (callsign < node->flight->callsign)
		return searchHelper(node->left, callsign);
    return searchHelper(node->right, callsign);
}

BSTNode* BSTflight::findMin(BSTNode* node) {
    while (node->left != nullptr) node = node->left;
    return node;
}
// Returns the new root of the subtree after removal.
BSTNode* BSTflight::removeHelper(BSTNode* node, const string& callsign) {
    if (node == nullptr)
		return nullptr;
    if (callsign < node->flight->callsign) {
        node->left = removeHelper(node->left, callsign);
    } else if (callsign > node->flight->callsign) {
        node->right = removeHelper(node->right, callsign);
    } else {
        if (node->left == nullptr) {
            BSTNode* right = node->right;
            delete node;
            return right;
        }
        if (node->right == nullptr) {
            BSTNode* left = node->left;
            delete node;
            return left;
        }
        BSTNode* smallest = findMin(node->right);
        node->flight = smallest->flight;
        node->right = removeHelper(node->right, smallest->flight->callsign);
    }
    return node;
}

void BSTflight::inorderHelper(BSTNode* node) {
    if (node == nullptr) return;
    inorderHelper(node->left);
    cout << "  " << node->flight->callsign << " - " << node->flight->aircraftType << "\n";
    inorderHelper(node->right);
}

int BSTflight::heightHelper(BSTNode* node) {
    if (node == nullptr) return 0;
    int l = heightHelper(node->left);
    int r = heightHelper(node->right);
    return 1 + (l > r ? l : r);
}

void BSTflight::destroyHelper(BSTNode* node) {
    if (node == nullptr) return;
    destroyHelper(node->left);
    destroyHelper(node->right);
    delete node;
}

void BSTflight::insert(Flight* flight) { 
	root = insertHelper(root, flight);
}

Flight* BSTflight::search(const string& callsign) { 
	return searchHelper(root, callsign);
}

void BSTflight::remove(const string& callsign) { 
	root = removeHelper(root, callsign);
}

void BSTflight::inorderTraversal() {
	inorderHelper(root);
}

int BSTflight::height() {
	return heightHelper(root);
}

void BSTflight::destroyTree() { 
	destroyHelper(root);
	root = nullptr; 
}
