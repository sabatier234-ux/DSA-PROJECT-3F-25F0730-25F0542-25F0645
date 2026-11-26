#include "AVLflight.h"

AVLflight::AVLflight() { root = nullptr; }
AVLflight::~AVLflight() { destroyTree(); }

int AVLflight::nodeHeight(AVLNode* node) { return node == nullptr ? 0 : node->height; }

int AVLflight::balanceFactor(AVLNode* node) {
    if (node == nullptr) return 0;
    return nodeHeight(node->left) - nodeHeight(node->right);
}

void AVLflight::updateHeight(AVLNode* node) {
    int l = nodeHeight(node->left);
    int r = nodeHeight(node->right);
    node->height = 1 + (l > r ? l : r);
}

AVLNode* AVLflight::rotateLeft(AVLNode* node) {
    AVLNode* pivot = node->right;
    node->right = pivot->left;
    pivot->left = node;
    updateHeight(node);
    updateHeight(pivot);
    return pivot;
}

AVLNode* AVLflight::rotateRight(AVLNode* node) {
    AVLNode* pivot = node->left;
    node->left = pivot->right;
    pivot->right = node;
    updateHeight(node);
    updateHeight(pivot);
    return pivot;
}

AVLNode* AVLflight::rotateLeftRight(AVLNode* node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

AVLNode* AVLflight::rotateRightLeft(AVLNode* node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

AVLNode* AVLflight::rebalance(AVLNode* node) {
    updateHeight(node);
    int balance = balanceFactor(node);
    if (balance > 1) {
        if (balanceFactor(node->left) >= 0) return rotateRight(node);
        return rotateLeftRight(node);
    }
    if (balance < -1) {
        if (balanceFactor(node->right) <= 0) return rotateLeft(node);
        return rotateRightLeft(node);
    }
    return node;
}

AVLNode* AVLflight::insertHelper(AVLNode* node, Flight* flight) {
    if (node == nullptr) {
        AVLNode* n = new AVLNode();
        n->flight = flight;
        n->left = nullptr;
        n->right = nullptr;
        n->height = 1;
        return n;
    }
    if (flight->callsign < node->flight->callsign) node->left = insertHelper(node->left, flight);
    else if (flight->callsign > node->flight->callsign) node->right = insertHelper(node->right, flight);
    else return node;
    return rebalance(node);
}

Flight* AVLflight::searchHelper(AVLNode* node, const string& callsign) {
    if (node == nullptr) return nullptr;
    if (callsign == node->flight->callsign) return node->flight;
    if (callsign < node->flight->callsign) return searchHelper(node->left, callsign);
    return searchHelper(node->right, callsign);
}

AVLNode* AVLflight::findMin(AVLNode* node) {
    while (node->left != nullptr) node = node->left;
    return node;
}

AVLNode* AVLflight::removeHelper(AVLNode* node, const string& callsign) {
    if (node == nullptr) return nullptr;
    if (callsign < node->flight->callsign) {
        node->left = removeHelper(node->left, callsign);
    } else if (callsign > node->flight->callsign) {
        node->right = removeHelper(node->right, callsign);
    } else {
        if (node->left == nullptr) {
            AVLNode* right = node->right;
            delete node;
            return right;
        }
        if (node->right == nullptr) {
            AVLNode* left = node->left;
            delete node;
            return left;
        }
        AVLNode* smallest = findMin(node->right);
        node->flight = smallest->flight;
        node->right = removeHelper(node->right, smallest->flight->callsign);
    }
    return rebalance(node);
}

void AVLflight::inorderHelper(AVLNode* node) {
    if (node == nullptr) return;
    inorderHelper(node->left);
    cout << "  " << node->flight->callsign << " - " << node->flight->aircraftType << "\n";
    inorderHelper(node->right);
}

void AVLflight::destroyHelper(AVLNode* node) {
    if (node == nullptr) return;
    destroyHelper(node->left);
    destroyHelper(node->right);
    delete node;
}

void AVLflight::insert(Flight* flight) { root = insertHelper(root, flight); }
Flight* AVLflight::search(const string& callsign) { return searchHelper(root, callsign); }
void AVLflight::remove(const string& callsign) { root = removeHelper(root, callsign); }
void AVLflight::inorderTraversal() { inorderHelper(root); }
int AVLflight::height() { return nodeHeight(root); }
void AVLflight::destroyTree() { destroyHelper(root); root = nullptr; }

void compareBSTandAVL() {
    BSTflight bst;
    AVLflight avl;
    Flight flights[15];
    cout << "Inserting 15 callsigns in alphabetical order into both trees...\n";
    cout << padRight("Inserted", 12) << padRight("BST height", 14) << "AVL height\n";
    for (int i = 0; i < 15; i++) {
        flights[i].callsign = "BB-" + intToString(101 + i);
        bst.insert(&flights[i]);
        avl.insert(&flights[i]);
        cout << padRight(flights[i].callsign, 12) << padRight(intToString(bst.height()), 14) << avl.height() << "\n";
    }
    cout << "Final heights -> BST: " << bst.height() << "   AVL: " << avl.height() << "\n";
}
