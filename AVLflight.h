#ifndef AVLFLIGHT_H
#define AVLFLIGHT_H
#include "Common.h"
#include "BSTflight.h"

struct AVLNode {
    Flight*  flight;
    AVLNode* left;
    AVLNode* right;
    int      height;
};

class AVLflight {
private:
    AVLNode* root;

    int      nodeHeight(AVLNode* node);
    int      balanceFactor(AVLNode* node);
    void     updateHeight(AVLNode* node);

    AVLNode* rotateLeft(AVLNode* node);
    AVLNode* rotateRight(AVLNode* node);
    AVLNode* rotateLeftRight(AVLNode* node);
    AVLNode* rotateRightLeft(AVLNode* node);
    AVLNode* rebalance(AVLNode* node);

    AVLNode* insertHelper(AVLNode* node, Flight* flight);
    Flight*  searchHelper(AVLNode* node, const string& callsign);
    AVLNode* removeHelper(AVLNode* node, const string& callsign);
    AVLNode* findMin(AVLNode* node);
    void     inorderHelper(AVLNode* node);
    void     destroyHelper(AVLNode* node);

public:
    AVLflight();
    ~AVLflight();

    void    insert(Flight* flight);
    Flight* search(const string& callsign);
    void    remove(const string& callsign);
    void    inorderTraversal();
    int     height();
    void    destroyTree();
};

// Menu option 22: builds 15 alphabetical callsigns in a fresh BST and AVL and prints both heights
void compareBSTandAVL();

#endif
